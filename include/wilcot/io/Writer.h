/**
 * @author Ivan Udovin
 * @license MIT
 */

#ifndef HEADER_wilcot_io_Writer
#define HEADER_wilcot_io_Writer

#include <wilcot/Object.h>

#include <wilcot/io/IStream.h>

#include <string>

namespace wilcot { namespace io {

/**
 * Class Writer
 *
 * @since 0.0.1
 */
class Writer : public Object {
public:
	/**
	 * Writer constructor
	 *
	 * @since 0.0.1
	 */
	Writer(IStream& stream);

	/**
	 * Write bytes to stream
	 *
	 * @param buffer
	 * @param size
	 * @return
	 *
	 * @since 0.0.1
	 */
	virtual std::size_t write(const void* buffer, std::size_t count);

private:
	/**
	 * @since 0.0.1
	 */
	IStream& stream_;
};

/**
 * @param writer 
 * @param c 
 * @return
 *
 * @since 0.0.1
 */
Writer& operator<<(Writer& writer, char c);

/**
 * @param writer 
 * @param s 
 * @return
 *
 * @since 0.0.1
 */
Writer& operator<<(Writer& writer, const std::string& s);

}}

#endif // HEADER_wilcot_io_Writer
