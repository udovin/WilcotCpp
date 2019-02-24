/**
 * @author Ivan Udovin
 * @license MIT
 */

#ifndef HEADER_wilcot_os_Process
#define HEADER_wilcot_os_Process

#include <wilcot/os/Path.h>
#include <wilcot/os/IFileHandle.h>
#include <vector>

namespace wilcot { namespace os {

/**
 * Class Process
 *
 * @since 0.0.1
 */
class Process : public Object {
public:
	/**
	 * Process constructor
	 *
	 * @since 0.0.1
	 */
	Process();

	/**
	 * Process destructor
	 *
	 * @since 0.0.1
	 */
	~Process();

	/**
	 * Get path to executable
	 *
	 * @return
	 *
	 * @since 0.0.1
	 */
	const Path& getProgram() const;

	/**
	 * Set path to executable
	 *
	 * @param program
	 * @return
	 *
	 * @since 0.0.1
	 */
	Process& setProgram(const Path& program);

	/**
	 * Get execution arguments
	 *
	 * @return
	 *
	 * @since 0.0.1
	 */
	const std::vector<std::string>& getArguments() const;

	/**
	 * Set execution arguments
	 *
	 * @param arguments
	 * @return
	 *
	 * @since 0.0.1
	 */
	Process& setArguments(const std::vector<std::string>& arguments);

	/**
	 * Get working directory
	 *
	 * @return
	 *
	 * @since 0.0.1
	 */
	const Path& getWorkingDirectory() const;

	/**
	 * Set working directory
	 *
	 * @param directory
	 * @return
	 *
	 * @since 0.0.1
	 */
	Process& setWorkingDirectory(const Path& directory);

	/**
	 * Get exit code
	 *
	 * @return
	 *
	 * @since 0.0.1
	 */
	int getExitCode() const;

	/**
	 * Set standard input
	 *
	 * @param inputHandle
	 * @return
	 *
	 * @since 0.0.1
	 */
	Process& setStandardInput(IFileHandle& inputHandle);

	/**
	 * Set standard output
	 *
	 * @param outputHandle
	 * @return
	 *
	 * @since 0.0.1
	 */
	Process& setStandardOutput(IFileHandle& outputHandle);

	/**
	 * Set standard error
	 *
	 * @param outputHandle
	 * @return
	 *
	 * @since 0.0.1
	 */
	Process& setStandardError(IFileHandle& outputHandle);

	/**
	 * Start process
	 *
	 * @return
	 *
	 * @since 0.0.1
	 */
	Process& start();

	/**
	 * Stop process
	 *
	 * @return
	 *
	 * @since 0.0.1
	 */
	Process& stop();

	/**
	 * Wait process for finished
	 *
	 * @return
	 *
	 * @since 0.0.1
	 */
	Process& wait();

private:
	/**
	 * @since 0.0.1
	 */
	int handle_;

	/**
	 * @since 0.0.1
	 */
	Path program_;

	/**
	 * @since 0.0.1
	 */
	std::vector<std::string> arguments_;

	/**
	 * @since 0.0.1
	 */
	Path workingDirectory_;

	/**
	 * @since 0.0.1
	 */
	int exitCode_;

	/**
	 * @since 0.0.1
	 */
	int standardInputHandle_;

	/**
	 * @since 0.0.1
	 */
	int standardOutputHandle_;

	/**
	 * @since 0.0.1
	 */
	int standardErrorHandle_;

	/**
	 * An entry point for child process
	 *
	 * @param process
	 * @return
	 *
	 * @since 0.0.1
	 */
	static int entryPoint_(void* process);

	/**
	 * An entry point for child process
	 *
	 * @return
	 *
	 * @since 0.0.1
	 */
	int entryPoint_();
};

}}

#endif // HEADER_wilcot_os_Process
