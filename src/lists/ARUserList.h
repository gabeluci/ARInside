//Copyright (C) 2011 John Luthgers | jls17
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

#include "../util/Uncopyable.h"
#include "ARListHelpers.h"
#include <assert.h>

class CARUserList : Uncopyable
{
public:
	CARUserList(void);
	~CARUserList(void);

	// type defs for public lists
	typedef vector<int> GroupList;
public:
	// loading...
	bool LoadFromServer();

	// list functions
	inline unsigned int GetCount() { return (unsigned int)names.size(); }
	int Find(const string& name);
	void Reserve(unsigned int size);
	void Sort();

	// data-access functions
	const string& UserGetRequestId(unsigned int index) { assert(index < requestId.size()); return requestId[sortedList[index]]; }
	const string& UserGetName(unsigned int index) { assert(index < names.size()); return names[sortedList[index]]; }
	const string& UserGetEmail(unsigned int index) { assert(index < email.size()); return email[sortedList[index]]; }
	const GroupList& UserGetGroups(unsigned int index) { assert(index < group.size()); return group[sortedList[index]]; }
	const string& UserGetFullName(unsigned int index) { assert(index < fullName.size()); return fullName[sortedList[index]]; }
	int UserGetDefaultNotify(unsigned int index) { assert(index < defaultNotify.size()); return defaultNotify[sortedList[index]]; }
	int UserGetLicenseType(unsigned int index) { assert(index < licType.size()); return licType[sortedList[index]]; }
	int UserGetFTLicenseType(unsigned int index) { assert(index < ftLicType.size()); return ftLicType[sortedList[index]]; }
	const ARAccessNameType& UserGetCreatedBy(unsigned int index) { assert(index < owners.numItems); return owners.nameList[sortedList[index]]; }
	ARTimestamp UserGetCreateDate(unsigned int index) { assert(index < createDate.size()); return createDate[sortedList[index]]; }
	const ARAccessNameType& UserGetModifiedBy(unsigned int index) { assert(index < changedUsers.numItems); return changedUsers.nameList[sortedList[index]]; }
	ARTimestamp UserGetModifiedDate(unsigned int index) { assert(index < modifiedDate.size()); return modifiedDate[sortedList[index]]; }
	static const ARPropList& UserGetPropList() { return emptyPropList; }

private:
	void StoreEntry(ARFieldValueList& value);

private:
	vector<string> requestId;
	vector<string> names;
	vector<string> email;
	vector<GroupList> group;
	vector<string> fullName;
	vector<int> defaultNotify;
	vector<int> licType;
	vector<int> ftLicType;
	//vector<ARAccessNameType> createdBy;
	vector<ARTimestamp> createDate;
	//vector<ARAccessNameType> modifiedBy;
	vector<ARTimestamp> modifiedDate;
	ARAccessNameList owners;
	ARAccessNameList changedUsers;


	vector<int> sortedList;	// a index, sorted by user names
	
	typedef map<string,int> CMapType;
	CMapType searchList;
};
