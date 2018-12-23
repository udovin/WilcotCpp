/**
 * @author Ivan Udovin
 * @license MIT
 */

#ifndef HEADER_wilcot_cli_OptionParser
#define HEADER_wilcot_cli_OptionParser

#include <wilcot/Object.h>
#include <wilcot/cli/Option.h>
#include <vector>
#include <string>
#include <map>

namespace wilcot { namespace cli {

class OptionParser : public Object {
private:
	std::vector<Option> options_;
	std::map<std::string, size_t> optionMap_;

	std::string getOptionHelp_() const;

public:
	OptionParser();

	OptionParser& addOption(const Option& option);

	std::string getHelp() const;

	void parse(int argc, const char* argv[]);
};

}}

#endif // HEADER_wilcot_cli_OptionParser
