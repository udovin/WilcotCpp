/**
 * @author Ivan Udovin
 * @license MIT
 */

#ifndef HEADER_wilcot_io_FileStream
#define HEADER_wilcot_io_FileStream

#include <wilcot/Object.h>
#include <wilcot/io/IStream.h>
#include <wilcot/system/IFileHandle.h>

#include <wilcot/system/Path.h>

namespace wilcot { namespace io {

/**
 * Class FileStream
 *
 * @since 0.0.1
 */
class FileStream : public Object, public IStream, public system::IFileHandle {
public:
	/**
	 * @since 0.0.1
	 */
	typedef int Mode;

	/**
	 * @since 0.0.1
	 */
	static const Mode READ;

	/**
	 * @since 0.0.1
	 */
	static const Mode WRITE;

	/**
	 * FileStream constructor
	 *
	 * @param path
	 * @param mode
	 *
	 * @since 0.0.1
	 */
	FileStream(const system::Path& path, Mode mode = READ | WRITE);

	/**
	 * FileStream destructor
	 */
	~FileStream();

	/**
	 * Read bytes from stream
	 *
	 * @param buffer
	 * @param count
	 * @return
	 *
	 * @since 0.0.1
	 */
	std::size_t read(void* buffer, std::size_t count);

	/**
	 * Write bytes to stream
	 *
	 * @param buffer
	 * @param size
	 * @return
	 *
	 * @since 0.0.1
	 */
	std::size_t write(const void* buffer, std::size_t count);

	/**
	 * Close stream
	 *
	 * @return
	 *
	 * @since 0.0.1
	 */
	IStream& close();

	/**
	 * Get system handle
	 *
	 * @return
	 *
	 * @since 0.0.1
	 */
	system::IFileHandle::Handle getHandle() const;

private:
	/**
	 * @since 0.0.1
	 */
	system::IFileHandle::Handle handle_;
};

}}

#endif // HEADER_wilcot_io_FileStream
