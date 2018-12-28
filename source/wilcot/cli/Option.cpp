/**
 * @author Ivan Udovin
 * @license MIT
 */

#include <wilcot/cli/Option.h>

namespace wilcot { namespace cli {

Option::Option() : names_(), description_(), argument_(NULL) {}

Option::Option(const std::string& name)
	: names_(1, name), description_(), argument_(NULL) {}

Option::Option(const std::vector<std::string>& names)
	: names_(names), description_(), argument_(NULL) {}

Option::Option(const Option& other)
	: names_(other.names_), description_(other.description_)
	, argument_(other.argument_) {}

Option& Option::operator=(const Option& other) {
	names_ = other.names_;
	description_ = other.description_;
	argument_ = other.argument_;
	return *this;
}

const std::vector<std::string>& Option::getNames() const {
	return names_;
}

Option& Option::setName(const std::string& name) {
	names_ = std::vector<std::string>(1, name);
	return *this;
}

Option& Option::setNames(const std::vector<std::string>& names) {
	names_ = names;
	return *this;
}

const std::string& Option::getDescription() const {
	return description_;
}

Option& Option::setDescription(const std::string& description) {
	description_ = description;
	return *this;
}

const IArgument* Option::getArgument() const {
	return argument_;
}

IArgument* Option::getArgument() {
	return argument_;
}

Option& Option::setArgument(IArgument& argument) {
	argument_ = &argument;
	return *this;
}

}}
