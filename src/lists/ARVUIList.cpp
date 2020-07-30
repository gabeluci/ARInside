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
#include "ARVUIList.h"
#include "../ARInside.h"
#include "../core/ARStatusList.h"

///////////////////////////////////////////////////////////////////////////////
// CARVUIListXML - implementation
void CARVUIListXML::FinishLoading()
{
	if (sortedList.empty() && vuiList.numItems > 0)
	{
		for (unsigned int i = 0; i < vuiList.numItems; ++i)
			sortedList.push_back(i);
	}

	Sort();
}

void CARVUIListXML::Sort()
{
	if (GetCount() > 0)
	{
		GenerateSortableList sortableContent(vuiList);
		std::sort(sortedList.begin(),sortedList.end(),SortByName(sortableContent));
	}
}

int CARVUIListXML::Find(unsigned int vuiId)
{
	unsigned int count = GetCount();
	for (unsigned int i = 0; i < count; ++i)
	{
		if (vuiList.vuiList[sortedList[i]].vuiId == vuiId)
			return i;
	}
	return -1;
}

const ARPropList& CARVUIListXML::VUIGetPropList(unsigned int index) const
{
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_763
	if (vuiList.numItems == 0)
		return emptyPropList;
	return vuiList.vuiList[sortedList[index]].smObjProp;
#else
	return emptyPropList;
#endif
}
///////////////////////////////////////////////////////////////////////////////
// CARVUIListServer - implementation
CARVUIListServer::CARVUIListServer(unsigned int schemaInsideId) 
{
	schemaId = schemaInsideId;
	ARZeroMemory(&ids);
	ARZeroMemory(&names);
	ARZeroMemory(&locales);
	ARZeroMemory(&types);
	ARZeroMemory(&dispProps);
	ARZeroMemory(&helpTexts);
	ARZeroMemory(&changedTimes);
	ARZeroMemory(&owners);
	ARZeroMemory(&changedUsers);
	ARZeroMemory(&changeDiary);
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_763
	ARZeroMemory(&objProps);
#endif
}

CARVUIListServer::~CARVUIListServer()
{
	FreeARInternalIdList(&ids, false);
	FreeARNameList(&names, false);
	FreeARLocaleList(&locales, false);
	FreeARUnsignedIntList(&types, false);
	FreeARPropListList(&dispProps, false);
	FreeARTextStringList(&helpTexts, false);
	FreeARTimestampList(&changedTimes, false);
	FreeARAccessNameList(&owners, false);
	FreeARAccessNameList(&changedUsers, false);
	FreeARTextStringList(&changeDiary, false);
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_763
	FreeARPropListList(&objProps, false);
#endif
}

bool CARVUIListServer::LoadFromServer()
{
	ARBooleanList   vuiExists;
	ARStatusList    status;
	CARInside*      arIn = CARInside::GetInstance();
	ARNameType			schemaName; memcpy(schemaName, arIn->schemaList.SchemaGetName(schemaId), sizeof(ARNameType));

	memset(&vuiExists, 0, sizeof(ARBooleanList));
	memset(&status, 0, sizeof(status));

	if (!arIn->appConfig.slowObjectLoading && ARGetMultipleVUIs(&arIn->arControl,
		schemaName, 
		NULL, // all field ids
		0,    // no changed since restriction
		&vuiExists,
		&ids,
		&names,
		&locales,
		&types,
		&dispProps,
		&helpTexts,
		&changedTimes,
		&owners,
		&changedUsers,
		&changeDiary,
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_763
		&objProps,
#endif
		&status) == AR_RETURN_OK)
	{
		FreeARBooleanList(&vuiExists, false);
		BuildIndex();
		return true;
	}
	else
	{
		cerr << BuildMessageAndFreeStatus(status);

		// ok, fallback to slow data retrieval
		// this could be necessaray if there is a corrupt vui that keeps us from getting all vuis at once
		if (!arIn->appConfig.slowObjectLoading)
			cout << "WARN: switching to slow vui loading for: " << schemaName << endl;

		ARInternalIdList	vuiIdList;
		ARZeroMemory(&vuiIdList);
		if (ARGetListVUI(&arIn->arControl, schemaName, 0, 
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_763
			NULL,
#endif			
			&vuiIdList, &status) == AR_RETURN_OK)
		{
			Reserve(vuiIdList.numItems);

			unsigned int currentWriteIndex = 0;
			for (unsigned int idx = 0; idx < vuiIdList.numItems; ++idx)
			{
				if (ARGetVUI(&arIn->arControl,
					schemaName,
					vuiIdList.internalIdList[idx],
					names.nameList[currentWriteIndex],
					locales.localeList[currentWriteIndex],
					&types.intList[currentWriteIndex],
					&dispProps.propsList[currentWriteIndex],
					&helpTexts.stringList[currentWriteIndex],
					&changedTimes.timestampList[currentWriteIndex],
					owners.nameList[currentWriteIndex],
					changedUsers.nameList[currentWriteIndex],
					&changeDiary.stringList[currentWriteIndex],
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_763
					&objProps.propsList[currentWriteIndex],
#endif
					&status) == AR_RETURN_OK)
				{
					ids.internalIdList[currentWriteIndex++] = vuiIdList.internalIdList[idx];
				}
				else
					cerr << "Schema: " << schemaName << " -- Failed to load vui " << vuiIdList.internalIdList[idx] << ": " << BuildMessageAndFreeStatus(status);
			}
			SetNumItems(currentWriteIndex);
			BuildIndex();
			return true;
		}
		else
		{
			cerr << BuildMessageAndFreeStatus(status);
			return false;
		}
	}
}

