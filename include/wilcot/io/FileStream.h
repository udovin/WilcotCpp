/*!
 * \author Ivan Udovin
 * \license http://www.spdx.org/licenses/MIT
 */

#ifndef HEADER_wilcot_io_FileStream
#define HEADER_wilcot_io_FileStream

#include <wilcot/Object.h>
#include <wilcot/io/Stream.h>
#include <wilcot/system/FileHandle.h>

#include <wilcot/system/Path.h>

namespace wilcot { namespace io {

/*!
 * FileStream class
 */
class FileStream
	: public Object, public Stream, public system::FileHandle
{
public:
	enum Mode
	{
		READ = 0,
		WRITE = 1
	};

	/*!
	 * A constructor
	 *
	 * \param path
	 * \param mode
	 */
	FileStream(const system::Path& path, Mode mode);

	/*!
	 * A destructor
	 */
	~FileStream();

	/*!
	 * Read bytes from stream
	 *
	 * \param buffer
	 * \param count
	 * \return
	 */
	std::size_t read(void* buffer, std::size_t count);

	/*!
	 * Write bytes to stream
	 *
	 * \param buffer
	 * \param size
	 * \return
	 */
	std::size_t write(const void* buffer, std::size_t count);

	/*!
	 * Close stream
	 */
	void close();

	/*!
	 * Get system handle
	 *
	 * \return
	 */
	int getHandle() const;

private:
	int handle_;
};

}}

#endif // HEADER_wilcot_io_FileStream
