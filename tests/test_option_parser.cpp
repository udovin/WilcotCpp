/**
 * @author Ivan Udovin
 * @license MIT
 */

#include <wilcot/tests/TestCase.h>
#include <wilcot/cli/OptionParser.h>
#include <iostream>

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
		int argc = 1;
		const char* argv[] = {
			"--help"
		};
		parser.parse(argc, argv);
	}

public:
	OptionParserTestCase() {
		ADD_TEST(OptionParserTestCase, testCreate);
	}
};

ADD_TEST_CASE(OptionParserTestCase);
