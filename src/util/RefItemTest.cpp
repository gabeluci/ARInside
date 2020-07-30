#include "ARInsideTest.h"
#include "RefItem.h"

TEST(ARefItem, WhenEmpty)
{
	CRefItem refItem;

	ASSERT_EQ(-1, refItem.GetMessageId());
	ASSERT_EQ(-1, refItem.GetObjectId());
	ASSERT_EQ(AR_STRUCT_ITEM_XML_NONE, refItem.GetObjectType());
}

TEST(ARefItem, StaysEmptyWhenSourceOfCopyIsEmpty)
{
	CRefItem emptyRefItem;
	CRefItem copy(emptyRefItem, 1);

	ASSERT_EQ(-1, copy.GetMessageId());
	ASSERT_EQ(-1, copy.GetObjectId());
	ASSERT_EQ(AR_STRUCT_ITEM_XML_NONE, copy.GetObjectType());
}
