/**
 * @author Ivan Udovin
 * @license MIT
 */

#include <cassert>
#include <cstdlib>

#include <wilcot/system/Process.h>

int main(int argc, char* argv[]) {
	wilcot::system::Process process;

	process.setProgram("/dev/null");

	process.start();
	process.wait();

	assert(process.getExitCode() != 0);

	std::vector<std::string> arguments;

	arguments.push_back("/bin/ls");
	arguments.push_back("-al");

	process.setProgram("/bin/ls");
	process.setArguments(arguments);

	process.start();
	process.wait();

	assert(process.getExitCode() == 0);

	process.setWorkingDirectory("/bin");

	process.start();
	process.wait();

	assert(process.getExitCode() == 0);

	return EXIT_SUCCESS;
}
