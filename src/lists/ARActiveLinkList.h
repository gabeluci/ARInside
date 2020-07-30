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
#include "ARListHelpers.h"
#include <assert.h>

class CARActiveLinkList : Uncopyable
{
public:
	CARActiveLinkList(void);
	~CARActiveLinkList(void);

	// loading...
	bool LoadFromServer();
	int AddActiveLinkFromXML(ARXMLParsedStream& stream, const char* actlinkName, unsigned int *arDocVersion = NULL);

	// referencing... do we need it? maybe for error handler references or containers?

	// list functions
	inline unsigned int GetCount() { return names.numItems; }
	int Find(const char *name);
	void Reserve(unsigned int size);
	void Sort();

	// referencing
	typedef vector<int> ObjectRefList;

	const ARNameType& ActiveLinkGetName(unsigned int index) const { assert(index < names.numItems); return names.nameList[sortedList[index]]; }
	unsigned int ActiveLinkGetOrder(unsigned int index) const { assert(index < orders.numItems); return orders.intList[sortedList[index]]; }
	const ARWorkflowConnectStruct& ActiveLinkGetSchemaList(unsigned int index) const { assert(index < schemas.numItems); return schemas.workflowConnectList[sortedList[index]]; }
	const ARInternalIdList& ActiveLinkGetGroupList(unsigned int index) const { assert(index < groups.numItems); return groups.internalIdListList[sortedList[index]]; }
	unsigned int ActiveLinkGetExecuteMask(unsigned int index) { assert(index < execMasks.numItems); return execMasks.intList[sortedList[index]]; }
	const ARInternalId& ActiveLinkGetControlField(unsigned int index) const { assert(index < controlFields.numItems); return controlFields.internalIdList[sortedList[index]]; }
	const ARInternalId& ActiveLinkGetFocusField(unsigned int index) const { assert(index < focusFields.numItems); return focusFields.internalIdList[sortedList[index]]; }
	unsigned int ActiveLinkGetEnabled(unsigned int index) { assert(index < enabledObjects.numItems); return enabledObjects.intList[sortedList[index]]; }
	const ARQualifierStruct& ActiveLinkGetRunIf(unsigned int index) const { assert(index < queries.numItems); return queries.qualifierList[sortedList[index]]; }
	const ARActiveLinkActionList& ActiveLinkGetIfActions(unsigned int index) const { assert(index < ifActions.numItems); return ifActions.actionListList[sortedList[index]]; }
	const ARActiveLinkActionList& ActiveLinkGetElseActions(unsigned int index) const { assert(index < elseActions.numItems); return elseActions.actionListList[sortedList[index]]; }
	char* ActiveLinkGetHelptext(unsigned int index) const { assert(index < helpTexts.numItems); return helpTexts.stringList[sortedList[index]]; }
	const ARTimestamp& ActiveLinkGetTimestamp(unsigned int index) const { return changedTimes.timestampList[sortedList[index]]; }
	const ARAccessNameType& ActiveLinkGetOwner(unsigned int index) const { assert(index < owners.numItems); return owners.nameList[sortedList[index]]; }
	const ARAccessNameType& ActiveLinkGetModifiedBy(unsigned int index) const { assert(index < changedUsers.numItems); return changedUsers.nameList[sortedList[index]]; }
	const char* ActiveLinkGetChangeDiary(unsigned int index) const { assert(index < changeDiary.numItems); return changeDiary.stringList[sortedList[index]]; }
	const ARPropList& ActiveLinkGetPropList(unsigned int index) const { assert(index < objProps.numItems); return objProps.propsList[sortedList[index]]; }

	const string& ActiveLinkGetAppRefName(unsigned int index) const { assert(index < appRefNames.size()); return appRefNames[sortedList[index]]; }
	void ActiveLinkSetAppRefName(unsigned int index, const string& appName) { assert(index < appRefNames.size()); appRefNames[sortedList[index]] = appName; }

	void AddOverlayOrCustom(unsigned int index);
	const ObjectRefList& GetOverlayAndCustomWorkflow();
	
private:
	// allocation state of internal structures
	enum ActiveLinkListState { EMPTY, ARAPI_ALLOC, INTERNAL_ALLOC };

private:
	unsigned int reservedSize;
	ARNameList names;
	ARUnsignedIntList orders;
	ARWorkflowConnectList schemas;
	ARInternalIdListList groups;
	ARUnsignedIntList execMasks;
	ARInternalIdList controlFields;
	ARInternalIdList focusFields;
	ARUnsignedIntList enabledObjects;
	ARQualifierList queries;
	ARActiveLinkActionListList ifActions;
	ARActiveLinkActionListList elseActions;
	ARTextStringList helpTexts;
	ARTimestampList changedTimes;
	ARAccessNameList owners;
	ARAccessNameList changedUsers;
	ARTextStringList changeDiary;
	ARPropListList objProps;
	vector<string> appRefNames;

	ActiveLinkListState internalListState;
	vector<int> sortedList;
	typedef map<string,int> CMapType;
	CMapType searchList;
	vector<int> overlayAndCustomList;
};
