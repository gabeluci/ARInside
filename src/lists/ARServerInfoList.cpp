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
#include "ARServerInfoList.h"
#include "../ARInside.h"
#include "../core/ARStatusList.h"
#include "../core/ARValue.h"

CARServerInfoList::CARServerInfoList()
{
	ARZeroMemory(&serverInfo);
	ARZeroMemory(&requestList);
}

CARServerInfoList::~CARServerInfoList(void)
{
	FreeARServerInfoList(&serverInfo, false);
}

void CARServerInfoList::FillRequest()
{	
	try
	{
		CARInside* pInside = CARInside::GetInstance();

#if AR_CURRENT_API_VERSION >= AR_API_VERSION_810
		if      (pInside->CompareServerVersion(8,1,0) >= 0) { requestList.numItems = 353 /*358*/; } else
#endif
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_800
		if      (pInside->CompareServerVersion(8,0,0) >= 0) { requestList.numItems = 353; } else
#endif
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_764
		if      (pInside->CompareServerVersion(7,6,4) >= 0) { requestList.numItems = 351; } else
#endif
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_763
		if      (pInside->CompareServerVersion(7,6,3) >= 0) { requestList.numItems = 341; } else
#endif
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_750
		if      (pInside->CompareServerVersion(7,5,0) >= 0) { requestList.numItems = 324; } else
#endif
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_710
		if      (pInside->CompareServerVersion(7,1,0) >= 0) { requestList.numItems = 255; } else
#endif
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_700
		if      (pInside->CompareServerVersion(7,0,1) >= 0) { requestList.numItems = 247; }
		else if (pInside->CompareServerVersion(7,0,0) >= 0) { requestList.numItems = 246; }
		else if (pInside->CompareServerVersion(6,3,0) >= 0) { requestList.numItems = 215; }
		else if (pInside->CompareServerVersion(6,0,0) >= 0) { requestList.numItems = 206; }
		else if (pInside->CompareServerVersion(5,1,0) >= 0) { requestList.numItems = 184; }
		else if (pInside->CompareServerVersion(4,5,1) >= 0) { requestList.numItems = 121; }
#endif
		else
		{
			cerr << "[ERROR] Unsupported server version: " << pInside->arServerVersion << endl;
			return;
		}

		requestList.requestList = new unsigned int[requestList.numItems];
		int infoProp = 1;
		for(unsigned int i=0; i < requestList.numItems; i++)
		{
			switch (infoProp)
			{
			case AR_SERVER_INFO_DB_PASSWORD:
			case AR_SERVER_INFO_DSO_MARK_PENDING_RETRY:
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_764
			case AR_SERVER_INFO_RESTART_PLUGIN:
#endif
				--requestList.numItems;
				--i;
				break;
			default:
				requestList.requestList[i] = infoProp;
				break;
			}
			infoProp++;
		}
	}
	catch(exception& e)
	{
		cout << "EXCEPTION filling server infos: " << e.what() << endl;
	}
}

bool CARServerInfoList::Load()
{
	try
	{
		CARInside* pInside = CARInside::GetInstance();

		ARStatusList arStatus;
		bool result = false;

		FillRequest();

		if (requestList.numItems == 0)	// in case the server version isn't supported and no items are requested
			return false;

		if(ARGetServerInfo(&pInside->arControl, &requestList, &serverInfo, &arStatus) == AR_RETURN_OK)
		{
			result = true;

			for(unsigned int i=0; i< serverInfo.numItems; i++)
			{
				ARServerInfoStruct& info = serverInfo.serverInfoList[i];
				LOG << "Loading ServerInfo: " << CAREnum::ServerInfoApiCall(info.operation) << "[OK]" << endl;
			}
		}
		else
		{
			cerr << "Error Loading System Information properties:" << BuildMessageAndFreeStatus(arStatus);
		}
		delete[] requestList.requestList;
		ARZeroMemory(&requestList);
		FreeARStatusList(&arStatus, false);
		return result;
	}
	catch(exception& e)
	{
		cout << "EXCEPTION loading server infos: " << e.what() << endl;
	}
	return false;
}

bool CARServerInfoList::LoadAndGetValue(unsigned int serverInfoVal, const CStoreToBase& pred)
{
	CARInside* pInside = CARInside::GetInstance();

	bool result = false;
	ARStatusList status;
	ARServerInfoRequestList requestList;
	ARServerInfoList serverInfo;

	ARZeroMemory(&status);
	ARZeroMemory(&serverInfo);

	requestList.numItems = 1;
	requestList.requestList = &serverInfoVal;

	if(ARGetServerInfo(&pInside->arControl, &requestList, &serverInfo, &status) == AR_RETURN_OK)
	{
		if (serverInfo.numItems > 0)
			result = pred(&serverInfo.serverInfoList[0].value);
	}
	else
	{
		cerr << "Failed to load server info " << serverInfoVal << ": " << BuildMessageAndFreeStatus(status);
	}

	FreeARServerInfoList(&serverInfo, false);
	FreeARStatusList(&status, false);

	return result;
}

unsigned int CARServerInfoList::GetCount()
{
	return serverInfo.numItems;
}

int CARServerInfoList::Find(int serverInfoId)
{
	for (unsigned int index = 0; index < serverInfo.numItems; ++index)
	{
		if (serverInfo.serverInfoList[index].operation == serverInfoId)
			return index;
	}
	return -1;
}

unsigned int CARServerInfoList::GetOperation(int index)
{
	if (index < 0 || static_cast<unsigned int>(index) > serverInfo.numItems)
		return 0;

	return serverInfo.serverInfoList[index].operation;
}

ARValueStruct* CARServerInfoList::GetValue(int ServerInfoVal)
{
	for (unsigned int index = 0; index < serverInfo.numItems; ++index)
	{
		if (serverInfo.serverInfoList[index].operation == ServerInfoVal)
		{
			return &serverInfo.serverInfoList[index].value;
		}
	}
	return NULL;
}

ARValueStruct* CARServerInfoList::GetValueByIndex(int index)
{
	if (index < 0 || static_cast<unsigned int>(index) > serverInfo.numItems)
		return NULL;

	return &serverInfo.serverInfoList[index].value;
}

template<> bool CStoreTo<string>::operator ()(ARValueStruct* val) const
{
	if (val != NULL)
	{
		t = CARValue::ValueToString(*val);
		return true;
	}
	else
		return false;
}

template<> bool CStoreTo<int>::operator ()(ARValueStruct *val) const
{
	if (val != NULL)
	{
		t = CARValue::ValueToInt(*val);
		return true;
	}
	else
		return false;
}
