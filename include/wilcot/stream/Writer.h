#ifndef HEADER_wilcot_stream_Writer
#define HEADER_wilcot_stream_Writer

/*!
 * \author Ivan Udovin
 */

#include <wilcot/Object.h>

#include <wilcot/stream/Stream.h>

namespace wilcot { namespace stream {

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

#endif // HEADER_wilcot_stream_Writer
