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

#include "stdafx.h"
#include "ARImageList.h"
#include "../ARInside.h"
#include "../output/WebUtil.h"
#include "../core/ARImage.h"
#include "../core/ARHandle.h"
#include "../core/ARStatusList.h"

#if AR_CURRENT_API_VERSION >= AR_API_VERSION_750

CARImageList::CARImageList(void)
{
	internalListState = CARImageList::EMPTY;
	reservedSize = 0;
	names.numItems = 0;
}

CARImageList::~CARImageList()
{
	if (internalListState == CARImageList::INTERNAL_ALLOC)
	{
		try
		{
			delete[] names.nameList;
			delete[] types.stringList;
			delete[] changedTimes.timestampList;
			delete[] descriptions.stringList;
			delete[] helpTexts.stringList;
			delete[] owners.nameList;
			delete[] changedUsers.nameList;
			delete[] changeDiary.stringList;
			delete[] objProps.propsList;
			delete[] data.imageList;
		}
		catch (...)
		{
		}
	}
	else if (internalListState == CARImageList::ARAPI_ALLOC)
	{		
		try
		{
			FreeARNameList(&names,false);
			FreeARTextStringList(&types,false);
			FreeARTimestampList(&changedTimes,false);
			FreeARTextStringList(&descriptions,false);
			FreeARTextStringList(&helpTexts,false);
			FreeARAccessNameList(&owners,false);
			FreeARAccessNameList(&changedUsers,false);
			FreeARTextStringList(&changeDiary,false);
			FreeARPropListList(&objProps,false);
			FreeARImageDataList(&data,false);
		}
		catch (...)
		{

		}
	}
}

