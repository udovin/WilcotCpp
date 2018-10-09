/**
 * @author Ivan Udovin
 * @license MIT
 */

#include <wilcot/guard/Container.h>

#include <wilcot/os/Path.h>
#include <wilcot/io/FileStream.h>

#ifdef WILCOT_OS_LINUX
#	include <unistd.h>
#	include <signal.h>
#	include <fcntl.h>
#	include <sys/wait.h>
#	include <sys/mount.h>
#	include <sys/stat.h>
#	include <sys/syscall.h>
#	include <cstring>
#endif

#include <stdexcept>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <ctime>

namespace wilcot { namespace guard {

#ifdef WILCOT_OS_LINUX
static const std::size_t STACK_SIZE__ = 1048576;

static void createDirectory__(const os::Path& path) {
	mkdir(path, 0777);
}

static void createFile__(const os::Path& path) {
	close(open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644));
}

static std::string getRandomString__(std::size_t length) {
	std::stringstream ss;

	srand(time(NULL));
	for (std::size_t i = 0; i < length; i++) {
		ss << "0123456789abcdef"[rand() % 16];
	}

	return ss.str();
}

int pivotRoot__(const char* oldRoot, const char* newRoot) {
	return syscall(SYS_pivot_root, oldRoot, newRoot);
}

#endif

Container::Container()
	: handle_(-1), program_(), arguments_()
	, workingDirectory_("/")
	, standardInputHandle_(STDIN_FILENO)
	, standardOutputHandle_(STDOUT_FILENO)
	, standardErrorHandle_(STDERR_FILENO)
	, bindMounts_()
	, exitCode_(0) {}

Container::~Container() {
	stop();
}

const os::Path& Container::getProgram() const {
	return program_;
}

Container& Container::setProgram(const os::Path& program) {
	program_ = program;

	return *this;
}

const std::vector<std::string>& Container::getArguments() const {
	return arguments_;
}

Container& Container::setArguments(
	const std::vector<std::string>& arguments) {
	arguments_ = arguments;

	return *this;
}

const os::Path& Container::getWorkingDirectory() const {
	return workingDirectory_;
}

Container& Container::setWorkingDirectory(const os::Path& directory) {
	workingDirectory_ = directory;

	return *this;
}

Container& Container::setStandardInput(os::IFileHandle& inputHandle) {
	standardInputHandle_ = inputHandle.getHandle();

	return *this;
}

Container& Container::setStandardOutput(os::IFileHandle& outputHandle) {
	standardOutputHandle_ = outputHandle.getHandle();

	return *this;
}

Container& Container::setStandardError(os::IFileHandle& outputHandle) {
	standardErrorHandle_ = outputHandle.getHandle();

	return *this;
}

Container& Container::addBindMount(
	const os::Path& source, const os::Path& target, bool readOnly) {
	bindMounts_.push_back(
		std::make_pair(std::make_pair(source, target), readOnly));

	return *this;
}

int Container::getExitCode() const {
	return exitCode_;
}

Container& Container::start() {
#ifdef WILCOT_OS_LINUX
	if (pipe(pipe_) == -1) {
		throw std::runtime_error("Unable to create pipe.");
	}

	// Child process needs separate stack.
	char *stack = new char[STACK_SIZE__];

	// Trying to clone current container.
	handle_ = clone(
		Container::entryPoint_,
		static_cast<void *>(stack + STACK_SIZE__),
		CLONE_NEWUSER | CLONE_NEWNS | CLONE_NEWNET | CLONE_NEWUTS
			| CLONE_NEWIPC | CLONE_NEWPID | SIGCHLD,
		static_cast<void *>(this));

	delete[] stack;

	close(pipe_[0]);
#endif

	// Failed to clone current container.
	if (handle_ == -1) {
#ifdef WILCOT_OS_LINUX
		close(pipe_[1]);
#endif

		throw std::runtime_error("Unable to start container.");
	}

#ifdef WILCOT_OS_LINUX
	prepareUserNamespace_();
	setupNamespaceHandles_();
#endif

	return *this;
}

Container& Container::stop() {
#ifdef WILCOT_OS_LINUX
	kill(handle_, SIGKILL);
#endif

	return *this;
}

Container& Container::wait() {
#ifdef WILCOT_OS_LINUX
	int status;

	waitpid(handle_, &status, 0);
	exitCode_ = WEXITSTATUS(status);
#endif

	return *this;
}

int Container::entryPoint_(void* container) {
	return static_cast<Container*>(container)->entryPoint_();
}

int Container::entryPoint_() {
#ifdef WILCOT_OS_LINUX
	close(pipe_[1]);
#endif

	try {
		setupUserNamespace_();
		// Now we should initialize mount namespace.
		setupMountNamespace_();
		setupNetworkNamespace_();
		setupUtsNamespace_();
		setupIpcNamespace_();

		dup2(standardInputHandle_, STDIN_FILENO);
		dup2(standardOutputHandle_, STDOUT_FILENO);
		dup2(standardErrorHandle_, STDERR_FILENO);

		// Convert string arguments to raw char arguments
		char** arguments = new char*[arguments_.size() + 1];

		for (std::size_t i = 0; i < arguments_.size(); i++) {
			arguments[i] = const_cast<char*>(arguments_[i].c_str());
		}

		arguments[arguments_.size()] = NULL;

		execv(program_, arguments);

		delete [] arguments;

		return EXIT_FAILURE;
	} catch (std::exception& exception) {
		return EXIT_FAILURE;
	}
}

void Container::prepareUserNamespace_() {
#ifdef WILCOT_OS_LINUX
	int fd;
	char path[40], data[256];

	// Our process user has overflow UID and the same GID.
	// We can not directly change UID to 0 before making mapping.
	sprintf(path, "/proc/%d/uid_map", handle_);
	sprintf(data, "%d %d %d\n", 0, getuid(), 1);

	fd = open(path, O_WRONLY | O_TRUNC);
	write(fd, data, strlen(data));
	close(fd);

	// Before making groups mapping we should write "deny" into
	// "/proc/$PID/setgroups".
	sprintf(path, "/proc/%d/setgroups", handle_);
	sprintf(data, "deny\n");

	fd = open(path, O_WRONLY | O_TRUNC);
	write(fd, data, strlen(data));
	close(fd);

	// Now we can easily make mapping for groups.
	sprintf(path, "/proc/%d/gid_map", handle_);
	sprintf(data, "%d %d %d\n", 0, getgid(), 1);

	fd = open(path, O_WRONLY | O_TRUNC);
	write(fd, data, strlen(data));
	close(fd);

	// Now we should unlock child process.
	close(pipe_[1]);
#endif
}

#ifdef WILCOT_OS_LINUX
static const char* NAMESPACE_FILES__[5] = {
	"/proc/%d/ns/user",
	"/proc/%d/ns/mnt",
	"/proc/%d/ns/net",
	"/proc/%d/ns/utc",
	"/proc/%d/ns/ipc"
};
#endif

void Container::setupNamespaceHandles_() {
#ifdef WILCOT_OS_LINUX
	char path[40];

	for (int i = 0; i < 5; i++) {
		sprintf(path, NAMESPACE_FILES__[i], handle_);
		namespaceHandles_[i] = open(path, O_RDONLY);
	}
#endif
}

void Container::setupUserNamespace_() {
#ifdef WILCOT_OS_LINUX
	char c;

	// We should wait for setup of user namespace from parent.
	if (read(pipe_[0], &c, 1) != 0) {
		throw std::runtime_error("Failed to wait pipe close.");
	}
#endif
}

void Container::setupMountNamespace_() {
#ifdef WILCOT_OS_LINUX
	// First of all make all changes are private for current root.
	if (mount("/", "/", NULL, MS_REC | MS_PRIVATE, NULL) == -1) {
		throw std::runtime_error("Failed to remount root as private");
	}

	os::Path newRoot = "/tmp/container";
	os::Path oldRoot = "/.OldRoot";

	createDirectory__(newRoot);
	createDirectory__(newRoot + oldRoot);

	std::vector<BindMount_>::const_iterator it;

	// Mount all rw and ro mounts of files and directories.
	for (it = bindMounts_.begin(); it != bindMounts_.end(); it++) {
		os::Path source = it->first.first;
		os::Path target = newRoot / it->first.second;
		if (mount(source, target, NULL, MS_BIND | MS_PRIVATE, NULL) == -1) {
			throw std::runtime_error("Unable to mount directory");
		}
	}

	// Remount read-only mounts.
	for (it = bindMounts_.begin(); it != bindMounts_.end(); it++) {
		if (it->second) {
			os::Path target = newRoot / it->first.second;
			if (mount(target, target, NULL, MS_REMOUNT | MS_RDONLY, NULL) == -1) {
				throw std::runtime_error("Unable to mount directory");
			}
		}
	}

	if (mount(newRoot, newRoot, NULL, MS_BIND | MS_PRIVATE, NULL) == -1) {
		throw std::runtime_error("Failed to remount new root");
	}

	if (pivotRoot__(newRoot, newRoot + oldRoot) != 0) {
		throw std::runtime_error("Failed to pivot root");
	}

	if (umount2(oldRoot, MNT_DETACH)) {
		throw std::runtime_error("Failed to unmount old root");
	}

	rmdir(oldRoot);

	if (chdir(workingDirectory_) != 0) {
		throw std::runtime_error("Failed to change working directory");
	}
#endif
}

void Container::setupNetworkNamespace_() {}

void Container::setupUtsNamespace_() {
#ifdef WILCOT_OS_LINUX
	std::string hostname = getRandomString__(16);
	if (sethostname(hostname.c_str(), hostname.size()) != 0) {
		throw std::runtime_error("Unable to set hostname.");
	}
#endif
}

void Container::setupIpcNamespace_() {}

}}
