/**
 * @author Ivan Udovin
 * @license MIT
 */

#include <wilcot/cli/FlagOption.h>

namespace wilcot { namespace cli {

FlagOption::FlagOption() : Option(), used_() {}

FlagOption::FlagOption(const std::string& name)
	: Option(name), used_() {}

FlagOption::FlagOption(const std::vector<std::string>& names)
	: Option(names), used_() {}

FlagOption::operator bool() const {
	return used_;
}

bool FlagOption::write(const std::string& argument) {
	WILCOT_UNUSED(argument);
	return false;
}

void FlagOption::close() {
	used_ = true;
}

void FlagOption::clear() {
	used_ = false;
}

}}
