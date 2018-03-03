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
class Stream : public stream::Stream
{
public:
	/*!
	 * Get system handle
	 *
	 * \return
	 */
	virtual int getHandle() const = 0;
};

}}

#endif // HEADER_wilcot_system_Stream
