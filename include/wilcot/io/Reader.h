/*!
 * \author Ivan Udovin
 * \license http://www.spdx.org/licenses/MIT
 */

#ifndef HEADER_wilcot_io_Reader
#define HEADER_wilcot_io_Reader

#include <wilcot/Object.h>

#include <wilcot/io/Stream.h>

namespace wilcot { namespace io {

/*!
 * Reader class
 */
class Reader : public Object
{
public:
	/*!
	 * A constructor
	 */
	Reader(Stream& stream);

private:
	Stream& stream_;
};

}}

#endif // HEADER_wilcot_io_Reader
