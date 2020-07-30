#include "ARInsideTest.h"
#include "ObjNotFound.h"

TEST(ObjNotFoundTests, BasicCreation)
{
	stringstream strm;
	strm << "Object: ";

	ObjNotFound notFound(strm);
	notFound << "TestObjName";
	notFound.End();

	strm << "<br/>";

	string result = strm.str();

	ASSERT_STREQ("Object: <span class=\"fieldNotFound\">TestObjName</span><br/>", result.c_str());
}
