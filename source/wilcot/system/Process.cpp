/**
 * @author Ivan Udovin
 * @license MIT
 */

#include <wilcot/system/Process.h>

#ifdef WILCOT_SYSTEM_LINUX
#	include <wait.h>
#	include <unistd.h>
#	include <signal.h>
#endif

#include <stdexcept>
#include <cstdlib>

#define STACK_SIZE__ 1048576

namespace wilcot { namespace system {

Process::Process()
	: handle_(-1), program_(), arguments_()
	, workingDirectory_(".")
	, standardInputHandle_(STDIN_FILENO)
	, standardOutputHandle_(STDOUT_FILENO)
	, standardErrorHandle_(STDERR_FILENO)
	, exitCode_(0) {}

Process::~Process() {
	stop();
}

const Path& Process::getProgram() const {
	return program_;
}

Process& Process::setProgram(const Path& program) {
	program_ = program;

	return *this;
}

const std::vector<std::string>& Process::getArguments() const {
	return arguments_;
}

Process& Process::setArguments(const std::vector<std::string>& arguments) {
	arguments_ = arguments;

	return *this;
}

const Path& Process::getWorkingDirectory() const {
	return workingDirectory_;
}

Process& Process::setWorkingDirectory(const Path& workingDirectory) {
	workingDirectory_ = workingDirectory;

	return *this;
}

Process& Process::setStandardInput(IFileHandle& inputHandle) {
	standardInputHandle_ = inputHandle.getHandle();

	return *this;
}

Process& Process::setStandardOutput(IFileHandle& outputHandle) {
	standardOutputHandle_ = outputHandle.getHandle();

	return *this;
}

Process& Process::setStandardError(IFileHandle& outputHandle) {
	standardErrorHandle_ = outputHandle.getHandle();

	return *this;
}

int Process::getExitCode() const {
	return exitCode_;
}

Process& Process::start() {
#ifdef WILCOT_SYSTEM_LINUX
	// Child process needs separate stack
	char *stack = new char[STACK_SIZE__];

	// Trying to clone current process
	handle_ = clone(
		Process::entryPoint_,
		static_cast<void *>(stack + STACK_SIZE__),
		SIGCHLD,
		static_cast<void *>(this));

	delete[] stack;
#endif

	// Failed to clone current process
	if (handle_ == -1) {
		throw std::runtime_error("Unable to start process.");
	}

	return *this;
}

Process& Process::stop() {
#ifdef WILCOT_SYSTEM_LINUX
	kill(handle_, SIGKILL);
#endif

	return *this;
}

Process& Process::wait() {
#ifdef WILCOT_SYSTEM_LINUX
	int status;

	waitpid(handle_, &status, 0);
	exitCode_ = WEXITSTATUS(status);
#endif

	return *this;
}

int Process::entryPoint_(void* process) {
	return static_cast<Process*>(process)->entryPoint_();
}

int Process::entryPoint_() {
#ifdef WILCOT_SYSTEM_LINUX
	dup2(standardInputHandle_, STDIN_FILENO);
	dup2(standardOutputHandle_, STDOUT_FILENO);
	dup2(standardErrorHandle_, STDERR_FILENO);

	if (chdir(workingDirectory_) != 0) {
		return EXIT_FAILURE;
	}

	// Convert string arguments to raw char arguments
	std::vector<char*> arguments;
	std::vector<std::string>::const_iterator it;

	for (it = arguments_.begin(); it != arguments_.end(); ++it) {
		arguments.push_back(const_cast<char*>(it->c_str()));
	}

	arguments.push_back(NULL);

	execv(program_, arguments.data());
#endif

	// Return failure code when execution failed
	return EXIT_FAILURE;
}

}}
