/**
 * @author Ivan Udovin
 * @license MIT
 */

#include <wilcot/cli/OptionParser.h>

#include <iostream>
#include <sstream>

namespace wilcot { namespace cli {

OptionParser::OptionParser() : options_(), optionMap_() {}

OptionParser& OptionParser::addOption(const Option& option) {
	const std::vector<std::string> names(option.getNames());
	for (size_t i = 0; i < names.size(); i++) {
		optionMap_[names[i]] = options_.size();
	}
	options_.push_back(option);
	return *this;
}

std::string OptionParser::getHelp() const {
	std::stringstream ss;
	ss << "Usage: " << "[program]" << std::endl;
	ss << "Options:" << std::endl;
	ss << getOptionHelp_();
	return ss.str();
}

void OptionParser::parse(int argc, const char* argv[]) {
	WILCOT_UNUSED(argv);
	for (int i = 1; i < argc; i++) {}
}

std::string OptionParser::getOptionHelp_() const {
	std::stringstream ss;
	std::vector<std::string> options;
	size_t maxLength = 0;
	for (size_t i = 0; i < options_.size(); i++) {
		const std::vector<std::string>& names = options_[i].getNames();
		for (size_t j = 0; j < names.size(); j++) {
			if (j > 0) {
				ss << ", ";
			}
			ss << names[j];
		}
		options.push_back(ss.str());
		if (maxLength < options[options.size() - 1].size()) {
			maxLength = options[options.size() - 1].size();
		}
		ss.str("");
	}
	if (maxLength > 14) {
		maxLength = 14;
	}
	for (size_t i = 0; i < options_.size(); i++) {
		ss << "  " << options[i];
		for (size_t j = options[i].size(); j < maxLength; j++) {
			ss << ' ';
		}
		if (options[i].size() > maxLength) {
			ss << std::endl;
			for (size_t j = 0; j < maxLength + 2; j++) {
				ss << ' ';
			}
		}
		ss << "  ";
		ss << options_[i].getDescription() << std::endl;
	}
	return ss.str();
}

}}
