/**
 * @author Ivan Udovin
 * @license MIT
 */

#ifndef HEADER_wilcot_lxc_Container
#define HEADER_wilcot_lxc_Container

#include <wilcot/os/Path.h>
#include <wilcot/os/IFileHandle.h>
#include <string>
#include <vector>

namespace wilcot { namespace lxc {

/**
 * Class Container
 *
 * @since 0.0.1
 */
class Container : public Object {
private:
	typedef std::pair<os::Path, os::Path> PathPair_;
	typedef std::pair<PathPair_, bool> BindMount_;

public:
	/**
	 * Container constructor
	 *
	 * @param path
	 *
	 * @since 0.0.1
	 */
	Container(const os::Path& path);

	/**
	 * Container destructor
	 *
	 * @since 0.0.1
	 */
	~Container();

	/**
	 * Get path to executable
	 *
	 * @return
	 *
	 * @since 0.0.1
	 */
	const os::Path& getProgram() const;

	/**
	 * Set path to executable
	 *
	 * @param program
	 * @return
	 *
	 * @since 0.0.1
	 */
	Container& setProgram(const os::Path& program);

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
	Container& setArguments(const std::vector<std::string>& arguments);

	/**
	 * Get working directory
	 *
	 * @return
	 *
	 * @since 0.0.1
	 */
	const os::Path& getWorkingDirectory() const;

	/**
	 * Set working directory
	 *
	 * @param directory
	 * @return
	 *
	 * @since 0.0.1
	 */
	Container& setWorkingDirectory(const os::Path& directory);

	/**
	 * Set standard input
	 *
	 * @param inputHandle
	 * @return
	 *
	 * @since 0.0.1
	 */
	Container& setStandardInput(os::IFileHandle& inputHandle);

	/**
	 * Set standard output
	 *
	 * @param outputHandle
	 * @return
	 *
	 * @since 0.0.1
	 */
	Container& setStandardOutput(os::IFileHandle& outputHandle);

	/**
	 * Set standard error
	 *
	 * @param outputHandle
	 * @return
	 *
	 * @since 0.0.1
	 */
	Container& setStandardError(os::IFileHandle& outputHandle);

	/**
	 * Add bind mount
	 *
	 * @param source
	 * @param target
	 * @return
	 *
	 * @since 0.0.1
	 */
	Container& addBindMount(
		const os::Path& source, const os::Path& target,
		bool readOnly = false);

	/**
	 * Get exit code
	 *
	 * @return
	 *
	 * @since 0.0.1
	 */
	int getExitCode() const;

	/**
	 * Start container
	 *
	 * @since 0.0.1
	 */
	Container& start();

	/**
	 * Stop container
	 *
	 * @since 0.0.1
	 */
	Container& stop();

	/**
	 * Wait container for finished
	 *
	 * @since 0.0.1
	 */
	Container& wait();

private:
	/**
	 * @since 0.0.1
	 */
	os::Path path_;

	/**
	 * @since 0.0.1
	 */
	int handle_;

	/**
	 * @since 0.0.1
	 */
	os::Path program_;

	/**
	 * @since 0.0.1
	 */
	std::vector<std::string> arguments_;

	/**
	 * @since 0.0.1
	 */
	os::Path workingDirectory_;

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
	 * @since 0.0.1
	 */
	std::vector<BindMount_> bindMounts_;

	/**
	 * @since 0.0.1
	 */
	int exitCode_;

	/**
	 * @since 0.0.1
	 */
	int pipe_[2];

	/**
	 * @since 0.0.1
	 */
	int namespaceHandles_[6];

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

	/**
	 * Make all mapping for users and groups
	 *
	 * @since 0.0.1
	 */
	void prepareUserNamespace_();

	/**
	 * Open descriptors for namespaces
	 *
	 * @since 0.0.1
	 */
	void setupNamespaceHandles_();

	/**
	 * Setup user namespace
	 *
	 * @since 0.0.1
	 */
	void setupUserNamespace_();

	/**
	 * Setup mount namespace
	 *
	 * @since 0.0.1
	 */
	void setupMountNamespace_();

	/**
	 * Setup network namespace
	 *
	 * @since 0.0.1
	 */
	void setupNetworkNamespace_();

	/**
	 * Setup UTS namespace
	 *
	 * @since 0.0.1
	 */
	void setupUtsNamespace_();

	/**
	 * Setup IPC namespace
	 *
	 * @since 0.0.1
	 */
	void setupIpcNamespace_();

	/**
	 * Setup cgroup namespace
	 *
	 * @since 0.1.0
	 */
	void setupCgroupNamespace_();
};

}}

#endif // HEADER_wilcot_lxc_Container
