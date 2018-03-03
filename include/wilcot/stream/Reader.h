#ifndef HEADER_wilcot_stream_Reader
#define HEADER_wilcot_stream_Reader

/*!
 * \author Ivan Udovin
 */

#include <wilcot/Object.h>

#include <wilcot/stream/Stream.h>

namespace wilcot { namespace stream {

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

#endif // HEADER_wilcot_stream_Reader
