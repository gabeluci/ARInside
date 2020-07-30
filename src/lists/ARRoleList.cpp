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
#include "ARRoleList.h"
#include "../ARInside.h"
#include "../AppConfig.h"
#include "../core/ARStatusList.h"

void GetGroupStringAsVector(const char* groupStr, vector<int>& addToGroupList)
{
	const char* curPos = groupStr;
	if (curPos != NULL)
	{
		do
		{
			int groupId = atoi(curPos);
			addToGroupList.push_back(groupId);
			curPos = strchr(curPos,';');
			if (curPos != NULL) ++curPos;
		} while ( curPos != NULL && curPos[0] != 0);
	}
	std::sort(addToGroupList.begin(), addToGroupList.end());
	addToGroupList.erase(unique(addToGroupList.begin(), addToGroupList.end()), addToGroupList.end());
}

CARRoleList::CARRoleList(void)
{
	ARZeroMemory(&owners);
	ARZeroMemory(&changedUsers);
}

CARRoleList::~CARRoleList(void)
{
	if (owners.nameList != NULL)
		delete[] owners.nameList;

	if (changedUsers.nameList != NULL)
		delete[] changedUsers.nameList;
}

bool CARRoleList::LoadFromServer()
{
	bool result = false;
	try
	{
		CARInside* arIn = CARInside::GetInstance();
		AppConfig &appConfig = arIn->appConfig;

		ARQualifierStruct	qualifier;
		ARStatusList status; ARZeroMemory(&status);

		ARNameType schemaName;
		strncpy(schemaName, appConfig.roleForm.c_str(), AR_MAX_NAME_SIZE);

		char *qualString;
		qualString = new char[appConfig.roleQuery.size() + 1];
		strcpy(qualString, appConfig.roleQuery.c_str());

		AREntryListFieldList fields;
		AREntryListFieldValueList values;

		fields.numItems = 10;
		fields.fieldsList = new AREntryListFieldStruct[fields.numItems];
		memset(fields.fieldsList,0,sizeof(AREntryListFieldStruct)*fields.numItems);

		int pos = 0;
		fields.fieldsList[pos++].fieldId = AR_RESERV_ROLE_MAPPING_APPLICATION; //ApplicationName
		fields.fieldsList[pos++].fieldId = AR_RESERV_ROLE_MAPPING_ROLE_NAME;   //RoleName
		fields.fieldsList[pos++].fieldId = AR_RESERV_ROLE_MAPPING_ROLE_ID;     //RoleID
		fields.fieldsList[pos++].fieldId = AR_RESERV_APP_STATE_TEST;           //GroupName Test
		fields.fieldsList[pos++].fieldId = AR_RESERV_APP_STATE_PRODUCTION;     //GroupName Production
		fields.fieldsList[pos++].fieldId = AR_CORE_SUBMITTER;                  //CreatedBy
		fields.fieldsList[pos++].fieldId = AR_CORE_CREATE_DATE;                //Created
		fields.fieldsList[pos++].fieldId = AR_CORE_LAST_MODIFIED_BY;           //ModifiedBy
		fields.fieldsList[pos++].fieldId = AR_CORE_MODIFIED_DATE;              //Modified
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
					NULL, /* sortList */
					offset,
					0,    /* maxRetrieve */
					0,    /* useLocale */
					&values,
					numMatchesPtr,
					&status);

				if (callResult == AR_RETURN_OK || callResult == AR_RETURN_WARNING)
				{
					// on the first pass reserve space for the expected roles
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
						if (applicationName.size() < requestId.size()) applicationName.resize(requestId.size());
						if (roleId.size() < requestId.size()) roleId.resize(requestId.size());
						if (groupsTest.size() < requestId.size()) groupsTest.resize(requestId.size());
						if (groupsProd.size() < requestId.size()) groupsProd.resize(requestId.size());
						if (createDate.size() < requestId.size()) createDate.resize(requestId.size());
						if (modifiedDate.size() < requestId.size()) modifiedDate.resize(requestId.size());
						while (owners.numItems < requestId.size()) { ARZeroMemory(owners.nameList[owners.numItems++]); }
						while (changedUsers.numItems < requestId.size()) { ARZeroMemory(changedUsers.nameList[changedUsers.numItems++]); }

						LOG << "Role '" << names.back() <<"' [OK]" << endl;	
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
					break;
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
		throw(AppException(e.what(), "Error loading roles.", "CARRoleList"));
	}
	return result;
}

void CARRoleList::Reserve(unsigned int count)
{
	requestId.reserve(count);
	applicationName.reserve(count);
	names.reserve(count);
	roleId.reserve(count);
	groupsTest.reserve(count);
	groupsProd.reserve(count);
	createDate.reserve(count);
	modifiedDate.reserve(count);

	owners.numItems = 0;
	owners.nameList = new ARAccessNameType[count];

	changedUsers.numItems = 0;
	changedUsers.nameList = new ARAccessNameType[count];
}

int CARRoleList::Find(int iRoleId, const string& appName)
{
	unsigned int count = GetCount();
	for (unsigned int i = 0; i < count; ++i)
	{
		if (roleId[sortedList[i]] == iRoleId && applicationName[sortedList[i]] == appName)
		{
			return i;
		}
	}
	return -1;
}

void CARRoleList::Sort()
{
	if (GetCount() > 0)
	{
		GenerateSortableList sortableContent(names);
		std::sort(sortedList.begin(),sortedList.end(),SortByName(sortableContent));
	}
}

void CARRoleList::StoreEntry(ARFieldValueList& value)
{
	for (unsigned int curFieldPos = 0; curFieldPos != value.numItems; ++curFieldPos)
	{
		switch (value.fieldValueList[curFieldPos].fieldId)
		{
		case AR_RESERV_ROLE_MAPPING_APPLICATION:
			if (value.fieldValueList[curFieldPos].value.dataType == AR_DATA_TYPE_CHAR)
				applicationName.push_back(value.fieldValueList[curFieldPos].value.u.charVal);
			break;
		case AR_RESERV_ROLE_MAPPING_ROLE_NAME:
			if (value.fieldValueList[curFieldPos].value.dataType == AR_DATA_TYPE_CHAR)
				names.push_back(value.fieldValueList[curFieldPos].value.u.charVal);
			break;
		case AR_RESERV_ROLE_MAPPING_ROLE_ID:
			if (value.fieldValueList[curFieldPos].value.dataType == AR_DATA_TYPE_INTEGER)
				roleId.push_back(value.fieldValueList[curFieldPos].value.u.intVal);
			break;
		case AR_RESERV_APP_STATE_TEST:
			if (value.fieldValueList[curFieldPos].value.dataType == AR_DATA_TYPE_CHAR)
			{
				vector<int> gids;
				GetGroupStringAsVector(value.fieldValueList[curFieldPos].value.u.charVal, gids);
				groupsTest.push_back(gids);
			}
			break;
		case AR_RESERV_APP_STATE_PRODUCTION:
			if (value.fieldValueList[curFieldPos].value.dataType == AR_DATA_TYPE_CHAR)
			{
				vector<int> gids;
				GetGroupStringAsVector(value.fieldValueList[curFieldPos].value.u.charVal, gids);
				groupsProd.push_back(gids);
			}
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
		}
	}
}
