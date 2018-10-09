/**
 * @author Ivan Udovin
 * @license MIT
 */

#ifndef _HEADER_wilcot_io_FileStream
#define _HEADER_wilcot_io_FileStream

#include <wilcot/Object.h>
#include <wilcot/io/IStream.h>
#include <wilcot/os/IFileHandle.h>

#include <wilcot/os/Path.h>

namespace wilcot { namespace io {

/**
 * Class FileStream
 *
 * @since 0.0.1
 */
class FileStream : public Object, public IStream, public os::IFileHandle {
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
	FileStream(const os::Path& path, Mode mode = READ | WRITE);

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
	os::IFileHandle::Handle getHandle() const;

private:
	/**
	 * @since 0.0.1
	 */
	os::IFileHandle::Handle handle_;
};

}}

#endif // _HEADER_wilcot_io_FileStream
