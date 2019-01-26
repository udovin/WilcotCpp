/**
 * @author Ivan Udovin
 * @license MIT
 */

#include <wilcot/base.h>

#ifdef WILCOT_OS_LINUX
#include <wilcot/lxc/Container.h>
#include <wilcot/os/files.h>
#include <wilcot/io/FileStream.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <cstring>
#include <stdexcept>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <ctime>

namespace wilcot { namespace lxc {

static const size_t STACK_SIZE_ = 1048576;

static std::string getRandomString__(size_t length) {
	std::stringstream ss;

	srand(static_cast<unsigned int>(time(NULL)));
	for (size_t i = 0; i < length; i++) {
		ss << "0123456789abcdef"[rand() % 16];
	}

	return ss.str();
}

long pivotRoot__(const char* oldRoot, const char* newRoot) {
	return syscall(SYS_pivot_root, oldRoot, newRoot);
}

static const size_t NAMESPACE_FILES_SIZE__ = 6;

static const char* NAMESPACE_FILES__[NAMESPACE_FILES_SIZE__] = {
	"/proc/%d/ns/user",
	"/proc/%d/ns/mnt",
	"/proc/%d/ns/net",
	"/proc/%d/ns/uts",
	"/proc/%d/ns/ipc",
	"/proc/%d/ns/cgroup",
};

Container::Container(const os::Path& path)
	: path_(path), handle_(-1), program_(), arguments_()
	, workingDirectory_("/"), exitCode_()
	, standardInputHandle_(STDIN_FILENO)
	, standardOutputHandle_(STDOUT_FILENO)
	, standardErrorHandle_(STDERR_FILENO)
	, bindMounts_(), pipe_()
	, namespaceHandles_(NAMESPACE_FILES_SIZE__, -1) {}

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

int Container::getExitCode() const {
	return exitCode_;
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

Container& Container::start() {
	if (pipe(pipe_) == -1) {
		throw std::runtime_error("Unable to create pipe.");
	}
	// Child process needs separate stack.
	char *stack = new char[STACK_SIZE_];
	// Trying to clone current container.
	handle_ = clone(
		Container::entryPoint_,
		static_cast<void *>(stack + STACK_SIZE_),
		CLONE_NEWUSER | CLONE_NEWNS | CLONE_NEWNET | CLONE_NEWUTS
			| CLONE_NEWIPC | CLONE_NEWPID | CLONE_NEWCGROUP | SIGCHLD,
		static_cast<void *>(this));
	delete[] stack;
	close(pipe_[0]);
	// Failed to clone current container.
	if (handle_ == -1) {
		close(pipe_[1]);
		throw std::runtime_error("Unable to start container.");
	}
	prepareUserNamespace_();
	setupNamespaceHandles_();
	return *this;
}

Container& Container::stop() {
	kill(handle_, SIGKILL);
	cleanNamespaceHandles_();
	handle_ = -1;
	return *this;
}

Container& Container::wait() {
	int status;
	waitpid(handle_, &status, 0);
	exitCode_ = WEXITSTATUS(status);
	return *this;
}

int Container::entryPoint_(void* container) {
	return static_cast<Container*>(container)->entryPoint_();
}

int Container::entryPoint_() {
	close(pipe_[1]);
	try {
		setupUserNamespace_();
		// Now we should initialize mount namespace.
		setupMountNamespace_();
		setupNetworkNamespace_();
		setupUtsNamespace_();
		setupIpcNamespace_();
		setupCgroupNamespace_();
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
		delete[] arguments;
		return EXIT_FAILURE;
	} catch (const std::exception& exception) {
		return EXIT_FAILURE;
	}
}

void Container::prepareUserNamespace_() {
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
}

void Container::setupNamespaceHandles_() {
	char path[40];
	for (size_t i = 0; i < NAMESPACE_FILES_SIZE__; i++) {
		sprintf(path, NAMESPACE_FILES__[i], handle_);
		namespaceHandles_[i] = open(path, O_RDONLY);
		if (namespaceHandles_[i] == -1) {
			throw std::runtime_error(
				"Unable to open namespace descriptor"
			);
		}
	}
}

void Container::cleanNamespaceHandles_() {
	for (size_t i = 0; i < NAMESPACE_FILES_SIZE__; i++) {
		if (namespaceHandles_[i] != -1) {
			::close(namespaceHandles_[i]);
			namespaceHandles_[i] = -1;
		}
	}
}

void Container::setupUserNamespace_() {
	char c;
	// We should wait for setup of user namespace from parent.
	if (read(pipe_[0], &c, 1) != 0) {
		throw std::runtime_error("Failed to wait pipe close");
	}
}

void Container::setupMountNamespace_() {
	// First of all make all changes are private for current root.
	if (mount("/", "/", NULL, MS_REC | MS_PRIVATE, NULL) == -1) {
		throw std::runtime_error("Failed to remount root as private");
	}
	os::Path newRoot = path_ / "rootfs";
	os::Path oldRoot = "/.oldroot";
	os::createDirectories(newRoot + oldRoot);
	if (mount(newRoot, newRoot, NULL, MS_BIND | MS_PRIVATE, NULL) == -1) {
		throw std::runtime_error("Failed to remount new root");
	}
	std::vector<BindMount_>::const_iterator it;
	// Mount all rw and ro mounts of files and directories.
	for (it = bindMounts_.begin(); it != bindMounts_.end(); it++) {
		os::Path source = it->first.first;
		os::Path target = newRoot + it->first.second;
		if (os::isFile(source)) {
			os::createDirectories(target.getParent());
			os::createFile(target);
		} else if (os::isDirectory(source)) {
			os::createDirectories(target);
		}
		long flags = MS_BIND | MS_PRIVATE;
		if (it->second) {
			flags = flags | MS_RDONLY;
		}
		if (mount(source, target, NULL, flags, NULL) == -1) {
			throw std::runtime_error("Unable to create bind mount");
		}
	}
	if (pivotRoot__(newRoot, newRoot + oldRoot) != 0) {
		throw std::runtime_error("Failed to pivot root");
	}
	if (umount2(oldRoot, MNT_DETACH)) {
		throw std::runtime_error("Failed to unmount old root");
	}
	os::removeDirectory(oldRoot);
	os::Path lxcPath("/.lxc");
	os::createDirectory(lxcPath);
	// Prepare 'proc' filesystem
	os::Path procPath(lxcPath / "proc");
	os::createDirectory(procPath);
	if (mount(
		procPath, procPath, "proc",
		MS_BIND | MS_PRIVATE, NULL) == -1) {
		throw std::runtime_error(
			"Failed to mount 'proc' filesystem"
		);
	}
	// Prepare 'cgroup' filesystem
	os::Path cgroupPath(lxcPath / "cgroup");
	os::createDirectory(cgroupPath);
	if (mount(
		cgroupPath, cgroupPath, "cgroup",
		MS_BIND | MS_PRIVATE, NULL) == -1) {
		throw std::runtime_error(
			"Failed to mount 'cgroup' filesystem"
		);
	}
	// Change working directory
	if (chdir(workingDirectory_) != 0) {
		throw std::runtime_error(
			"Failed to change working directory"
		);
	}
}

void Container::setupNetworkNamespace_() {}

void Container::setupUtsNamespace_() {
	std::string hostname = getRandomString__(16);
	if (sethostname(hostname.c_str(), hostname.size()) != 0) {
		throw std::runtime_error("Unable to set hostname");
	}
	if (setdomainname(hostname.c_str(), hostname.size()) != 0) {
		throw std::runtime_error("Unable to set domainname");
	}
}

void Container::setupIpcNamespace_() {}

void Container::setupCgroupNamespace_() {}

}}
#endif
