/**
 * @author Ivan Udovin
 * @license MIT
 */

#include <wilcot/system/FileHandle.h>

namespace wilcot { namespace system {

#ifdef WILCOT_SYSTEM_WINDOWS
const FileHandle::Handle FileHandle::INVALID_VALUE = INVALID_HANDLE_VALUE;
#else
const FileHandle::Handle FileHandle::INVALID_VALUE = -1;
#endif

}}
