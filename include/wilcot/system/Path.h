/**
 * @author Ivan Udovin
 * @license MIT
 */

#ifndef HEADER_wilcot_system_Path
#define HEADER_wilcot_system_Path

#include <wilcot/Object.h>

#include <wilcot/system/detect.h>

#include <string>

namespace wilcot { namespace system {

/**
 * Class Path.
 */
class Path : public Object
{
public:
	/**
	 * Path constructor.
	 */
	Path();

	/**
	 * Path copy constructor.
	 *
	 * @param other
	 */
	Path(const Path& other);

	/**
	 * @param other
	 * @return
	 */
	Path& operator=(const Path& other);

	/**
	 * A constructor.
	 *
	 * @param path
	 */
	Path(const char* path);

	/**
	 * A constructor.
	 *
	 * @param path
	 */
	Path(const std::string& path);

	/**
	 * Get raw path string.
	 *
	 * @return
	 */
	operator const char*() const;

	/**
	 * Check that path is absolute.
	 *
	 * @return
	 */
	bool isAbsolute() const;

	/**
	 * Get absolute path.
	 *
	 * @return
	 */
	Path getAbsolute() const;

	/**
	 * @param other
	 * @return
	 */
	Path& operator+=(const Path& other);

	/**
	 * @param other
	 * @return
	 */
	Path& operator/=(const Path& other);

	/**
	 * @param other
	 * @return
	 */
	Path operator+(const Path& other) const;

	/**
	 * @param other
	 * @return
	 */
	Path operator/(const Path& other) const;

	/**
	 * @param other
	 * @return
	 */
	bool operator==(const Path& other) const;

	/**
	 * @param other
	 * @return
	 */
	bool operator!=(const Path& other) const;

	/**
	 * @param other
	 * @return
	 */
	bool operator<(const Path& other) const;

	/**
	 * @param other
	 * @return
	 */
	bool operator<=(const Path& other) const;

	/**
	 * @param other
	 * @return
	 */
	bool operator>(const Path& other) const;

	/**
	 * @param other
	 * @return
	 */
	bool operator>=(const Path& other) const;

private:
	std::string path_;
};

}}

#endif // HEADER_wilcot_system_Path
