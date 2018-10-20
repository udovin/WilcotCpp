/**
 * @author Ivan Udovin
 * @license MIT
 */

#include <wilcot/os/Path.h>

namespace wilcot { namespace os {

Path::Path() : path_() {}

Path::Path(const Path& other) : path_(other.path_) {}

Path& Path::operator=(const Path& other) {
	path_ = other.path_;

	return *this;
}

Path::Path(const char* path) : path_(path) {}

Path::Path(const std::string& path) : path_(path) {}

Path::operator const char*() const {
	return path_.c_str();
}

bool Path::isAbsolute() const {
	return !path_.empty() && path_[0] == '/';
}

Path Path::getAbsolute() const {
	return Path();
}

Path Path::getParent() const {
	std::size_t i;

	for (i = path_.size(); i > 0; i--) {
		if (path_[i - 1] == '/') {
			break;
		}
	}

	return Path(path_.substr(0, i > 0 ? i - 1 : 0));
}

Path& Path::operator+=(const Path& other) {
	path_ += other.path_;

	return *this;
}

Path& Path::operator/=(const Path& other) {
	path_ += '/' + other.path_;

	return *this;
}

Path Path::operator+(const Path& other) const {
	return Path(path_ + other.path_);
}

Path Path::operator/(const Path& other) const {
	return Path(path_ + '/' + other.path_);
}

bool Path::operator==(const Path& other) const {
	return path_ == other.path_;
}

bool Path::operator!=(const Path& other) const {
	return path_ != other.path_;
}

bool Path::operator<(const Path& other) const {
	return path_ < other.path_;
}

bool Path::operator<=(const Path& other) const {
	return path_ <= other.path_;
}

bool Path::operator>(const Path& other) const {
	return path_ > other.path_;
}

bool Path::operator>=(const Path& other) const {
	return path_ >= other.path_;
}

}}
