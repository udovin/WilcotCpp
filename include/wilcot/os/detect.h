/**
 * @author Ivan Udovin
 * @license MIT
 */

#ifndef _HEADER_wilcot_os_detect
#define _HEADER_wilcot_os_detect

#if defined(__linux__)
#	define WILCOT_OS_LINUX
#elif defined(WIN32)
#	define WILCOT_OS_WINDOWS
#endif

#endif // _HEADER_wilcot_os_detect
