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
#include "ARCharMenu.h"
#include "../ARInside.h"

CARCharMenu::CARCharMenu()
: CARServerObject(-1)
{
}

CARCharMenu::CARCharMenu(int insideId)
: CARServerObject(insideId)
{
}

CARCharMenu::CARCharMenu(const string& name)
: CARServerObject(-1)
{
	insideId = CARInside::GetInstance()->menuList.Find(name.c_str());
}

CARCharMenu::~CARCharMenu(void)
{
}

bool CARCharMenu::Exists() const
{
	return (insideId >= 0 && (unsigned int)insideId < CARInside::GetInstance()->menuList.GetCount());
}

bool CARCharMenu::IsClonable() const
{
	return true;
}

CARServerObject* CARCharMenu::Clone() const
{
	return new CARCharMenu(*this);
}

string CARCharMenu::GetName()
{
	return CARInside::GetInstance()->menuList.MenuGetName(GetInsideId());
}

string CARCharMenu::GetName() const
{
	return CARInside::GetInstance()->menuList.MenuGetName(GetInsideId());
}

string CARCharMenu::GetNameFirstChar()
{
	return CARObject::GetNameFirstChar(CARInside::GetInstance()->menuList.MenuGetName(GetInsideId()));
}

bool CARCharMenu::NameStandardFirstChar()
{
	return CARObject::NameStandardFirstChar(GetNameFirstChar());
}

const char* CARCharMenu::GetHelpText() const
{
	return CARInside::GetInstance()->menuList.MenuGetHelptext(GetInsideId());
}

ARTimestamp CARCharMenu::GetTimestamp() const
{
	return CARInside::GetInstance()->menuList.MenuGetTimestamp(GetInsideId());
}

const ARAccessNameType& CARCharMenu::GetOwner() const
{
	return CARInside::GetInstance()->menuList.MenuGetOwner(GetInsideId());
}

const ARAccessNameType& CARCharMenu::GetLastChanged() const
{
	return CARInside::GetInstance()->menuList.MenuGetModifiedBy(GetInsideId());
}

const char* CARCharMenu::GetChangeDiary() const
{
	return CARInside::GetInstance()->menuList.MenuGetChangeDiary(GetInsideId());
}

const ARNameType& CARCharMenu::GetARName() const
{
	return CARInside::GetInstance()->menuList.MenuGetName(GetInsideId());
}

const ARPropList& CARCharMenu::GetPropList() const
{
	return CARInside::GetInstance()->menuList.MenuGetPropList(GetInsideId());
}

const string& CARCharMenu::GetAppRefName() const
{
	return CARInside::GetInstance()->menuList.MenuGetAppRefName(GetInsideId());
}

void CARCharMenu::SetAppRefName(const string& appName)
{
	return CARInside::GetInstance()->menuList.MenuSetAppRefName(GetInsideId(), appName);
}

unsigned int CARCharMenu::GetRefreshCode() const
{
	return CARInside::GetInstance()->menuList.MenuGetRefreshCode(GetInsideId());
}

const ARCharMenuStruct& CARCharMenu::GetDefinition() const
{
	return CARInside::GetInstance()->menuList.MenuGetDefinition(GetInsideId());
}

void CARCharMenu::AddReference(const CRefItem &refItem)
{
	return CARInside::GetInstance()->menuList.AddReference(GetInsideId(), refItem);
}

bool CARCharMenu::ReferenceExists(const CRefItem &refItem) const
{
	return CARInside::GetInstance()->menuList.ReferenceExists(GetInsideId(), refItem);
}

const CARCharMenu::ReferenceList& CARCharMenu::GetReferences() const
{
	return CARInside::GetInstance()->menuList.GetReferences(GetInsideId());
}

bool CARCharMenu::IsUsedInWorkflow() const
{
	const ReferenceList& refs = GetReferences();
	ReferenceList::const_iterator curIt = refs.begin();
	ReferenceList::const_iterator endIt = refs.end();

	for (; curIt != endIt; ++curIt)
	{
		if (curIt->GetObjectType() == AR_STRUCT_ITEM_XML_FIELD && curIt->GetMessageId() == REFM_FIELD_CHARMENU)
			return true;
		if (curIt->GetObjectType() == AR_STRUCT_ITEM_XML_ACTIVE_LINK)
			return true;
	}
	return false;
}
