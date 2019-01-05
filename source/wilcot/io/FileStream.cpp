/**
 * @author Ivan Udovin
 * @license MIT
 */

#include <wilcot/io/FileStream.h>
#include <unistd.h>
#include <fcntl.h>

namespace wilcot { namespace io {

/**
 * @todo Implement more modes for file stream
 * @todo Handle all errors when file is opened
 */
FileStream::FileStream(const os::Path& path, Mode mode)
	: handle_(os::IFileHandle::INVALID_VALUE), mode_(NOT_OPEN) {
	int flags = 0;
	if ((mode & READ) == READ) {
		flags |= O_RDONLY;
	}
	if ((mode & WRITE) == WRITE) {
		// For more convenient usage we can implicitly add
		// flags for creating and clearing the file.
		flags |= O_WRONLY | O_CREAT | O_TRUNC;
	}
	handle_ = ::open(path, flags);
	if (handle_ != os::IFileHandle::INVALID_VALUE) {
		mode_ = mode;
	}
}

FileStream::~FileStream() {
	close();
}

size_t FileStream::read(void* buffer, size_t count) {
	ssize_t result = ::read(handle_, buffer, count);
	if (result < 0) {
		mode_ = NOT_OPEN;
		return 0;
	}
	return result;
}

size_t FileStream::write(const void* buffer, size_t count) {
	ssize_t result = ::write(handle_, buffer, count);
	if (result < 0) {
		mode_ = NOT_OPEN;
		return 0;
	}
	return result;
}

IStream& FileStream::close() {
	if (handle_ != os::IFileHandle::INVALID_VALUE) {
		::close(handle_);
		handle_ = os::IFileHandle::INVALID_VALUE;
		mode_ = NOT_OPEN;
	}
	return *this;
}

IStream::Mode FileStream::getMode() const {
	return mode_;
}

bool FileStream::isOpen() const {
	return mode_ != NOT_OPEN;
}

bool FileStream::isReadable() const {
	return (mode_ & READ) > 0;
}

bool FileStream::isWritable() const {
	return (mode_ & WRITE) > 0;
}

os::IFileHandle::Handle FileStream::getHandle() const {
	return handle_;
}

}}
