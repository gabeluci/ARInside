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
#include "ARGroupList.h"
#include "../ARInside.h"
#include "../AppConfig.h"
#include "../core/ARStatusList.h"

CARGroupList::CARGroupList(void)
{
}

CARGroupList::~CARGroupList(void)
{
}


bool CARGroupList::LoadFromServer()
{
	bool result = false;
	try
	{
		CARInside* arIn = CARInside::GetInstance();
		AppConfig &appConfig = arIn->appConfig;

		ARQualifierStruct	qualifier;
		ARStatusList status; ARZeroMemory(&status);

		ARNameType schemaName;
		strncpy(schemaName, appConfig.groupForm.c_str(), AR_MAX_NAME_SIZE);

		char *qualString;
		qualString = new char[appConfig.groupQuery.size() + 1];
		strcpy(qualString, appConfig.groupQuery.c_str());

		AREntryListFieldList fields;
		AREntryListFieldValueList values;

		fields.numItems = 10;
		fields.fieldsList = (AREntryListFieldStruct*)new AREntryListFieldStruct[fields.numItems];
		memset(fields.fieldsList,0,sizeof(AREntryListFieldStruct)*fields.numItems);
		ARZeroMemory(&values);

		int pos = 0;
		fields.fieldsList[pos++].fieldId = AR_RESERV_GROUP_NAME;     //GroupName
		fields.fieldsList[pos++].fieldId = AR_RESERV_GROUP_ID;       //GroupId
		fields.fieldsList[pos++].fieldId = AR_RESERV_GROUP_TYPE;     //GroupType
		fields.fieldsList[pos++].fieldId = AR_CORE_SHORT_DESCRIPTION;//LongGroupName
		fields.fieldsList[pos++].fieldId = AR_CORE_SUBMITTER;        //CreatedBy
		fields.fieldsList[pos++].fieldId = AR_CORE_CREATE_DATE;      //Created
		fields.fieldsList[pos++].fieldId = AR_CORE_LAST_MODIFIED_BY; //ModifiedBy
		fields.fieldsList[pos++].fieldId = AR_CORE_MODIFIED_DATE;    //Modified
		if (arIn->CompareServerVersion(7,0) >= 0)
		{
			// if serv ver >= 7.0 get "Category" and "Computed Group Definition" field
			fields.fieldsList[pos++].fieldId = AR_RESERV_GROUP_CATEGORY;      //Category
			fields.fieldsList[pos++].fieldId = AR_RESERV_COMPUTED_GROUP_QUAL; //Computed Group Definition
		}
		fields.numItems = pos;

		for (unsigned int k=0; k<fields.numItems; ++k) { fields.fieldsList[k].columnWidth=1; fields.fieldsList[k].separator[0]='|'; }

		if(ARLoadARQualifierStruct(&arIn->arControl, 
			schemaName,
			NULL,
			qualString,
			&qualifier, 
			&status) == AR_RETURN_OK)
		{
			unsigned int offset = 0;
			unsigned int numMatches = 0;

			do
			{
				// the matches are just loaded on the first pass
				unsigned int *numMatchesPtr = (offset == 0 ? &numMatches : NULL);

				int callResult = ARGetListEntryWithFields(
					&arIn->arControl,
					schemaName,
					&qualifier,
					&fields,
					NULL,  // sortList
					offset,
					0,     // maxRetrieve
					0,     // useLocale
					&values,
					numMatchesPtr,
					&status);

				if (callResult == AR_RETURN_OK || callResult == AR_RETURN_WARNING)
				{
					// on the first pass reserve space for the expected groups
					if (numMatchesPtr != NULL && numMatches > 0)
						Reserve(numMatches);

					for (unsigned int row=0; row<values.numItems; ++row)
					{
						if (values.entryList[row].entryValues->numItems != fields.numItems)
							continue;

						AREntryIdList& entryId = values.entryList[row].entryId;
						ARFieldValueList& rowValues = *values.entryList[row].entryValues;

						sortedList.push_back(static_cast<int>(requestId.size()));
						requestId.push_back((entryId.numItems == 1 ? entryId.entryIdList[0] : ""));

						StoreEntry(rowValues);

						if (names.size() < requestId.size()) names.resize(requestId.size());
						if (ids.size() < requestId.size()) ids.resize(requestId.size());
						if (longNames.size() < requestId.size()) longNames.resize(requestId.size());
						if (types.size() < requestId.size()) types.resize(requestId.size());
						if (category.size() < requestId.size()) category.resize(requestId.size());
						if (computedQual.size() < requestId.size()) computedQual.resize(requestId.size());
						if (createDate.size() < requestId.size()) createDate.resize(requestId.size());
						if (modifiedDate.size() < requestId.size()) modifiedDate.resize(requestId.size());
						while (owners.numItems < requestId.size()) { ARZeroMemory(owners.nameList[owners.numItems++]); }
						while (changedUsers.numItems < requestId.size()) { ARZeroMemory(changedUsers.nameList[changedUsers.numItems++]); }

						LOG << "Group '" << names.back() <<"' [OK]" << endl;
					}

					// in case the result set is limited by server, load next chunk
					if (values.numItems > 0 && callResult == AR_RETURN_WARNING && status.numItems > 0 && status.statusList[0].messageNum == AR_WARN_MAX_ENTRIES_SERVER)
					{
						offset += values.numItems;
					}
					else
					{
						offset = 0;
					}

					FreeAREntryListFieldValueList(&values,false);
					if (callResult == AR_RETURN_OK) { result = true; }
				}
				else // ARGetListEntryWithFields failed
				{
					cerr << BuildMessageAndFreeStatus(status);
				}
			}
			while (offset > 0);
			FreeARQualifierStruct(&qualifier, false);
			Sort();
		}
		else // ARLoadARQualifierStruct failed
		{
			cerr << BuildMessageAndFreeStatus(status);
		}

		delete[] fields.fieldsList;
		delete[] qualString;
	}
	catch(exception &e)
	{		
		throw(AppException(e.what(),"Error loading groups.", "CARGroupList"));
	}
	return result;
}

