#include <wilcot/tests/TestCase.h>

#include <sstream>
#include <iomanip>

#include <fcntl.h>
#include <unistd.h>

namespace wilcot { namespace tests {

TestCase::TestCase() : tests_() {}

TestCase::~TestCase() {
	for (std::size_t i = 0; i < tests_.size(); i++) {
		delete tests_[i];
	}
}

TestCase& TestCase::run() {
	int oldStdout = dup(STDOUT_FILENO);
	int newStdout = open("/dev/null", O_WRONLY);

	dup2(STDOUT_FILENO, oldStdout);
	dup2(newStdout, STDOUT_FILENO);

	std::vector<Failure_> failures;

	for (std::size_t i = 0; i < tests_.size(); i++) {
		if ((i + 1) % 60 == 0) {
			write(oldStdout, "\n", 1);
		}

		setUp();

		try {
			tests_[i]->invoke();
			write(oldStdout, ".", 1);
		} catch (const Failure_& failure) {
			write(oldStdout, "F", 1);
			failures.push_back(failure);
		} catch (const std::exception& exception) {
			write(oldStdout, "E", 1);
		}

		tearDown();
	}

	write(oldStdout, "\n", 1);

	for (std::size_t i = 0; i < failures.size(); i++) {
		std::stringstream ss;
		ss << "Test '" << tests_[i]->name_ << "':" << std::endl;
		ss << std::setw(6) << failures[i].line_ << ": ";
		ss << failures[i].code_ << std::endl;
		std::string message(ss.str());
		write(oldStdout, message.c_str(), message.size());
	}

	close(oldStdout);

	return *this;
}

void TestCase::setUp() {}

void TestCase::tearDown() {}

void TestCase::assert_(
	bool result, const std::string& code, std::size_t line) {
	if (!result) {
		throw Failure_(code, line);
	}
}

}}
