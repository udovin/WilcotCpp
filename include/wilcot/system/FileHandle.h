/*!
 * \author Ivan Udovin
 * \license http://www.spdx.org/licenses/MIT
 */

#ifndef HEADER_wilcot_system_FileHandle
#define HEADER_wilcot_system_FileHandle

#include <wilcot/system/detect.h>

namespace wilcot { namespace system {

/*!
 * FileHandle interface
 */
class FileHandle
{
public:
	/*!
	 * Get system handle
	 *
	 * \return
	 */
	virtual int getHandle() const = 0;
};

}}

#endif // HEADER_wilcot_system_FileHandle
