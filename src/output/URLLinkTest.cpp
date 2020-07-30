#include "ARInsideTest.h"
#include "URLLink.h"

#include "FileNaming.h"
#include "IFileStructure.h"
#include "ImageTag.h"
#include "WebUtil.h"

#include "../test/fakes/FakeARServerObject.h"

using namespace testing;
using namespace OUTPUT;

const int rootLevel = 1; // we use rootLevel 1 in most cases

class URLLinkTests : public Test
{
public:
	// TODO: replace the following with a fake implementation!!
	OUTPUT::FileNaming::ObjectNameFileNamingStrategy defaultFileNaming;
	
	void SetUp() 
	{
		SetFileNamingStrategy(&defaultFileNaming);
		CWebUtil::webpageFileExtension = "htm";
	}

	void TearDown()
	{
		CWebUtil::webpageFileExtension = "";
	}
};

TEST_F(URLLinkTests, BasicMainSelfLink)
{
	CPageParams page(PAGE_MAINHOME);
	ImageTag image(ImageTag::NoImage, rootLevel);

	stringstream strm;
	strm << URLLink("LinkCaption", page, image, rootLevel, false, URLLink::TARGET_MODE_SELF);
	string result = strm.str();

	ASSERT_STREQ("<a href=\"../index.htm\">LinkCaption</a>", result.c_str());
}

TEST_F(URLLinkTests, MainLinkWithImageAndTarget)
{
	CPageParams page(PAGE_MAINHOME);
	ImageTag image(ImageTag::Server, rootLevel);

	stringstream strm;
	strm << URLLink("<Main Page>", page, image, rootLevel, true, URLLink::TARGET_MODE_PARENT);
	string result = strm.str();

	ASSERT_STREQ("<img src=\"../img/server.gif\" width=\"16\" height=\"16\" alt=\"server.gif\" /><a href=\"../index.htm\" target=\"_parent\">&lt;Main Page&gt;</a>", result.c_str());
}

TEST_F(URLLinkTests, MainLinkWithImageShort)
{
	stringstream strm;
	strm << URLLink("<Main Page>", PAGE_MAINHOME, ImageTag::Server, rootLevel);
	string result = strm.str();

	ASSERT_STREQ("<img src=\"../img/server.gif\" width=\"16\" height=\"16\" alt=\"server.gif\" /><a href=\"../index.htm\">&lt;Main Page&gt;</a>", result.c_str());
}

TEST_F(URLLinkTests, ObjectLinkWithImage)
{
	CFakeServerObject fakeWorkflow("TheTestObj");

	stringstream strm;
	strm << URLLink(fakeWorkflow, rootLevel);
	string result = strm.str();

	ASSERT_STREQ("<img src=\"../img/active_link.gif\" width=\"16\" height=\"16\" alt=\"active_link.gif\" /><a href=\"../active_link/TheTestObj.htm\">TheTestObj</a>", result.c_str());
}

TEST_F(URLLinkTests, ObjectFilterLinkWithImage)
{
	CFakeServerObject fakeWorkflow("TheTestObj", AR_STRUCT_ITEM_XML_FILTER);

	stringstream strm;
	strm << URLLink(fakeWorkflow, rootLevel);
	string result = strm.str();

	ASSERT_STREQ("<img src=\"../img/filter.gif\" width=\"16\" height=\"16\" alt=\"filter.gif\" /><a href=\"../filter/TheTestObj.htm\">TheTestObj</a>", result.c_str());
}

TEST_F(URLLinkTests, ObjectEscalationLinkWithoutImage)
{
	CFakeServerObject fakeWorkflow("TheTestObj", AR_STRUCT_ITEM_XML_ESCALATION);

	stringstream strm;
	strm << URLLink(fakeWorkflow, rootLevel, false);
	string result = strm.str();

	ASSERT_STREQ("<a href=\"../escalation/TheTestObj.htm\">TheTestObj</a>", result.c_str());
}

