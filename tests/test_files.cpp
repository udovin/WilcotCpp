/**
 * @author Ivan Udovin
 * @license MIT
 */

#include <wilcot/tests/TestCase.h>

#include <wilcot/os/files.h>
#include <wilcot/os/Path.h>

#include <algorithm>
#include <iostream>

class FileTestCase : public wilcot::tests::TestCase {
public:
	wilcot::os::Path tempPath;

	void tearDown() {
		if (wilcot::os::isFile(tempPath)) {
			wilcot::os::removeFile(tempPath);
		}
		if (wilcot::os::isDirectory(tempPath)) {
			wilcot::os::recursiveRemoveDirectory(tempPath);
		}
	}

	void testCreateFile() {
		ASSERT(!wilcot::os::pathExists(tempPath));
		wilcot::os::createFile(tempPath);
		ASSERT(wilcot::os::pathExists(tempPath));
		ASSERT(wilcot::os::isFile(tempPath));
		ASSERT(!wilcot::os::isDirectory(tempPath));
	}

	void testCreateDirectory() {
		ASSERT(!wilcot::os::pathExists(tempPath));
		wilcot::os::createDirectory(tempPath);
		ASSERT(wilcot::os::pathExists(tempPath));
		ASSERT(!wilcot::os::isFile(tempPath));
		ASSERT(wilcot::os::isDirectory(tempPath));
	}

	void testListDirectory() {
		wilcot::os::createDirectory(tempPath);

		ASSERT(wilcot::os::listDirectory(tempPath).empty());

		wilcot::os::createFile(tempPath / "test_file");
		wilcot::os::createDirectory(tempPath / "test_directory");

		std::vector<wilcot::os::Path> list;
		list.push_back("test_file");
		list.push_back("test_directory");

		std::vector<wilcot::os::Path> children
			= wilcot::os::listDirectory(tempPath);

		for (std::size_t i = 0; i < children.size(); i++) {
			std::vector<wilcot::os::Path>::const_iterator it
				= std::find(list.begin(), list.end(), children[i]);
			ASSERT(it != list.end());
		}
	}

	FileTestCase() : tempPath("/tmp/wilcotcpp-test") {
		ADD_TEST(FileTestCase, testCreateFile);
		ADD_TEST(FileTestCase, testCreateDirectory);
		ADD_TEST(FileTestCase, testListDirectory);
	}
};

ADD_TEST_CASE(FileTestCase);
