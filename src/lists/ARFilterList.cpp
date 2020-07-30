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

#include "stdafx.h"
#include "ARFilterList.h"
#include "../ARInside.h"
#include "../core/ARStatusList.h"
#include "../output/WebUtil.h"
#include "BlackList.h"

CARFilterList::CARFilterList(void)
{
	ARZeroMemory(&names);
	ARZeroMemory(&orders);
	ARZeroMemory(&schemas);
	ARZeroMemory(&operationSets);
	ARZeroMemory(&enabledObjects);
	ARZeroMemory(&queries);
	ARZeroMemory(&ifActions);
	ARZeroMemory(&elseActions);
	ARZeroMemory(&helpTexts);
	ARZeroMemory(&changedTimes);
	ARZeroMemory(&owners);
	ARZeroMemory(&changedUsers);
	ARZeroMemory(&changeDiary);
	ARZeroMemory(&objProps);
	ARZeroMemory(&errorOptions);
	ARZeroMemory(&errorHandlers);
	internalListState = CARFilterList::EMPTY;
	reservedSize = 0;
}

CARFilterList::~CARFilterList(void)
{
	if (internalListState == CARFilterList::INTERNAL_ALLOC)
	{
		try
		{
			delete[] names.nameList;
			delete[] orders.intList;
			delete[] schemas.workflowConnectList;
			delete[] operationSets.intList;
			delete[] enabledObjects.intList;
			delete[] queries.qualifierList;
			delete[] ifActions.actionListList;
			delete[] elseActions.actionListList;
			delete[] helpTexts.stringList;
			delete[] changedTimes.timestampList;
			delete[] owners.nameList;
			delete[] changedUsers.nameList;
			delete[] changeDiary.stringList;
			delete[] objProps.propsList;
			delete[] errorOptions.intList;
			delete[] errorHandlers.nameList;
		}
		catch (...)
		{
		}
	}
	else if (internalListState == CARFilterList::ARAPI_ALLOC)
	{		
		try
		{
			FreeARNameList(&names,false);
			FreeARUnsignedIntList(&orders,false);
			FreeARWorkflowConnectList(&schemas,false);
			FreeARUnsignedIntList(&operationSets,false);
			FreeARUnsignedIntList(&enabledObjects,false);
			FreeARQualifierList(&queries,false);
			FreeARFilterActionListList(&ifActions,false);
			FreeARFilterActionListList(&elseActions,false);
			FreeARTextStringList(&helpTexts,false);
			FreeARTimestampList(&changedTimes,false);
			FreeARAccessNameList(&owners,false);
			FreeARAccessNameList(&changedUsers,false);
			FreeARTextStringList(&changeDiary,false);
			FreeARPropListList(&objProps,false);
			FreeARUnsignedIntList(&errorOptions,false);
			FreeARNameList(&errorHandlers,false);
		}
		catch (...)
		{

		}
	}
}

