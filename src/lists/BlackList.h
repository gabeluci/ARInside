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
#include "../ARApi.h"
#include "../util/Uncopyable.h"

class CBlackList : Uncopyable
{
public:
	CBlackList(void);
	~CBlackList(void);

	bool LoadFromServer(const string &packingListName);

	size_t GetCountOf(unsigned int nType);
	bool Contains(unsigned int nType, const char *objName);
	void Exclude(unsigned int nType, ARNameList *objNames);

private:
	string blackListName;
	vector<string> schemas;
	vector<string> actlinks;
	vector<string> filters;
	vector<string> escalations;
	vector<string> containers;
	vector<string> menus;
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_750
	vector<string> images;
#endif
};
