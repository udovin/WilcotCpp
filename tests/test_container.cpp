/**
 * @author Ivan Udovin
 * @license MIT
 */

#include <wilcot/tests/TestCase.h>

#include <wilcot/lxc/Container.h>
#include <wilcot/os/files.h>

class ContainerTestCase : public wilcot::tests::TestCase {
public:
	wilcot::os::Path tempPath;

	void tearDown() {
		if (wilcot::os::isDirectory(tempPath)) {
			wilcot::os::recursiveRemoveDirectory(tempPath);
		}
	}

	void testBinLs() {
		wilcot::lxc::Container container(tempPath);
		std::vector<std::string> arguments;
		arguments.push_back("/bin/ls");
		arguments.push_back("-al");
		container.setProgram("/bin/ls");
		container.setArguments(arguments);
		container.addBindMount("/bin", "/bin", true);
		container.addBindMount("/lib", "/lib", true);
		if (wilcot::os::pathExists("/lib64")) {
			container.addBindMount("/lib64", "/lib64", true);
		}
		container.start();
		container.wait();
		ASSERT(container.getExitCode() == 0);
	}

	ContainerTestCase() : tempPath("/tmp/wilcotcpp-test") {
		ADD_TEST(ContainerTestCase, testBinLs);
	}
};

ADD_TEST_CASE(ContainerTestCase);
