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
#include "ARListHelpers.h"
#include <assert.h>

class CARFilterList : Uncopyable
{
public:
	CARFilterList(void);
	~CARFilterList(void);

	// loading...
	bool LoadFromServer();
	int AddFilterFromXML(ARXMLParsedStream& stream, const char* filterName, unsigned int *arDocVersion = NULL);

	// referencing... do we need it? maybe for error handler references or containers?
	typedef vector<int> ObjectRefList;

	// list functions
	inline unsigned int GetCount() { return names.numItems; }
	int Find(const char *name);
	void Reserve(unsigned int size);
	void Sort();

	// data-access functions
	const ARNameType& FilterGetName(unsigned int index) const { assert(index < names.numItems); return names.nameList[sortedList[index]]; }
	unsigned int FilterGetOrder(unsigned int index) const { assert(index < orders.numItems); return orders.intList[sortedList[index]]; }
	const ARWorkflowConnectStruct& FilterGetSchemaList(unsigned int index) const { assert(index < schemas.numItems); return schemas.workflowConnectList[sortedList[index]]; }
	unsigned int FilterGetOperation(unsigned int index) { assert(index < operationSets.numItems); return operationSets.intList[sortedList[index]]; }
	unsigned int FilterGetEnabled(unsigned int index) { assert(index < enabledObjects.numItems); return enabledObjects.intList[sortedList[index]]; }
	const ARQualifierStruct& FilterGetRunIf(unsigned int index) const { assert(index < queries.numItems); return queries.qualifierList[sortedList[index]]; }
	const ARFilterActionList& FilterGetIfActions(unsigned int index) const { assert(index < ifActions.numItems); return ifActions.actionListList[sortedList[index]]; }
	const ARFilterActionList& FilterGetElseActions(unsigned int index) const { assert(index < elseActions.numItems); return elseActions.actionListList[sortedList[index]]; }
	char* FilterGetHelptext(unsigned int index) const { assert(index < helpTexts.numItems); return helpTexts.stringList[sortedList[index]]; }
	const ARTimestamp& FilterGetTimestamp(unsigned int index) const { return changedTimes.timestampList[sortedList[index]]; }
	const ARAccessNameType& FilterGetOwner(unsigned int index) const { assert(index < owners.numItems); return owners.nameList[sortedList[index]]; }
	const ARAccessNameType& FilterGetModifiedBy(unsigned int index) const { assert(index < changedUsers.numItems); return changedUsers.nameList[sortedList[index]]; }
	const char* FilterGetChangeDiary(unsigned int index) const { assert(index < changeDiary.numItems); return changeDiary.stringList[sortedList[index]]; }
	const ARPropList& FilterGetPropList(unsigned int index) const { assert(index < objProps.numItems); return objProps.propsList[sortedList[index]]; }

	// Notice about the function below (FilterGetErrorOption)
	// The errorOptions list might contain zero items if we connect to a 7.0/6.3
	// or older server. If thats the case simply return 0. This implies 
	// additionally, that the FilterGetErrorHandler function is only called when
	// FilterGetErrorOption return nonzero.
	unsigned int FilterGetErrorOption(unsigned int index) { if (index >= errorOptions.numItems) return 0; else return errorOptions.intList[sortedList[index]]; }
	const ARNameType& FilterGetErrorHandler(unsigned int index) const { assert(index < errorHandlers.numItems); return errorHandlers.nameList[sortedList[index]]; }

	const string& FilterGetAppRefName(unsigned int index) const { assert(index < appRefNames.size()); return appRefNames[sortedList[index]]; }
	void FilterSetAppRefName(unsigned int index, const string& appName) { assert(index < appRefNames.size()); appRefNames[sortedList[index]] = appName; }
	vector<unsigned int> &FilterErrorCallers(unsigned int index) { assert(index < errorCallers.size()); return errorCallers[sortedList[index]]; }

	void AddOverlayOrCustom(unsigned int index);
	const ObjectRefList& GetOverlayAndCustomWorkflow();
private:
	// allocation state of internal structures
	enum FilterListState { EMPTY, ARAPI_ALLOC, INTERNAL_ALLOC };

private:
	unsigned int reservedSize;
	ARNameList names;
	ARUnsignedIntList orders;
	ARWorkflowConnectList schemas;
	ARUnsignedIntList operationSets;
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
	ARUnsignedIntList errorOptions;
	ARNameList errorHandlers;
	vector<string> appRefNames;
	vector< vector<unsigned int> > errorCallers;

	FilterListState internalListState;
	vector<int> sortedList;	// a index, sorted by filter names
	typedef map<string,int> CMapType;
	CMapType searchList;
	vector<int> overlayAndCustomList;
};
