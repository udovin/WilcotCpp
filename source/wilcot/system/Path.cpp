/**
 * @author Ivan Udovin
 * @license MIT
 */

#include <wilcot/system/Path.h>

namespace wilcot { namespace system {

Path::Path()
	: path_()
{}

Path::Path(const Path& other)
	: path_(other.path_)
{}

Path& Path::operator=(const Path& other)
{
	path_ = other.path_;

	return *this;
}

Path::Path(const char* path)
	: path_(path)
{}

Path::Path(const std::string& path)
	: path_(path)
{}

Path::operator const char*() const
{
	return path_.c_str();
}

bool Path::isAbsolute() const
{
	return !path_.empty() && path_[0] == '/';
}

Path Path::getAbsolute() const
{
	return Path();
}

Path& Path::operator+=(const Path& other)
{
	path_ += other.path_;

	return *this;
}

Path& Path::operator/=(const Path& other)
{
	path_ += '/' + other.path_;

	return *this;
}

Path Path::operator+(const Path& other) const
{
	return Path(path_ + other.path_);
}

Path Path::operator/(const Path& other) const
{
	return Path(path_ + '/' + other.path_);
}

bool Path::operator==(const Path& other) const
{
	return path_ == other.path_;
}

bool Path::operator!=(const Path& other) const
{
	return path_ != other.path_;
}

bool Path::operator<(const Path& other) const
{
	return path_ < other.path_;
}

bool Path::operator<=(const Path& other) const
{
	return path_ <= other.path_;
}

bool Path::operator>(const Path& other) const
{
	return path_ > other.path_;
}

bool Path::operator>=(const Path& other) const
{
	return path_ >= other.path_;
}

}}
