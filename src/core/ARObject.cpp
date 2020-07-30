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
#include "ARObject.h"
#include "../output/WebPage.h"

using namespace OUTPUT;

const char* objectNameFirstCharLetters = "abcdefghijklmnopqrstuvwxyz0123456789#";
const int otherObjectNameIndex = 36; // strlen(objectNameFirstCharLetter) - 1

CARObject::CARObject(int insideId)
{
	this->insideId = insideId;
}

CARObject::~CARObject(void)
{
}

string CARObject::FileID(int insideId)
{
	char buffer[20];
	// use sprintf instead of _itoa to make it work under linux. 
	// Linux doesnt come with an implementation for itoa.
	sprintf(buffer,"%d", insideId);	
	//return _itoa(this->insideId, buffer, 10);
	return buffer;
}

string CARObject::GetNameFirstChar(const std::string &str)
{
	if (str.empty()) return str;
	return GetNameFirstChar(str.c_str());
}

// this function returns the first none-space charater of the string in lower-case
string CARObject::GetNameFirstChar(const char* str)
{
	if (str == NULL) return "";

	unsigned int pos = 0;
	char c;
	while ((c = str[pos]) != 0)
	{
		if (c != ' ')
		{
			char result[4];
			memset(&result, '\0', 4);
			result[0] = tolower(c);
			return result;
		}
		pos++;
	}
	return "";
}

bool CARObject::NameStandardFirstChar(char ch)
{
	ch = tolower(ch);
	return (ch >= 'a' && ch <= 'z' || ch >= '0' && ch <= '9' ? true : false);
}

bool CARObject::NameStandardFirstChar(const std::string &str)
{
	string firstChar = GetNameFirstChar(str);
	if (!firstChar.empty()) 
		return CARObject::NameStandardFirstChar(firstChar[0]);
	return false;
}

int CARObject::GetFirstCharIndex(char ch)
{
	const char* index = strchr(objectNameFirstCharLetters, ch);
	if (index == NULL) return otherObjectNameIndex;
	return (int)(index - objectNameFirstCharLetters);
}
