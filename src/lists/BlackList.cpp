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
#include "BlackList.h"
#include "../ARInside.h"
#include "../core/ARStatusList.h"

// with this its easier to change container type later, if needed
typedef vector<string> BlacklistContainer;
typedef vector<string>::iterator BlacklistIterator;

CBlackList::CBlackList(void)
{
}

CBlackList::~CBlackList(void)
{
}

bool CBlackList::LoadFromServer(const string &packingListName)
{
	if (packingListName.empty()) return true;

	CARInside *pInside = CARInside::GetInstance();

	ARReferenceTypeList   refTypes;
	ARReferenceList       refItems;
	ARStatusList          status;

	int refTypeStorage = ARREF_ALL;
	refTypes.refType = &refTypeStorage;
	refTypes.numItems = 1;
	
	memset(&status, 0, sizeof(ARStatusList));
	memset(&refItems, 0, sizeof(ARStatusList));
	memset(&refTypes, 0, sizeof(ARReferenceTypeList));

	cout << "Loading blacklist from packinglist '" << packingListName << "'" << endl;

	if( ARGetContainer(&pInside->arControl,
		(char*)packingListName.c_str(),
		&refTypes,
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_763
		NULL, // groupListList 
#endif
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		&refItems,
		NULL,
		NULL,
		NULL,					
		NULL,
		NULL,
		NULL,
		&status) == AR_RETURN_OK)
	{
		unsigned int schemaCount = 0;
		unsigned int actlinkCount = 0;
		unsigned int filterCount = 0;
		unsigned int escalationCount = 0;
		unsigned int containerCount = 1;	// start with one, bc the blacklist ifself is excluded by default
		unsigned int menuCount = 0;
		unsigned int imageCount = 0;

		for (unsigned int i=0; i < refItems.numItems; ++i)
		{
			switch (refItems.referenceList[i].type)
			{
			case ARREF_SCHEMA: ++schemaCount; break;
			case ARREF_ACTLINK:	++actlinkCount; break;
			case ARREF_FILTER: ++filterCount; break;
			case ARREF_ESCALATION: ++escalationCount; break;
			case ARREF_CONTAINER: ++containerCount; break;
			case ARREF_CHAR_MENU: ++menuCount; break;
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_750
			case ARREF_IMAGE: ++imageCount; break;
#endif
			}
		}

		// we reserve the needed size to avoid memory fragmentation
		schemas.reserve(schemaCount);
		actlinks.reserve(actlinkCount);
		filters.reserve(filterCount);
		escalations.reserve(escalationCount);
		containers.reserve(containerCount);
		menus.reserve(menuCount);
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_750
		images.reserve(imageCount);
#endif

		// we add the black list too, so its not documented at all
		containers.push_back(packingListName);

		// now store the blacklisted items in the corresponding lists
		for (unsigned int i=0; i < refItems.numItems; ++i)
		{
			BlacklistContainer *list = NULL;

			switch (refItems.referenceList[i].type)
			{
			case ARREF_SCHEMA: list = &schemas; break;
			case ARREF_ACTLINK:	list = &actlinks; break;
			case ARREF_FILTER: list = &filters; break;
			case ARREF_ESCALATION: list = &escalations; break;
			case ARREF_CONTAINER: list = &containers; break;
			case ARREF_CHAR_MENU: list = &menus; break;
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_750
			case ARREF_IMAGE: list = &images; break;
#endif
			default: continue;
			}
			
			list->push_back(refItems.referenceList[i].reference.u.name);
		}

		// to use search algorithms the vectors must be sorted ascending
		if (refItems.numItems > 0)
		{
			sort(schemas.begin(), schemas.end());
			sort(actlinks.begin(), actlinks.end());
			sort(filters.begin(), filters.end());
			sort(escalations.begin(), escalations.end());
			sort(containers.begin(), containers.end());
			sort(menus.begin(), menus.end());
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_750
			sort(images.begin(), images.end());
#endif
		}

		// free the memory of the api structures
		FreeARReferenceTypeList(&refTypes, false);
		FreeARReferenceList(&refItems, false);

		return true;
	}
	else
		cerr << "Failed loading the blacklist: " << BuildMessageAndFreeStatus(status);

	return false;
}

