/**
 * @author Ivan Udovin
 * @license MIT
 */

#include <wilcot/os/IFileHandle.h>

namespace wilcot { namespace os {

#ifdef WILCOT_OS_WINDOWS
const IFileHandle::Handle IFileHandle::INVALID_VALUE = INVALID_HANDLE_VALUE;
#else
const IFileHandle::Handle IFileHandle::INVALID_VALUE = -1;
#endif

}}
