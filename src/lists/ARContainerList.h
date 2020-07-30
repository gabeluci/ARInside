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
//    along with ARInside.  If not, see <http://www.gnu.org/licenses/>.
#pragma once
#include "../ARApi.h"
#include "../util/Uncopyable.h"
#include "../util/RefItem.h"
#include "ARListHelpers.h"
#include <assert.h>

class CARContainerList : Uncopyable
{
public:
	CARContainerList(void);
	~CARContainerList(void);

	// loading...
	bool LoadFromServer();
	int AddContainerFromXML(ARXMLParsedStream& stream, const char* cntName, unsigned int *arDocVersion = NULL);

	// list functions
	inline unsigned int GetCount() { return names.numItems; }
	int Find(const char *name);
	void Reserve(unsigned int size);
	void Sort();

	// referencing
	typedef vector<int> ObjectRefList;

	// data access
	const ARNameType& ContainerGetName(unsigned int index) const { assert(index < names.numItems); return names.nameList[sortedList[index]]; }
	const ARPermissionList& ContainerGetPermissions(unsigned int index) const { assert(index < permissions.numItems); return permissions.permissionList[sortedList[index]]; }
	const ARInternalIdList& ContainerGetSubadmins(unsigned int index) const { assert(index < subadmins.numItems); return subadmins.internalIdListList[sortedList[index]]; }
	const ARContainerOwnerObjList& ContainerGetOwnerObjects(unsigned int index) const { assert(index < ownerObjects.numItems); return ownerObjects.ownerObjListList[sortedList[index]]; }
	char* ContainerGetLabel(unsigned int index) const { assert(index < labels.numItems); return labels.stringList[sortedList[index]]; }
	char* ContainerGetDescription(unsigned int index) const { assert(index < descriptions.numItems); return descriptions.stringList[sortedList[index]]; }
	unsigned int ContainerGetType(unsigned int index) const { assert(index < types.numItems); return types.intList[sortedList[index]]; }
	const ARReferenceList& ContainerGetContent(unsigned int index) const { assert(index < content.numItems); return content.referenceListList[sortedList[index]]; }
	char* ContainerGetHelptext(unsigned int index) const { assert(index < helpTexts.numItems); return helpTexts.stringList[sortedList[index]]; }
	const ARTimestamp& ContainerGetTimestamp(unsigned int index) const { return changedTimes.timestampList[sortedList[index]]; }
	const ARAccessNameType& ContainerGetOwner(unsigned int index) const { assert(index < owners.numItems); return owners.nameList[sortedList[index]]; }
	const ARAccessNameType& ContainerGetModifiedBy(unsigned int index) const { assert(index < changedUsers.numItems); return changedUsers.nameList[sortedList[index]]; }
	const char* ContainerGetChangeDiary(unsigned int index) const { assert(index < changeDiary.numItems); return changeDiary.stringList[sortedList[index]]; }
	const ARPropList& ContainerGetPropList(unsigned int index) const { assert(index < objProps.numItems); return objProps.propsList[sortedList[index]]; }
	const string& ContainerGetAppRefName(unsigned int index) const { assert(index < appRefNames.size()); return appRefNames[sortedList[index]]; }
	void ContainerSetAppRefName(unsigned int index, const string& appName) { assert(index < appRefNames.size()); appRefNames[sortedList[index]] = appName; }

	// referencing
	typedef vector<CRefItem> ReferenceList;
	void AddReference(unsigned int index, const CRefItem& refItem);
	bool ReferenceExists(unsigned int index, const CRefItem& refItem);
	const ReferenceList& GetReferences(unsigned int index);

	void AddOverlayOrCustom(unsigned int index);
	const ObjectRefList& GetOverlayAndCustomWorkflow();
private:
	// allocation state of internal structures
	enum ContainerListState { EMPTY, ARAPI_ALLOC, INTERNAL_ALLOC };

private:
	unsigned int reservedSize;
	ARNameList names;
	ARPermissionListList permissions;
	ARInternalIdListList subadmins;
	ARContainerOwnerObjListList ownerObjects;
	ARTextStringList labels;
	ARTextStringList descriptions;
	ARUnsignedIntList types;
	ARReferenceListList content;
	ARTextStringList helpTexts;
	ARTimestampList changedTimes;
	ARAccessNameList owners;
	ARAccessNameList changedUsers;
	ARTextStringList changeDiary;
	ARPropListList objProps;
	vector<string> appRefNames;

	ContainerListState internalListState;
	vector<int> sortedList;
	typedef map<string,int> CMapType;
	CMapType searchList;
	vector<int> overlayAndCustomList;
	vector<ReferenceList> references;
};
