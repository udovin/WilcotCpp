#ifndef HEADER_wilcot_system_Stream
#define HEADER_wilcot_system_Stream

/*!
 * \author Ivan Udovin
 */

#include <wilcot/stream/Stream.h>

namespace wilcot { namespace system {

/*!
 * Stream interface
 */
class Stream : stream::Stream
{
public:
	virtual int getHandle() = 0;
};

}}

#endif // HEADER_wilcot_system_Stream
