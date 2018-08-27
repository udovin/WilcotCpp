/**
 * @author Ivan Udovin
 * @license MIT
 */

#include <wilcot/tests/TestCase.h>

#include <wilcot/guard/Container.h>

class ContainerTestCase : public wilcot::tests::TestCase {
public:
	void testCreateContainer() {
		wilcot::guard::Container container;
	}

	ContainerTestCase() {
		addTest("testCreateContainer", &ContainerTestCase::testCreateContainer);
	}
};

int main(int argc, char* argv[]) {
	ContainerTestCase().run();
	return 0;
}
