#include <wilcot/cli/Option.h>

namespace wilcot { namespace cli {

Option::Option() : names_(), description_() {}

Option::Option(const std::string& name)
	: names_(1, name), description_() {}

Option::Option(const std::vector<std::string>& names)
	: names_(names), description_() {}

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

}}
