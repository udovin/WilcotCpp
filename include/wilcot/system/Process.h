/*!
 * \author Ivan Udovin
 * \license http://www.spdx.org/licenses/MIT
 */

#ifndef HEADER_wilcot_system_Process
#define HEADER_wilcot_system_Process

#include <wilcot/Object.h>

#include <wilcot/system/detect.h>
#include <wilcot/system/Path.h>
#include <wilcot/system/FileHandle.h>

#include <vector>

namespace wilcot { namespace system {

/*!
 * Process class
 */
class Process : public Object
{
public:
	/*!
	 * A constructor
	 */
	Process();

	/*!
	 * A destructor
	 */
	~Process();

	/*!
	 * Get path to executable
	 *
	 * \return
	 */
	const Path& getProgram() const;

	/*!
	 * Set path to executable
	 *
	 * \param program
	 */
	void setProgram(const Path& program);

	/*!
	 * Get execution arguments
	 *
	 * \return
	 */
	const std::vector<std::string>& getArguments() const;

	/*!
	 * Set execution arguments
	 *
	 * \param arguments
	 */
	void setArguments(const std::vector<std::string>& arguments);

	/*!
	 * Get working directory
	 *
	 * \return
	 */
	const Path& getWorkingDirectory() const;

	/*!
	 * Set working directory
	 *
	 * \param workingDirectory
	 */
	void setWorkingDirectory(const Path& workingDirectory);

	/*!
	 * Set standard input
	 *
	 * \param inputHandle
	 */
	void setStandardInput(FileHandle& inputHandle);

	/*!
	 * Set standard output
	 *
	 * \param outputHandle
	 */
	void setStandardOutput(FileHandle& outputHandle);

	/*!
	 * Set standard error
	 *
	 * \param outputHandle
	 */
	void setStandardError(FileHandle& outputHandle);

	/*!
	 * Get exit code
	 *
	 * \return
	 */
	int getExitCode() const;

	/*!
	 * Start process
	 */
	void start();

	/*!
	 * Stop process
	 */
	void stop();

	/*!
	 * Wait process for finished
	 */
	void wait();

private:
	int handle_;

	Path program_;

	std::vector<std::string> arguments_;

	Path workingDirectory_;

	int standardInputHandle_;

	int standardOutputHandle_;

	int standardErrorHandle_;

	int exitCode_;

	/*!
	 * An entry point for child process
	 *
	 * \param process
	 * \return
	 */
	static int entryPoint_(void* process);

	/*!
	 * An entry point for child process
	 *
	 * \return
	 */
	int entryPoint_();
};

}}

#endif // HEADER_wilcot_system_Process