void CARGroupList::Reserve(unsigned int count)
{
	requestId.reserve(count);
	names.reserve(count);
	longNames.reserve(count);
	ids.reserve(count);
	types.reserve(count);
	category.reserve(count);
	computedQual.reserve(count);
	createDate.reserve(count);
	modifiedDate.reserve(count);

	owners.numItems = 0;
	owners.nameList = new ARAccessNameType[count];

	changedUsers.numItems = 0;
	changedUsers.nameList = new ARAccessNameType[count];
}

int CARGroupList::Find(int groupId)
{
	unsigned int count = GetCount();
	for (unsigned int i = 0; i < count; ++i)
	{
		if (ids[sortedList[i]] == groupId)
		{
			return i;
		}
	}
	return -1;
}

void CARGroupList::Sort()
{
	if (GetCount() > 0)
	{
		GenerateSortableList sortableContent(names);
		std::sort(sortedList.begin(),sortedList.end(),SortByName(sortableContent));
	}
}

void CARGroupList::StoreEntry(ARFieldValueList& value)
{
	for (unsigned int curFieldPos = 0; curFieldPos != value.numItems; ++curFieldPos)
	{
		switch (value.fieldValueList[curFieldPos].fieldId)
		{
		case AR_RESERV_GROUP_NAME:
			if (value.fieldValueList[curFieldPos].value.dataType == AR_DATA_TYPE_CHAR)
				names.push_back(value.fieldValueList[curFieldPos].value.u.charVal);
			break;
		case AR_RESERV_GROUP_ID:
			if (value.fieldValueList[curFieldPos].value.dataType == AR_DATA_TYPE_INTEGER)
				ids.push_back(value.fieldValueList[curFieldPos].value.u.intVal);
			break;
		case AR_RESERV_GROUP_TYPE:
			if (value.fieldValueList[curFieldPos].value.dataType == AR_DATA_TYPE_ENUM ||
			    value.fieldValueList[curFieldPos].value.dataType == AR_DATA_TYPE_INTEGER)
				types.push_back(value.fieldValueList[curFieldPos].value.u.intVal);
			break;
		case AR_CORE_SHORT_DESCRIPTION:
			if (value.fieldValueList[curFieldPos].value.dataType == AR_DATA_TYPE_CHAR)
				longNames.push_back(value.fieldValueList[curFieldPos].value.u.charVal);
			break;
		case AR_CORE_SUBMITTER:
			if (value.fieldValueList[curFieldPos].value.dataType == AR_DATA_TYPE_CHAR)
			{
				int index = owners.numItems++;
				strncpy(owners.nameList[index], value.fieldValueList[curFieldPos].value.u.charVal, AR_MAX_ACCESS_NAME_SIZE);
				owners.nameList[index][AR_MAX_ACCESS_NAME_SIZE] = 0;
			}
			break;
		case AR_CORE_CREATE_DATE:
			if (value.fieldValueList[curFieldPos].value.dataType == AR_DATA_TYPE_TIME)
				createDate.push_back(value.fieldValueList[curFieldPos].value.u.dateVal);
			break;
		case AR_CORE_LAST_MODIFIED_BY:
			if (value.fieldValueList[curFieldPos].value.dataType == AR_DATA_TYPE_CHAR)
			{
				int index = changedUsers.numItems++;
				strncpy(changedUsers.nameList[index], value.fieldValueList[curFieldPos].value.u.charVal, AR_MAX_ACCESS_NAME_SIZE);
				changedUsers.nameList[index][AR_MAX_ACCESS_NAME_SIZE] = 0;
			}
			break;
		case AR_CORE_MODIFIED_DATE:
			if (value.fieldValueList[curFieldPos].value.dataType == AR_DATA_TYPE_TIME)
				modifiedDate.push_back(value.fieldValueList[curFieldPos].value.u.dateVal);
			break;
		case AR_RESERV_GROUP_CATEGORY:
			if (value.fieldValueList[curFieldPos].value.dataType == AR_DATA_TYPE_ENUM ||
			    value.fieldValueList[curFieldPos].value.dataType == AR_DATA_TYPE_INTEGER)
				category.push_back(value.fieldValueList[curFieldPos].value.u.enumVal);
			break;
		case AR_RESERV_COMPUTED_GROUP_QUAL:
			if (value.fieldValueList[curFieldPos].value.dataType == AR_DATA_TYPE_CHAR)
				computedQual.push_back(value.fieldValueList[curFieldPos].value.u.charVal);
			break;
		}
	}
}
