/**
 * @author Ivan Udovin
 * @license MIT
 */

#ifndef HEADER_wilcot_io_Reader
#define HEADER_wilcot_io_Reader

#include <wilcot/Object.h>
#include <wilcot/io/IStream.h>
#include <string>

namespace wilcot { namespace io {

/**
 * Class Reader
 *
 * @since 0.0.1
 */
class Reader : public Object {
public:
	/**
	 * Reader constructor
	 *
	 * @since 0.0.1
	 */
	Reader(IStream& stream);

	/**
	 * Read bytes from stream
	 *
	 * @param buffer
	 * @param count
	 * @return
	 *
	 * @since 0.0.1
	 */
	virtual std::size_t read(void* buffer, std::size_t count);

private:
	/**
	 * @since 0.0.1
	 */
	IStream& stream_;
};

/**
 * @param reader 
 * @param c 
 * @return
 *
 * @since 0.0.1
 */
Reader& operator>>(Reader& reader, char& c);

/**
 * @param reader 
 * @param s 
 * @return
 *
 * @since 0.0.1
 */
Reader& operator>>(Reader& reader, std::string& s);

}}

#endif // HEADER_wilcot_io_Reader
