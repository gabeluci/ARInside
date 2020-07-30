//Copyright (C) 2009 Stefan Nerlich | stefan.nerlich@hotmail.com
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
#include "ARGroup.h"
#include "../ARInside.h"

// call methods:
//   1) CARGroup(15)    ...  gets the group at position 15 within the list
//   2) CARGroup(-1, 1) ...  finds the group with id 1 (usually Administrator); 
//                           first param is ignored in this case
//                           check Exists function after this call
CARGroup::CARGroup(int insideId, int groupId)
: CARServerObject(insideId)
{
	if (groupId >= 0)
	{
		this->insideId = CARInside::GetInstance()->groupList.Find(groupId);
	}
}

CARGroup::~CARGroup(void)
{
}

bool CARGroup::Exists() const
{
	return (insideId >= 0 && (unsigned int)insideId < CARInside::GetInstance()->groupList.GetCount());
}

bool CARGroup::IsClonable() const
{
	return true;
}

CARServerObject* CARGroup::Clone() const
{
	return new CARGroup(*this);
}

string CARGroup::GetName()
{
	return CARInside::GetInstance()->groupList.GroupGetName(GetInsideId());
}

string CARGroup::GetName() const
{
	return CARInside::GetInstance()->groupList.GroupGetName(GetInsideId());
}

string CARGroup::GetNameFirstChar()
{
	return CARObject::GetNameFirstChar(CARInside::GetInstance()->groupList.GroupGetName(GetInsideId()));
}

bool CARGroup::NameStandardFirstChar()
{
	return CARObject::NameStandardFirstChar(GetNameFirstChar());
}

const char* CARGroup::GetHelpText() const
{
	return NULL; // no support for helptext
}

ARTimestamp CARGroup::GetTimestamp() const
{
	return CARInside::GetInstance()->groupList.GroupGetModifiedDate(GetInsideId());
}

const ARAccessNameType& CARGroup::GetOwner() const
{
	return CARInside::GetInstance()->groupList.GroupGetCreatedBy(GetInsideId());
}

const ARAccessNameType& CARGroup::GetLastChanged() const
{
	return CARInside::GetInstance()->groupList.GroupGetModifiedBy(GetInsideId());
}

const char* CARGroup::GetChangeDiary() const
{
	return NULL;
}

const ARPropList& CARGroup::GetPropList() const
{
	return CARGroupList::GroupGetPropList();
}

const string& CARGroup::GetRequestId() const
{
	return CARInside::GetInstance()->groupList.GroupGetRequestId(GetInsideId());
}

const string& CARGroup::GetLongName() const
{
	return CARInside::GetInstance()->groupList.GroupGetLongName(GetInsideId());
}

ARULong32 CARGroup::GetGroupId() const
{
	return CARInside::GetInstance()->groupList.GroupGetID(GetInsideId());
}

int CARGroup::GetType() const
{
	return CARInside::GetInstance()->groupList.GroupGetType(GetInsideId());
}

int CARGroup::GetCategory() const
{
	return CARInside::GetInstance()->groupList.GroupGetCategory(GetInsideId());
}

const string& CARGroup::GetComputedQualification() const
{
	return CARInside::GetInstance()->groupList.GroupGetComputedQual(GetInsideId());
}
