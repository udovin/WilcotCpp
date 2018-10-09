/**
 * @author Ivan Udovin
 * @license MIT
 */

#ifndef _HEADER_wilcot_io_IStream
#define _HEADER_wilcot_io_IStream

#include <wilcot/os/detect.h>

#include <cstddef>

namespace wilcot { namespace io {

/**
 * Interface IStream
 *
 * @since 0.0.1
 */
class IStream {
public:
	/**
	 * Read bytes from stream
	 *
	 * @param buffer
	 * @param count
	 * @return
	 *
	 * @since 0.0.1
	 */
	virtual std::size_t read(void* buffer, std::size_t count) = 0;

	/**
	 * Write bytes to stream
	 *
	 * @param buffer
	 * @param size
	 * @return
	 *
	 * @since 0.0.1
	 */
	virtual std::size_t write(const void* buffer, std::size_t count) = 0;

	/**
	 * Close stream
	 *
	 * @since 0.0.1
	 */
	virtual IStream& close() = 0;
};

}}

#endif // _HEADER_wilcot_io_IStream
