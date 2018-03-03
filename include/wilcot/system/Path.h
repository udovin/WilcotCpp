#ifndef HEADER_wilcot_system_Path
#define HEADER_wilcot_system_Path

/*!
 * \author Ivan Udovin
 */

#include <wilcot/Object.h>

#include <wilcot/system/detect.h>

#include <string>

namespace wilcot { namespace system {

/*!
 * Path class
 */
class Path : public Object
{
public:
	/*!
	 * A constructor
	 */
	Path();

	/*!
	 * A copy constructor
	 *
	 * \param other
	 */
	Path(const Path& other);

	/*!
	 *
	 * \param other
	 * \return
	 */
	Path& operator=(const Path& other);

	/*!
	 * A constructor
	 *
	 * \param path
	 */
	Path(const char* path);

	/*!
	 * A constructor
	 *
	 * \param path
	 */
	Path(const std::string& path);

	/*!
	 * Get raw path string
	 *
	 * \return
	 */
	operator const char*() const;

	/*!
	 * Check that path is absolute
	 *
	 * \return
	 */
	bool isAbsolute() const;

	/*!
	 * Get absolute path
	 *
	 * \return
	 */
	Path getAbsolute() const;

	/*!
	 *
	 * \param other
	 * \return
	 */
	Path& operator+=(const Path& other);

	/*!
	 *
	 * \param other
	 * \return
	 */
	Path& operator/=(const Path& other);

	/*!
	 *
	 * \param other
	 * \return
	 */
	Path operator+(const Path& other) const;

	/*!
	 *
	 * \param other
	 * \return
	 */
	Path operator/(const Path& other) const;

	/*!
	 *
	 * \param other
	 * \return
	 */
	bool operator==(const Path& other) const;

	/*!
	 *
	 * \param other
	 * \return
	 */
	bool operator!=(const Path& other) const;

	/*!
	 *
	 * \param other
	 * \return
	 */
	bool operator<(const Path& other) const;

	/*!
	 *
	 * \param other
	 * \return
	 */
	bool operator<=(const Path& other) const;

	/*!
	 *
	 * \param other
	 * \return
	 */
	bool operator>(const Path& other) const;

	/*!
	 *
	 * \param other
	 * \return
	 */
	bool operator>=(const Path& other) const;

private:
	std::string path_;
};

}}

#endif // HEADER_wilcot_system_Path
