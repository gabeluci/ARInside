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
#include "Util.h"

CUtil::CUtil(void)
{
}

CUtil::~CUtil(void)
{
}

string CUtil::DateTimeToHTMLString(ARTimestamp ts)
{
	string result = "";
	struct tm *stm;
	char dest[100];

	// a value of "1970-01-01T01:00:00+01:00" in a diary field timestamp loaded from xml (changeHistory of a field)
	// resulted in a negative value and strftime crashed afterwards
	if (ts < 0) ts = 0;

	time_t dtime = (time_t) ts;
	stm = localtime(&dtime);
	strftime(dest, 100, "%Y-%m-%d&nbsp;%H:%M:%S", stm);

	result = dest;
	return result;
}

string CUtil::CurrentDateTimeToHTMLString()
{
	time_t curseconds;
	time(&curseconds);
	return DateTimeToHTMLString(static_cast<ARTimestamp>(curseconds));
}

string CUtil::DateTimeToString(ARTimestamp ts)
{
	string result = "";
	struct tm *stm;
	char dest[100];

	time_t dtime = (time_t) ts;
	stm = localtime(&dtime);
	strftime(dest, 100, "%Y-%m-%d %H:%M:%S", stm);

	result = dest;
	return result;
}

string CUtil::ClearSpaces(const string &inStr)
{
	string result = "";
	remove_copy_if( inStr.begin(), inStr.end(), insert_iterator<string>(result, result.begin()), bind2nd(equal_to<char>(), ' '));    
	return result;
}

string CUtil::String2Comp(string inStr)
{
	inStr = ClearSpaces(inStr);

	for(unsigned i = 0; i < inStr.length(); i++)
		inStr[i] = tolower(inStr[i]);

	return inStr;
}

string CUtil::StrReplace(const std::string &search, const std::string &replace, std::string searchin)
{
	std::string::size_type pos = searchin.find(search, 0);
	unsigned int searchLength = (unsigned int)search.length();

	while(pos != std::string::npos)
	{
		searchin.replace(pos, searchLength, replace);
		pos = searchin.find(search, pos + searchLength);
	}

	return searchin;
}

int CUtil::SplitString(const std::string& input_record, std::vector<std::string>& colv)
{
	std::istringstream s(input_record);
	std::string temp;

	colv.clear();
	while (std::getline(s, temp, ';')) 
	{
		colv.push_back(temp);
	}

	return static_cast<int>(colv.size());
}

string CUtil::DateToString(int dateInt)
{
	//formula found from http://en.wikipedia.org/wiki/Julian_day#Gregorian_calendar_from_Julian_day_number
	int J = dateInt;
	int j = J+32044;
	int g = j/146097;
	int dg = j%146097;
	int c = ((dg/36524) + 1)*3/4;
	int dc = dg - (c*36524);
	int b = dc/1461;
	int db = dc%1461;
	int a = (db/365 + 1)*3/4;
	int da = db - a*365;
	int y = g*400 + c*100 + b*4 + a;
	int m = (da*5 + 308)/153 - 2;
	int d = da - (m + 4)*153/5 + 122;
	int Y = y - 4800 + (m + 2)/12;
	int M = (m + 2)%12 + 1; 
	int D = d + 1;

	stringstream strm;
	strm.str("");
	strm << Y << "-" << M << "-" << D;
	return strm.str();
}

string CUtil::TimeOfDayToString(ARTime time)
{
	time_t rawtime = (time_t) time;
	struct tm * timeinfo;
	char buffer [20];

	timeinfo = gmtime ( &rawtime );

	strftime (buffer,20,"%I:%M:%S %p",timeinfo);

	return buffer;
}

bool CUtil::StrEndsWith(const std::string &str, const std::string &search)
{
	if (search.size() > str.size()) return false;
	return equal(str.end() - search.size(), str.end(), search.begin());
}
