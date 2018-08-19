/**
 * @author Ivan Udovin
 * @license MIT
 */

#include <wilcot/system/IFileHandle.h>

namespace wilcot { namespace system {

#ifdef WILCOT_SYSTEM_WINDOWS
const IFileHandle::Handle IFileHandle::INVALID_VALUE = INVALID_HANDLE_VALUE;
#else
const IFileHandle::Handle IFileHandle::INVALID_VALUE = -1;
#endif

}}
