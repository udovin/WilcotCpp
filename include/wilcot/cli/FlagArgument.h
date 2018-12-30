/**
 * @author Ivan Udovin
 * @license MIT
 */

#ifndef HEADER_wilcot_cli_FlagArgument
#define HEADER_wilcot_cli_FlagArgument

#include <wilcot/Object.h>
#include <wilcot/cli/IArgument.h>
#include <string>

namespace wilcot { namespace cli {

class FlagArgument : public Object, public IArgument {
private:
	bool flag_;

public:
	FlagArgument();

	std::string getName() const;

	operator bool() const;

protected:
	bool write(const std::string& argument);

	void flush();

	void clear();
};

}}

#endif // HEADER_wilcot_cli_FlagArgument