TEST_F(URLLinkTests, ObjectOverlayLink)
{
	CFakeServerObject fakeWorkflow("SampleMenu", AR_STRUCT_ITEM_XML_CHAR_MENU, AR_OVERLAY_OBJECT);
	
	stringstream strm;
	strm << URLLink(fakeWorkflow, rootLevel);
	string result = strm.str();

	ASSERT_STREQ("<img src=\"../img/overlay.gif\" style=\"background:url(../img/menu.gif)\" width=\"16\" height=\"16\" alt=\"menu.gif\" /><a href=\"../menu/SampleMenu.htm\">SampleMenu</a>", result.c_str());
}

TEST_F(URLLinkTests, SpecificCaptionForObject)
{
	// This construct is normally used for fields to show a different link name than 
	// the fields name. But currently we can't test with a field, because of the
	// CARSchema dependency of the CARField class. So we'll test with an escalation
	// instead.
	CFakeServerObject fakeWorkflow("TheTestObj", AR_STRUCT_ITEM_XML_ESCALATION);
	
	stringstream strm;
	strm << URLLink("RealTestObj", fakeWorkflow, rootLevel, false);
	string result = strm.str();

	ASSERT_STREQ("<a href=\"../escalation/TheTestObj.htm\">RealTestObj</a>", result.c_str());
}

TEST_F(URLLinkTests, NoSpecificCaptionForObject)
{
	CFakeServerObject fakeWorkflow("TheTestObj", AR_STRUCT_ITEM_XML_ESCALATION);
	
	stringstream strm;
	strm << URLLink("", fakeWorkflow, rootLevel, false);
	string result = strm.str();

	ASSERT_STREQ("<a href=\"../escalation/TheTestObj.htm\">TheTestObj</a>", result.c_str());
}

TEST_F(URLLinkTests, CheckedObject)
{
	CFakeServerObject fakeWorkflow("TheTestObj", AR_STRUCT_ITEM_XML_ESCALATION);

	stringstream strm;
	strm << CheckedURLLink(fakeWorkflow, "<p>Object is missing</p>", rootLevel);
	string result = strm.str();

	ASSERT_STREQ("<img src=\"../img/escalation.gif\" width=\"16\" height=\"16\" alt=\"escalation.gif\" /><a href=\"../escalation/TheTestObj.htm\">TheTestObj</a>", result.c_str());
}

TEST_F(URLLinkTests, CheckedObjectMissing)
{
	const char* AlternateHTMLIfObjectDoesNotExist = "<p>Object is missing</p>";
	CFakeServerObject noneExistingWorkflow;

	stringstream strm;
	strm << CheckedURLLink(noneExistingWorkflow, AlternateHTMLIfObjectDoesNotExist, rootLevel);
	string result = strm.str();

	ASSERT_STREQ(AlternateHTMLIfObjectDoesNotExist, result.c_str());
}

TEST_F(URLLinkTests, TopLinkCreation)
{
	stringstream strm;
	strm << DirectURLLink::CreateTop;
	string result = strm.str();

	ASSERT_STREQ("<a id=\"top\"></a>", result.c_str());
}

TEST_F(URLLinkTests, LinkToTop)
{
	stringstream strm;
	strm << DirectURLLink(DirectURLLink::LinkToTop, rootLevel);
	string result = strm.str();

	ASSERT_STREQ("<img src=\"../img/up.gif\" width=\"14\" height=\"10\" alt=\"up.gif\" /><a href=\"#top\">Top</a>", result.c_str());
}

TEST_F(URLLinkTests, LinkToJavascriptVoid)
{
	stringstream strm;
	strm << DirectURLLink(DirectURLLink::JavascriptVoid, "JSLink", rootLevel);
	string result = strm.str();

	ASSERT_STREQ("<a href=\"javascript:void(0)\">JSLink</a>", result.c_str());
}
