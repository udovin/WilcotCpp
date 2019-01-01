/**
 * @author Ivan Udovin
 * @license MIT
 */

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

Buffer::Buffer(const Buffer& other)
	: begin_(NULL), end_(NULL), start_(NULL), finish_(NULL) {
	begin_ = new char[other.maxSize()];
	end_ = begin_ + other.maxSize();
	start_ = finish_ = begin_;
	if (other.start_ > other.finish_) {
		if (other.start_ < other.end_) {
			memcpy(finish_, other.start_, other.end_ - other.start_);
			finish_ += other.end_ - other.start_;
		}
		memcpy(finish_, other.begin_, other.finish_ - other.begin_ + 1);
		finish_ += other.finish_ - other.begin_ + 1;
	} else {
		memcpy(finish_, other.start_, other.size());
		finish_ += other.size();
	}
}

Buffer::~Buffer() {
	delete[] begin_;
}

Buffer& Buffer::operator=(const Buffer& other) {
	if (maxSize() < other.maxSize()) {
		char* newBegin_ = new char[other.maxSize()];
		delete[] begin_;
		begin_ =  newBegin_;
		end_ = begin_ + other.maxSize();
	}
	start_ = finish_ = begin_;
	if (other.start_ > other.finish_) {
		if (other.start_ < other.end_) {
			memcpy(finish_, other.start_, other.end_ - other.start_);
			finish_ += other.end_ - other.start_;
		}
		memcpy(finish_, other.begin_, other.finish_ - other.begin_ + 1);
		finish_ += other.finish_ - other.begin_ + 1;
	} else {
		memcpy(finish_, other.start_, other.size());
		finish_ += other.size();
	}
	return *this;
}

std::size_t Buffer::read(void* buffer, std::size_t count) {
	count = std::min(count, size());
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
	count = std::min(count, capacity());
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

std::size_t Buffer::maxSize() const {
	return static_cast<std::size_t>(end_ - begin_);
}

std::size_t Buffer::size() const {
	if (start_ <= finish_) {
		return finish_ - start_;
	}
	return (finish_ - begin_) + (end_ - start_) + 1;
}

std::size_t Buffer::capacity() const {
	if (start_ <= finish_) {
		return (end_ - finish_) + (start_ - begin_);
	}
	return (start_ - finish_) - 1;
}

bool Buffer::empty() const {
	return start_ == finish_;
}

bool Buffer::full() const {
	return (start_ == begin_ && finish_ == end_)
		|| finish_ + 1 == start_;
}

}}
