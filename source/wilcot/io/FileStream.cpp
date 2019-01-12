/**
 * @author Ivan Udovin
 * @license MIT
 */

#include <wilcot/io/FileStream.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdexcept>

namespace wilcot { namespace io {

const FileStream::Mode FileStream::READ = 1;

const FileStream::Mode FileStream::WRITE = 2;

/**
 * @todo Implement more modes for file stream
 * @todo Handle all errors when file is opened
 */
FileStream::FileStream(const os::Path& path, Mode mode)
	: handle_(os::IFileHandle::INVALID_VALUE) {
	int flags = 0;
	if ((mode & READ) == READ) {
		flags |= O_RDONLY;
	}
	if ((mode & WRITE) == WRITE) {
		// For more convenient usage we can implicitly add
		// flags for creating and clearing the file.
		flags |= O_WRONLY | O_CREAT | O_TRUNC;
	}
	handle_ = ::open(path, flags,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH
	);
	if (handle_ == os::IFileHandle::INVALID_VALUE) {
		throw std::runtime_error("Unable to open file");
	}
}

FileStream::~FileStream() {
	close();
}

std::size_t FileStream::read(void* buffer, std::size_t count) {
	return ::read(handle_, buffer, count);
}

std::size_t FileStream::write(const void* buffer, std::size_t count) {
	return ::write(handle_, buffer, count);
}

IStream& FileStream::close() {
	if (handle_ != os::IFileHandle::INVALID_VALUE) {
		::close(handle_);
		handle_ = os::IFileHandle::INVALID_VALUE;
	}
	return *this;
}

os::IFileHandle::Handle FileStream::getHandle() const {
	return handle_;
}

}}
