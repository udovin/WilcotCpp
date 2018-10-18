/**
 * @author Ivan Udovin
 * @license MIT
 */

#include <wilcot/tests/TestCase.h>

#include <wilcot/system/Process.h>

class ProcessTestCase : public wilcot::tests::TestCase {
public:
	void testDevNull() {
		wilcot::system::Process process;

		process.setProgram("/dev/null");
		process.start();
		process.wait();

		ASSERT(process.getExitCode() != 0);
	}

	void testBinLs() {
		wilcot::system::Process process;
		std::vector<std::string> arguments;

		arguments.push_back("/bin/ls");
		arguments.push_back("-al");

		process.setProgram("/bin/ls");
		process.setArguments(arguments);
		process.start();
		process.wait();

		ASSERT(process.getExitCode() == 0);
	}

	void testBinLsWorkDir() {
		wilcot::system::Process process;
		std::vector<std::string> arguments;

		arguments.push_back("/bin/ls");
		arguments.push_back("-al");

		process.setProgram("/bin/ls");
		process.setArguments(arguments);
		process.setWorkingDirectory("/bin");
		process.start();
		process.wait();

		ASSERT(process.getExitCode() == 0);
	}

	ProcessTestCase() {
		ADD_TEST(ProcessTestCase, testDevNull);
		ADD_TEST(ProcessTestCase, testBinLs);
		ADD_TEST(ProcessTestCase, testBinLsWorkDir);
	}
};

ADD_TEST_CASE(ProcessTestCase);
