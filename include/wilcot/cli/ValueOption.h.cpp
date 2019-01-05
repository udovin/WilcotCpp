/**
 * @author Ivan Udovin
 * @license MIT
 */

#include <string>
#include <sstream>

namespace wilcot { namespace cli {

template<class ValueType>
ValueOption<ValueType>::ValueOption()
	: Option(), argument_(), required_(), value_(), empty_() {}

template<class ValueType>
ValueOption<ValueType>::ValueOption(const std::string& name)
	: Option(name), argument_(), required_(), value_(), empty_() {}

template<class ValueType>
ValueOption<ValueType>::ValueOption(const std::vector<std::string>& names)
	: Option(names), argument_(), required_(), value_(), empty_() {}

template<class ValueType>
std::string ValueOption<ValueType>::getArgument() const {
	return argument_;
}

template<class ValueType>
ValueOption<ValueType>& 
	ValueOption<ValueType>::setArgument(const std::string& argument) {
	argument_ = argument;
	return *this;
}

template<class ValueType>
ValueOption<ValueType>::operator const ValueType&() const {
	return value_;
}

template<class ValueType>
bool ValueOption<ValueType>::write(const std::string& argument) {
	if (!empty_) {
		return false;
	}
	std::stringstream ss(argument);
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
bool ValueOption<std::string>::write(const std::string& value) {
	if (!empty_) {
		return false;
	}
	value_ = value;
	empty_ = false;
	return true;
}

template<class ValueType>
void ValueOption<ValueType>::close() {
	if (required_ && empty_) {
		throw std::exception();
	}
}

template<class ValueType>
void ValueOption<ValueType>::clear() {
	value_ = ValueType();
	empty_ = true;
}

}}