int CARVUIListServer::Find(unsigned int vuiId)
{
	unsigned int vuiCount = GetCount();
	for (unsigned int i = 0; i < vuiCount; ++i)
	{
		if (ids.internalIdList[i] == vuiId)
			return i;
	}
	return -1;
}

void CARVUIListServer::Sort()
{
	if (GetCount() > 0)
	{
		GenerateSortableList sortableContent(names);
		std::sort(sortedList.begin(),sortedList.end(),SortByName(sortableContent));
	}
}

const ARPropList& CARVUIListServer::VUIGetPropList(unsigned int index) const
{
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_763
	if (objProps.numItems == 0)
		return emptyPropList;
	return objProps.propsList[sortedList[index]];
#else
	return emptyPropList;
#endif
}

void CARVUIListServer::Reserve(unsigned int amount)
{
	ids.internalIdList = new ARInternalId[amount];
	ARZeroMemory(ids.internalIdList, sizeof(ARInternalId) * amount);

	names.nameList = new ARNameType[amount];
	ARZeroMemory(names.nameList, sizeof(ARNameType) * amount);

	locales.localeList = new ARLocaleType[amount];
	ARZeroMemory(locales.localeList, sizeof(ARLocaleType) * amount);

	types.intList = new unsigned int[amount];
	ARZeroMemory(types.intList, sizeof(unsigned int) * amount);

	dispProps.propsList = new ARPropList[amount];
	ARZeroMemory(dispProps.propsList, sizeof(ARPropList) * amount);
	
	helpTexts.stringList = new char*[amount];
	ARZeroMemory(helpTexts.stringList, sizeof(char*) * amount);

	changedTimes.timestampList = new ARTimestamp[amount];
	ARZeroMemory(changedTimes.timestampList, sizeof(ARTimestamp) * amount);
	
	owners.nameList = new ARAccessNameType[amount];
	ARZeroMemory(owners.nameList, sizeof(ARAccessNameType) * amount);
	
	changedUsers.nameList = new ARAccessNameType[amount];
	ARZeroMemory(changedUsers.nameList, sizeof(ARAccessNameType) * amount);
	
	changeDiary.stringList = new char*[amount];
	ARZeroMemory(changeDiary.stringList, sizeof(char*) * amount);

#if AR_CURRENT_API_VERSION >= AR_API_VERSION_763
	objProps.propsList = new ARPropList[amount];
	ARZeroMemory(objProps.propsList, sizeof(ARPropList) * amount);
#endif
}

void CARVUIListServer::SetNumItems(unsigned int amount)
{
	ids.numItems = amount;
	names.numItems = amount;
	locales.numItems = amount;
	types.numItems = amount;
	dispProps.numItems = amount;
	helpTexts.numItems = amount;
	changedTimes.numItems = amount;
	owners.numItems = amount;
	changedUsers.numItems = amount;
	changeDiary.numItems = amount;
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_763
	objProps.numItems = amount;
#endif
}

void CARVUIListServer::BuildIndex()
{
	sortedList.reserve(names.numItems);
	for (unsigned int i=0; i<names.numItems; ++i)
	{
		sortedList.push_back(i);
	}
}
