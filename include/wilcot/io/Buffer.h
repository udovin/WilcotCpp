/**
 * @author Ivan Udovin
 * @license MIT
 */

#ifndef HEADER_wilcot_io_Buffer
#define HEADER_wilcot_io_Buffer

#include <wilcot/Object.h>
#include <cstddef>

namespace wilcot { namespace io {

/**
 * Class Buffer
 *
 * @since 0.0.1
 */
class Buffer : public Object {
public:
	/**
	 * Buffer constructor
	 *
	 * @since 0.0.1
	 */
	Buffer(std::size_t size = 0);

	/**
	 * Buffer copy constructor
	 *
	 * @since 0.0.1
	 */
	Buffer(const Buffer& other);

	/**
	 * Buffer destructor
	 * 
	 * @since 0.0.1
	 */
	~Buffer();

	/**
	 * Buffer assign operator
	 *
	 * @since 0.0.1
	 */
	Buffer& operator=(const Buffer& other);

	/**
	 * Read bytes from buffer
	 *
	 * @param buffer
	 * @param count
	 * @return
	 *
	 * @since 0.0.1
	 */
	std::size_t read(void* buffer, std::size_t count);

	/**
	 * Write bytes to buffer
	 *
	 * @param buffer
	 * @param size
	 * @return
	 *
	 * @since 0.0.1
	 */
	std::size_t write(const void* buffer, std::size_t count);

	/**
	 * Clear all data from buffer
	 * 
	 * This method does not remove data from memory.
	 * 
	 * @return Buffer& 
	 */
	Buffer& clear();

	/**
	 * @return
	 *
	 * @since 0.0.1
	 */
	std::size_t maxSize() const;

	/**
	 * @return
	 * 
	 * @since 0.0.1 
	 */
	std::size_t size() const;

	/**
	 * @return
	 * 
	 * @since 0.0.1
	 */
	std::size_t capacity() const;

	/**
	 * @return
	 *
	 * @since 0.0.1
	 */
	bool empty() const;

	/**
	 * @return
	 *
	 * @since 0.0.1
	 */
	bool full() const;

private:
	/**
	 * @since 0.0.1
	 */
	char* begin_;

	/**
	 * @since 0.0.1
	 */
	char* end_;

	/**
	 * @since 0.0.1
	 */
	char* start_;

	/**
	 * @since 0.0.1
	 */
	char* finish_;
};

}}

#endif // HEADER_wilcot_io_Buffer
