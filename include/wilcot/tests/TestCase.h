/**
 * @author Ivan Udovin
 * @license MIT
 */

#ifndef HEADER_wilcot_tests_TestCase
#define HEADER_wilcot_tests_TestCase

#include <wilcot/Object.h>

#include <string>
#include <vector>

namespace wilcot { namespace tests {

/**
 * Class TestCase
 *
 * @since 0.0.1
 */
class TestCase : public Object {
private:
	struct ITest_ {
		std::string name_;

		virtual ~ITest_() {}

		ITest_(const std::string& name) : name_(name) {}

		virtual void invoke() const = 0;
	};

	template<class T>
	struct Test_ : public ITest_ {
		T* object_;
		void (T::*method_)();

		Test_(T* object, void (T::*method)(), const std::string& name)
			: ITest_(name), object_(object), method_(method) {}

		void invoke() const {
			(object_->*method_)();
		}
	
	private:
		Test_(const Test_<T>& other);

		Test_& operator=(const Test_<T>& other);
	};

	struct Failure_ {
		std::string code_;
		std::size_t line_;

		Failure_(const std::string& code, std::size_t line)
			: code_(code), line_(line) {}
	};

	/**
	 * @since 0.0.1
	 */
	std::vector<ITest_*> tests_;

public:
	/**
	 * TestCase destructor
	 *
	 * @since 0.0.1
	 */
	~TestCase();

	/**
	 * @return
	 *
	 * @since 0.0.1
	 */
	TestCase& run();

protected:
	/**
	 * TestCase constructor
	 *
	 * @since 0.0.1
	 */
	TestCase();

	/**
	 * @since 0.0.1
	 */
	virtual void setUp();

	/**
	 * @since 0.0.1
	 */
	virtual void tearDown();

	template<class T>
	void addTest_(void (T::*method)(), const std::string& name) {
		tests_.push_back(
			new Test_<T>(dynamic_cast<T*>(this), method, name)
		);
	}

	void assert_(bool result, const std::string& code, std::size_t line);
};

}}

#define ADD_TEST_CASE(Class) \
	int main(int argc, char* argv[]) { \
		(void) argc; \
		(void) argv; \
		Class().run(); \
		return 0; \
	} \
	class Main__ {}

#define ADD_TEST(Class, method) \
	addTest_(&Class::method, #method)

#define ASSERT(expression) \
	assert_(expression, #expression, __LINE__)

#endif // HEADER_wilcot_tests_TestCase
