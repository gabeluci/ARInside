//Copyright (C) 2009 John Luthgers | jls17
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

#pragma once
#include "../ARInside.h"

class OpenWindowReportData
{
public:
	OpenWindowReportData(char* reportString);
	~OpenWindowReportData(void);

	bool IsValid(); // returns true if the report string passed to the constructor could be parsed without errors
	string getReportType();
	string getReportLocation();
	string getReportName();
	string getReportDestination();
	string getEntryIds();
	string getQueryOverride();
	string getReportOperation();
	string getCharEncoding();
	string getInlineForm();

private:
	void CheckAlreadyParsed();
	bool ParseReportData();

private:
	bool isParsed;
	bool isValid;
	char* reportString;

	const char* reportType_Start;
	const char* reportType_End;
	const char* reportLocation_Start;
	const char* reportLocation_End;
	const char* reportName_Start;
	const char* reportName_End;
	const char* reportDestination_Start;
	//const char* reportDestination_End;
	const char* entryIds_Start;
	const char* entryIds_End;
	const char* queryOverride_Start;
	const char* queryOverride_End;
	const char* reportOperation_Start;
	const char* reportOperation_End;
	const char* charEncoding_Start;
	const char* charEncoding_End;
	const char* inlineForm_Start;
	const char* inlineForm_End;
};
