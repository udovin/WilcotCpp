/**
 * @author Ivan Udovin
 * @license MIT
 */

#include <wilcot/tests/TestCase.h>
#include <wilcot/lxc/Container.h>
#include <wilcot/os/files.h>
#include <wilcot/io/FileStream.h>
#include <wilcot/io/Writer.h>
#include <wilcot/io/Reader.h>

class ContainerTestCase : public wilcot::tests::TestCase {
protected:
	wilcot::os::Path tempPath;

	void setUp() {
		wilcot::os::createDirectories(tempPath);
	}

	void tearDown() {
		if (wilcot::os::isDirectory(tempPath)) {
			wilcot::os::recursiveRemoveDirectory(tempPath);
		}
	}

	void testBinLs() {
		wilcot::lxc::Container container(tempPath / "container");
		std::vector<std::string> arguments;
		arguments.push_back("/bin/ls");
		arguments.push_back("-al");
		container.setProgram("/bin/ls");
		container.setArguments(arguments);
#ifdef WILCOT_OS_LINUX
		container.addBindMount("/bin", "/bin", true);
		container.addBindMount("/lib", "/lib", true);
		if (wilcot::os::pathExists("/lib64")) {
			container.addBindMount("/lib64", "/lib64", true);
		}
#endif
		container.start();
		container.wait();
		ASSERT(container.getExitCode() == 0);
	}

	void testShell() {
		wilcot::lxc::Container container(tempPath / "container");
		std::vector<std::string> arguments;
		arguments.push_back("/bin/sh");
		container.setProgram("/bin/sh");
		container.setArguments(arguments);
#ifdef WILCOT_OS_LINUX
		container.addBindMount("/bin", "/bin", true);
		container.addBindMount("/lib", "/lib", true);
		if (wilcot::os::pathExists("/lib64")) {
			container.addBindMount("/lib64", "/lib64", true);
		}
#endif
		{
			wilcot::io::FileStream inputFileStream(
				tempPath / "input",
				wilcot::io::FileStream::WRITE
			);
			wilcot::io::Writer inputWriter(inputFileStream);
			inputWriter << "echo 'qwerty123'\n";
		}
		{
			wilcot::io::FileStream inputStream(
				tempPath / "input",
				wilcot::io::FileStream::READ
			);
			wilcot::io::FileStream outputStream(
				tempPath / "output",
				wilcot::io::FileStream::WRITE
			);
			container.setStandardInput(inputStream);
			container.setStandardOutput(outputStream);
			container.start();
			container.wait();
		}
		ASSERT(container.getExitCode() == 0);
		wilcot::io::FileStream outputFileStream(
			tempPath / "output",
			wilcot::io::FileStream::READ
		);
		std::string answer;
		wilcot::io::Reader outputReader(outputFileStream);
		outputReader >> answer;
		ASSERT(answer == "qwerty123");
	}

public:
	ContainerTestCase() : tempPath("/tmp/wilcotcpp-test-container") {
		ADD_TEST(ContainerTestCase, testBinLs);
		ADD_TEST(ContainerTestCase, testShell);
	}
};

ADD_TEST_CASE(ContainerTestCase);
