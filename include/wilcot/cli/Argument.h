/**
 * @author Ivan Udovin
 * @license MIT
 */

#ifndef HEADER_wilcot_cli_Argument
#define HEADER_wilcot_cli_Argument

#include <wilcot/Object.h>
#include <wilcot/cli/IArgument.h>
#include <string>
#include <sstream>

namespace wilcot { namespace cli {

template<class ValueType>
class Argument : public Object, public IArgument {
private:
	std::string name_;
	bool required_;
	ValueType value_;
	bool empty_;

public:
	Argument(const std::string& name, bool required = true);

	std::string getName() const;

	operator const ValueType&() const;

protected:
	bool write(const std::string& argument);

	void flush();

	void clear();
};

}}

#include <wilcot/cli/Argument.h.cpp>

#endif // HEADER_wilcot_cli_Argument
