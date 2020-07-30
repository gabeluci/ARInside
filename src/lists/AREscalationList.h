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
#include "ARListHelpers.h"
#include <assert.h>

class CAREscalationList : Uncopyable
{
public:
	CAREscalationList(void);
	~CAREscalationList(void);

	// loading...
	bool LoadFromServer();
	int AddEscalationFromXML(ARXMLParsedStream& stream, const char* escalationName, unsigned int *arDocVersion = NULL);

	// list functions
	inline unsigned int GetCount() { return names.numItems; }
	int Find(const char *name);
	void Reserve(unsigned int size);
	void Sort();

	// referencing
	typedef vector<int> ObjectRefList;

	// data-access functions
	const ARNameType& EscalationGetName(unsigned int index) const { assert(index < names.numItems); return names.nameList[sortedList[index]]; }
	const AREscalationTmStruct& EscalationGetTime(unsigned int index) const { assert(index < times.numItems); return times.escalationTmList[sortedList[index]]; }
	const ARWorkflowConnectStruct& EscalationGetSchemaList(unsigned int index) const { assert(index < schemas.numItems); return schemas.workflowConnectList[sortedList[index]]; }
	unsigned int EscalationGetEnabled(unsigned int index) { assert(index < enabledObjects.numItems); return enabledObjects.intList[sortedList[index]]; }
	const ARQualifierStruct& EscalationGetRunIf(unsigned int index) const { assert(index < queries.numItems); return queries.qualifierList[sortedList[index]]; }
	const ARFilterActionList& EscalationGetIfActions(unsigned int index) const { assert(index < ifActions.numItems); return ifActions.actionListList[sortedList[index]]; }
	const ARFilterActionList& EscalationGetElseActions(unsigned int index) const { assert(index < elseActions.numItems); return elseActions.actionListList[sortedList[index]]; }
	char* EscalationGetHelptext(unsigned int index) const { assert(index < helpTexts.numItems); return helpTexts.stringList[sortedList[index]]; }
	const ARTimestamp& EscalationGetTimestamp(unsigned int index) const { return changedTimes.timestampList[sortedList[index]]; }
	const ARAccessNameType& EscalationGetOwner(unsigned int index) const { assert(index < owners.numItems); return owners.nameList[sortedList[index]]; }
	const ARAccessNameType& EscalationGetModifiedBy(unsigned int index) const { assert(index < changedUsers.numItems); return changedUsers.nameList[sortedList[index]]; }
	const char* EscalationGetChangeDiary(unsigned int index) const { assert(index < changeDiary.numItems); return changeDiary.stringList[sortedList[index]]; }
	const ARPropList& EscalationGetPropList(unsigned int index) const { assert(index < objProps.numItems); return objProps.propsList[sortedList[index]]; }

	const string& EscalationGetAppRefName(unsigned int index) const { assert(index < appRefNames.size()); return appRefNames[sortedList[index]]; }
	void EscalationSetAppRefName(unsigned int index, const string& appName) { assert(index < appRefNames.size()); appRefNames[sortedList[index]] = appName; }

	void AddOverlayOrCustom(unsigned int index);
	const ObjectRefList& GetOverlayAndCustomWorkflow();
private:
	// allocation state of internal structures
	enum EscalationListState { EMPTY, ARAPI_ALLOC, INTERNAL_ALLOC };

private:
	unsigned int reservedSize;
	ARNameList names;
	AREscalationTmList times;
	ARWorkflowConnectList schemas;
	ARUnsignedIntList enabledObjects;
	ARQualifierList queries;
	ARFilterActionListList ifActions;
	ARFilterActionListList elseActions;
	ARTextStringList helpTexts;
	ARTimestampList changedTimes;
	ARAccessNameList owners;
	ARAccessNameList changedUsers;
	ARTextStringList changeDiary;
	ARPropListList objProps;
	vector<string> appRefNames;

	EscalationListState internalListState;
	vector<int> sortedList;	// a index, sorted by escalation names
	typedef map<string,int> CMapType;
	CMapType searchList;
	vector<int> overlayAndCustomList;
};
