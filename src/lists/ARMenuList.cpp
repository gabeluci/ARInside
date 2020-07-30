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

#include "stdafx.h"
#include "ARMenuList.h"
#include "../ARInside.h"
#include "../core/ARStatusList.h"
#include "../output/WebUtil.h"
#include "BlackList.h"

CARMenuList::CARMenuList(void)
{
	internalListState = CARMenuList::EMPTY;
	reservedSize = 0;
	names.numItems = 0;
}

CARMenuList::~CARMenuList(void)
{
	if (internalListState == INTERNAL_ALLOC)
	{
		try
		{
			delete[] names.nameList;
			delete[] refreshCodes.intList;
			delete[] definitions.list;
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
	else if (internalListState == ARAPI_ALLOC)
	{		
		try
		{
			FreeARNameList(&names,false);
			FreeARUnsignedIntList(&refreshCodes,false);
			FreeARCharMenuStructList(&definitions,false);
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

bool CARMenuList::LoadFromServer()
{
	ARBooleanList   mnuExists;
	ARStatusList    status;
	CARInside*      arIn = CARInside::GetInstance();
	ARNameList*     objectsToLoad = NULL;
	ARNameList      objectNames;
	unsigned int    originalObjectNameCount = 0;
	bool            funcResult = false;

	memset(&mnuExists, 0, sizeof(mnuExists));
	memset(&status, 0, sizeof(status));

	// if the blacklist contains menus, we should first load all menu names
	// from the server and remove those that are contained in the blacklist.
	// after that call ARGetMultiple... to retrieve just the needed objects.
	if (arIn->blackList.GetCountOf(ARREF_CHAR_MENU) > 0)
	{
		memset(&objectNames, 0, sizeof(objectNames));

		if (ARGetListCharMenu(&arIn->arControl, 0, NULL, NULL, NULL, &objectNames, &status) == AR_RETURN_OK)
		{
			originalObjectNameCount = objectNames.numItems;
			arIn->blackList.Exclude(ARREF_CHAR_MENU, &objectNames);
			objectsToLoad = &objectNames;
		}
		else
			cerr << BuildMessageAndFreeStatus(status);
	}

	// ok, now retrieve all informations of the menus we need
	if (!arIn->appConfig.slowObjectLoading && ARGetMultipleCharMenus(&arIn->arControl,
		0,
		objectsToLoad,
		&mnuExists,
		&names,
		&refreshCodes,
		&definitions,
		&helpTexts,
		&changedTimes,
		&owners,
		&changedUsers,
		&changeDiary,
		&objProps,
		&status) == AR_RETURN_OK)
	{
		FreeARBooleanList(&mnuExists, false);
		internalListState = CARMenuList::ARAPI_ALLOC;
		funcResult = true;
	}
	else
	{
		cerr << BuildMessageAndFreeStatus(status);

		// ok, fallback to slow data retrieval
		// this could be necessaray if there is a corrupt object that keeps us from getting all at once
		if (!arIn->appConfig.slowObjectLoading)
			cout << "WARN: switching to slow menu loading!" << endl;

		// first check if object names are already loaded
		if (objectsToLoad == NULL)
		{
			// no object names loaded ... now get all names from server
			memset(&objectNames, 0, sizeof(objectNames));

			if (ARGetListCharMenu(&arIn->arControl, 0, NULL, NULL, NULL, &objectNames, &status) == AR_RETURN_OK)
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
				LOG << "Loading Menu: " << objectsToLoad->nameList[i] << " ";

				strncpy(names.nameList[curListPos], objectsToLoad->nameList[i], AR_MAX_NAME_SIZE);
				names.nameList[curListPos][AR_MAX_NAME_SIZE] = 0;

				if (ARGetCharMenu(&arIn->arControl,
					names.nameList[curListPos],
					&refreshCodes.intList[curListPos],
					&definitions.list[curListPos],
					&helpTexts.stringList[curListPos],
					&changedTimes.timestampList[curListPos],
					owners.nameList[curListPos],
					changedUsers.nameList[curListPos],
					&changeDiary.stringList[curListPos],
					&objProps.propsList[curListPos],
					&status) == AR_RETURN_OK)
				{
					LOG << " (InsideID: " << curListPos << ") [OK]" << endl;						
					curListPos++;

					FreeARStatusList(&status, false);
				}	
				else
					cerr << "Failed to load '" << names.nameList[curListPos] << "' : " << BuildMessageAndFreeStatus(status);

				// now update list counts
				names.numItems = curListPos;
				refreshCodes.numItems = curListPos;
				definitions.numItems = curListPos;
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
	}

	// check if we have to clean up the name list
	if (originalObjectNameCount > 0)
	{
		objectNames.numItems = originalObjectNameCount;
		FreeARNameList(&objectNames, false);
	}

	if (funcResult)
	{
		references.resize(names.numItems);
		sortedList.reserve(names.numItems);
		for (unsigned int i=0; i<names.numItems; ++i)
		{
			appRefNames.push_back("");
			sortedList.push_back(i);
		}
	}

	return funcResult;
}

void CARMenuList::Reserve(unsigned int size)
{
	if (internalListState != CARMenuList::EMPTY) throw AppException("object isnt reusable!", "MenuList");

	sortedList.reserve(size);
	appRefNames.reserve(size);
	references.resize(size);

	names.numItems = 0;
	names.nameList = new ARNameType[size];

	refreshCodes.numItems = 0;
	refreshCodes.intList = new unsigned int[size];

	definitions.numItems = 0;
	definitions.list = new ARCharMenuStruct[size];

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

	reservedSize = size;
	internalListState = CARMenuList::INTERNAL_ALLOC;
}

int CARMenuList::AddMenuFromXML(ARXMLParsedStream &stream, const char* menuName, unsigned int *outDocVersion)
{
	if (internalListState != CARMenuList::INTERNAL_ALLOC) throw AppException("illegal usage!", "MenuList");
	if (names.numItems >= reservedSize) return -1;
	if (outDocVersion != NULL) *outDocVersion = 0;
	
	CARInside* arIn = CARInside::GetInstance();
	ARNameType appBlockName; appBlockName[0] = 0;
	ARStatusList status;

	unsigned int arDocVersion = 0;
	unsigned int index = names.numItems;
	strncpy(names.nameList[index], menuName, 254);	// copy name over
	names.nameList[index][254] = 0;

	if (ARGetMenuFromXML(&arIn->arControl,
		&stream,
		names.nameList[index],
		appBlockName,
		&refreshCodes.intList[index],
		&definitions.list[index],
		owners.nameList[index],
		changedUsers.nameList[index],
		&changedTimes.timestampList[index],
		&helpTexts.stringList[index],
		&changeDiary.stringList[index],
		&objProps.propsList[index],
		&arDocVersion,
		&status) == AR_RETURN_OK)
	{
		++names.numItems;
		++refreshCodes.numItems;
		++definitions.numItems;
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

int CARMenuList::Find(const char* name)
{
	CMapType::const_iterator it = searchList.find(string(name));
	if (it == searchList.end()) return -1;
	return it->second;
}

void CARMenuList::Sort()
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

void CARMenuList::AddReference(unsigned int index, const CRefItem &refItem)
{
	references[sortedList[index]].push_back(refItem);
}

bool CARMenuList::ReferenceExists(unsigned int index, const CRefItem &refItem)
{
	ReferenceList::iterator curIt = references[sortedList[index]].begin();
	ReferenceList::iterator endIt = references[sortedList[index]].end();

	for (; curIt != endIt; ++curIt)
	{
		if (*curIt == refItem)
			return true;
	}
	return false;
}

const CARMenuList::ReferenceList& CARMenuList::GetReferences(unsigned int index)
{
	return references[sortedList[index]];
}

void CARMenuList::AddOverlayOrCustom(unsigned int index)
{
	overlayAndCustomList.push_back(index);
}

const CARMenuList::ObjectRefList& CARMenuList::GetOverlayAndCustomWorkflow()
{
	return overlayAndCustomList;
}
