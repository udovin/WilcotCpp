/**
 * @author Ivan Udovin
 * @license MIT
 */

#ifndef HEADER_wilcot_io_FileStream
#define HEADER_wilcot_io_FileStream

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
	size_t read(void* buffer, size_t count);

	/**
	 * Write bytes to stream
	 *
	 * @param buffer
	 * @param count
	 * @return
	 *
	 * @since 0.0.1
	 */
	size_t write(const void* buffer, size_t count);

	/**
	 * Close stream
	 *
	 * @return
	 *
	 * @since 0.0.1
	 */
	IStream& close();

	/**
	 * Get stream mode
	 *
	 * @since 0.0.1
	 */
	Mode getMode() const;

	/**
	 * Checks that stream is closed
	 *
	 * @since 0.0.1
	 */
	bool isOpen() const;

	/**
	 * Checks that stream is readable
	 *
	 * @since 0.0.1
	 */
	bool isReadable() const;

	/**
	 * Checks that stream is writable
	 *
	 * @since 0.0.1
	 */
	bool isWritable() const;

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

	/**
	 * @since 0.0.1
	 */
	Mode mode_;
};

}}

#endif // HEADER_wilcot_io_FileStream
