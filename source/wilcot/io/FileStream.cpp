/*!
 * \author Ivan Udovin
 * \license http://www.spdx.org/licenses/MIT
 */

#include <wilcot/io/FileStream.h>

#include <unistd.h>
#include <fcntl.h>

namespace wilcot { namespace io {

FileStream::FileStream(const system::Path& path, Mode mode)
	: handle_(-1)
{
	switch (mode)
	{
	case READ:
		handle_ = ::open(path, O_RDONLY);
		break;
	case WRITE:
		handle_ = ::open(path, O_WRONLY | O_CREAT | O_TRUNC);
		break;
	}
}

FileStream::~FileStream()
{
	close();
}

std::size_t FileStream::read(void* buffer, std::size_t count)
{
	return ::read(handle_, buffer, count);
}

std::size_t FileStream::write(const void* buffer, std::size_t count)
{
	return ::write(handle_, buffer, count);
}

void FileStream::close()
{
	::close(handle_);
}

int FileStream::getHandle() const
{
	return handle_;
}

}}
