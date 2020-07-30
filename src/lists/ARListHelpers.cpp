//Copyright (C) 2011 John Luthgers | jls17
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
#include "ARListHelpers.h"
#include "../ARInside.h"

ARPropList emptyPropList;

GenerateSortableList::GenerateSortableList(ARNameList &list)
{
	InitList(list.numItems);
	for (unsigned int i = 0; i < list.numItems; ++i)
	{
		unsigned int curWritePos = 0;
		for (unsigned int j = 0; j < AR_MAX_NAME_SIZE; ++j)
		{
			if (list.nameList[i][j] == ' ' && curWritePos == 0) continue;	// skip space at the beginning
			theList->nameList[i][curWritePos++] = tolower(list.nameList[i][j]);
		}
	}
}

GenerateSortableList::GenerateSortableList(ARFieldInfoList &list)
{
	InitList(list.numItems);
	for (unsigned int i = 0; i < list.numItems; ++i)
	{
		unsigned int curWritePos = 0;
		for (unsigned int j = 0; j < AR_MAX_NAME_SIZE; ++j)
		{
			if (list.fieldList[i].fieldName[j] == ' ' && curWritePos == 0) continue;	// skip space at the beginning
			theList->nameList[i][curWritePos++] = tolower(list.fieldList[i].fieldName[j]);
		}
	}
}

GenerateSortableList::GenerateSortableList(ARVuiInfoList &list)
{
	InitList(list.numItems);
	for (unsigned int i = 0; i < list.numItems; ++i)
	{
		unsigned int curWritePos = 0;
		for (unsigned int j = 0; j < AR_MAX_NAME_SIZE; ++j)
		{
			if (list.vuiList[i].vuiName[j] == ' ' && curWritePos == 0) continue;	// skip space at the beginning
			theList->nameList[i][curWritePos++] = tolower(list.vuiList[i].vuiName[j]);
		}
	}
}

GenerateSortableList::GenerateSortableList(vector<string> &list)
{
	InitList(static_cast<unsigned int>(list.size()));
	for (unsigned int i = 0; i < theList->numItems; ++i)
	{
		unsigned int curWritePos = 0;
		size_t maxSourceLength = list[i].length();
		memset(theList->nameList[i], '\0', AR_MAX_NAME_SIZE + 1);
		
		for (unsigned int j = 0; j < maxSourceLength; ++j)
		{
			if (list[i][j] == ' ' && curWritePos == 0) continue;	// skip space at the beginning
			theList->nameList[i][curWritePos++] = tolower(list[i][j]);
		}
	}
}

GenerateSortableList::~GenerateSortableList()
{
	if (theList != NULL)
	{
		delete[] theList->nameList;
		delete theList;
	}
}

void GenerateSortableList::InitList(unsigned int size)
{
	theList = new ARNameList;
	theList->nameList = new ARNameType[size];
	theList->numItems = size;
}

ARNameList* GenerateSortableList::GetList()
{
	return theList;
}

#if AR_CURRENT_API_VERSION >= AR_API_VERSION_764
/////// additional functions ///////
void NormalizeNameListForSorting(ARNameList &names, ARPropListList &objProps)
{
	// Since ARS 7.6.4 we have two workflow layers, like an object inherited from another. It
	// uses layer-numbering, where 0 is the base layer mostly used for out-of-the-box stuff and
	// 1 is the custom layer. You can switch the active layer on the server. If layer 0 is
	// active only out of the box workflow is executed and visible to clients (WUT/midtier).
	// If layer 1 is active (this is the default) all workflow is inherited from layer 0 and
	// extended by custom workflow or overlaid ones contained in layer 1. ARInside should
	// always document the current workflow execution model, so we have to take the Overlay-
	// Mode into account.
	// overlayMode 0 = only origin workflow should be visible (no custom, no overlay)
	// overlayMode 1 = origin, custom and overlaid workflow should be visible
	// In later version of ARSystem there might be more layers available.

	// for overlays we need to rename the object names accordingly
	unsigned int count = min(names.numItems, objProps.numItems);
	for (unsigned int idx = 0; idx < count; ++idx)
	{
		ARValueStruct* val = CARProplistHelper::Find(objProps.propsList[idx], AR_SMOPROP_OVERLAY_PROPERTY);

		if (val != NULL && val->dataType == AR_DATA_TYPE_INTEGER)
		{
			switch (val->u.intVal)
			{
			case AR_OVERLAID_OBJECT:
				{
					if (CARInside::GetInstance()->overlayMode == 1)
					{
						// add the AR_RESERVED_OVERLAY_STRING to the end of the name .. this becomes the original object: "__o" ;-)
						strncat(names.nameList[idx], AR_RESERV_OVERLAY_STRING, AR_MAX_NAME_SIZE);
						names.nameList[idx][AR_MAX_NAME_SIZE] = 0;
					}
				}
				break;
			case AR_OVERLAY_OBJECT:
				{
					if (CARInside::GetInstance()->overlayMode == 1)
					{
						// strip the AR_RESERVED_OVERLAY_STRING from end of the name, so it gets the real object name
						size_t nameLen = strlen(names.nameList[idx]);
						if (nameLen > 3)
						{
							nameLen -= 3;
							if (strcmp(&names.nameList[idx][nameLen], AR_RESERV_OVERLAY_STRING) == 0)
								names.nameList[idx][nameLen] = 0;
						}
					}
				}
			case AR_CUSTOM_OBJECT:
				{
					// strip the AR_RESERV_OVERLAY_CUSTOM_STRING from end of the name, so it gets the real object name
					size_t nameLen = strlen(names.nameList[idx]);
					if (nameLen > 3)
					{
						nameLen -= 3;
						if (strcmp(&names.nameList[idx][nameLen], AR_RESERV_OVERLAY_CUSTOM_STRING) == 0)
							names.nameList[idx][nameLen] = 0;
					}
				}
				break;
			}
		}
	}
}

void NormalizeNameListToRealNames(ARNameList &names, ARPropListList &objProps)
{
	// now make sure the real object names are used
	unsigned int count = min(names.numItems, objProps.numItems);
	for (unsigned int idx = 0; idx < count; ++idx)
	{
		ARValueStruct* val = CARProplistHelper::Find(objProps.propsList[idx], AR_SMOPROP_OVERLAY_PROPERTY);

		if (val != NULL && val->dataType == AR_DATA_TYPE_INTEGER)
		{
			switch (val->u.intVal)
			{
			case AR_OVERLAID_OBJECT:  // this occurs if overlayMode = 1
			case AR_OVERLAY_OBJECT:   // this occurs if overlayMode = 0
				{
					// strip the AR_RESERVED_OVERLAY_STRING again, so it gets the real object name
					size_t nameLen = strlen(names.nameList[idx]);
					if (nameLen > 3)
					{
						nameLen -= 3;
						if (strcmp(&names.nameList[idx][nameLen], AR_RESERV_OVERLAY_STRING) == 0)
							names.nameList[idx][nameLen] = 0;
					}
				}
				break;
			}
		}
	}
}
#endif
