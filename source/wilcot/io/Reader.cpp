/**
 * @author Ivan Udovin
 * @license MIT
 */

#include <wilcot/io/Reader.h>

namespace wilcot { namespace io {

Reader::Reader(IStream& stream) : stream_(stream) {}

std::size_t Reader::read(void* buffer, std::size_t count) {
	return stream_.read(buffer, count);
}

static inline void readChar__(Reader& reader, char& c) {
	reader.read(&c, 1);
}

Reader& operator>>(Reader& reader, char& c) {
	readChar__(reader, c);

	return reader;
}

Reader& operator>>(Reader& reader, std::string& s) {
	char c;

	do {
		readChar__(reader, c);
	} while (c == ' ' || c == '\n' || c == '\r');

	s.push_back(c);
	readChar__(reader, c);

	while (c != ' ' && c != '\n' && c != '\r') {
		s.push_back(c);
		readChar__(reader, c);
	}

	return reader;
}

}}
