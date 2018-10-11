#include <wilcot/io/Buffer.h>

#include <algorithm>
#include <cstring>

namespace wilcot { namespace io {

Buffer::Buffer(std::size_t size)
	: begin_(NULL), end_(NULL), start_(NULL), finish_(NULL) {
	begin_ = new char[size];
	end_ = begin_ + size;
	start_ = finish_ = begin_;
}

Buffer::~Buffer() {
	delete[] begin_;
}

std::size_t Buffer::read(void* buffer, std::size_t count) {
	count = std::min(count, getMaxReadSize());
	if (start_ <= finish_) {
		memcpy(buffer, start_, count);
		start_ += count;
	} else {
		std::size_t suffix = end_ - start_;
		if (count <= suffix) {
			memcpy(buffer, start_, count);
			start_ += count;
		} else {
			std::size_t prefix = count - suffix;
			if (suffix > 0) {
				memcpy(buffer, start_, suffix);
			}
			memcpy(
				static_cast<char*>(buffer) + suffix,
				begin_,
				prefix);
			start_ = begin_ + prefix;
			finish_++;
		}
	}

	return count;
}

std::size_t Buffer::write(const void* buffer, std::size_t count) {
	count = std::min(count, getMaxWriteSize());
	if (start_ > finish_) {
		memcpy(finish_ + 1, buffer, count);
		finish_ += count;
	} else {
		std::size_t suffix = end_ - finish_;
		if (count <= suffix) {
			memcpy(finish_, buffer, count);
			finish_ += count;
		} else {
			std::size_t prefix = count - suffix;
			if (suffix > 0) {
				memcpy(finish_, buffer, suffix);
			}
			memcpy(
				begin_,
				static_cast<const char*>(buffer) + suffix,
				prefix);
			finish_ = begin_ + (prefix - 1);
		}
	}

	return count;
}

Buffer& Buffer::clear() {
	start_ = finish_ = begin_;

	return *this;
}

std::size_t Buffer::getMaxReadSize() const {
	if (start_ <= finish_) {
		return finish_ - start_;
	} else {
		return (finish_ - begin_) + (end_ - start_) + 1;
	}
}

std::size_t Buffer::getMaxWriteSize() const {
	if (start_ <= finish_) {
		return (end_ - finish_) + (start_ - begin_);
	} else {
		return (start_ - finish_) - 1;
	}
}

}}
