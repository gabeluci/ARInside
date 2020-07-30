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
#include "ARServerInfo.h"
#include "../ARInside.h"


CARServerInfo::CARServerInfo(int serverInfo, CARServerInfo::SearchMode mode)
{
	switch (mode)
	{
	case INDEX:
		insideId = serverInfo;
		break;
	case SERVER_INFO:
		{
			CARInside* pInside = CARInside::GetInstance();
			insideId = pInside->serverInfoList.Find(serverInfo);
		}
		break;
	default:
		insideId = -1;
	}
}

CARServerInfo::~CARServerInfo(void)
{
}

bool CARServerInfo::Exists()
{
	return (insideId >= 0 && (unsigned int)insideId < CARInside::GetInstance()->serverInfoList.GetCount());
}

unsigned int CARServerInfo::GetOperation()
{
	return CARInside::GetInstance()->serverInfoList.GetOperation(insideId);
}

ARValueStruct* CARServerInfo::GetValue()
{
	return CARInside::GetInstance()->serverInfoList.GetValueByIndex(insideId);
}
