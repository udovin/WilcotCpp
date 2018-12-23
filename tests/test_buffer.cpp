/**
 * @author Ivan Udovin
 * @license MIT
 */

#include <wilcot/tests/TestCase.h>

#include <wilcot/io/Buffer.h>
#include <vector>
#include <cstring>

class BufferTestCase : public wilcot::tests::TestCase {
public:
	char data[255];
	char test[255];
	std::size_t testSize;

	void setUp() {
		memset(data, 0, sizeof(data));
	}

	void testCreate() {
		wilcot::io::Buffer buffer(10);
		ASSERT(buffer.size() == 0);
		ASSERT(buffer.capacity() == 10);
		ASSERT(buffer.size() + buffer.capacity() == buffer.maxSize());
		ASSERT(buffer.empty());
		ASSERT(!buffer.full());
		wilcot::io::Buffer zeroBuffer;
		ASSERT(zeroBuffer.maxSize() == 0);
		ASSERT(zeroBuffer.capacity() == 0);
		ASSERT(zeroBuffer.size() == 0);
		ASSERT(zeroBuffer.empty());
		ASSERT(zeroBuffer.full());
	}

	void testReadFromEmpty() {
		wilcot::io::Buffer buffer(10);
		ASSERT(buffer.read(data, 10) == 0);
	}

	void testWriteToEmpty() {
		wilcot::io::Buffer buffer(10);
		ASSERT(buffer.write(data, 10) == 10);
		ASSERT(buffer.capacity() == 0);
		ASSERT(buffer.size() == 10);
		ASSERT(!buffer.empty());
		ASSERT(buffer.full());
	}

	void testReadWrite() {
		wilcot::io::Buffer buffer(255);
		ASSERT(buffer.write(test, testSize) == testSize);
		ASSERT(!buffer.empty());
		ASSERT(!buffer.full());
		ASSERT(buffer.read(data, testSize) == testSize);
		ASSERT(memcmp(data, test, testSize + 1) == 0);
		ASSERT(buffer.empty());
	}

	void testTryOverflow() {
		wilcot::io::Buffer buffer(testSize * 5 + testSize / 3);
		for (int i = 0; i < 5; i++) {
			ASSERT(buffer.write(test, testSize) == testSize);
			ASSERT(!buffer.full());
		}
		ASSERT(buffer.write(test, testSize) == testSize / 3);
		ASSERT(buffer.full());
	}

	void testRingReadWrite() {
		std::size_t ringPart = testSize / 4;
		wilcot::io::Buffer buffer(ringPart * 2);
		buffer.write(test, ringPart);
		for (std::size_t i = 0; i < 3; i++) {
			buffer.write(test + ringPart * (i + 1), ringPart);
			ASSERT(buffer.full());
			buffer.read(data, ringPart);
			ASSERT(memcmp(data, test + ringPart * i, ringPart) == 0);
			ASSERT(!buffer.full());
		}
		buffer.read(data, ringPart);
		ASSERT(memcmp(data, test + ringPart * 3, ringPart) == 0);
		ASSERT(!buffer.full());
	}

	void testRandomReadWrite() {
		wilcot::io::Buffer buffer(21);
		std::vector<char> state;
		std::size_t stateStart = 0;
		unsigned long seed = 12345;
		for (std::size_t i = 0; i < 30000; i++) {
			seed = (seed * 1103515245 + 12345) & 0xFFFFFFFF;
			if (stateStart == state.size()
				|| (seed % 2 == 1 && buffer.capacity() > 0)) {
				seed = (seed * 1103515245 + 12345) & 0xFFFFFFFF;
				ASSERT(buffer.write(test + seed % testSize, 1) == 1);
				state.push_back(test[seed % testSize]);
			} else {
				ASSERT(buffer.read(data, 1) == 1);
				ASSERT(data[0] == state[stateStart]);
				stateStart++;
			}
		}
	}

	void testCopyRingReadWrite() {
		std::size_t ringPart = testSize / 4;
		wilcot::io::Buffer buffer(ringPart * 2);
		buffer.write(test, ringPart);
		for (std::size_t i = 0; i < 3; i++) {
			buffer.write(test + ringPart * (i + 1), ringPart);
			wilcot::io::Buffer copyBuffer(buffer);
			buffer.read(data, ringPart);
			ASSERT(memcmp(data, test + ringPart * i, ringPart) == 0);
			memset(data, 0, ringPart);
			copyBuffer.read(data, ringPart);
			ASSERT(memcmp(data, test + ringPart * i, ringPart) == 0);
		}
		wilcot::io::Buffer copyBuffer(buffer);
		buffer.read(data, ringPart);
		ASSERT(memcmp(data, test + ringPart * 3, ringPart) == 0);
		memset(data, 0, ringPart);
		copyBuffer.read(data, ringPart);
		ASSERT(memcmp(data, test + ringPart * 3, ringPart) == 0);
		ASSERT(buffer.maxSize() <= copyBuffer.maxSize());
	}

	void testAssignRingReadWrite() {
		std::size_t ringPart = testSize / 4;
		wilcot::io::Buffer buffer(ringPart * 2);
		wilcot::io::Buffer copyBuffer;
		buffer.write(test, ringPart);
		for (std::size_t i = 0; i < 3; i++) {
			buffer.write(test + ringPart * (i + 1), ringPart);
			copyBuffer = buffer;
			buffer.read(data, ringPart);
			ASSERT(memcmp(data, test + ringPart * i, ringPart) == 0);
			memset(data, 0, ringPart);
			copyBuffer.read(data, ringPart);
			ASSERT(memcmp(data, test + ringPart * i, ringPart) == 0);
		}
		copyBuffer = buffer;
		buffer.read(data, ringPart);
		ASSERT(memcmp(data, test + ringPart * 3, ringPart) == 0);
		memset(data, 0, ringPart);
		copyBuffer.read(data, ringPart);
		ASSERT(memcmp(data, test + ringPart * 3, ringPart) == 0);
		ASSERT(buffer.maxSize() <= copyBuffer.maxSize());
	}

	void testCopySize() {
		wilcot::io::Buffer buffer;
		buffer = wilcot::io::Buffer(10);
		ASSERT(buffer.maxSize() == 10);
		buffer = wilcot::io::Buffer(20);
		ASSERT(buffer.maxSize() == 20);
		buffer = wilcot::io::Buffer(10);
		ASSERT(buffer.maxSize() == 20);
	}

	BufferTestCase() : testSize() {
		ADD_TEST(BufferTestCase, testCreate);
		ADD_TEST(BufferTestCase, testReadFromEmpty);
		ADD_TEST(BufferTestCase, testWriteToEmpty);
		ADD_TEST(BufferTestCase, testReadWrite);
		ADD_TEST(BufferTestCase, testTryOverflow);
		ADD_TEST(BufferTestCase, testRingReadWrite);
		ADD_TEST(BufferTestCase, testRandomReadWrite);
		ADD_TEST(BufferTestCase, testCopyRingReadWrite);
		ADD_TEST(BufferTestCase, testAssignRingReadWrite);
		ADD_TEST(BufferTestCase, testCopySize);
		strcpy(test, "KtgECWnxbRMY4vajwbVeuoX5HgI3tzWS");
		testSize = strlen(test);
	}
};

ADD_TEST_CASE(BufferTestCase);
