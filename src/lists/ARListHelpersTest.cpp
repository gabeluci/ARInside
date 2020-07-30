#include "ARInsideTest.h"
#include "ARListHelpers.h"

TEST(GenerateSortableList, VectorOfStringsTest)
{
	vector<string> testList;
	testList.push_back("Demo");
	testList.push_back("  Test");

	GenerateSortableList sortableContent(testList);

	ARNameList* list = sortableContent.GetList();
	ASSERT_EQ(2, list->numItems);
	ASSERT_STREQ("demo", list->nameList[0]);
	ASSERT_STREQ("test", list->nameList[1]);
}
