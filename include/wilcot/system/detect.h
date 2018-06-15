/**
 * @author Ivan Udovin
 * @license MIT
 */

#ifndef HEADER_wilcot_system_detect
#define HEADER_wilcot_system_detect

#if defined(__linux__)
#	define WILCOT_SYSTEM_LINUX
#elif defined(WIN32)
#	define WILCOT_SYSTEM_WINDOWS
#endif

#endif // HEADER_wilcot_system_detect
