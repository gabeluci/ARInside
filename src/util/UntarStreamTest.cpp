#include "ARInsideTest.h"
#include "UntarStream.h"
#include "UntarStreamTest.h"
#include "../gzstream.h"

TEST(UntarStreamTests, DISABLED_CodeGenerator)
{
	ifstream input("E:\\Programm\\work\\arinside\\test\\test.tar", ios_base::in | ios_base::binary);

	int curLineWidth = 0;	
	int c = 0;

	while (input)
	{
		if (curLineWidth > 120)
		{
			cout << endl;
			curLineWidth = 0;
		}

		input.read(reinterpret_cast<char*>(&c), 1);
		cout << "0x" << hex << setw(2) << setfill('0') << int(c) << ", ";
		
		curLineWidth += 6;
	}
}

TEST(UntarStreamTests, ExtractTest)
{
	fixed_size_memory_buf buf(test_tar_file_content, sizeof test_tar_file_content);
	istream input(&buf);

	UntarStreamToMemory untar(input);
	untar.ExtractAllTo("memory");

#ifdef WIN32
	ASSERT_EQ(1, untar.dirNames.size());
	ASSERT_STREQ("memory\\test/", untar.dirNames[0].c_str());

	ASSERT_EQ(2, untar.fileNames.size());
	ASSERT_STREQ("memory\\test/file1.txt", untar.fileNames[0].c_str());
	ASSERT_STREQ("memory\\test/file2.txt", untar.fileNames[1].c_str());

	ASSERT_EQ(2, untar.fileContent.size());
	ASSERT_STREQ("Content of file 1", untar.fileContent[0].c_str());
	ASSERT_STREQ("Content of file 2\n", untar.fileContent[1].c_str());
#else
	ASSERT_EQ(1, untar.dirNames.size());
	ASSERT_STREQ("memory/test/", untar.dirNames[0].c_str());

	ASSERT_EQ(2, untar.fileNames.size());
	ASSERT_STREQ("memory/test/file1.txt", untar.fileNames[0].c_str());
	ASSERT_STREQ("memory/test/file2.txt", untar.fileNames[1].c_str());

	ASSERT_EQ(2, untar.fileContent.size());
	ASSERT_STREQ("Content of file 1", untar.fileContent[0].c_str());
	ASSERT_STREQ("Content of file 2\n", untar.fileContent[1].c_str());
#endif
}

TEST(UntarStreamTests, DISABLED_ExtractFailTest)
{
	fixed_size_memory_buf buf(test_tar_file_content, sizeof test_tar_file_content);
	istream input(&buf);

	UntarStreamToMemory untar(input);
	untar.theFilesAlreadyExist = true;

	try
	{
		untar.ExtractAllTo("memory");
	}
	catch (untar_exception &untarEx)
	{
		ASSERT_STREQ("writing destination file failed: code=17, File exists", untarEx.what());
	}
}

TEST(UntarStreamTests, ExtractFilesystem)
{
	fixed_size_memory_buf buf(test_tar_file_content, sizeof test_tar_file_content);
	istream input(&buf);

	UntarStreamToMemory untar(input);
	untar.theFilesAlreadyExist = true;
	untar.ExtractAllTo(".", UntarStream::SKIP);
}

TEST(UntarExceptionTests, ThrowRead)
{
	try
	{
		errno = 2; // no such file or directory
		throw untar_exception(untar_exception::READ);
	}
	catch (exception &ex)
	{
		ASSERT_STREQ("reading source file failed: code=2, No such file or directory", ex.what());
	}
}

TEST(UntarExceptionTests, ThrowRead_Without_errno)
{
	try
	{
		errno = 0; // set to zero .. might be the default value
		throw untar_exception(untar_exception::READ);
	}
	catch (exception &ex)
	{
		ASSERT_STREQ("reading source file failed", ex.what());
	}
}

TEST(UntarExceptionTests, ThrowWrite)
{
	try
	{
		errno = 13; // permission denied
		throw untar_exception(untar_exception::WRITE);
	}
	catch (exception &ex)
	{
		ASSERT_STREQ("writing destination file failed: code=13, Permission denied", ex.what());
	}
}

TEST(UntarExceptionTests, ThrowWrite_Without_errno)
{
	try
	{
		errno = 0; // set to zero .. might be the default value
		throw untar_exception(untar_exception::WRITE);
	}
	catch (exception &ex)
	{
		ASSERT_STREQ("writing destination file failed", ex.what());
	}
}

TEST(UntarExceptionTests, ThrowGeneric)
{
	try
	{
		errno = 28; // no space left on device
		throw untar_exception();
	}
	catch (exception &ex)
	{
		ASSERT_STREQ("generic untar exception: code=28, No space left on device", ex.what());
	}
}

TEST(UntarExceptionTests, ThrowGeneric_Without_errno)
{
	try
	{
		errno = 0; // set to zero .. might be the default value
		throw untar_exception();
	}
	catch (exception &ex)
	{
		ASSERT_STREQ("generic untar exception", ex.what());
	}
}

