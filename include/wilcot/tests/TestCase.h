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
	void addTest(const std::string& name, void (T::*method)()) {
		tests_.push_back(
			new Test_<T>(name, dynamic_cast<T*>(this), method));
	}

	virtual void setUp();

	virtual void tearDown();

	void assert(bool result);
};

}}

#endif // _HEADER_wilcot_tests_TestCase
