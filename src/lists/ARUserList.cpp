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
#include "ARUserList.h"
#include "../ARInside.h"
#include "../AppConfig.h"
#include "../core/ARStatusList.h"

CARUserList::CARUserList(void)
{
	ARZeroMemory(&owners);
	ARZeroMemory(&changedUsers);
}

CARUserList::~CARUserList(void)
{
	if (owners.nameList != NULL)
		delete[] owners.nameList;

	if (changedUsers.nameList != NULL)
		delete[] changedUsers.nameList;
}

bool CARUserList::LoadFromServer()
{
	bool result = false;
	try
	{
		CARInside* arIn = CARInside::GetInstance();
		AppConfig &appConfig = arIn->appConfig;

		ARQualifierStruct	qualifier;
		ARStatusList status; ARZeroMemory(&status);

		ARNameType schemaName;
		strncpy(schemaName, appConfig.userForm.c_str(), AR_MAX_NAME_SIZE);

		char *qualString;
		qualString = new char[appConfig.userQuery.size() + 1];
		strcpy(qualString, appConfig.userQuery.c_str());

		AREntryListFieldList fields;
		AREntryListFieldValueList values;

		fields.numItems = 11;
		fields.fieldsList = (AREntryListFieldStruct*)new AREntryListFieldStruct[fields.numItems];
		memset(fields.fieldsList,0,sizeof(AREntryListFieldStruct)*fields.numItems);

		int pos = 0;
		fields.fieldsList[pos++].fieldId = AR_RESERV_USER_NAME;         //LoginName
		fields.fieldsList[pos++].fieldId = AR_RESERV_EMAIL;             //Email
		fields.fieldsList[pos++].fieldId = AR_RESERV_GROUP_LIST;        //GroupList
		fields.fieldsList[pos++].fieldId = AR_CORE_SHORT_DESCRIPTION;   //FullName
		fields.fieldsList[pos++].fieldId = AR_RESERV_USER_NOTIFY;       //DefNotify
		fields.fieldsList[pos++].fieldId = AR_RESERV_LICENSE_TYPE;      //LicType
		fields.fieldsList[pos++].fieldId = AR_RESERV_LIC_FULL_TEXT;     //FtLicType
		fields.fieldsList[pos++].fieldId = AR_CORE_SUBMITTER;           //CreatedBy
		fields.fieldsList[pos++].fieldId = AR_CORE_CREATE_DATE;         //Created
		fields.fieldsList[pos++].fieldId = AR_CORE_LAST_MODIFIED_BY;    //ModifiedBy
		fields.fieldsList[pos++].fieldId = AR_CORE_MODIFIED_DATE;       //Modified
		fields.numItems = pos;
		
		for (unsigned int k=0; k<fields.numItems; ++k) { fields.fieldsList[k].columnWidth=1; fields.fieldsList[k].separator[0]='|'; }

		if(ARLoadARQualifierStruct(&arIn->arControl,
			schemaName,
			NULL,
			qualString,
			&qualifier,
			&status) == AR_RETURN_OK)
		{
			// clean up status before we use it again
			FreeARStatusList(&status, false);

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
					// on the first pass reserve space for the expected users
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
						
						// check count and fill-up any missing array items
						if (names.size() < requestId.size()) names.resize(requestId.size());
						if (email.size() < requestId.size()) email.resize(requestId.size());
						if (group.size() < requestId.size()) group.resize(requestId.size());
						if (fullName.size() < requestId.size()) fullName.resize(requestId.size());
						if (defaultNotify.size() < requestId.size()) defaultNotify.resize(requestId.size());
						if (licType.size() < requestId.size()) licType.resize(requestId.size());
						if (ftLicType.size() < requestId.size()) ftLicType.resize(requestId.size());
						if (createDate.size() < requestId.size()) createDate.resize(requestId.size());
						if (modifiedDate.size() < requestId.size()) modifiedDate.resize(requestId.size());
						while (owners.numItems < requestId.size()) { ARZeroMemory(owners.nameList[owners.numItems++]); }
						while (changedUsers.numItems < requestId.size()) { ARZeroMemory(changedUsers.nameList[changedUsers.numItems++]); }
						
						LOG << "User '" << names.back() <<"' [OK]" << endl;
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
	catch(exception& e)
	{		
		throw(AppException(e.what(), "Error loading users.", "CARUserList"));
	}
	return result;
}

void CARUserList::Reserve(unsigned int count)
{
	requestId.reserve(count);
	names.reserve(count);
	email.reserve(count);
	group.reserve(count);
	fullName.reserve(count);
	defaultNotify.reserve(count);
	licType.reserve(count);
	ftLicType.reserve(count);
	createDate.reserve(count);
	modifiedDate.reserve(count);

	owners.numItems = 0;
	owners.nameList = new ARAccessNameType[count];

	changedUsers.numItems = 0;
	changedUsers.nameList = new ARAccessNameType[count];
}

int CARUserList::Find(const string& name)
{
	CMapType::const_iterator it = searchList.find(name);
	if (it == searchList.end()) return -1;
	return it->second;
}

void CARUserList::Sort()
{
	if (GetCount() > 0)
	{
		GenerateSortableList sortableContent(names);
		std::sort(sortedList.begin(),sortedList.end(),SortByName(sortableContent));
	}

	// setup lookup map
	if (!searchList.empty()) searchList.clear();
	for (unsigned int i = 0; i < sortedList.size(); ++i)
	{
		searchList[names[sortedList[i]]] = i;
	}
}

void CARUserList::StoreEntry(ARFieldValueList& value)
{
	for (unsigned int curFieldPos = 0; curFieldPos != value.numItems; ++curFieldPos)
	{
		switch (value.fieldValueList[curFieldPos].fieldId)
		{
		case AR_RESERV_USER_NAME:        //LoginName
			if (value.fieldValueList[curFieldPos].value.dataType == AR_DATA_TYPE_CHAR)
				names.push_back(value.fieldValueList[curFieldPos].value.u.charVal);
			break;
		case AR_RESERV_EMAIL:            //Email
			if (value.fieldValueList[curFieldPos].value.dataType == AR_DATA_TYPE_CHAR)
				email.push_back(value.fieldValueList[curFieldPos].value.u.charVal);
			break;
		case AR_RESERV_GROUP_LIST:       //GroupList
			if (value.fieldValueList[curFieldPos].value.dataType == AR_DATA_TYPE_CHAR)
			{
				vector<int> gids;
				char* curPos = value.fieldValueList[curFieldPos].value.u.charVal;
				if (curPos != NULL)
				{
					do
					{
						int groupId = atoi(curPos);
						gids.push_back(groupId);

						curPos = strchr(curPos,';');
						if (curPos != NULL) ++curPos;
					} while ( curPos != NULL && curPos[0] != 0);
				}
				std::sort(gids.begin(), gids.end());
				group.push_back(gids);
			}
			break;
		case AR_CORE_SHORT_DESCRIPTION:  //FullName
			if (value.fieldValueList[curFieldPos].value.dataType == AR_DATA_TYPE_CHAR)
				fullName.push_back(value.fieldValueList[curFieldPos].value.u.charVal);
			break;
		case AR_RESERV_USER_NOTIFY:      //DefNotify
			if (value.fieldValueList[curFieldPos].value.dataType == AR_DATA_TYPE_ENUM || 
			    value.fieldValueList[curFieldPos].value.dataType == AR_DATA_TYPE_INTEGER)
				defaultNotify.push_back(value.fieldValueList[curFieldPos].value.u.intVal);
			break;
		case AR_RESERV_LICENSE_TYPE:     //LicType
			if (value.fieldValueList[curFieldPos].value.dataType == AR_DATA_TYPE_ENUM || 
			    value.fieldValueList[curFieldPos].value.dataType == AR_DATA_TYPE_INTEGER)
				licType.push_back(value.fieldValueList[curFieldPos].value.u.intVal);
			break;
		case AR_RESERV_LIC_FULL_TEXT:    //FtLicType
			if (value.fieldValueList[curFieldPos].value.dataType == AR_DATA_TYPE_ENUM || 
			    value.fieldValueList[curFieldPos].value.dataType == AR_DATA_TYPE_INTEGER)
				ftLicType.push_back(value.fieldValueList[curFieldPos].value.u.intVal);
			break;
		case AR_CORE_SUBMITTER:          //CreatedBy
			if (value.fieldValueList[curFieldPos].value.dataType == AR_DATA_TYPE_CHAR)
			{
				int index = owners.numItems++;
				strncpy(owners.nameList[index], value.fieldValueList[curFieldPos].value.u.charVal, AR_MAX_ACCESS_NAME_SIZE);
				owners.nameList[index][AR_MAX_ACCESS_NAME_SIZE] = 0;
			}
			break;
		case AR_CORE_CREATE_DATE:        //Created
			if (value.fieldValueList[curFieldPos].value.dataType == AR_DATA_TYPE_TIME)
				createDate.push_back(value.fieldValueList[curFieldPos].value.u.dateVal);
			break;
		case AR_CORE_LAST_MODIFIED_BY:   //ModifiedBy
			if (value.fieldValueList[curFieldPos].value.dataType == AR_DATA_TYPE_CHAR)
			{
				int index = changedUsers.numItems++;
				strncpy(changedUsers.nameList[index], value.fieldValueList[curFieldPos].value.u.charVal, AR_MAX_ACCESS_NAME_SIZE);
				changedUsers.nameList[index][AR_MAX_ACCESS_NAME_SIZE] = 0;
			}
			break;
		case AR_CORE_MODIFIED_DATE:      //Modified
			if (value.fieldValueList[curFieldPos].value.dataType == AR_DATA_TYPE_TIME)
				modifiedDate.push_back(value.fieldValueList[curFieldPos].value.u.dateVal);
			break;
		}
	}
}
