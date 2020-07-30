#include "ARInsideTest.h"
#include "rapidjson/document.h"
#include "rapidjson/filestream.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/genericwritestream.h"

using namespace rapidjson;

TEST(RapidJSONTests, GenerateArray)
{
	Document document;
	Document::AllocatorType& allocator = document.GetAllocator();

	document.SetArray();
	ASSERT_TRUE(document.IsArray());

	document.PushBack("Test1", allocator);
	document.PushBack("Test2", allocator);

	Value item;
	item.SetObject();
	item.AddMember("Id", 1, allocator);
	item.AddMember("Name", "ARInside", allocator);
	document.PushBack(item, allocator);

	// check array size
	ASSERT_EQ(3, document.Size());

	FileStream f(stdout);
	Writer<FileStream> writer(f);
	document.Accept(writer);
	cout << endl;
}

TEST(RapidJSONTests, CreateInMemoryStream)
{
	Document document;
	Document::AllocatorType& allocator = document.GetAllocator();

	document.SetArray();
	ASSERT_TRUE(document.IsArray());

	document.PushBack("Test1", allocator);
	document.PushBack("Test2", allocator);

	Value item;
	item.SetObject();
	item.AddMember("Id", 1, allocator);
	item.AddMember("Name", "ARInside", allocator);
	document.PushBack(item, allocator);

	// check array size
	ASSERT_EQ(3, document.Size());

	stringstream strm;
	GenericWriteStream output(strm);
	Writer<GenericWriteStream> writer(output);
	document.Accept(writer);

	string result = strm.str();
	ASSERT_EQ("[\"Test1\",\"Test2\",{\"Id\":1,\"Name\":\"ARInside\"}]", result);
}

string generateRapidJsonValueString(int num)
{
	stringstream strm;
	strm << "Value" << num;
	return strm.str();
}

TEST(RapidJSONTests, AllocatorTest)
{
	Document document;
	Document::AllocatorType& allocator = document.GetAllocator();

	document.SetArray();
	ASSERT_TRUE(document.IsArray());

	for (int i = 0; i < 3; i++)
	{
		string value = generateRapidJsonValueString(i);
		Value item(value.c_str(), value.size(), allocator);
		document.PushBack(item, allocator);
	}

	stringstream strm;
	GenericWriteStream output(strm);
	Writer<GenericWriteStream> writer(output);
	document.Accept(writer);

	string result = strm.str();
	ASSERT_EQ("[\"Value0\",\"Value1\",\"Value2\"]",result);
}

