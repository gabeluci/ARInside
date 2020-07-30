//Copyright (C) 2014 John Luthgers | jls17
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
#include "ARStatusList.h"
#include "../ARApi.h"

CARStatusList::CARStatusList(ARStatusList &statusList, bool autoFreeStruct)
: status(statusList), freeStatusList(autoFreeStruct)
{
}

CARStatusList::~CARStatusList(void)
{
	if (freeStatusList)
		FreeARStatusList(&status, false);
}

const char* CARStatusList::getMessageTypeAsStr(int resultCode)
{
	switch (resultCode)
	{
	case AR_RETURN_OK: return "OK";
	case AR_RETURN_WARNING: return "ARWARN";
	case AR_RETURN_ERROR: return "ARERR";
	case AR_RETURN_FATAL: return "ARFATAL";
	default: return "ARUNKNOWN";
	}
}

void CARStatusList::ToStream(ostream &strm)
{
	if (&status == NULL || status.numItems == 0) return;

	if(status.statusList != NULL)
	{
		for (unsigned int i = 0; i < status.numItems; i++)
		{
			const char* typeStr = getMessageTypeAsStr(status.statusList[i].messageType);
			strm << "[" << typeStr << " " << status.statusList[i].messageNum << "] ";
			strm << status.statusList[i].messageText << endl;
			if (status.statusList[i].appendedText != NULL) 
				strm << "  " << status.statusList[i].appendedText << endl;
		}
	}
}

string CARStatusList::ToString()
{
	stringstream strm;
	ToStream(strm);
	return strm.str();
}

string BuildMessageAndFreeStatus(ARStatusList &statusList)
{
	CARStatusList status(statusList);
	return status.ToString();
}