bool CARImageList::LoadFromServer()
{
	ARBooleanList   imgExists;
	ARStatusList    status;
	CARInside*      arIn = CARInside::GetInstance();

	ARNameList*     objectsToLoad = NULL;
	ARNameList      objectNames;
	unsigned int    originalObjectNameCount = 0;
	bool            funcResult = false;

	ARZeroMemory(&status);
	ARZeroMemory(&imgExists);

	// if the blacklist contains images, we should first load all image names from 
	// the server and remove those that are contained in the blacklist. after that 
	// call ARGetMultipleImages to retrieve just the needed images.
	if (arIn->blackList.GetCountOf(ARREF_IMAGE) > 0)
	{
		memset(&objectNames, 0, sizeof(objectNames));

		if (ARGetListImage(&arIn->arControl, NULL, 0, NULL, 
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_800
			NULL, // objPropList
#endif
			&objectNames, &status) == AR_RETURN_OK)
		{
			originalObjectNameCount = objectNames.numItems;
			arIn->blackList.Exclude(ARREF_IMAGE, &objectNames);
			objectsToLoad = &objectNames;
		}
		else
			cerr << BuildMessageAndFreeStatus(status);
	}

	if (!arIn->appConfig.slowObjectLoading && ARGetMultipleImages(&arIn->arControl,
		0,
		objectsToLoad,
		&imgExists,
		&names,
		&types,
		&changedTimes,
		&descriptions,
		&helpTexts,
		&owners,
		&changedUsers,
		&changeDiary,
		&objProps,
		NULL, // no checksum needed yet
		&data,
		&status) == AR_RETURN_OK)
	{
		FreeARBooleanList(&imgExists, false);
		internalListState = CARImageList::ARAPI_ALLOC;
		funcResult = true;
	}
	else
	{
		cerr << BuildMessageAndFreeStatus(status);

		// ok, fallback to slow data retrieval
		// this could be necessaray if there is a corrupt object that keeps us from getting all at once
		if (!arIn->appConfig.slowObjectLoading)
			cout << "WARN: switching to slow image loading!" << endl;

		// first check if object names are already loaded
		if (objectsToLoad == NULL)
		{
			// no object names loaded ... now get all names from server
			memset(&objectNames, 0, sizeof(objectNames));

			if (ARGetListImage(&arIn->arControl, NULL, 0, NULL, 
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_800
				NULL, // objPropList
#endif
				&objectNames, &status) == AR_RETURN_OK)
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
				LOG << "Loading Image: " << objectsToLoad->nameList[i] << " ";

				strncpy(names.nameList[curListPos], objectsToLoad->nameList[i], AR_MAX_NAME_SIZE);
				names.nameList[curListPos][AR_MAX_NAME_SIZE] = 0;
				
				if (ARGetImage(&arIn->arControl,
					names.nameList[curListPos],
					&data.imageList[curListPos],
					&types.stringList[curListPos],
					&changedTimes.timestampList[curListPos],
					NULL,
					&descriptions.stringList[curListPos],
					&helpTexts.stringList[curListPos],
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
				types.numItems = curListPos;
				changedTimes.numItems = curListPos;
				descriptions.numItems = curListPos;
				helpTexts.numItems = curListPos;
				owners.numItems = curListPos;
				changedUsers.numItems = curListPos;
				changeDiary.numItems = curListPos;
				objProps.numItems = curListPos;
				data.numItems = curListPos;

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
		referenceList.resize(names.numItems);
		sortedList.reserve(names.numItems);
		for (unsigned int i=0; i<names.numItems; ++i)
		{
			sortedList.push_back(i);
		}
	}
	return funcResult;
}

void CARImageList::Reserve(unsigned int size)
{
	if (internalListState != CARImageList::EMPTY) throw AppException("object isnt reusable!", "ImageList");

	sortedList.reserve(size);

	names.numItems = 0;
	names.nameList = new ARNameType[size];

	types.numItems = 0;
	types.stringList = new char*[size];

	changedTimes.numItems = 0;
	changedTimes.timestampList = new ARTimestamp[size];

	descriptions.numItems = 0;
	descriptions.stringList = new char*[size];

	helpTexts.numItems = 0;
	helpTexts.stringList = new char*[size];

	owners.numItems = 0;
	owners.nameList = new ARAccessNameType[size];

	changedUsers.numItems = 0;
	changedUsers.nameList = new ARAccessNameType[size];

	changeDiary.numItems = 0;
	changeDiary.stringList = new char*[size];

	objProps.numItems = 0;
	objProps.propsList = new ARPropList[size];

	data.numItems = 0;
	data.imageList = new ARImageDataStruct[size];

	reservedSize = size;
	internalListState = CARImageList::INTERNAL_ALLOC;

	referenceList.resize(size);
}

int CARImageList::AddImageFromXML(ARXMLParsedStream &stream, const char* imageName)
{
	if (internalListState != CARImageList::INTERNAL_ALLOC) throw AppException("illegal usage!", "ImageList");
	if (names.numItems >= reservedSize) return -1;
	
	CARInside* arIn = CARInside::GetInstance();
	ARNameType appBlockName; appBlockName[0] = 0;
	ARStatusList status;

	unsigned int dataSize = 0;
	unsigned int index = names.numItems;
	strncpy(names.nameList[index], imageName, 254);	// copy name over
	names.nameList[index][254] = 0;
	char *checkSum = NULL;

	if (ARGetImageFromXML(&arIn->arControl,
		&stream,
		names.nameList[index],
		appBlockName,
		&types.stringList[index],
		&data.imageList[index].numItems,
		&checkSum, // checksum isnt needed
		&changedTimes.timestampList[index],
		&descriptions.stringList[index],
		owners.nameList[index],
		changedUsers.nameList[index],
		&helpTexts.stringList[index],
		&changeDiary.stringList[index],
		&objProps.propsList[index],
		(char**)&data.imageList[index].bytes,
		&status) == AR_RETURN_OK)
	{
		++names.numItems;
		++types.numItems;
		++changedTimes.numItems;
		++descriptions.numItems;
		++helpTexts.numItems;
		++owners.numItems;
		++changedUsers.numItems;
		++changeDiary.numItems;
		++objProps.numItems;
		++data.numItems;

		sortedList.push_back(index);

		return index;
	}
	else
	{
		cerr << BuildMessageAndFreeStatus(status);
		return -1;
	}
}

int CARImageList::FindImage(const char* name)
{
	CMapType::const_iterator it = searchList.find(string(name));
	if (it == searchList.end()) return -1;
	return it->second;
}

void CARImageList::Sort()
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

void CARImageList::AddReference(unsigned int index, const CRefItem &referenceItem)
{
	CARHandle<> hObj(referenceItem);
	if (CARInside::GetInstance()->appConfig.bOverlaySupport && hObj.Exists() && !IsVisibleObject(*hObj))
		return;

	referenceList[sortedList[index]].push_back(referenceItem);
}

const CRefItemList& CARImageList::GetReferences(unsigned int index)
{
	return referenceList[sortedList[index]];
}

void CARImageList::AddOverlayOrCustom(unsigned int index)
{
	overlayAndCustomList.push_back(index);
}

const CARImageList::ObjectRefList& CARImageList::GetOverlayAndCustomWorkflow()
{
	return overlayAndCustomList;
}

#endif
