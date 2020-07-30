#include "ARInsideTest.h"
#include "CommandLineValidator.h"

TEST(CommandLineValidatorTest, MinimalArguments)
{
	int argc = 3;
	char* argv[] = { "program", "-i", "test.ini" };

	CommandLineValidator validator(argc, argv);
	ASSERT_TRUE(validator.Validate());
}

TEST(CommandLineValidatorTest, AllArgumentMappings)
{
	int argc = 15;
	char* argv[] = { "program", 
		"-i", "test.ini", 
		"-s", "myTestServer",
		"-l", "AccountName",
		"-p", "pwd",
		"-t", "4321",
		"-r", "390680", 
		"-o", "/tmp/arinside.run/",
	};

	CommandLineValidator validator(argc, argv);
	ASSERT_TRUE(validator.Validate());
	ASSERT_EQ("test.ini", validator.GetIniFilename());
	ASSERT_EQ("myTestServer", validator.GetServer());
	ASSERT_EQ("AccountName", validator.GetUsername());
	ASSERT_EQ("pwd", validator.GetPassword());
	ASSERT_EQ(4321, validator.GetTcpPort());
	ASSERT_EQ(390680, validator.GetRpcPort());
}

TEST(CommandLineValidatorTest, MissingArgument)
{
	int argc = 1;
	char* argv[] = { "program" };

	CommandLineValidator validator(argc, argv);
	ASSERT_EXIT(validator.Validate(), ::testing::ExitedWithCode(1), "Required argument missing");
}

TEST(CommandLineValidatorTest, DISABLED_InvalidNumericArgument)
{
	int argc = 5;
	char* argv[] = { "program", 
		"-i", "test.ini", 
		"-t", "abc",
	};

	CommandLineValidator validator(argc, argv);
	ASSERT_EXIT(validator.Validate(), ::testing::ExitedWithCode(1), "Couldn't read argument value from string 'abc'");
}

TEST(CommandLineValidatorTest, InvalidArgument)
{
	int argc = 2;
	char* argv[] = { "program", "--no-such-argument" };

	CommandLineValidator validator(argc, argv);
	ASSERT_EXIT(validator.Validate(), ::testing::ExitedWithCode(1), "PARSE ERROR: Argument: --no-such-argument");
}
