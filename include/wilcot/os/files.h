/**
 * @author Ivan Udovin
 * @license MIT
 */

#ifndef HEADER_wilcot_os_files
#define HEADER_wilcot_os_files

#include <wilcot/Object.h>

#include <wilcot/os/Path.h>

#include <vector>

namespace wilcot { namespace os {

/**
 * @param path
 * @return
 *
 * @since 0.0.1
 */
bool pathExists(const Path& path);

/**
 * @param path
 * @return
 *
 * @since 0.0.1
 */
bool isFile(const Path& path);

/**
 * @param path
 * @return
 *
 * @since 0.0.1
 */
bool isDirectory(const Path& path);

/**
 * @param path
 * @return
 *
 * @since 0.0.1
 */
std::vector<Path> listDirectory(const Path& path);

/**
 * @param path
 *
 * @since 0.0.1
 */
void createFile(const Path& path);

/**
 * @param path
 *
 * @since 0.0.1
 */
void createDirectory(const Path& path);

/**
 * @param path
 *
 * @since 0.0.1
 */
void createDirectories(const Path& path);

/**
 * @param path
 *
 * @since 0.0.1
 */
void removeFile(const Path& path);

/**
 * @param path
 *
 * @since 0.0.1
 */
void removeDirectory(const Path& path);

/**
 * @param path
 *
 * @since 0.0.1
 */
void recursiveRemoveDirectory(const Path& path);

}}

#endif // HEADER_wilcot_os_file
