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
#include "ARRole.h"
#include "../ARInside.h"

using namespace OUTPUT;

CARRole::CARRole(int insideId)
: CARServerObject(insideId)
{
}

CARRole::CARRole(int roleId, const string& appName)
: CARServerObject(-1)
{
	insideId = CARInside::GetInstance()->roleList.Find(roleId, appName);
}

CARRole::~CARRole(void)
{
}

bool CARRole::Exists() const
{
	return (insideId >= 0 && (unsigned int)insideId < CARInside::GetInstance()->roleList.GetCount());
}

bool CARRole::IsClonable() const
{
	return true;
}

CARServerObject* CARRole::Clone() const
{
	return new CARRole(*this);
}

string CARRole::GetName()
{
	return CARInside::GetInstance()->roleList.RoleGetName(GetInsideId());
}

string CARRole::GetName() const
{
	return CARInside::GetInstance()->roleList.RoleGetName(GetInsideId());
}

string CARRole::GetNameFirstChar()
{
	return CARObject::GetNameFirstChar(CARInside::GetInstance()->roleList.RoleGetName(GetInsideId()));
}

bool CARRole::NameStandardFirstChar()
{
	return CARObject::NameStandardFirstChar(GetNameFirstChar());
}

const char* CARRole::GetHelpText() const
{
	return NULL; // no support for helptext
}

ARTimestamp CARRole::GetTimestamp() const
{
	return CARInside::GetInstance()->roleList.RoleGetModifiedDate(GetInsideId());
}

const ARAccessNameType& CARRole::GetOwner() const
{
	return CARInside::GetInstance()->roleList.RoleGetCreatedBy(GetInsideId());
}

const ARAccessNameType& CARRole::GetLastChanged() const
{
	return CARInside::GetInstance()->roleList.RoleGetModifiedBy(GetInsideId());
}

const char* CARRole::GetChangeDiary() const
{
	return NULL;
}

const ARPropList& CARRole::GetPropList() const
{
	return CARRoleList::RoleGetPropList();
}

const string& CARRole::GetRequestId() const
{
	return CARInside::GetInstance()->roleList.RoleGetRequestId(GetInsideId());
}

const string& CARRole::GetApplicationName() const
{
	return CARInside::GetInstance()->roleList.RoleGetApplicationName(GetInsideId());
}

int CARRole::GetRoleId() const
{
	return CARInside::GetInstance()->roleList.RoleGetId(GetInsideId());
}

const CARRole::GroupList& CARRole::GetGroupsTest() const
{
	return CARInside::GetInstance()->roleList.RoleGetGroupsTest(GetInsideId());
}

const CARRole::GroupList& CARRole::GetGroupsProd() const
{
	return CARInside::GetInstance()->roleList.RoleGetGroupsProd(GetInsideId());
}

ARTimestamp CARRole::GetCreateDate() const
{
	return CARInside::GetInstance()->roleList.RoleGetCreateDate(GetInsideId());
}
