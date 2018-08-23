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
		registerTest(testCreateContainer);
	}
};

REGISTER_TEST_CASE(ContainerTestCase)