//Copyright (C) 2013 John Luthgers | jls17
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

#include "stdafx.h"
#include "ResourceFileLocatorAndExtractor.h"
#include "UntarStream.h"
#include "../AppException.h"
#include "../ARInside.h"
#include "../FileSystemUtil.h"
#include "../gzstream.h"


ResourceFileLocatorAndExtractor::ResourceFileLocatorAndExtractor(const std::string &resourceFilename)
: resFile(resourceFilename)
{
}

ResourceFileLocatorAndExtractor::~ResourceFileLocatorAndExtractor()
{
}

bool ResourceFileLocatorAndExtractor::ExtractTo(const std::string &targetDir)
{
	char* envInstallDir = getenv("ARINSIDE_INSTALL_DIR");

	string directory;

	// if the environment var is set, use it and check if it is a real path
	if (envInstallDir != NULL && envInstallDir[0] != 0)
	{
		directory = FileSystemUtil::GetRealPathName(envInstallDir);
	}
	
	// if the directory variable is still empty, try to use the path to the current executable
	if (directory.empty())
	{
		directory = FileSystemUtil::GetRealPathName(FileSystemUtil::GetExecutableDirectory(CARInside::GetInstance()->appConfig.argv_0.c_str()));
	}

	// still empty, then we don't know where to look
	if (directory.empty())
	{
		throw AppException("Couldn't detect directory of resource file!");
	}

	// check if the file to extract exists
	string resourceFile = FileSystemUtil::CombinePath(directory, resFile);
	if (!FileSystemUtil::FileExistsAndReadable(resourceFile))
	{
		throw untar_exception(untar_exception::READ);
	}

	// now extract the content
	igzstream unzipStrm(resourceFile.c_str());
	UntarStream untarStrm(unzipStrm);
	untarStrm.ExtractAllTo(targetDir, UntarStream::REPLACE);

	return true;
}
