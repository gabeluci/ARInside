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

class CARRoleList : Uncopyable
{
public:
	CARRoleList(void);
	~CARRoleList(void);

public:
	// loading...
	bool LoadFromServer();

	// list functions
	inline unsigned int GetCount() { return (unsigned int)names.size(); }
	int Find(int iRoleId, const string& appName);
	void Reserve(unsigned int size);
	void Sort();

	// type defs for public lists
	typedef vector<int> GroupList;

	// data-access functions
	const string& RoleGetRequestId(unsigned int index) { assert(index < requestId.size()); return requestId[sortedList[index]]; }
	const string& RoleGetApplicationName(unsigned int index) { assert(index < applicationName.size()); return applicationName[sortedList[index]]; }
	const string& RoleGetName(unsigned int index) { assert(index < names.size()); return names[sortedList[index]]; }
	int RoleGetId(unsigned int index) { assert(index < roleId.size()); return roleId[sortedList[index]]; }
	const GroupList& RoleGetGroupsTest(unsigned int index) { assert(index < groupsTest.size()); return groupsTest[sortedList[index]]; }
	const GroupList& RoleGetGroupsProd(unsigned int index) { assert(index < groupsProd.size()); return groupsProd[sortedList[index]]; }
	ARTimestamp RoleGetCreateDate(unsigned int index) { assert(index < createDate.size()); return createDate[sortedList[index]]; }
	ARTimestamp RoleGetModifiedDate(unsigned int index) { assert(index < modifiedDate.size()); return modifiedDate[sortedList[index]]; }
	const ARAccessNameType& RoleGetCreatedBy(unsigned int index) { assert(index < owners.numItems); return owners.nameList[sortedList[index]]; }
	const ARAccessNameType& RoleGetModifiedBy(unsigned int index) { assert(index < changedUsers.numItems); return changedUsers.nameList[sortedList[index]]; }
	static const ARPropList& RoleGetPropList(/*unsigned int index*/) { return emptyPropList; }

private:
	void StoreEntry(ARFieldValueList& value);

private:
	vector<string> requestId;
	vector<string> applicationName;
	vector<string> names;
	vector<int> roleId;
	vector<GroupList> groupsTest;
	vector<GroupList> groupsProd;
	vector<ARTimestamp> createDate;
	vector<ARTimestamp> modifiedDate;
	ARAccessNameList owners;
	ARAccessNameList changedUsers;

	vector<int> sortedList;	// a index, sorted by role names
};
