#ifndef HEADER_wilcot_tests_TestCase
#define HEADER_wilcot_tests_TestCase

#include <wilcot/Object.h>

#include <string>
#include <vector>

namespace wilcot { namespace tests {

class TestCase : public Object {
private:
	struct ITest_ {
		std::string name;

		ITest_(const std::string& name) : name(name) {}

		virtual ~ITest_() {};

		virtual void invoke() const = 0;
	};

	template<class T>
	struct Test_ : public ITest_ {
		T* object;

		void (T::*method)();

		Test_(const std::string& name, T* object, void (T::*method)())
			: ITest_(name), object(object), method(method) {}

		void invoke() const {
			(object->*method)();
		}
	};

	struct Assert_ {};

	std::vector<ITest_*> tests_;

public:
	~TestCase();

	TestCase& run();

protected:
	TestCase();

	template<class T>
	void registerTest(const std::string& name, void (T::*method)()) {
		tests_.push_back(
			new Test_<T>(name, dynamic_cast<T*>(this), method));
	}

	virtual void setUp();

	virtual void tearDown();

	void assert(bool result);
};

#define REGISTER_TEST(method) \
	do { \
		registerTest(#method, method); \
	} while (false)

#define REGISTER_TEST_CASE(TestCase) \
	int main(int argc, char* argv[]) { \
		TestCase().run(); \
		return 0;\
	}

}}

#endif // HEADER_wilcot_tests_TestCase