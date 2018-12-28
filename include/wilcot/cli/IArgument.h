/**
 * @author Ivan Udovin
 * @license MIT
 */

#ifndef HEADER_wilcot_cli_IArgument
#define HEADER_wilcot_cli_IArgument

#include <string>

namespace wilcot { namespace cli {

class IArgument {
	friend class OptionParser;

public:
	virtual ~IArgument() = 0;

protected:
	virtual bool write(const std::string& value) = 0;

	virtual void flush() = 0;

	virtual void clear() = 0;
};

}}

#endif // HEADER_wilcot_cli_IArgument