bool CARFilterList::LoadFromServer()
{
	ARBooleanList   fltExists;
	ARStatusList    status;
	CARInside*      arIn = CARInside::GetInstance();
	ARNameList*     objectsToLoad = NULL;
	ARNameList      objectNames;
	unsigned int    originalObjectNameCount = 0;
	bool            funcResult = false;

	memset(&fltExists, 0, sizeof(fltExists));
	memset(&status, 0, sizeof(status));

	// if the blacklist contains filters, we should first load all filter names from the
	// server and remove those that are contained in the blacklist. after that call
	// ARGetMultipleFilters to retrieve just the needed objects.
	if (arIn->blackList.GetCountOf(ARREF_FILTER) > 0)
	{
		memset(&objectNames, 0, sizeof(objectNames));

		if (ARGetListFilter(&arIn->arControl, NULL, 0, NULL, &objectNames, &status) == AR_RETURN_OK)
		{
			originalObjectNameCount = objectNames.numItems;
			arIn->blackList.Exclude(ARREF_FILTER, &objectNames);
			objectsToLoad = &objectNames;
		}
		else
			cerr << BuildMessageAndFreeStatus(status);
	}

	// ok, now retrieve all informations of the filters we need
	if (!arIn->appConfig.slowObjectLoading && ARGetMultipleFilters(&arIn->arControl,
		0,
		objectsToLoad,
		&fltExists,
		&names,
		&orders,
		&schemas,
		&operationSets,
		&enabledObjects,
		&queries,
		&ifActions,
		&elseActions,
		&helpTexts,
		&changedTimes,
		&owners,
		&changedUsers,
		&changeDiary,
		&objProps,
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_710
		&errorOptions,
		&errorHandlers,
#endif
		&status) == AR_RETURN_OK)
	{
		FreeARBooleanList(&fltExists, false);
		internalListState = CARFilterList::ARAPI_ALLOC;
		funcResult = true;
	}
	else
	{
		cerr << BuildMessageAndFreeStatus(status);

		// ok, fallback to slow data retrieval
		// this could be necessaray if there is a corrupt object that keeps us from getting all at once
		if (!arIn->appConfig.slowObjectLoading)
			cout << "WARN: switching to slow filter loading!" << endl;

		// first check if object names are already loaded
		if (objectsToLoad == NULL)
		{
			// no object names loaded ... now get all names from server
			memset(&objectNames, 0, sizeof(objectNames));

			if (ARGetListFilter(&arIn->arControl, NULL, 0, NULL, &objectNames, &status) == AR_RETURN_OK)
			{
				originalObjectNameCount = objectNames.numItems;
				objectsToLoad = &objectNames;
			}
			else
				cerr << BuildMessageAndFreeStatus(status);
		}

		if (objectsToLoad != NULL && objectsToLoad->numItems > 0)
		{
			// allocate needed size for internal lists
			this->Reserve(objectsToLoad->numItems);

			// use a separate counter for the store index, because if a filter can't be loaded, this index is not incremented
			unsigned int curListPos = 0; 

			// now load each filter
			for (unsigned int i=0; i < objectsToLoad->numItems; ++i)
			{
				LOG << "Loading Filter: " << objectsToLoad->nameList[i] << " ";

				strncpy(names.nameList[curListPos], objectsToLoad->nameList[i], AR_MAX_NAME_SIZE);
				names.nameList[curListPos][AR_MAX_NAME_SIZE] = 0;
				
				if (ARGetFilter(&arIn->arControl,
					names.nameList[curListPos],
					&orders.intList[curListPos],
					&schemas.workflowConnectList[curListPos],
					&operationSets.intList[curListPos],
					&enabledObjects.intList[curListPos],
					&queries.qualifierList[curListPos],
					&ifActions.actionListList[curListPos],
					&elseActions.actionListList[curListPos],
					&helpTexts.stringList[curListPos],
					&changedTimes.timestampList[curListPos],
					owners.nameList[curListPos],
					changedUsers.nameList[curListPos],
					&changeDiary.stringList[curListPos],
					&objProps.propsList[curListPos],
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_710
					&errorOptions.intList[curListPos],
					errorHandlers.nameList[curListPos],
#endif
					&status) == AR_RETURN_OK)
				{
					LOG << " (InsideID: " << curListPos << ") [OK]" << endl;						
					curListPos++;

					FreeARStatusList(&status, false);
				}	
				else
					cerr << "Failed to load '" << names.nameList[curListPos] << "' : " << BuildMessageAndFreeStatus(status);
			}

			// now update list counts
			names.numItems = curListPos;
			orders.numItems = curListPos;
			schemas.numItems = curListPos;
			operationSets.numItems = curListPos;
			enabledObjects.numItems = curListPos;
			queries.numItems = curListPos;
			ifActions.numItems = curListPos;
			elseActions.numItems = curListPos;
			helpTexts.numItems = curListPos;
			changedTimes.numItems = curListPos;
			owners.numItems = curListPos;
			changedUsers.numItems = curListPos;
			changeDiary.numItems = curListPos;
			objProps.numItems = curListPos;
			errorOptions.numItems = curListPos;
			errorHandlers.numItems = curListPos;

			if (curListPos > 0 || objectsToLoad->numItems == 0)
				funcResult = true;
		}
	}

	// check if we have to clean up the name list
	if (originalObjectNameCount > 0)
	{
		objectNames.numItems = originalObjectNameCount;
		FreeARNameList(&objectNames, false);
	}

	if (funcResult)
	{
		sortedList.reserve(names.numItems);
		for (unsigned int i=0; i<names.numItems; ++i)
		{
			appRefNames.push_back("");
			errorCallers.push_back(vector<unsigned int>());
			sortedList.push_back(i);
		}
	}

	return funcResult;
}

