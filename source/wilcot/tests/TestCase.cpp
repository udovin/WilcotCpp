#include <wilcot/tests/TestCase.h>

#include <iostream>

namespace wilcot { namespace tests {

TestCase::TestCase() : tests_() {}

TestCase::~TestCase() {
	for (std::size_t i = 0; i < tests_.size(); i++) {
		delete tests_[i];
	}
}

TestCase& TestCase::run() {
	for (std::size_t i = 0; i < tests_.size(); i++) {
		try {
			tests_[i]->invoke();
			std::cerr << '+';
		} catch (const Assert_& exception) {
			std::cerr << '-';
		} catch (const std::exception& exception) {
			std::cerr << '!';
		}
	}
	std::cerr << std::endl;

	return *this;
}

void TestCase::setUp() {}

void TestCase::tearDown() {}

void TestCase::assert(bool result) {
	if (!result) {
		throw Assert_();
	}
	std::cerr << '.';
}

}}
