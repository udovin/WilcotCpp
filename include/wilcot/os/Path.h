/**
 * @author Ivan Udovin
 * @license MIT
 */

#ifndef _HEADER_wilcot_os_Path
#define _HEADER_wilcot_os_Path

#include <wilcot/Object.h>

#include <string>

namespace wilcot { namespace os {

/**
 * Class Path
 *
 * @since 0.0.1
 */
class Path : public Object {
public:
	/**
	 * Path constructor
	 *
	 * @since 0.0.1
	 */
	Path();

	/**
	 * Path copy constructor
	 *
	 * @param other
	 *
	 * @since 0.0.1
	 */
	Path(const Path& other);

	/**
	 * @param other
	 * @return
	 *
	 * @since 0.0.1
	 */
	Path& operator=(const Path& other);

	/**
	 * Path constructor
	 *
	 * @param path
	 *
	 * @since 0.0.1
	 */
	Path(const char* path);

	/**
	 * Path constructor
	 *
	 * @param path
	 *
	 * @since 0.0.1
	 */
	Path(const std::string& path);

	/**
	 * Get raw path string
	 *
	 * @return
	 *
	 * @since 0.0.1
	 */
	operator const char*() const;

	/**
	 * Check that path is absolute
	 *
	 * @return
	 *
	 * @since 0.0.1
	 */
	bool isAbsolute() const;

	/**
	 * Get absolute path
	 *
	 * @return
	 *
	 * @since 0.0.1
	 */
	Path getAbsolute() const;

	/**
	 * @param other
	 * @return
	 *
	 * @since 0.0.1
	 */
	Path& operator+=(const Path& other);

	/**
	 * @param other
	 * @return
	 *
	 * @since 0.0.1
	 */
	Path& operator/=(const Path& other);

	/**
	 * @param other
	 * @return
	 *
	 * @since 0.0.1
	 */
	Path operator+(const Path& other) const;

	/**
	 * @param other
	 * @return
	 *
	 * @since 0.0.1
	 */
	Path operator/(const Path& other) const;

	/**
	 * @param other
	 * @return
	 *
	 * @since 0.0.1
	 */
	bool operator==(const Path& other) const;

	/**
	 * @param other
	 * @return
	 *
	 * @since 0.0.1
	 */
	bool operator!=(const Path& other) const;

	/**
	 * @param other
	 * @return
	 *
	 * @since 0.0.1
	 */
	bool operator<(const Path& other) const;

	/**
	 * @param other
	 * @return
	 *
	 * @since 0.0.1
	 */
	bool operator<=(const Path& other) const;

	/**
	 * @param other
	 * @return
	 *
	 * @since 0.0.1
	 */
	bool operator>(const Path& other) const;

	/**
	 * @param other
	 * @return
	 *
	 * @since 0.0.1
	 */
	bool operator>=(const Path& other) const;

private:
	/**
	 * @since 0.0.1
	 */
	std::string path_;
};

}}

#endif // _HEADER_wilcot_os_Path
