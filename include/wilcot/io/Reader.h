/**
 * @author Ivan Udovin
 * @license MIT
 */

#ifndef HEADER_wilcot_io_Reader
#define HEADER_wilcot_io_Reader

#include <wilcot/Object.h>

#include <wilcot/io/Stream.h>

namespace wilcot { namespace io {

/**
 * Class Reader.
 */
class Reader : public Object
{
public:
	/**
	 * Reader constructor.
	 */
	Reader(Stream& stream);

private:
	Stream& stream_;
};

}}

#endif // HEADER_wilcot_io_Reader