size_t CBlackList::GetCountOf(unsigned int nType)
{
	switch (nType)
	{
	case ARREF_SCHEMA: return schemas.size();
	case ARREF_ACTLINK: return actlinks.size();
	case ARREF_FILTER: return filters.size();
	case ARREF_ESCALATION: return escalations.size();
	case ARREF_CONTAINER: return containers.size();
	case ARREF_CHAR_MENU: return menus.size();
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_750
	case ARREF_IMAGE: return images.size();
#endif
	case ARREF_ALL:
		{
			size_t totalCount = schemas.size();
			totalCount += actlinks.size();
			totalCount += filters.size();
			totalCount += escalations.size();
			totalCount += containers.size();
			totalCount += menus.size();
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_750
			totalCount += images.size();
#endif
			return totalCount;
		}		
	default: return 0;
	}
}

// this function is just for compatibility for CARInside::InBlacklist
// we'll remove this later again.
bool CBlackList::Contains(unsigned int nType, const char *objName)
{
	BlacklistContainer *list = NULL;

	switch (nType)
	{
	case ARREF_SCHEMA: list = &schemas; break;
	case ARREF_ACTLINK:	list = &actlinks; break;
	case ARREF_FILTER: list = &filters; break;
	case ARREF_ESCALATION: list = &escalations; break;
	case ARREF_CONTAINER: list = &containers; break;
	case ARREF_CHAR_MENU: list = &menus; break;
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_750
	case ARREF_IMAGE: list = &images; break;
#endif
	default: return false;
	}
	
	if (list != NULL)
	{
		BlacklistIterator blEndIt = list->end();
		BlacklistIterator blFindIt = lower_bound(list->begin(), blEndIt, objName);
		
		if (blFindIt != blEndIt && (*blFindIt).compare(objName) == 0)
			return true;
	}
	return false;
}

/// This function removes the blacklisted items from the list specified by
/// objNames. The list is changed in place so the caller should backup
/// numItems if necessary.
void CBlackList::Exclude(unsigned int nType, ARNameList *objNames)
{
	if (objNames == NULL || objNames->numItems == 0) return;

	BlacklistContainer *list = NULL;

	switch (nType)
	{
	case ARREF_SCHEMA: list = &schemas; break;
	case ARREF_ACTLINK:	list = &actlinks; break;
	case ARREF_FILTER: list = &filters; break;
	case ARREF_ESCALATION: list = &escalations; break;
	case ARREF_CONTAINER: list = &containers; break;
	case ARREF_CHAR_MENU: list = &menus; break;
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_750
	case ARREF_IMAGE: list = &images; break;
#endif
	default: return;
	}

	CARInside* pInside = CARInside::GetInstance();
	BlacklistIterator blEndIt = list->end();
	BlacklistIterator blBegIt = list->begin();
	unsigned int curObjWriteIndex = 0;
	unsigned int curObjReadIndex = 0;
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_764
	size_t reservedLen = strlen(AR_RESERV_OVERLAY_STRING);
	bool checkForOverlayAndCustomName = (pInside->appConfig.bOverlaySupport && pInside->CompareServerVersion(7,6) >= 0);
#endif

	while (curObjWriteIndex < objNames->numItems)
	{
		string searchFor(objNames->nameList[curObjReadIndex]);

#if AR_CURRENT_API_VERSION >= AR_API_VERSION_764
		// In version 7.6.04 it's not allowed to create objects with "__o" and "__c"
		// at the end (see ARERR8858). Thats great, because now we don't need to
		// check, if this is really a custom- or overlay-object. Simply check if the
		// object name ends with that.
		if (checkForOverlayAndCustomName && (CUtil::StrEndsWith(searchFor, AR_RESERV_OVERLAY_STRING) || CUtil::StrEndsWith(searchFor, AR_RESERV_OVERLAY_CUSTOM_STRING)))
		{
			searchFor.resize(searchFor.length() - reservedLen);
		}
#endif

		// lets see if we could find the current object name in the blacklist
		BlacklistIterator blFindIt = lower_bound(blBegIt, blEndIt, searchFor);
		if (blFindIt == blEndIt || (*blFindIt).compare(searchFor) != 0)
		{
			// not found, keep it
			if (curObjWriteIndex != curObjReadIndex)
			{
				memcpy(objNames->nameList[curObjWriteIndex], objNames->nameList[curObjReadIndex], sizeof(ARNameType));
			}
			++curObjReadIndex;
			++curObjWriteIndex;
		}
		else
		{
			// this object should be removed from the list
			++curObjReadIndex;
			--objNames->numItems;
		}
	}
}
