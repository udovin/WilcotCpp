/**
 * @author Ivan Udovin
 * @license MIT
 */

#include <wilcot/tests/TestCase.h>

#include <wilcot/io/Buffer.h>
#include <cstring>

class BufferTestCase : public wilcot::tests::TestCase {
public:
	char data[255];
	char test[255];
	std::size_t testSize;

	void setUp() {
		memset(data, 0, sizeof(data));
	}

	void testCreateBuffer() {
		wilcot::io::Buffer buffer(10);

		ASSERT(buffer.getMaxReadSize() == 0);
		ASSERT(buffer.getMaxWriteSize() == 10);
	}

	void testReadFromEmptyBuffer() {
		wilcot::io::Buffer buffer(10);

		ASSERT(buffer.read(data, 10) == 0);
	}

	void testWriteToEmptyBuffer() {
		wilcot::io::Buffer buffer(10);

		ASSERT(buffer.write(data, 10) == 10);
	}

	void testStringReadWriteBuffer() {
		wilcot::io::Buffer buffer(255);

		ASSERT(buffer.write(test, testSize) == testSize);
		ASSERT(buffer.read(data, testSize) == testSize);
		ASSERT(memcmp(data, test, testSize + 1) == 0);
	}

	void testTryBufferOverflow() {
		wilcot::io::Buffer buffer(testSize * 5 + testSize / 3);

		for (int i = 0; i < 5; i++) {
			ASSERT(buffer.write(test, testSize) == testSize);
		}
		ASSERT(buffer.write(test, testSize) == testSize / 3);
	}

	void testRingReadWriteBuffer() {
		std::size_t ringPart = testSize / 4;
		wilcot::io::Buffer buffer(ringPart * 2);

		buffer.write(test, ringPart);
		for (std::size_t i = 0; i < 3; i++) {
			buffer.write(test + ringPart * (i + 1), ringPart);
			buffer.read(data, ringPart);
			ASSERT(memcmp(data, test + ringPart * i, ringPart) == 0);
		}
		buffer.read(data, ringPart);
		ASSERT(memcmp(data, test + ringPart * 3, ringPart) == 0);
	}

	BufferTestCase() {
		ADD_TEST(BufferTestCase, testCreateBuffer);
		ADD_TEST(BufferTestCase, testReadFromEmptyBuffer);
		ADD_TEST(BufferTestCase, testWriteToEmptyBuffer);
		ADD_TEST(BufferTestCase, testStringReadWriteBuffer);
		ADD_TEST(BufferTestCase, testTryBufferOverflow);
		ADD_TEST(BufferTestCase, testRingReadWriteBuffer);

		strcpy(test, "KtgECWnxbRMY4vajwbVeuoX5HgI3tzWS");
		testSize = strlen(test);
	}
};

ADD_TEST_CASE(BufferTestCase);
