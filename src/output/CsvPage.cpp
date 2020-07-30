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
//    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.

#include "stdafx.h"
#include "CsvPage.h"
#include "WebUtil.h"
#include "../ARInside.h"

using namespace OUTPUT;

extern int nFilesCreated;

// TODO: this class should use CPageParams instead of fileName
CCsvPage::CCsvPage(string fileName, AppConfig &appConfig)
{
	this->fileName = fileName;
	this->appConfig = appConfig;
}

CCsvPage::~CCsvPage(void)
{

}

int CCsvPage::SaveInFolder(string path, string content)
{
	int result = 0;

	stringstream strm;
	strm.str("");

	if(!path.empty())
		strm << this->appConfig.targetFolder << "/" << path << "/" << CWebUtil::CsvDocName(this->fileName);
	else
		strm << this->appConfig.targetFolder << "/" << CWebUtil::CsvDocName(this->fileName);

	try
	{	
		LOG << "Save file '" << strm.str();

		ofstream fout( strm.str().c_str(), ios::out);
		fout << content << endl;
		fout.close();

		LOG << "' [OK]" << endl;

		nFilesCreated++;
		result = 1;
	}
	catch(exception& e)
	{		
		stringstream erStrm;
		erStrm << "Error saving file '" << strm.str() << "' to disk. Error: " << e.what();
		throw(AppException(erStrm.str(), "undefined", "FileIo"));
	}

	return result;
}
