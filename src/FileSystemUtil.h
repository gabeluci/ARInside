//Copyright (C) 2009 Stefan Nerlich | stefan.nerlich@hotmail.com
//
//This file is part of ARInside.
//
//    ARInside is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, version 2 of the License.
//
//    ARInside is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with ARInside.  If not, see <http://www.gnu.org/licenses/>.

#pragma once
#include "AppConfig.h"

#ifdef WIN32
#define ARINSIDE_PATH_SEPARATOR "\\"
#else
#define ARINSIDE_PATH_SEPARATOR "/"
#endif

class FileSystemUtil
{
public:
	FileSystemUtil(AppConfig &appConfig);
	~FileSystemUtil(void);

	bool CreateAppDirectory();
	int CreateSubDirectory(string name);

	static int ValidateTargetDir(std::string targetFolder);
	static std::string GetRealPathName(const std::string &path);
	static bool FileExistsAndReadable(const std::string &filename);
	static bool DeleteDirectory(const char* sPath, bool topLevel = true);
	static bool IsDots(const char* str);
	static void CompactFolder(std::string path);
	static std::string GetExecutableDirectory(const char* argv_0);
	static std::string CombinePath(const std::string &path1, const std::string &path2);
#if WIN32
	static std::string GetFormattedMessage(unsigned int error);
#endif

private:
	AppConfig &appConfig;
};
