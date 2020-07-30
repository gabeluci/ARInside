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

#include "stdafx.h"
#include "resource.h"
#include "FileSystemUtil.h"
#include "AppException.h"
#include "ARApi.h"

#include <sys/types.h>
#include <sys/stat.h>

FileSystemUtil::FileSystemUtil(AppConfig &appConfig)
: appConfig(appConfig)
{
}

FileSystemUtil::~FileSystemUtil(void)
{
}

bool FileSystemUtil::CreateAppDirectory()
{
	int nResult = 
#ifdef WIN32
	_mkdir(appConfig.targetFolder.c_str());
#else
	mkdir(appConfig.targetFolder.c_str(), S_IRWXU|S_IRWXG|S_IRWXO);
#endif
	cout << "Create target directory: " << appConfig.targetFolder << " [" << (nResult == 0 ? "OK" : strerror(errno)) <<"]" << endl;	

	return (nResult==0);
}

int FileSystemUtil::CreateSubDirectory(string name)
{	
	stringstream strm;
	strm << appConfig.targetFolder << "/" << name;

	try
	{
#ifdef WIN32		
		return (_mkdir(strm.str().c_str()) == 0);
#else
		return (mkdir(strm.str().c_str(), S_IRWXU|S_IRWXG|S_IRWXO) == 0);
#endif
	}
	catch(exception& e)
	{
		cout << "Error creating directory '" << strm.str() << "': " << e.what() << endl;
	}

	return 0;
}

string FileSystemUtil::GetRealPathName(const std::string &path)
{
#ifdef WIN32
	char buffer[MAX_PATH]; buffer[0] = 0;
	LPSTR *filePos = NULL;

	DWORD len = GetFullPathName(path.c_str(), MAX_PATH, buffer, filePos);
	if (len > MAX_PATH || len == 0)
	{
		stringstream tmp;
		tmp << "Error: could not retrieve the full output path! (" << GetLastError() << ")";
		throw AppException(tmp.str(), "filesystem");			
	}
#else
	// NOTE: realpath doesn't return the full path under SunOS if a relativ path is specified.
	char buffer[PATH_MAX]; buffer[0] = 0;
	char *p;
	p = realpath(path.c_str(), buffer);
	if (p == NULL)
	{
		if (errno == ENOENT) return path;
		stringstream tmp;
		tmp << strerror(errno) << ": " << path;
		throw AppException(tmp.str(), "filesystem");			
	}
#endif
	return buffer;
}

bool FileSystemUtil::FileExistsAndReadable(const std::string &filename)
{
	bool result = false;

	try
	{
		fstream fin;
		fin.open(filename.c_str(),ios::in);
		result = fin.is_open();
		fin.close();
	}
	catch(exception& e)
	{
		cout << "EXCEPTION An error occured while checking file exists: " << e.what() << endl;
	}

	return result;
}

