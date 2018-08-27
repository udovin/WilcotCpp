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

		assert(process.getExitCode() != 0);
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

		assert(process.getExitCode() == 0);
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

		assert(process.getExitCode() == 0);
	}

	ProcessTestCase() {
		addTest("testDevNull", &ProcessTestCase::testDevNull);
		addTest("testBinLs", &ProcessTestCase::testBinLs);
		addTest("testBinLsWorkDir", &ProcessTestCase::testBinLsWorkDir);
	}
};

int main(int argc, char* argv[]) {
	ProcessTestCase().run();
	return 0;
}
