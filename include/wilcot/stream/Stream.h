#ifndef HEADER_wilcot_stream_Stream
#define HEADER_wilcot_stream_Stream

/*!
 * \author Ivan Udovin
 */

#include <cstddef>

namespace wilcot { namespace stream {

/*!
 * Stream interface
 */
class Stream
{
public:
	/*!
	 * Read bytes from stream
	 *
	 * \param buffer
	 * \param count
	 * \return
	 */
	virtual std::size_t read(void* buffer, std::size_t count) = 0;

	/*!
	 * Write bytes to stream
	 *
	 * \param buffer
	 * \param size
	 * \return
	 */
	virtual std::size_t write(const void* buffer, std::size_t count) = 0;

	/*!
	 * Close stream
	 */
	virtual void close() = 0;
};

}}

#endif // HEADER_wilcot_stream_Stream
