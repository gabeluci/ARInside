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

#pragma once
#include <string>
#include <sstream>
#include <iostream>
#include <time.h>
#include <list>
#include <vector>
#include <algorithm>

#include <ar.h>

using namespace std;

class CUtil
{
public:
	CUtil(void);
public:
	~CUtil(void);	
	static string DateTimeToString(ARTimestamp ts);
	static string DateTimeToHTMLString(ARTimestamp ts);
	static string DateToString(int dateInt);
	static string CurrentDateTimeToHTMLString();
	static string TimeOfDayToString(ARTime time);
	static string ClearSpaces(const string &strIn);
	static string String2Comp(string strIn);
	static string StrReplace(const std::string &search, const std::string &replace, std::string searchin);
	static bool StrEndsWith(const std::string &str, const std::string &search);
	static int SplitString(const std::string& input_record, std::vector<std::string>& colv);
};
