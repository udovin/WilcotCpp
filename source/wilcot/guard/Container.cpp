/**
 * @author Ivan Udovin
 * @license MIT
 */

#include <wilcot/guard/Container.h>

#include <wilcot/system/Path.h>
#include <wilcot/io/FileStream.h>

#ifdef WILCOT_SYSTEM_LINUX
#	include <wait.h>
#	include <unistd.h>
#	include <signal.h>
#	include <fcntl.h>
#	include <sys/mount.h>
#	include <sys/stat.h>
#endif

#include <stdexcept>
#include <sstream>
#include <cstdlib>
#include <cstdio>

#define STACK_SIZE__ 1048576

namespace wilcot { namespace guard {

#ifdef WILCOT_SYSTEM_LINUX
static void createDirectory__(const system::Path& path)
{
	mkdir(path, 0777);
}

static void createFile__(const system::Path& path)
{
	close(open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644));
}
#endif

Container::Container()
	: handle_(-1)
{}

Container::~Container()
{}

void Container::start()
{
#ifdef WILCOT_SYSTEM_LINUX
	if (pipe(pipe_) == -1)
	{
		throw std::runtime_error("Unable to create pipe.");
	}

	// Child process needs separate stack
	char *stack = new char[STACK_SIZE__];

	// Trying to clone current container
	handle_ = clone(
		Container::entryPoint_,
		static_cast<void *>(stack + STACK_SIZE__),
		CLONE_NEWUSER | CLONE_NEWNS | CLONE_NEWNET | CLONE_NEWUTS |
			CLONE_NEWIPC | CLONE_NEWCGROUP | CLONE_NEWPID | SIGCHLD,
		static_cast<void *>(this)
	);

	delete[] stack;
#endif

	close(pipe_[0]);

	// Failed to clone current container.
	if (handle_ == -1)
	{
		close(pipe_[1]);

		throw std::runtime_error("Unable to start container.");
	}

#ifdef WILCOT_SYSTEM_LINUX
	setupUserNamespace_();
#endif
}

/*void Container::stop()
{
#ifdef WILCOT_SYSTEM_LINUX
	kill(handle_, SIGKILL);
#endif
}

void Container::wait()
{
#ifdef WILCOT_SYSTEM_LINUX
	int status;

	waitpid(handle_, &status, 0);
#endif
}*/

int Container::entryPoint_(void* container)
{
	return static_cast<Container*>(container)->entryPoint_();
}

int Container::entryPoint_()
{
#ifdef WILCOT_SYSTEM_LINUX
	close(pipe_[1]);
#endif

	try
	{
		setupUserNamespaceFromChild_();

		// Now we should initialize mount namespace.
		setupMountNamespace_();

		setupNetworkNamespace_();

		setupUtsNamespace_();

		setupIpcNamespace_();

		setupCgroupNamespace_();
	}
	catch (std::exception& exception)
	{
		return EXIT_FAILURE;
	}
}

void Container::setupUserNamespaceFromParent_()
{
#ifdef WILCOT_SYSTEM_LINUX
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

void Container::setupUserNamespaceFromChild_()
{
#ifdef WILCOT_SYSTEM_LINUX
	char c;

	// We should wait for setup of user namespace from parent.
	if (read(pipe_[0], &c, 1) != 0)
	{
		throw std::runtime_error("Failed to wait pipe close.");
    }
#endif
}

void Container::setupMountNamespace_()
{
#ifdef WILCOT_SYSTEM_LINUX
	// First of all make all changes are private for current root.
	if (mount("/", "/", NULL, MS_REC | MS_PRIVATE, NULL) == -1)
	{
		exit(EXIT_FAILURE);
	}

	// Mount proc directory if we create new PID namespace.

	// Mount all rw and ro mounts of files and directories.

	// Remount read-only mounts.
#endif
}

void Container::setupNetworkNamespace_()
{
#ifdef WILCOT_SYSTEM_LINUX
#endif
}

static std::string getRandomString__(size_t length)
{
	std::stringstream ss;
	std::random_device rd;
	std::mt19937 mt(rd);
	std::uniform_int_distribution<int> gen;

	for (int i = 0; i < length; i++)
	{
		ss << "0123456789abcdef"[gen(mt) % 16];
	}

	return ss.str();
}

void Container::setupUtsNamespace_()
{
#ifdef WILCOT_SYSTEM_LINUX
	std::string hostname = getRandomString__(16);

	if (sethostname(hostname.c_str(), hostname.size()) != 0)
	{
		throw std::runtime_error("Unable to set hostname.");
	}
#endif
}

void Container::setupIpcNamespace_()
{
#ifdef WILCOT_SYSTEM_LINUX
#endif
}

}}
