/*!
 * \author Ivan Udovin
 * \license http://www.spdx.org/licenses/MIT
 */

#ifndef HEADER_wilcot_io_Writer
#define HEADER_wilcot_io_Writer

#include <wilcot/Object.h>

#include <wilcot/io/Stream.h>

namespace wilcot { namespace io {

/*!
 * Writer class
 */
class Writer : public Object
{
public:
	/*!
	 * A constructor
	 */
	Writer(Stream& stream);

private:
	Stream& stream_;
};

}}

#endif // HEADER_wilcot_io_Writer
