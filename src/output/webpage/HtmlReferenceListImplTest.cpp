#include "ARInsideTest.h"
#include "HtmlReferenceListImpl.h"

using namespace OUTPUT::WebPage;

TEST(HtmlReferenceListImplTest, Basic)
{
	stringstream output;
	HtmlReferenceListImpl refList(0);

	refList.AddScriptReference("jquery.js");
	refList.AddStyleSheetReference("page.css");

	output << refList;
	ASSERT_FALSE(output.str().empty());
}

TEST(HtmlReferenceListImplTest, ValidateScriptOutput)
{
	stringstream output;
	HtmlReferenceListImpl refList(0);

	refList.AddScriptReference("jquery.js");

	output << refList;
	ASSERT_EQ("<script src=\"jquery.js\" type=\"text/javascript\"></script>\n", output.str());
}

TEST(HtmlReferenceListImplTest, ValidateStylesheetOutput)
{
	stringstream output;
	HtmlReferenceListImpl refList(0);

	refList.AddStyleSheetReference("page.css");

	output << refList;
	ASSERT_EQ("<link rel=\"stylesheet\" type=\"text/css\" href=\"page.css\" />\n", output.str());
}
