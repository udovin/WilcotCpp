/**
 * @author Ivan Udovin
 * @license MIT
 */

#ifndef HEADER_wilcot_cli_Option
#define HEADER_wilcot_cli_Option

#include <wilcot/Object.h>
#include <wilcot/cli/IArgument.h>
#include <string>
#include <vector>

namespace wilcot { namespace cli {

class Option : public Object {
private:
	std::vector<std::string> names_;
	std::string description_;
	IArgument* argument_;

public:
	Option();

	Option(const std::string& name);

	Option(const std::vector<std::string>& names);

	Option(const Option& other);

	Option& operator=(const Option& other);

	const std::vector<std::string>& getNames() const;

	Option& setName(const std::string& name);

	Option& setNames(const std::vector<std::string>& names);

	const std::string& getDescription() const;

	Option& setDescription(const std::string& description);

	const IArgument* getArgument() const;

	IArgument* getArgument();

	Option& setArgument(IArgument& argument);
};

}}

#endif // HEADER_wilcot_cli_Option
