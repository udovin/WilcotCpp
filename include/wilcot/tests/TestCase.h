#ifndef _HEADER_wilcot_tests_TestCase
#define _HEADER_wilcot_tests_TestCase

#include <wilcot/Object.h>

#include <string>
#include <vector>

namespace wilcot { namespace tests {

class TestCase : public Object {
private:
	struct ITest_ {
		std::string name;

		ITest_(const std::string& name) : name(name) {}

		virtual ~ITest_() {}

		virtual void invoke() const = 0;
	};

	template<class T>
	struct Test_ : public ITest_ {
		T* object;
		void (T::*method)();

		Test_(T* object, void (T::*method)(), const std::string& name)
			: ITest_(name), object(object), method(method) {}

		void invoke() const {
			(object->*method)();
		}
	};

	struct Failure_ {
		std::string code;
		std::size_t line;

		Failure_(const std::string& code, std::size_t line)
			: code(code), line(line) {}
	};

	std::vector<ITest_*> tests_;

public:
	~TestCase();

	TestCase& run();

protected:
	TestCase();

	virtual void setUp();

	virtual void tearDown();

	template<class T>
	void addTest__(void (T::*method)(), const std::string& name) {
		tests_.push_back(
			new Test_<T>(dynamic_cast<T*>(this), method, name)
		);
	}

	void assert__(bool result, const std::string& code, std::size_t line);
};

}}

#define ADD_TEST_CASE(Class) \
	int main(int argc, char* argv[]) { \
		Class().run(); \
		return 0; \
	} \
	class Main__ {}

#define ADD_TEST(Class, method) \
	addTest__(&Class::method, #method)

#define ASSERT(expression) \
	assert__(expression, #expression, __LINE__)

#endif // _HEADER_wilcot_tests_TestCase
