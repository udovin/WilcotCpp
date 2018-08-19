/**
 * @author Ivan Udovin
 * @license MIT
 */

#include <wilcot/io/Writer.h>

namespace wilcot { namespace io {

Writer::Writer(IStream& stream) : stream_(stream) {}

std::size_t Writer::write(const void* buffer, std::size_t count) {
	return stream_.write(buffer, count);
}

static inline void writeChar__(Writer& writer, char c) {
	writer.write(&c, 1);
}

Writer& operator<<(Writer& writer, char c) {
	writeChar__(writer, c);

	return writer;
}

Writer& operator<<(Writer& writer, const std::string& s) {
	for (std::size_t i = 0; i < s.size(); i++) {
		writeChar__(writer, s[i]);
	}

	return writer;
}

}}
