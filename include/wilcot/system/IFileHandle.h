/**
 * @author Ivan Udovin
 * @license MIT
 */

#ifndef HEADER_wilcot_system_IFileHandle
#define HEADER_wilcot_system_IFileHandle

#include <wilcot/system/detect.h>

namespace wilcot { namespace system {

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
#ifdef WILCOT_SYSTEM_WINDOWS
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
	 * Get system handle
	 *
	 * @return
	 *
	 * @since 0.0.1
	 */
	virtual Handle getHandle() const = 0;
};

}}

#endif // HEADER_wilcot_system_IFileHandle
