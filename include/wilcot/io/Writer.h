/**
 * @author Ivan Udovin
 * @license MIT
 */

#ifndef HEADER_wilcot_io_Writer
#define HEADER_wilcot_io_Writer

#include <wilcot/Object.h>

#include <wilcot/io/Stream.h>

namespace wilcot { namespace io {

/**
 * Class Writer.
 */
class Writer : public Object
{
public:
	/**
	 * Writer constructor.
	 */
	Writer(Stream& stream);

private:
	Stream& stream_;
};

}}

#endif // HEADER_wilcot_io_Writer
