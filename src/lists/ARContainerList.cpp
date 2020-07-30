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
#include "ARContainerList.h"
#include "../ARInside.h"
#include "../core/ARStatusList.h"
#include "BlackList.h"

CARContainerList::CARContainerList(void)
{
	internalListState = EMPTY;
	reservedSize = 0;
	
	ARZeroMemory(&names);
	ARZeroMemory(&permissions);
	ARZeroMemory(&subadmins);
	ARZeroMemory(&ownerObjects);
	ARZeroMemory(&labels);
	ARZeroMemory(&descriptions);
	ARZeroMemory(&types);
	ARZeroMemory(&content);
	ARZeroMemory(&helpTexts);
	ARZeroMemory(&changedTimes);
	ARZeroMemory(&owners);
	ARZeroMemory(&changedUsers);
	ARZeroMemory(&changeDiary);
	ARZeroMemory(&objProps);
}

CARContainerList::~CARContainerList(void)
{
	if (internalListState == INTERNAL_ALLOC)
	{
		try
		{
			delete[] names.nameList;
			delete[] permissions.permissionList;
			delete[] subadmins.internalIdListList;
			delete[] ownerObjects.ownerObjListList;
			delete[] labels.stringList;
			delete[] descriptions.stringList;
			delete[] types.intList;
			delete[] content.referenceListList;
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
			FreeARPermissionListList(&permissions,false);
			FreeARInternalIdListList(&subadmins,false);
			FreeARContainerOwnerObjListList(&ownerObjects,false);
			FreeARTextStringList(&labels,false);
			FreeARTextStringList(&descriptions,false);
			FreeARUnsignedIntList(&types,false);
			FreeARReferenceListList(&content,false);
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

bool CARContainerList::LoadFromServer()
{
	ARBooleanList   cntExists;
	ARStatusList    status;
	CARInside*      arIn = CARInside::GetInstance();
	ARNameList*     objectsToLoad = NULL;
	ARNameList      objectNames;
	unsigned int    originalObjectNameCount = 0;
	bool            funcResult = false;

	ARZeroMemory(&cntExists);
	ARZeroMemory(&status);
	
	objectNames.numItems = 0;

	// if the blacklist contains containers, we should first load all names
	// from the server and remove those that are contained in the blacklist.
	// after that call ARGetMultiple... to retrieve just the needed objects.
	if (arIn->blackList.GetCountOf(ARREF_CONTAINER) > 0)
	{
		ARContainerInfoList cntInfoList;
		ARZeroMemory(&objectNames);
		ARZeroMemory(&cntInfoList);
		if (ARGetListContainer(&arIn->arControl, 0, NULL, AR_HIDDEN_INCREMENT, NULL, NULL, &cntInfoList, &status) == AR_RETURN_OK)
		{
			// create a temporate ARNameList
			objectNames.numItems = cntInfoList.numItems;
			objectNames.nameList = new ARNameType[cntInfoList.numItems];
			for (unsigned int index = 0; index < cntInfoList.numItems; ++index)
				memcpy(&objectNames.nameList[index], cntInfoList.conInfoList[index].name, sizeof(ARNameType));

			// clean up the structs we dont need anymore
			FreeARContainerInfoList(&cntInfoList, false);

			// backup count and exclude all name contained in the blacklist
			originalObjectNameCount = objectNames.numItems;
			arIn->blackList.Exclude(ARREF_CONTAINER, &objectNames);
			objectsToLoad = &objectNames;
		}
		else
			cerr << BuildMessageAndFreeStatus(status);
	}

	// ok, now retrieve all informations of the containers we need
	if (!arIn->appConfig.slowObjectLoading && ARGetMultipleContainers(&arIn->arControl,
		0,
		objectsToLoad,
		NULL,
		AR_HIDDEN_INCREMENT,
		NULL, // owners list
		NULL,
		&cntExists,
		&names,
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_763
		NULL, // groupListList // TODO: support static inherited permissions
#endif
		&permissions,
		&subadmins,
		&ownerObjects,
		&labels,
		&descriptions,
		&types,
		&content,
		&helpTexts,
		&owners,
		&changedTimes,
		&changedUsers,
		&changeDiary,
		&objProps,
		&status) == AR_RETURN_OK)
	{
		FreeARBooleanList(&cntExists, false);
		internalListState = ARAPI_ALLOC;
		funcResult = true;
	}
	else
	{
		cerr << BuildMessageAndFreeStatus(status);

		// ok, fallback to slow data retrieval
		if (!arIn->appConfig.slowObjectLoading)
			cout << "WARN: switching to slow container loading!" << endl;

		// first check if container names are already loaded
		if (objectsToLoad == NULL)
		{
			// no names loaded ... now get all names from server
			memset(&objectNames, 0, sizeof(objectNames));
			
			ARContainerInfoList contNames;			
			ARZeroMemory(&contNames);

			if (ARGetListContainer(&arIn->arControl, 0, NULL, AR_HIDDEN_INCREMENT, NULL, NULL, &contNames, &status) == AR_RETURN_OK)
			{
				// create a temporate ARNameList
				objectNames.numItems = contNames.numItems;
				objectNames.nameList = new ARNameType[contNames.numItems];
				for (unsigned int index = 0; index < contNames.numItems; ++index)
					memcpy(&objectNames.nameList[index], contNames.conInfoList[index].name, sizeof(ARNameType));

				// clean up the structs we dont need anymore
				FreeARContainerInfoList(&contNames, false);

				// backup count
				originalObjectNameCount = contNames.numItems;
				objectsToLoad = &objectNames;
			}
			else
				cerr << BuildMessageAndFreeStatus(status);
		}

		if (objectsToLoad != NULL && objectsToLoad->numItems > 0)
		{
			// allocate needed size for internal lists
			this->Reserve(objectsToLoad->numItems);

			// use a separate counter for the store index, because if an object can't be loaded, this index is not incremented
			unsigned int curListPos = 0; 

			// now load each object
			for (unsigned int i=0; i < objectsToLoad->numItems; ++i)
			{
				LOG << "Loading Container: " << objectsToLoad->nameList[i] << " ";

				strncpy(names.nameList[curListPos], objectsToLoad->nameList[i], AR_MAX_NAME_SIZE);
				names.nameList[curListPos][AR_MAX_NAME_SIZE] = 0;
				
				if(ARGetContainer(&arIn->arControl,
					names.nameList[curListPos],
					NULL,
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_763
					NULL, // groupListList // TODO: support static inherited permissions
#endif
					&permissions.permissionList[curListPos],
					&subadmins.internalIdListList[curListPos],
					&ownerObjects.ownerObjListList[curListPos],
					&labels.stringList[curListPos],
					&descriptions.stringList[curListPos],
					&types.intList[curListPos],
					&content.referenceListList[curListPos],
					&helpTexts.stringList[curListPos],
					owners.nameList[curListPos],
					&changedTimes.timestampList[curListPos],
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
				permissions.numItems = curListPos;
				subadmins.numItems = curListPos;
				ownerObjects.numItems = curListPos;
				labels.numItems = curListPos;
				descriptions.numItems = curListPos;
				types.numItems = curListPos;
				content.numItems = curListPos;
				helpTexts.numItems = curListPos;
				changedTimes.numItems = curListPos;
				owners.numItems = curListPos;
				changedUsers.numItems = curListPos;
				changeDiary.numItems = curListPos;
				objProps.numItems = curListPos;

				if (curListPos > 0)
					funcResult = true;
			}
		}
	}

	// check if we have to clean up the name list
	if (originalObjectNameCount > 0)
	{
		objectNames.numItems = originalObjectNameCount;
		delete[] objectNames.nameList;
	}

	if (funcResult)
	{
		sortedList.reserve(names.numItems);
		for (unsigned int i=0; i<names.numItems; ++i)
		{
			appRefNames.push_back("");
			sortedList.push_back(i);
		}
		references.resize(names.numItems);
	}

	return funcResult;
}

void CARContainerList::Reserve(unsigned int size)
{
	if (internalListState != EMPTY) throw AppException("object isnt reusable!", "ContainerList");

	sortedList.reserve(size);
	appRefNames.reserve(size);

	names.numItems = 0;
	names.nameList = new ARNameType[size];

	permissions.numItems = 0;
	permissions.permissionList = new ARPermissionList[size];

	subadmins.numItems = 0;
	subadmins.internalIdListList = new ARInternalIdList[size];

	ownerObjects.numItems = 0;
	ownerObjects.ownerObjListList = new ARContainerOwnerObjList[size];

	labels.numItems = 0;
	labels.stringList = new char*[size];

	descriptions.numItems = 0;
	descriptions.stringList = new char*[size];

	types.numItems = 0;
	types.intList = new unsigned int[size];

	content.numItems = 0;
	content.referenceListList = new ARReferenceList[size];

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

	references.resize(size);

	reservedSize = size;
	internalListState = INTERNAL_ALLOC;
}

int CARContainerList::AddContainerFromXML(ARXMLParsedStream &stream, const char* containerName, unsigned int *outDocVersion)
{
	if (internalListState != INTERNAL_ALLOC) throw AppException("illegal usage!", "ContainerList");
	if (names.numItems >= reservedSize) return -1;
	if (outDocVersion != NULL) *outDocVersion = 0;
	
	CARInside* arIn = CARInside::GetInstance();
	ARNameType appBlockName; appBlockName[0] = 0;
	ARStatusList status;

	unsigned int arDocVersion = 0;
	unsigned int index = names.numItems;
	strncpy(names.nameList[index], containerName, 254);	// copy name over
	names.nameList[index][254] = 0;

	if (ARGetContainerFromXML(&arIn->arControl,
		&stream,
		names.nameList[index],
		appBlockName,
		&permissions.permissionList[index],
		&subadmins.internalIdListList[index],
		&ownerObjects.ownerObjListList[index],
		&labels.stringList[index],
		&descriptions.stringList[index],
		&types.intList[index],
		&content.referenceListList[index],
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
		++permissions.numItems;
		++subadmins.numItems;
		++ownerObjects.numItems;
		++labels.numItems;
		++descriptions.numItems;
		++types.numItems;
		++content.numItems;
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

int CARContainerList::Find(const char* name)
{
	CMapType::const_iterator it = searchList.find(string(name));
	if (it == searchList.end()) return -1;
	return it->second;
}

void CARContainerList::Sort()
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

void CARContainerList::AddOverlayOrCustom(unsigned int index)
{
	overlayAndCustomList.push_back(index);
}

const CARContainerList::ObjectRefList& CARContainerList::GetOverlayAndCustomWorkflow()
{
	return overlayAndCustomList;
}

void CARContainerList::AddReference(unsigned int index, const CRefItem &refItem)
{
	if (!ReferenceExists(index, refItem))
		references[sortedList[index]].push_back(refItem);
}

bool CARContainerList::ReferenceExists(unsigned int index, const CRefItem &refItem)
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

const CARContainerList::ReferenceList& CARContainerList::GetReferences(unsigned int index)
{
	return references[sortedList[index]];
}