bool FileSystemUtil::DeleteDirectory(const char* sPath, bool topLevel)
{
#ifdef WIN32
	try
	{
		HANDLE hFind; // file handle
		WIN32_FIND_DATA FindFileData;

		char DirPath[MAX_PATH+1];
		char FileName[MAX_PATH+1];

		strncpy(DirPath, sPath, MAX_PATH);
		strncat(DirPath, "/", MAX_PATH);
		DirPath[MAX_PATH] = 0;

		strncpy(FileName, sPath, MAX_PATH);
		strncat(FileName, "/*", MAX_PATH); // searching all files
		FileName[MAX_PATH] = 0;

		hFind = FindFirstFile(FileName, &FindFileData); // find the first file
		if (hFind != INVALID_HANDLE_VALUE)
		{
			do
			{
				if (IsDots(FindFileData.cFileName))
					continue;

				strcpy(FileName + strlen(DirPath), FindFileData.cFileName);
				if((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
				{
					// we have found a directory, recurse
					LOG << "Delete " << FileName << endl;

					if( !DeleteDirectory(FileName, false) )
						break; // directory couldn't be deleted
				}
				else
				{
					if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_READONLY)
						_chmod(FileName, _S_IWRITE); // change read-only file mode

					LOG << "Delete " << FileName << endl;
					if( !DeleteFile(FileName) )
						break; // file couldn't be deleted
				}
			}

			while( FindNextFile(hFind,&FindFileData) );	
			FindClose(hFind); // closing file handle

		}
	}
	catch(exception& e)
	{
		cout << "EXCEPTION in DeleteDirectory: " << e.what() << endl; 
	}	

	return (topLevel || _rmdir(sPath)==0 ? true : false); // remove the empty (maybe not) directory
#else
	if (strlen(sPath) == 0) return false;

	// first off, we need to create a pointer to a directory
	DIR *pdir;
	pdir = opendir(sPath);
	
	struct dirent *pent = NULL;
	if (pdir == NULL)
		return false; // return false to say "we couldn't do it"

	string file;
	struct stat stats;

	while (pent = readdir(pdir)) { // while there is still something in the directory to list
		if (!IsDots(pent->d_name))
		{
			file = sPath;
			char lastChar = file.at(file.length()-1);
		  if (lastChar != '/' || lastChar != '\\') file += "/";
			file += pent->d_name;		

			if (stat(file.c_str(), &stats) != 0)
				return false;

			LOG << "Delete " << file << endl;

			if (S_ISDIR(stats.st_mode))
				DeleteDirectory(file.c_str(), false);
		else
				remove(file.c_str());
		}
	}

	// finally, let's clean up
	closedir(pdir); // close the directory
	if (!topLevel && !rmdir(sPath)) return false; // delete the directory
	return true;
#endif
}

bool FileSystemUtil::IsDots(const char* str) 
{
	if(strcmp(str,".") && strcmp(str,"..")) return false;
	return true;
}

int FileSystemUtil::ValidateTargetDir(string targetFolder)
{		
	int nResult = -1;
	try
	{
		cout << "Validating target folder: " << targetFolder << endl;

		stringstream fName;
		fName << targetFolder << "/valid.txt";

		ofstream fout( fName.str().c_str(), ios::out);
		fout << "arinside" << endl;
		fout.close();

		nResult = remove(fName.str().c_str());
	}
	catch(exception& e)
	{
		cout << "EXCEPTION ValidateTargetDir '" << targetFolder << "' -- " << e.what() << endl;
	}

	return nResult;
}

void FileSystemUtil::CompactFolder(string path)
{
#ifdef WIN32
	string compactCmd = "compact /C /I /Q /S:" + path;
	WinExec(compactCmd.c_str(), SW_SHOWNORMAL);
#else
	cout << "[WARN] CompactFolder is only supported on windows platform!" << endl;
#endif
}

string FileSystemUtil::GetExecutableDirectory(const char* argv_0)
{
	// http://stackoverflow.com/questions/933850/how-to-find-the-location-of-the-executable-in-c
#if WIN32
	DWORD size = 1024;
	LPTSTR buffer = NULL;
ged_start:
	buffer = (LPTSTR)realloc(buffer, size);
	if (buffer == NULL)
	{
		cerr << "GetExecutableDirectory: Failed to realloc memory buffer to " << size << "!" << endl;
		return "";
	}
	
	if (GetModuleFileName(NULL, buffer, size) == 0)
	{
		cerr << "Failed to get executable directory" << GetFormattedMessage(GetLastError()) << endl;
		return "";
	}
	
	if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
	{
		size = size << 1;
		goto ged_start;
	}

	PathRemoveFileSpec(buffer);
	string path = buffer;
	free(buffer);

	return path;
#else
	// first, we want to make sure we did get a valid argument
	if (argv_0 == NULL || argv_0[0] == 0)
	{
		return "";
	}

	string path;

	// if the program name starts with an '/', there is an absolute path specified
	if (argv_0[0] == '/')
	{
		path = argv_0;
		
		string::size_type pos = path.find_last_of("/");
		if (pos != -1)
		{
			path.resize(pos+1);  // keep the slash at the end, it's safer.
		}
	}

	// otherwise we use the current working directory or an additional relative path
	else
	{
		char cwd[PATH_MAX+1];
		ARZeroMemory(cwd);

		if (getcwd(cwd, PATH_MAX) == NULL)
		{
			// error while getting current working directory
			return "";
		}
		path = cwd;

		// ok, do we have some relative path informations?
		if (strchr(argv_0, '/') != NULL)
		{
			if (path.length() > 0 && path[path.length()-1] != '/')
			{
				path += '/';
			}

			path += argv_0;
			string::size_type pos = path.find_last_of("/");
			if (pos != -1)
			{
				path.resize(pos+1);  // keep the slash at the end, it's safer.
			}
		}
	}
	return path;
#endif
}

#if WIN32
string FileSystemUtil::GetFormattedMessage(unsigned int error)
{
	LPSTR buffer = NULL;
	if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, error, 0, buffer, 200, NULL) == 0)
	{
		return "failed to get error message";
	}
	string errMessage = buffer;
	LocalFree(buffer);
	return errMessage;
}
#endif

string FileSystemUtil::CombinePath(const std::string &path1, const std::string &path2)
{
	// if the second path points to the root (starts with PATH_SEPARATOR, we just return the 2nd path)
	if (path2.length() > 0 && 
#ifdef WIN32
		(path2[0] == '/' || path2[0] == '\\')
#else
		path2[0] == '/'
#endif
		)
	{
		return path2;
	}

	stringstream result;

	// add first part
	result << path1;

	// check if we need to add PATH_SEPARATOR
	if (path1.length() > 0)
	{
		char lastPathChar = path1[path1.length()-1];
#ifdef WIN32
		if (lastPathChar != '/' && lastPathChar != '\\')
#else
		if (lastPathChar != '/')
#endif
		{
			result << ARINSIDE_PATH_SEPARATOR;
		}
	}

	result << path2;
	return result.str();
}