void CARFilterList::Reserve(unsigned int size)
{
	if (internalListState != CARFilterList::EMPTY) throw AppException("object isnt reusable!", "FilterList");

	sortedList.reserve(size);

	names.numItems = 0;
	names.nameList = new ARNameType[size];

	orders.numItems = 0;
	orders.intList = new unsigned int[size];

	schemas.numItems = 0;
	schemas.workflowConnectList = new ARWorkflowConnectStruct[size];

	operationSets.numItems = 0;
	operationSets.intList = new unsigned int[size];

	enabledObjects.numItems = 0;
	enabledObjects.intList = new unsigned int[size];

	queries.numItems = 0;
	queries.qualifierList = new ARQualifierStruct[size];

	ifActions.numItems = 0;
	ifActions.actionListList = new ARFilterActionList[size];

	elseActions.numItems = 0;
	elseActions.actionListList = new ARFilterActionList[size];

	helpTexts.numItems = 0;
	helpTexts.stringList = new char*[size];

	changedTimes.numItems = 0;
	changedTimes.timestampList = new ARTimestamp[size];

	owners.numItems = 0;
	owners.nameList = new ARAccessNameType[size];

	changedUsers.numItems = 0;
	changedUsers.nameList = new ARAccessNameType[size];

	changeDiary.numItems = 0;
	changeDiary.stringList = new char*[size];

	objProps.numItems = 0;
	objProps.propsList = new ARPropList[size];
	
	errorOptions.numItems = 0;
	errorOptions.intList = new unsigned int[size];

	errorHandlers.numItems = 0;
	errorHandlers.nameList = new ARNameType[size];

	appRefNames.reserve(size);
	errorCallers.reserve(size);

	reservedSize = size;
	internalListState = CARFilterList::INTERNAL_ALLOC;
}

int CARFilterList::AddFilterFromXML(ARXMLParsedStream &stream, const char* filterName, unsigned int *outDocVersion)
{
	if (internalListState != CARFilterList::INTERNAL_ALLOC) throw AppException("illegal usage!", "FilterList");
	if (names.numItems >= reservedSize) return -1;
	if (outDocVersion != NULL) *outDocVersion = 0;
	
	CARInside* arIn = CARInside::GetInstance();
	ARNameType appBlockName; appBlockName[0] = 0;
	ARStatusList status;

	unsigned int arDocVersion = 0;
	unsigned int index = names.numItems;
	strncpy(names.nameList[index], filterName, 254);	// copy name over
	names.nameList[index][254] = 0;

	if (ARGetFilterFromXML(&arIn->arControl,
		&stream,
		names.nameList[index],
		appBlockName,
		&orders.intList[index],
		&schemas.workflowConnectList[index],
		&operationSets.intList[index],
		&enabledObjects.intList[index],
		&queries.qualifierList[index],
		&ifActions.actionListList[index],
		&elseActions.actionListList[index],
		owners.nameList[index],
		changedUsers.nameList[index],
		&changedTimes.timestampList[index],
		&helpTexts.stringList[index],
		&changeDiary.stringList[index],
		&objProps.propsList[index],
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_710
		&errorOptions.intList[index],
		errorHandlers.nameList[index],
#endif
		&arDocVersion,
		&status) == AR_RETURN_OK)
	{
		++names.numItems;
		++orders.numItems;
		++schemas.numItems;
		++operationSets.numItems;
		++enabledObjects.numItems;
		++queries.numItems;
		++ifActions.numItems;
		++elseActions.numItems;
		++helpTexts.numItems;
		++changedTimes.numItems;
		++owners.numItems;
		++changedUsers.numItems;
		++changeDiary.numItems;
		++objProps.numItems;
		++errorOptions.numItems;
		++errorHandlers.numItems;

		sortedList.push_back(index);
		appRefNames.push_back("");
		errorCallers.push_back(vector<unsigned int>());

		if (outDocVersion != NULL) *outDocVersion = arDocVersion;

		return index;
	}
	else
	{
		cerr << BuildMessageAndFreeStatus(status);
		return -1;
	}
}

int CARFilterList::Find(const char* name)
{
	CMapType::const_iterator it = searchList.find(string(name));
	if (it == searchList.end()) return -1;
	return it->second;
}

void CARFilterList::Sort()
{
	if (GetCount() > 0)
	{
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_764
		NormalizeNameListForSorting(names, objProps);
#endif

		GenerateSortableList sortableContent(names);
		std::sort(sortedList.begin(),sortedList.end(),SortByName(sortableContent));
	}

	// setup lookup map
	if (!searchList.empty()) searchList.clear();
	for (unsigned int i = 0; i < sortedList.size(); ++i)
	{
		searchList[string(names.nameList[sortedList[i]])] = i;
	}

#if AR_CURRENT_API_VERSION >= AR_API_VERSION_764
	NormalizeNameListToRealNames(names, objProps);
#endif
}

void CARFilterList::AddOverlayOrCustom(unsigned int index)
{
	overlayAndCustomList.push_back(index);
}

const CARFilterList::ObjectRefList& CARFilterList::GetOverlayAndCustomWorkflow()
{
	return overlayAndCustomList;
}
