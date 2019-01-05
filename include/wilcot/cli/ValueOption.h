/**
 * @author Ivan Udovin
 * @license MIT
 */

#ifndef HEADER_wilcot_cli_ValueOption
#define HEADER_wilcot_cli_ValueOption

#include <wilcot/cli/Option.h>
#include <string>
#include <vector>

namespace wilcot { namespace cli {

template<class ValueType>
class ValueOption : public Option {
public:
	ValueOption();

	ValueOption(const std::string& name);

	ValueOption(const std::vector<std::string>& names);

	std::string getArgument() const;

	ValueOption& setArgument(const std::string& argument);

	operator const ValueType&() const;

protected:
	virtual bool write(const std::string& argument);

	virtual void close();

	virtual void clear();

private:
	std::string argument_;

	bool required_;

	ValueType value_;

	bool empty_;
};

}}

#include <wilcot/cli/ValueOption.h.cpp>

#endif // HEADER_wilcot_cli_ValueOption
