/**
 * @author Ivan Udovin
 * @license MIT
 */

#ifndef HEADER_wilcot_guard_Container
#define HEADER_wilcot_guard_Container

#include <wilcot/Object.h>

#include <wilcot/system/detect.h>
//#include <wilcot/guard/Process.h>

namespace wilcot { namespace guard {

/**
 * Class Container.
 * 
 * @since 0.1.0
 */
class Container : public Object
{
public:
	/**
	 * Container constructor.
	 */
	Container();

	/**
	 * Container destructor.
	 */
	~Container();

	/**
	 * Start container.
	 */
	void start();

	/**
	 * Stop container.
	 */
//	void stop();

	/**
	 * Wait container for finished.
	 */
//	void wait();

	/**
	 * Create and execute process in this container.
	 *
	 * @param process
	 */
//	void attach(Process& process);

private:
	int handle_;

	int pipe_[2];

	int namespaceHandles_[5];

	/**
	 * An entry point for child process.
	 *
	 * @param process
	 * @return
	 */
	static int entryPoint_(void* process);

	/**
	 * An entry point for child process.
	 *
	 * @return
	 */
	int entryPoint_();

	/**
	 * Make all mapping for users and groups.
	 */
	void prepareUserNamespace_();

	void setupNamespaceHandles_();

	/**
	 * Setup user namespace.
	 */
	void setupUserNamespace_();

	/**
	 * Setup mount namespace.
	 */
	void setupMountNamespace_();

	/**
	 * Setup network namespace.
	 */
	void setupNetworkNamespace_();

	/**
	 * Setup UTS namespace.
	 */
	void setupUtsNamespace_();

	/**
	 * Setup IPC namespace.
	 */
	void setupIpcNamespace_();
};

}}

#endif // HEADER_wilcot_guard_Container
