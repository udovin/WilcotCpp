/*!
 * \author Ivan Udovin
 * \license http://www.spdx.org/licenses/MIT
 */

#ifndef HEADER_wilcot_guard_Container
#define HEADER_wilcot_guard_Container

#include <wilcot/Object.h>

#include <wilcot/system/detect.h>
//#include <wilcot/guard/Process.h>

namespace wilcot { namespace guard {

/*!
 * \since 0.1.0
 */
class Container : public Object
{
public:
	/*!
	 * Container constructor
	 */
	Container();

	/*!
	 * Container destructor
	 */
	~Container();

	/*!
	 * Start container
	 */
	void start();

	/*!
	 * Stop container
	 */
	void stop();

	/*!
	 * Wait container for finished
	 */
	void wait();

	/*!
	 * Create and execute process in this container
	 *
	 * \param process
	 */
	//void attach(Process& process);

private:
	int handle_;

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

	void setupUserNamespace_();

	void setupMountNamespace_();

	void setupNetworkNamespace_();

	void setupUtsNamespace_();

	void setupIpcNamespace_();

	void setupCgroupNamespace_();
};

}}

#endif // HEADER_wilcot_guard_Container
