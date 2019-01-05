/**
 * @author Ivan Udovin
 * @license MIT
 */

#include <wilcot/io/Reader.h>

namespace wilcot { namespace io {

Reader::Reader(IStream& stream) : stream_(stream) {}

size_t Reader::read(void* buffer, size_t count) {
	return stream_.read(buffer, count);
}

Reader::operator bool() const {
	return stream_.isReadable();
}

static inline bool readChar__(Reader& reader, char& c) {
	size_t result = reader.read(&c, 1);
	while (static_cast<bool>(reader) && result == 0) {
		result = reader.read(&c, 1);
	}
	return result == 1;
}

Reader& operator>>(Reader& reader, char& c) {
	readChar__(reader, c);
	return reader;
}

Reader& operator>>(Reader& reader, std::string& s) {
	char c;
	s.clear();
	do {
		if (!readChar__(reader, c)) {
			return reader;
		}
	} while (c == ' ' || c == '\n' || c == '\r');
	s.push_back(c);
	if (!readChar__(reader, c)) {
		return reader;
	}
	while (c != ' ' && c != '\n' && c != '\r') {
		s.push_back(c);
		if (!readChar__(reader, c)) {
			return reader;
		}
	}
	return reader;
}

}}
