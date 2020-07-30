#include "ARInsideTest.h"
#include "FileSystemUtil.h"
#include "FileSystemUtilTest.h"

TEST(FileSystemUtil, IsDots_WithDots_Test)
{
	ASSERT_EQ(true, FileSystemUtil::IsDots("."));
	ASSERT_EQ(true, FileSystemUtil::IsDots(".."));
}

TEST(FileSystemUtil, IsDots_WithoutDots_Test)
{
	ASSERT_EQ(false, FileSystemUtil::IsDots("testfile"));
}

TEST(FileSystemUtil, GetExecutableDirectory)
{
	string directory = FileSystemUtil::GetExecutableDirectory(argv_0);
	directory = FileSystemUtil::GetRealPathName(directory);

	string expectedDir = DIRECTORY_OF_TEST_BINARY;
#ifdef WIN32
	expectedDir = CUtil::StrReplace("/","\\", expectedDir);
	std::transform(directory.begin(), directory.end(), directory.begin(), ::tolower);
	std::transform(expectedDir.begin(), expectedDir.end(), expectedDir.begin(), ::tolower);
#endif

	ASSERT_STREQ(expectedDir.c_str(), directory.c_str());
}

TEST(FileSystemUtil, CombinePathSimpleWithoutSeparator)
{
#ifdef WIN32
	string directory = FileSystemUtil::CombinePath("C:\\Windows", "Temp");
	ASSERT_STREQ("C:\\Windows\\Temp", directory.c_str());
#else
	string directory = FileSystemUtil::CombinePath("/c/Windows", "Temp");
	ASSERT_STREQ("/c/Windows/Temp", directory.c_str());
#endif
}

TEST(FileSystemUtil, CombinePathSimpleWithSeparator)
{
#ifdef WIN32
	string directory = FileSystemUtil::CombinePath("C:\\", "Temp");
	ASSERT_STREQ("C:\\Temp", directory.c_str());
#else
	string directory = FileSystemUtil::CombinePath("/tmp/", "test_dir");
	ASSERT_STREQ("/tmp/test_dir", directory.c_str());
#endif
}

TEST(FileSystemUtil, CombinePathSecondPathStartsWithRootDir)
{
#ifdef WIN32
	string directory = FileSystemUtil::CombinePath("C:\\Windows", "\\Temp");
	ASSERT_STREQ("\\Temp", directory.c_str());
#else
	string directory = FileSystemUtil::CombinePath("/tmp/", "/test_dir");
	ASSERT_STREQ("/test_dir", directory.c_str());
#endif
}

#ifdef WIN32
TEST(FileSystemUtil, CombinePathSecondPathStartsWithRootDir2)
{
	string directory = FileSystemUtil::CombinePath("C:\\Windows", "/Temp");
	ASSERT_STREQ("/Temp", directory.c_str());
}
#endif

TEST(FileSystemUtil, CombinePathWithMixedSeparators)
{
#ifdef WIN32
	string directory = FileSystemUtil::CombinePath("C:/Windows/Temp", "MyDir");
	ASSERT_STREQ("C:/Windows/Temp\\MyDir", directory.c_str());
#else
	string directory = FileSystemUtil::CombinePath("/tmp\\", "MyDir");
	ASSERT_STREQ("/tmp\\/MyDir", directory.c_str());
#endif
}
