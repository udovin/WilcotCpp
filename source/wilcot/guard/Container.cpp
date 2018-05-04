/*!
 * \author Ivan Udovin
 * \license http://www.spdx.org/licenses/MIT
 */

#include <wilcot/guard/Container.h>

#include <wilcot/system/Path.h>
#include <wilcot/io/FileStream.h>

#ifdef WILCOT_SYSTEM_LINUX
#	include <wait.h>
#	include <unistd.h>
#	include <signal.h>
#	include <fcntl.h>
#endif

#include <stdexcept>
#include <cstdlib>

#define STACK_SIZE__ 1048576

namespace wilcot { namespace guard {

static void createDirectory__(const system::Path& path)
{
	mkdir(path, 0777);
}

static void createFile__(const system::Path& path)
{
	close(open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644));
}

Container::Container()
	: handle_(-1)
{}

Container::~Container()
{}

void Container::start()
{
#ifdef WILCOT_SYSTEM_LINUX
	// Child process needs separate stack
	char *stack = new char[STACK_SIZE__];

	// Trying to clone current container
	handle_ = clone(
		Container::entryPoint_,
		static_cast<void *>(stack + STACK_SIZE__),
		CLONE_NEWUSER | CLONE_NEWNS | CLONE_NEWNET | CLONE_NEWUTS
			CLONE_NEWIPC | CLONE_NEWCGROUP | CLONE_NEWPID | SIGCHLD,
		static_cast<void *>(this)
	);

	delete[] stack;
#endif

	// Failed to clone current container
	if (handle_ == -1)
	{
		throw std::runtime_error("Unable to start container.");
	}
}

void Container::stop()
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

	exitCode_ = WEXITSTATUS(status);
#endif
}

int Container::entryPoint_(void* container)
{
	return static_cast<Container*>(container)->entryPoint_();
}

int Container::entryPoint_()
{
	// First of all we should initialize user namespace.
	// Without initializing it we can not correctly
	// setup other namespaces.
	setupUserNamespace_();

	// Now we should initialize mount namespace
	setupMountNamespace_();

	setupNetworkNamespace_();

	setupUtsNamespace_();

	setupIpcNamespace_();

	setupCgroupNamespace_();
}

/*!
 * TODO: Remove hardcoded user and group IDs
 */
void Container::setupUserNamespace_()
{
#ifdef WILCOT_SYSTEM_LINUX
	int fd;
	char path[26];

	// Our user has UID = [overflow UID] and the same GID.
	// We can not directly change UID to 0 before making mapping.
	sprintf(path, "/proc/%d/uid_map", getpid());
	fd = open(path, , 0644);
	write(fd, "0 1000 1", 8);
	close(fd);

	// Before making groups mapping we should write "deny" into
	// "/proc/$$/setgroups".
	sprintf(path, "/proc/%d/setgroups", getpid());
	fd = open(path, , 0644);
	write(fd, "deny", 4);
	close(fd);

	// Now we can easily make mapping for groups.
	sprintf(path, "/proc/%d/gid_map", getpid());
	fd = open(path, , 0644);
	write(fd, "0 1000 1", 8);
	close(fd);
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

void Container::setupUtsNamespace_()
{
#ifdef WILCOT_SYSTEM_LINUX
#endif
}

void Container::setupIpcNamespace_()
{
#ifdef WILCOT_SYSTEM_LINUX
#endif
}

}}
