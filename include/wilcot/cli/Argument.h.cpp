/**
 * @author Ivan Udovin
 * @license MIT
 */

#include <string>
#include <sstream>

namespace wilcot { namespace cli {

template<class T>
Argument<T>::Argument(bool required)
	: required_(required), value_(), empty_(true) {}

template<class T>
Argument<T>::operator const T&() const {
	return value_;
}

template<class T>
bool Argument<T>::write(const std::string& value) {
	if (!empty_) {
		return false;
	}
	std::stringstream ss;
	ss << value;
	if (!(ss >> value_)) {
		if (required_) {
			throw std::exception();
		}
		return false;
	}
	empty_ = false;
	return true;
}

// 'std::string' has special case with spaces
template<>
bool Argument<std::string>::write(const std::string& value) {
	if (!empty_) {
		return false;
	}
	value_ = value;
	empty_ = false;
	return true;
}

template<class T>
void Argument<T>::flush() {
	if (empty_) {
		throw std::exception();
	}
}

template<class T>
void Argument<T>::clear() {
	value_ = T();
	empty_ = true;
}

}}
