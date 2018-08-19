/**
 * @author Ivan Udovin
 * @license MIT
 */

#ifndef HEADER_wilcot_guard_Container
#define HEADER_wilcot_guard_Container

#include <wilcot/Object.h>

//#include <wilcot/guard/Process.h>

namespace wilcot { namespace guard {

/**
 * Class Container
 * 
 * @since 0.0.1
 */
class Container : public Object {
public:
	/**
	 * Container constructor
	 *
	 * @since 0.0.1
	 */
	Container();

	/**
	 * Container destructor
	 *
	 * @since 0.0.1
	 */
	~Container();

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

	/**
	 * Create and execute process in this container
	 *
	 * @param process
	 *
	 * @since 0.0.1
	 */
//	void attach(Process& process);

private:
	/**
	 * @since 0.0.1
	 */
	int handle_;

	/**
	 * @since 0.0.1
	 */
	int pipe_[2];

	int namespaceHandles_[5];

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
};

}}

#endif // HEADER_wilcot_guard_Container
