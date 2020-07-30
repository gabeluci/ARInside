#include "ARInsideTest.h"
#include "OpenWindowReportData.h"

using namespace testing;

char* testReportString = "Report: \00121=AR System\00122=\00129=\00127=\00128=null\00124=\00125=\00126=\00130=0\00131=\00132=true\001\nto-screen: ";

// A fixture class with a instance of OpenWindowReportData using the testReportString above
class OpenWindowReportDataTests : public Test
{
public:
	OpenWindowReportDataTests() : reportData(testReportString) {}

protected:
	OpenWindowReportData reportData;
};

// verify the testReportString above is valid for the parser
TEST_F(OpenWindowReportDataTests, ValidInput)
{
	ASSERT_TRUE(reportData.IsValid());
}

// now just verify a few values we've in the report string
TEST_F(OpenWindowReportDataTests, VerifyReportType)
{
	string result = reportData.getReportType();
	ASSERT_STREQ("AR System", result.c_str());
}

TEST_F(OpenWindowReportDataTests, VerifyReportName)
{
	string result = reportData.getReportName();
	ASSERT_STREQ("", result.c_str());
}

TEST_F(OpenWindowReportDataTests, VerifyQueryOverride)
{
	string result = reportData.getQueryOverride();
	ASSERT_STREQ("null", result.c_str());
}

TEST_F(OpenWindowReportDataTests, VerifyReportDestination)
{
	string result = reportData.getReportDestination();
	ASSERT_STREQ("to-screen: ", result.c_str());
}

TEST_F(OpenWindowReportDataTests, VerifyInlineForm)
{
	string result = reportData.getInlineForm();
	ASSERT_STREQ("true", result.c_str());
}

// even if the property (here "Report Name") is not in the (valid) report, it shouldn't fail
TEST_F(OpenWindowReportDataTests, TryToReadAValueNotInTheReportString)
{
	char* mostlyEmptyReport = "Report: \00121=AR System\001\nto-screen: ";
	OpenWindowReportData reportData(mostlyEmptyReport);

	string result = reportData.getReportName();
	ASSERT_STREQ("", result.c_str());
}

// if the report is simply invalid, it shouldn't fail as well
TEST_F(OpenWindowReportDataTests, TryToReadAValueFromInvalidReport)
{
	char* invalidReport = "WrongReport: \001";
	OpenWindowReportData reportData(invalidReport);

	string result = reportData.getReportDestination();
	ASSERT_STREQ("", result.c_str());
}
