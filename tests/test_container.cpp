#include <cassert>
#include <cstdlib>

#include <wilcot/guard/Container.h>

int main(int argc, char *argv[])
{
	wilcot::guard::Container container;

	container.start();
	container.wait();

	return EXIT_SUCCESS;
}
