/**
 * @author Ivan Udovin
 * @license MIT
 */

#include <wilcot/cli/FlagArgument.h>

namespace wilcot { namespace cli {

FlagArgument::FlagArgument() : flag_() {}

std::string FlagArgument::getName() const {
	return std::string();
}

FlagArgument::operator bool() const {
	return flag_;
}

bool FlagArgument::write(const std::string& argument) {
	WILCOT_UNUSED(argument);
	return false;
}

void FlagArgument::flush() {
	flag_ = true;
}

void FlagArgument::clear() {
	flag_ = false;
}

}}
