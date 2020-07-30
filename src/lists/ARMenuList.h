//Copyright (C) 2010 John Luthgers | jls17
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
#include "../ARApi.h"
#include "../util/Uncopyable.h"
#include "../util/RefItem.h"
#include "ARListHelpers.h"
#include <assert.h>

class CARMenuList : Uncopyable
{
public:
	CARMenuList(void);
	~CARMenuList(void);

	// loading...
	bool LoadFromServer();
	int AddMenuFromXML(ARXMLParsedStream& stream, const char* menuName, unsigned int *arDocVersion = NULL);

	// list functions
	inline unsigned int GetCount() { return names.numItems; }
	int Find(const char *name);
	void Reserve(unsigned int size);
	void Sort();

	// data access
	const ARNameType& MenuGetName(unsigned int index) const { assert(index < names.numItems); return names.nameList[sortedList[index]]; }
	unsigned int MenuGetRefreshCode(unsigned int index) const { assert(index < refreshCodes.numItems); return refreshCodes.intList[sortedList[index]]; }
	const ARCharMenuStruct& MenuGetDefinition(unsigned int index) const { assert(index < definitions.numItems); return definitions.list[sortedList[index]]; }
	char* MenuGetHelptext(unsigned int index) const { assert(index < helpTexts.numItems); return helpTexts.stringList[sortedList[index]]; }
	const ARTimestamp& MenuGetTimestamp(unsigned int index) const { return changedTimes.timestampList[sortedList[index]]; }
	const ARAccessNameType& MenuGetOwner(unsigned int index) const { assert(index < owners.numItems); return owners.nameList[sortedList[index]]; }
	const ARAccessNameType& MenuGetModifiedBy(unsigned int index) const { assert(index < changedUsers.numItems); return changedUsers.nameList[sortedList[index]]; }
	const char* MenuGetChangeDiary(unsigned int index) const { assert(index < changeDiary.numItems); return changeDiary.stringList[sortedList[index]]; }
	const ARPropList& MenuGetPropList(unsigned int index) const { assert(index < objProps.numItems); return objProps.propsList[sortedList[index]]; }
	const string& MenuGetAppRefName(unsigned int index) const { assert(index < appRefNames.size()); return appRefNames[sortedList[index]]; }
	void MenuSetAppRefName(unsigned int index, const string& appName) { assert(index < appRefNames.size()); appRefNames[sortedList[index]] = appName; }

	// referencing
	typedef vector<int> ObjectRefList;
	typedef vector<CRefItem> ReferenceList;
	void AddReference(unsigned int index, const CRefItem& refItem);
	bool ReferenceExists(unsigned int index, const CRefItem& refItem);
	const ReferenceList& GetReferences(unsigned int index);

	void AddOverlayOrCustom(unsigned int index);
	const ObjectRefList& GetOverlayAndCustomWorkflow();
private:
	// allocation state of internal structures
	enum MenuListState { EMPTY, ARAPI_ALLOC, INTERNAL_ALLOC };

private:
	unsigned int reservedSize;
	ARNameList names;
	ARUnsignedIntList refreshCodes;
	ARCharMenuStructList definitions;
	ARTextStringList helpTexts;
	ARTimestampList changedTimes;
	ARAccessNameList owners;
	ARAccessNameList changedUsers;
	ARTextStringList changeDiary;
	ARPropListList objProps;
	vector<string> appRefNames;

	MenuListState internalListState;
	vector<int> sortedList;
	vector<ReferenceList> references;
	typedef map<string,int> CMapType;
	CMapType searchList;
	vector<int> overlayAndCustomList;
};
