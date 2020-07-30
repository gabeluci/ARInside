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
#include "ARUser.h"
#include "../ARInside.h"

CARUser::CARUser(int insideId)
: CARServerObject(insideId)
{
}

CARUser::CARUser(const string& userName)
: CARServerObject(-1)
{
	insideId = CARInside::GetInstance()->userList.Find(userName);
}

CARUser::~CARUser(void)
{
}

bool CARUser::Exists() const
{
	return (insideId >= 0 && (unsigned int)insideId < CARInside::GetInstance()->userList.GetCount());
}

bool CARUser::IsClonable() const
{
	return true;
}

CARServerObject* CARUser::Clone() const
{
	return new CARUser(*this);
}

string CARUser::GetName()
{
	return CARInside::GetInstance()->userList.UserGetName(GetInsideId());
}

string CARUser::GetName() const
{
	return CARInside::GetInstance()->userList.UserGetName(GetInsideId());
}

string CARUser::GetNameFirstChar()
{
	return CARObject::GetNameFirstChar(CARInside::GetInstance()->userList.UserGetName(GetInsideId()));
}

bool CARUser::NameStandardFirstChar()
{
	return CARObject::NameStandardFirstChar(GetNameFirstChar());
}

const char* CARUser::GetHelpText() const
{
	return NULL; // no support for helptext
}

ARTimestamp CARUser::GetTimestamp() const
{
	return CARInside::GetInstance()->userList.UserGetModifiedDate(GetInsideId());
}

const ARAccessNameType& CARUser::GetOwner() const
{
	return CARInside::GetInstance()->userList.UserGetCreatedBy(GetInsideId());
}

const ARAccessNameType& CARUser::GetLastChanged() const
{
	return CARInside::GetInstance()->userList.UserGetModifiedBy(GetInsideId());
}

const char* CARUser::GetChangeDiary() const
{
	return NULL;
}

const ARPropList& CARUser::GetPropList() const
{
	return CARUserList::UserGetPropList();
}

const string& CARUser::GetRequestId() const
{
	return CARInside::GetInstance()->userList.UserGetRequestId(GetInsideId());
}

const string& CARUser::GetEmail() const
{
	return CARInside::GetInstance()->userList.UserGetEmail(GetInsideId());
}

const CARUser::GroupList& CARUser::GetGroups() const
{
	return CARInside::GetInstance()->userList.UserGetGroups(GetInsideId());
}

const string& CARUser::GetFullName() const
{
	return CARInside::GetInstance()->userList.UserGetFullName(GetInsideId());
}

int CARUser::GetDefaultNotify() const
{
	return CARInside::GetInstance()->userList.UserGetDefaultNotify(GetInsideId());
}

int CARUser::GetLicenseType() const
{
	return CARInside::GetInstance()->userList.UserGetLicenseType(GetInsideId());
}

int CARUser::GetFTLicenseType() const
{
	return CARInside::GetInstance()->userList.UserGetFTLicenseType(GetInsideId());
}

ARTimestamp CARUser::GetCreateDate() const
{
	return CARInside::GetInstance()->userList.UserGetCreateDate(GetInsideId());
}
