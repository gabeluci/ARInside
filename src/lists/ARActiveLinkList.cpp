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
#include "ARActiveLinkList.h"
#include "../ARInside.h"
#include "../core/ARStatusList.h"
#include "../output/WebUtil.h"
#include "../output/IFileStructure.h"
#include "BlackList.h"

CARActiveLinkList::CARActiveLinkList(void)
{
	internalListState = CARActiveLinkList::EMPTY;
	reservedSize = 0;
	names.numItems = 0;
}

CARActiveLinkList::~CARActiveLinkList(void)
{
	if (internalListState == CARActiveLinkList::INTERNAL_ALLOC)
	{
		try
		{
			delete[] names.nameList;
			delete[] orders.intList;
			delete[] schemas.workflowConnectList;
			delete[] groups.internalIdListList;
			delete[] execMasks.intList;
			delete[] controlFields.internalIdList;
			delete[] focusFields.internalIdList;
			delete[] enabledObjects.intList;
			delete[] queries.qualifierList;
			delete[] ifActions.actionListList;
			delete[] elseActions.actionListList;
			delete[] changedTimes.timestampList;
			delete[] helpTexts.stringList;
			delete[] owners.nameList;
			delete[] changedUsers.nameList;
			delete[] changeDiary.stringList;
			delete[] objProps.propsList;
		}
		catch (...)
		{
		}
	}
	else if (internalListState == CARActiveLinkList::ARAPI_ALLOC)
	{		
		try
		{
			FreeARNameList(&names,false);
			FreeARUnsignedIntList(&orders,false);
			FreeARWorkflowConnectList(&schemas,false);
			FreeARInternalIdListList(&groups,false);
			FreeARUnsignedIntList(&execMasks,false);
			FreeARInternalIdList(&controlFields,false);
			FreeARInternalIdList(&focusFields,false);
			FreeARUnsignedIntList(&enabledObjects,false);
			FreeARQualifierList(&queries,false);
			FreeARActiveLinkActionListList(&ifActions,false);
			FreeARActiveLinkActionListList(&elseActions,false);
			FreeARTextStringList(&helpTexts,false);
			FreeARTimestampList(&changedTimes,false);
			FreeARAccessNameList(&owners,false);
			FreeARAccessNameList(&changedUsers,false);
			FreeARTextStringList(&changeDiary,false);
			FreeARPropListList(&objProps,false);
		}
		catch (...)
		{

		}
	}
}

