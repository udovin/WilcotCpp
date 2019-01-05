/**
 * @author Ivan Udovin
 * @license MIT
 */

#include <wilcot/io/Writer.h>

namespace wilcot { namespace io {

Writer::Writer(IStream& stream) : stream_(stream) {}

size_t Writer::write(const void* buffer, size_t count) {
	return stream_.write(buffer, count);
}

Writer::operator bool() const {
	return stream_.isWritable();
}

static inline bool writeChar__(Writer& writer, char c) {
	size_t result = writer.write(&c, 1);
	while (static_cast<bool>(writer) && result == 0) {
		result = writer.write(&c, 1);
	}
	return result == 1;
}

Writer& operator<<(Writer& writer, char c) {
	writeChar__(writer, c);
	return writer;
}

Writer& operator<<(Writer& writer, const std::string& s) {
	for (std::size_t i = 0; i < s.size(); i++) {
		if (!writeChar__(writer, s[i])) {
			return writer;
		}
	}
	return writer;
}

}}
