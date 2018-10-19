/**
 * @author Ivan Udovin
 * @license MIT
 */

#ifndef HEADER_wilcot_os_IFileHandle
#define HEADER_wilcot_os_IFileHandle

#include <wilcot/os/detect.h>

namespace wilcot { namespace os {

/**
 * Interface IFileHandle
 *
 * @since 0.0.1
 */
class IFileHandle {
public:
	/**
	 * Type of system handle
	 *
	 * @since 0.0.1
	 */
#ifdef WILCOT_OS_WINDOWS
	typedef HANDLE Handle;
#else
	typedef int Handle;
#endif

	/**
	 * Invalid system handle value
	 *
	 * @since 0.0.1
	 */
	static const Handle INVALID_VALUE;

	/**
	 * Empty destructor
	 *
	 * @since 0.0.1
	 */
	virtual ~IFileHandle() = 0;

	/**
	 * Get system handle
	 *
	 * @return
	 *
	 * @since 0.0.1
	 */
	virtual Handle getHandle() const = 0;
};

}}

#endif // HEADER_wilcot_os_IFileHandle
