/**
 * @author Ivan Udovin
 * @license MIT
 */

#ifndef HEADER_wilcot_cli_Argument
#define HEADER_wilcot_cli_Argument

#include <wilcot/Object.h>
#include <wilcot/cli/IArgument.h>
#include <string>
#include <vector>
#include <sstream>

namespace wilcot { namespace cli {

template<class T>
class Argument : public IArgument {
private:
	bool required_;
	T value_;
	bool empty_;

public:
	Argument(bool required = true);

	operator const T&() const;

protected:
	bool write(const std::string& argument);

	void flush();

	void clear();
};

}}

#include <wilcot/cli/Argument.h.cpp>

#endif // HEADER_wilcot_cli_Argument
