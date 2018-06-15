/**
 * @author Ivan Udovin
 * @license MIT
 */

#ifndef HEADER_wilcot_system_FileHandle
#define HEADER_wilcot_system_FileHandle

#include <wilcot/system/detect.h>

namespace wilcot { namespace system {

/**
 * Interface FileHandle.
 */
class FileHandle
{
public:
	/**
	 * Type of system handle.
	 */
#ifdef WILCOT_SYSTEM_WINDOWS
	typedef HANDLE Handle;
#else
	typedef int Handle;
#endif

	/**
	 * Invalid system handle value.
	 */
	static const Handle INVALID_VALUE;

	/**
	 * Get system handle.
	 *
	 * @return
	 */
	virtual Handle getHandle() const = 0;
};

}}

#endif // HEADER_wilcot_system_FileHandle
