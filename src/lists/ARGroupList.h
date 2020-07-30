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

class CARGroupList : Uncopyable
{
public:
	CARGroupList(void);
	~CARGroupList(void);

public:
	// loading...
	bool LoadFromServer();

	// list functions
	inline unsigned int GetCount() { return (unsigned int)names.size(); }
	int Find(int groupId);
	void Reserve(unsigned int size);
	void Sort();

	// data-access functions
	const string& GroupGetRequestId(unsigned int index) { assert(index < requestId.size()); return requestId[sortedList[index]]; }
	const string& GroupGetName(unsigned int index) { assert(index < names.size()); return names[sortedList[index]]; }
	const string& GroupGetLongName(unsigned int index) { assert(index < longNames.size()); return longNames[sortedList[index]]; }
	ARULong32 GroupGetID(unsigned int index) { assert(index < ids.size()); return ids[sortedList[index]]; }
	int GroupGetType(unsigned int index) { assert(index < types.size()); return types[sortedList[index]]; }
	int GroupGetCategory(unsigned int index) { assert(index < category.size()); return category[sortedList[index]]; }
	const string& GroupGetComputedQual(unsigned int index) { assert(index < computedQual.size()); return computedQual[sortedList[index]]; }
	ARTimestamp GroupGetCreateDate(unsigned int index) { assert(index < createDate.size()); return createDate[sortedList[index]]; }
	ARTimestamp GroupGetModifiedDate(unsigned int index) { assert(index < modifiedDate.size()); return modifiedDate[sortedList[index]]; }
	const ARAccessNameType& GroupGetCreatedBy(unsigned int index) { assert(index < owners.numItems); return owners.nameList[sortedList[index]]; }
	const ARAccessNameType& GroupGetModifiedBy(unsigned int index) { assert(index < changedUsers.numItems); return changedUsers.nameList[sortedList[index]]; }
	static const ARPropList& GroupGetPropList(/*unsigned int index*/) { return emptyPropList; }

private:
	void StoreEntry(ARFieldValueList& value);

private:
	vector<string> requestId;
	vector<string> names;
	vector<string> longNames;
	vector<ARULong32> ids;
	vector<int> types;
	vector<int> category;
	vector<string> computedQual;
	vector<ARTimestamp> createDate;
	vector<ARTimestamp> modifiedDate;
	ARAccessNameList owners;
	ARAccessNameList changedUsers;

	vector<int> sortedList;	// a index, sorted by group names
};
