/**
 * @author Ivan Udovin
 * @license MIT
 */

#ifndef HEADER_wilcot_io_IStream
#define HEADER_wilcot_io_IStream

#include <wilcot/base.h>
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
	 * @since 0.0.1
	 */
	typedef int Mode;

	/**
	 * @since 0.0.1
	 */
	static const Mode NOT_OPEN;

	/**
	 * @since 0.0.1
	 */
	static const Mode READ;

	/**
	 * @since 0.0.1
	 */
	static const Mode WRITE;

	/**
	 * Empty destructor
	 *
	 * @since 0.0.1
	 */
	virtual ~IStream() = 0;

	/**
	 * Read bytes from stream
	 *
	 * @param buffer
	 * @param count
	 * @return
	 *
	 * @since 0.0.1
	 */
	virtual size_t read(void* buffer, size_t count) = 0;

	/**
	 * Write bytes to stream
	 *
	 * @param buffer
	 * @param count
	 * @return
	 *
	 * @since 0.0.1
	 */
	virtual size_t write(const void* buffer, size_t count) = 0;

	/**
	 * Get stream mode
	 *
	 * @since 0.0.1
	 */
	virtual Mode getMode() const = 0;

	/**
	 * Close stream
	 *
	 * @since 0.0.1
	 */
	virtual IStream& close() = 0;

	/**
	 * Checks that stream is not closed
	 *
	 * @since 0.0.1
	 */
	virtual bool isOpen() const = 0;

	/**
	 * Checks that stream is readable
	 *
	 * @since 0.0.1
	 */
	virtual bool isReadable() const = 0;

	/**
	 * Checks that stream is writable
	 *
	 * @since 0.0.1
	 */
	virtual bool isWritable() const = 0;
};

}}

#endif // HEADER_wilcot_io_IStream
