/**
 * @author Ivan Udovin
 * @license MIT
 */

#include <string>
#include <sstream>

namespace wilcot { namespace cli {

template<class ValueType>
Argument<ValueType>::Argument(const std::string& name, bool required)
	: name_(name), required_(required), value_(), empty_(true) {}

template<class ValueType>
std::string Argument<ValueType>::getName() const {
	return name_;
}

template<class ValueType>
Argument<ValueType>::operator const ValueType&() const {
	return value_;
}

template<class ValueType>
bool Argument<ValueType>::write(const std::string& argument) {
	if (!empty_) {
		return false;
	}
	std::stringstream ss;
	ss << argument;
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

template<class ValueType>
void Argument<ValueType>::flush() {
	if (empty_) {
		throw std::exception();
	}
}

template<class ValueType>
void Argument<ValueType>::clear() {
	value_ = ValueType();
	empty_ = true;
}

}}
