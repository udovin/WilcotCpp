/**
 * @author Ivan Udovin
 * @license MIT
 */

#include <wilcot/cli/OptionParser.h>

#include <iostream>
#include <sstream>

namespace wilcot { namespace cli {

static const size_t __MAX_OPTION_LENGTH = 16;

OptionParser::OptionParser() : options_(), optionMap_() {}

OptionParser& OptionParser::addOption(Option& option) {
	const std::vector<std::string> names(option.getNames());
	for (size_t i = 0; i < names.size(); i++) {
		optionMap_[names[i]] = options_.size();
	}
	options_.push_back(&option);
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
	for (size_t i = 0; i < options_.size(); i++) {
		options_[i]->clear();
	}
	for (int i = 1; i < argc; i++) {
		std::map<std::string, size_t>::const_iterator it(
			optionMap_.find(argv[i])
		);
		if (it != optionMap_.end()) {
			Option& option = *options_[it->second];
			while (i + 1 < argc && option.write(argv[i + 1])) {
				i++;
			}
			option.close();
		} else {
			throw std::exception();
		}
	}
}

std::string OptionParser::getOptionHelp_() const {
	std::stringstream ss;
	std::vector<std::string> options;
	size_t maxLength = 0;
	for (size_t i = 0; i < options_.size(); i++) {
		const Option& option = *options_[i];
		const std::vector<std::string>& names = option.getNames();
		for (size_t j = 0; j < names.size(); j++) {
			if (j > 0) {
				ss << ", ";
			}
			ss << names[j];
			if (!option.getArgument().empty()) {
				ss << ' ' << option.getArgument();
			}
		}
		options.push_back(ss.str());
		if (maxLength < options[options.size() - 1].size()) {
			maxLength = options[options.size() - 1].size();
		}
		ss.str("");
	}
	if (maxLength > __MAX_OPTION_LENGTH) {
		maxLength = __MAX_OPTION_LENGTH;
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
		ss << options_[i]->getDescription() << std::endl;
	}
	return ss.str();
}

}}
