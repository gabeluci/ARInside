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
#include "../ARApi.h"

extern const char* objectNameFirstCharLetters;

class CARObject
{
public:
	CARObject(int insideId);
	~CARObject(void);

protected:
	int insideId;

public:
	virtual string GetName() = 0;
	virtual string GetName() const = 0;
	int GetInsideId() { return insideId; }
	int GetInsideId() const { return insideId; }
	
	string FileID() const { return FileID(insideId); }
	virtual string GetNameFirstChar() = 0;
	virtual bool NameStandardFirstChar() = 0;

	static string FileID(int insideId);
	static string GetNameFirstChar(const string& str);
	static string GetNameFirstChar(const char* str);
	static bool NameStandardFirstChar(char ch);
	static bool NameStandardFirstChar(const string &str);
	static int GetFirstCharIndex(char ch);
};
