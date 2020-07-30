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
#include "RoleTable.h"
#include "URLLink.h"

using namespace OUTPUT;
using namespace rapidjson;

CRoleTable::CRoleTable(CARInside &arIn)
: CObjectTable("roleList", "TblObjectList")
{
	this->pInside = &arIn;

	tbl.AddColumn(25, "Role Name");
	tbl.AddColumn(5, "RoleID");
	tbl.AddColumn(30, "Application");	
	tbl.AddColumn(20, "Modified");
	tbl.AddColumn(20, "By");
}

CRoleTable::~CRoleTable(void)
{
}

void CRoleTable::AddRow(CARRole &role, int rootLevel)
{
	CTableRow tblRow("");
	tblRow.AddCell( CTableCell(URLLink(role, rootLevel)));
	tblRow.AddCell( CTableCell(role.GetRoleId()));
	tblRow.AddCell( CTableCell(this->pInside->LinkToContainer(role.GetApplicationName(), rootLevel)));
	tblRow.AddCell( CTableCell(CUtil::DateTimeToHTMLString(role.GetTimestamp())));
	tblRow.AddCell( CTableCell(this->pInside->LinkToUser(role.GetLastChanged(), rootLevel)));
	this->tbl.AddRow(tblRow);
}

void CRoleTable::AddRowJson(CARRole &role, int rootLevel)
{
	if (!role.Exists()) return;

	CARContainer app(role.GetApplicationName());

	CPageParams roleDetailPage(PAGE_DETAILS, &role);
	Document::AllocatorType &alloc = doc.GetAllocator();

	Value roleRow;
	roleRow.SetArray();

	// now build the needed temporary variables
	string strName = role.GetName();
	string strAppName = role.GetApplicationName();
	string strModifiedDate = CUtil::DateTimeToString(role.GetTimestamp());
	string strLink = CWebUtil::GetRelativeURL(rootLevel, roleDetailPage);
	string strAppLink = (app.Exists() ? CWebUtil::GetRelativeURL(rootLevel, CPageParams(PAGE_DETAILS, &app)) : "");

	Value valName(strName.c_str(), static_cast<SizeType>(strName.size()), alloc);
	Value valAppName(strAppName.c_str(), static_cast<SizeType>(strAppName.size()), alloc);
	Value valModifiedDate(strModifiedDate.c_str(), static_cast<SizeType>(strModifiedDate.size()), alloc);
	Value valLink(strLink.c_str(), static_cast<SizeType>(strLink.size()), alloc);
	Value valAppLink(strAppLink.c_str(), static_cast<SizeType>(strAppLink.size()), alloc);

	// add everything to the row
	roleRow.PushBack(role.GetRoleId(), alloc);
	roleRow.PushBack(valName, alloc);
	roleRow.PushBack(valAppName, alloc);
	roleRow.PushBack(valModifiedDate, alloc);
	roleRow.PushBack(role.GetLastChanged(), alloc);
	roleRow.PushBack(valLink, alloc);
	roleRow.PushBack(valAppLink, alloc);

	// add the row to the document
	doc.PushBack(roleRow, alloc);	

}