bool CARActiveLinkList::LoadFromServer()
{
	ARBooleanList   alExists;
	ARStatusList    status;
	CARInside*      arIn = CARInside::GetInstance();
	ARNameList*     objectsToLoad = NULL;
	ARNameList      objectNames;
	unsigned int    originalObjectNameCount = 0;
	bool            funcResult = false;

	memset(&alExists, 0, sizeof(alExists));
	memset(&status, 0, sizeof(status));

	// if the blacklist contains active links, we should first load all active link names
	// from the server and remove those that are contained in the blacklist. after that 
	// call ARGetMultipleActiveLinks to retrieve just the needed active links.
	if (arIn->blackList.GetCountOf(ARREF_ACTLINK) > 0)
	{
		memset(&objectNames, 0, sizeof(objectNames));

		if (ARGetListActiveLink(&arIn->arControl, NULL, 0, NULL, &objectNames, &status) == AR_RETURN_OK)
		{
			originalObjectNameCount = objectNames.numItems;
			arIn->blackList.Exclude(ARREF_ACTLINK, &objectNames);
			objectsToLoad = &objectNames;
		}
		else
			cerr << BuildMessageAndFreeStatus(status);
	}

	// ok, now retrieve all informations of the active links we need
	if (!arIn->appConfig.slowObjectLoading && ARGetMultipleActiveLinks(&arIn->arControl,
		0,
		objectsToLoad,
		&alExists,
		&names,
		&orders,
		&schemas,
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_763
		NULL, // groupListList // TODO: support static inherited permissions
#endif
		&groups,
		&execMasks,
		&controlFields,
		&focusFields,
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
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_750 // Version 7.5 and higher
		NULL,NULL,  // as of version 7.5 this two parameters should be NULL; reserverd for future use
#endif
		&status) == AR_RETURN_OK)
	{
		FreeARBooleanList(&alExists, false);
		internalListState = CARActiveLinkList::ARAPI_ALLOC;
		funcResult = true;
	}
	else
	{
		cerr << BuildMessageAndFreeStatus(status);

		// ok, fallback to slow data retrieval
		// this could be necessaray if there is a corrupt actlink that keeps us from getting all activelinks at once
		if (!arIn->appConfig.slowObjectLoading)
			cout << "WARN: switching to slow activelink loading!" << endl;

		// first check if active link names are already loaded
		if (objectsToLoad == NULL)
		{
			// no activelink names loaded ... now get all names from server
			memset(&objectNames, 0, sizeof(objectNames));

			if (ARGetListActiveLink(&arIn->arControl, NULL, 0, NULL, &objectNames, &status) == AR_RETURN_OK)
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

			// use a separate counter for the store index, because if an activelink can't be loaded, this index is not incremented
			unsigned int curListPos = 0; 

			// now load each actlink
			for (unsigned int i=0; i < objectsToLoad->numItems; ++i)
			{
				LOG << "Loading ActiveLink: " << objectsToLoad->nameList[i] << " ";

				strncpy(names.nameList[curListPos], objectsToLoad->nameList[i], AR_MAX_NAME_SIZE);
				names.nameList[curListPos][AR_MAX_NAME_SIZE] = 0;
				
				if( ARGetActiveLink(&arIn->arControl, 
					names.nameList[curListPos], 
					&orders.intList[curListPos],
					&schemas.workflowConnectList[curListPos],
	#if AR_CURRENT_API_VERSION >= AR_API_VERSION_763
			NULL, // groupListList // TODO: support static inherited permissions
	#endif
					&groups.internalIdListList[curListPos],
					&execMasks.intList[curListPos],
					&controlFields.internalIdList[curListPos],
					&focusFields.internalIdList[curListPos],
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
	#if AR_CURRENT_API_VERSION >= AR_API_VERSION_750
					NULL,NULL,  // as of version 7.5 this two parameters should be NULL; reserverd for future use
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
			groups.numItems = curListPos;
			execMasks.numItems = curListPos;
			controlFields.numItems = curListPos;
			focusFields.numItems = curListPos;
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
		// now allocate/initialize helper data and additional lists
		sortedList.reserve(names.numItems);
		for (unsigned int i=0; i<names.numItems; ++i)
		{
			appRefNames.push_back("");
			sortedList.push_back(i);
		}
	}
	return funcResult;
}

void CARActiveLinkList::Reserve(unsigned int size)
{
	if (internalListState != CARActiveLinkList::EMPTY) throw AppException("object isnt reusable!", "ActiveLinkList");

	sortedList.reserve(size);

	names.numItems = 0;
	names.nameList = new ARNameType[size];

	orders.numItems = 0;
	orders.intList = new unsigned int[size];

	schemas.numItems = 0;
	schemas.workflowConnectList = new ARWorkflowConnectStruct[size];

	groups.numItems = 0;
	groups.internalIdListList = new ARInternalIdList[size];

	execMasks.numItems = 0;
	execMasks.intList = new unsigned int[size];

	controlFields.numItems = 0;
	controlFields.internalIdList = new ARInternalId[size];

	focusFields.numItems = 0;
	focusFields.internalIdList= new ARInternalId[size];

	enabledObjects.numItems = 0;
	enabledObjects.intList = new unsigned int[size];

	queries.numItems = 0;
	queries.qualifierList = new ARQualifierStruct[size];

	ifActions.numItems = 0;
	ifActions.actionListList = new ARActiveLinkActionList[size];

	elseActions.numItems = 0;
	elseActions.actionListList = new ARActiveLinkActionList[size];

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

	appRefNames.reserve(size);

	reservedSize = size;
	internalListState = CARActiveLinkList::INTERNAL_ALLOC;
}

int CARActiveLinkList::AddActiveLinkFromXML(ARXMLParsedStream &stream, const char* actlinkName, unsigned int *outDocVersion)
{
	if (internalListState != CARActiveLinkList::INTERNAL_ALLOC) throw AppException("illegal usage!", "ActiveLinkList");
	if (names.numItems >= reservedSize) return -1;
	if (outDocVersion != NULL) *outDocVersion = 0;
	
	CARInside* arIn = CARInside::GetInstance();
	ARNameType appBlockName; appBlockName[0] = 0;
	ARStatusList status;

	unsigned int arDocVersion = 0;
	unsigned int index = names.numItems;
	strncpy(names.nameList[index], actlinkName, 254);	// copy name over
	names.nameList[index][254] = 0;

	if (ARGetActiveLinkFromXML(&arIn->arControl,
		&stream,
		names.nameList[index],
		appBlockName,
		&orders.intList[index],
		&schemas.workflowConnectList[index],
		&groups.internalIdListList[index],
		&execMasks.intList[index],
		&controlFields.internalIdList[index],
		&focusFields.internalIdList[index],
		&enabledObjects.intList[index],
		&queries.qualifierList[index],
		&ifActions.actionListList[index],
		&elseActions.actionListList[index],
		NULL, // what is support file info for?
		owners.nameList[index],
		changedUsers.nameList[index],
		&changedTimes.timestampList[index],
		&helpTexts.stringList[index],
		&changeDiary.stringList[index],
		&objProps.propsList[index],
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_750 // Version 7.5 and higher
		NULL,NULL,  // as of version 7.5 this two parameters should be NULL; reserverd for future use
#endif
		&arDocVersion,
		&status) == AR_RETURN_OK)
	{
		++names.numItems;
		++orders.numItems;
		++schemas.numItems;
		++groups.numItems;
		++execMasks.numItems;
		++controlFields.numItems;
		++focusFields.numItems;
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

		sortedList.push_back(index);
		appRefNames.push_back("");

		if (outDocVersion != NULL) *outDocVersion = arDocVersion;

		return index;
	}
	else
	{
		cerr << BuildMessageAndFreeStatus(status);
		return -1;
	}
}

int CARActiveLinkList::Find(const char* name)
{
	CMapType::const_iterator it = searchList.find(string(name));
	if (it == searchList.end()) return -1;
	return it->second;
}


void CARActiveLinkList::Sort()
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

void CARActiveLinkList::AddOverlayOrCustom(unsigned int index)
{
	overlayAndCustomList.push_back(index);
}

const CARActiveLinkList::ObjectRefList& CARActiveLinkList::GetOverlayAndCustomWorkflow()
{
	return overlayAndCustomList;
}
