/**
 * @author Ivan Udovin
 * @license MIT
 */

#include <wilcot/tests/TestCase.h>
#include <wilcot/cli/OptionParser.h>
#include <wilcot/cli/Argument.h>
#include <string>

class OptionParserTestCase : public wilcot::tests::TestCase {
protected:
	void testCreate() {
		wilcot::cli::OptionParser parser;
		std::vector<std::string> helpNames;
		helpNames.push_back("--help");
		helpNames.push_back("-h");
		wilcot::cli::Option helpOption(helpNames);
		helpOption.setDescription("Show this help");
		parser.addOption(helpOption);
		const char* argv[] = {
			"program", "--help"
		};
		parser.parse(sizeof(argv) / sizeof(const char*), argv);
	}

	void testIntegerArgument() {
		wilcot::cli::OptionParser parser;
		wilcot::cli::Option numberOption("--number");
		wilcot::cli::Argument<int> number;
		numberOption.setArgument(number);
		parser.addOption(numberOption);
		const char* argv1[] = {
			"program", "--number", "12345"
		};
		parser.parse(sizeof(argv1) / sizeof(const char*), argv1);
		ASSERT(static_cast<int>(number) == 12345);
		const char* argv2[] = {
			"program", "--number", "-54321"
		};
		parser.parse(sizeof(argv2) / sizeof(const char*), argv2);
		ASSERT(static_cast<int>(number) == -54321);
		const char* argv3[] = {
			"program", "--number", "not_a_number"
		};
		try {
			parser.parse(sizeof(argv3) / sizeof(const char*), argv3);
			ASSERT(false);
		} catch(const std::exception& exc) {
			ASSERT(true);
		}
	}

	void testStringArgument() {
		wilcot::cli::OptionParser parser;
		wilcot::cli::Option stringOption("--string");
		wilcot::cli::Argument<std::string> string;
		stringOption.setArgument(string);
		parser.addOption(stringOption);
		const char* argv1[] = {
			"program", "--string", "simple_string"
		};
		parser.parse(sizeof(argv1) / sizeof(const char*), argv1);
		ASSERT(static_cast<std::string>(string) == argv1[2]);
		const char* argv2[] = {
			"program", "--string", "string with spaces"
		};
		parser.parse(sizeof(argv2) / sizeof(const char*), argv2);
		ASSERT(static_cast<std::string>(string) == argv2[2]);
	}

public:
	OptionParserTestCase() {
		ADD_TEST(OptionParserTestCase, testCreate);
		ADD_TEST(OptionParserTestCase, testIntegerArgument);
		ADD_TEST(OptionParserTestCase, testStringArgument);
	}
};

ADD_TEST_CASE(OptionParserTestCase);
