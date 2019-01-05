/**
 * @author Ivan Udovin
 * @license MIT
 */

#ifndef HEADER_wilcot_cli_FlagOption
#define HEADER_wilcot_cli_FlagOption

#include <wilcot/cli/Option.h>
#include <string>
#include <vector>

namespace wilcot { namespace cli {

class FlagOption : public Option {
public:
	FlagOption();

	FlagOption(const std::string& name);

	FlagOption(const std::vector<std::string>& names);

	operator bool() const;

protected:
	virtual bool write(const std::string& argument);

	virtual void close();

	virtual void clear();

private:
	bool used_;
};

}}

#endif // HEADER_wilcot_cli_FlagOption
