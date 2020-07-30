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
#include "GroupTable.h"
#include "URLLink.h"
#include "../core/ARGroup.h"
#include "../core/ARRole.h"

using namespace OUTPUT;
using namespace rapidjson;

CGroupTable::CGroupTable(CARInside &arIn)
: CObjectTable("groupList", "TblObjectList")
{
	this->pInside = &arIn;

	tbl.AddColumn(0, "Name");
	tbl.AddColumn(0, "ID");
	tbl.AddColumn(0, "Type");
	tbl.AddColumn(0, "Category");
	tbl.AddColumn(0, "Modified");
	tbl.AddColumn(0, "By");
}

CGroupTable::~CGroupTable(void)
{
}

void CGroupTable::AddRow(string appRefName, int id, int rootLevel)
{
	if(id < 0)
		this->AddRoleRow(appRefName, id, rootLevel);
	else
		this->AddGroupRow(appRefName, id, rootLevel);
}

void CGroupTable::AddRoleRow(string appRefName, int roleId, int rootLevel)
{
	CARRole role(roleId, appRefName);

	if(role.Exists())
	{
		CTableRow tblRow("");
		tblRow.AddCell( CTableCell("Role"));
		tblRow.AddCell( CTableCell(URLLink(role, rootLevel)));	
		tblRow.AddCell( CTableCell(role.GetRoleId()));
		tblRow.AddCell( CTableCell(CUtil::DateTimeToHTMLString(role.GetTimestamp())));
		tblRow.AddCell( CTableCell(this->pInside->LinkToUser(role.GetLastChanged(), rootLevel)));
		this->tbl.AddRow(tblRow);
	}
	else
	{
		CTableRow tblRow("");

		stringstream strmName, strmId;
		strmName << roleId << " (not loaded)";
		strmId << roleId;

		tblRow.AddCell( CTableCell("Role"));
		tblRow.AddCell( CTableCell(strmName.str()));	
		tblRow.AddCell( CTableCell(strmId.str()));
		tblRow.AddCell( CTableCell(EmptyValue)); // Timestamp
		tblRow.AddCell( CTableCell(EmptyValue)); // LastChangedBy
		this->tbl.AddRow(tblRow);
	}
}

// TODO: check calls to this function; maybe they have already found the group and this function searches again
void CGroupTable::AddGroupRow(string appRefName, int groupId, int rootLevel)
{
	// search group by id
	CARGroup insertGrp(-1, groupId);

	if(insertGrp.Exists())
	{
		CTableRow tblRow("");
		tblRow.AddCell( CTableCell(this->pInside->LinkToGroup(appRefName, insertGrp.GetGroupId(), rootLevel)));	
		tblRow.AddCell( CTableCell(insertGrp.GetGroupId()));
		tblRow.AddCell( CTableCell(CAREnum::GroupType(insertGrp.GetType())));
		tblRow.AddCell( CTableCell(CAREnum::GroupCategory(insertGrp.GetCategory())));
		tblRow.AddCell( CTableCell(CUtil::DateTimeToHTMLString(insertGrp.GetTimestamp())));
		tblRow.AddCell( CTableCell(this->pInside->LinkToUser(insertGrp.GetLastChanged(), rootLevel)));
		this->tbl.AddRow(tblRow);
	}
	else
	{
		CTableRow tblRow("");

		stringstream strmName, strmId;
		strmName << groupId << " (not loaded)";
		strmId << groupId;

		tblRow.AddCell( CTableCell(strmName.str()));// Name
		tblRow.AddCell( CTableCell(strmId.str()));  // Id
		tblRow.AddCell( CTableCell(EmptyValue));    // Type
		tblRow.AddCell( CTableCell(EmptyValue));    // Category
		tblRow.AddCell( CTableCell(EmptyValue));    // Timestamp
		tblRow.AddCell( CTableCell(EmptyValue));    // LastChangedBy
		this->tbl.AddRow(tblRow);
	}	
}

void CGroupTable::AddRowJson(CARGroup &group, int rootLevel)
{
	if (!group.Exists()) return;

	CPageParams groupDetailPage(PAGE_DETAILS, &group);
	Document::AllocatorType &alloc = doc.GetAllocator();

	Value groupRow;
	groupRow.SetArray();

	// now build the needed temporary variables
	string strName = group.GetName();
	string strModifiedDate = CUtil::DateTimeToString(group.GetTimestamp());
	string strLink = CWebUtil::GetRelativeURL(rootLevel, groupDetailPage);

	Value valName(strName.c_str(), static_cast<SizeType>(strName.size()), alloc);
	Value valModifiedDate(strModifiedDate.c_str(), static_cast<SizeType>(strModifiedDate.size()), alloc);
	Value valLink(strLink.c_str(), static_cast<SizeType>(strLink.size()), alloc);

	// add everything to the row
	groupRow.PushBack((unsigned int)group.GetGroupId(), alloc);
	groupRow.PushBack(valName, alloc);
	groupRow.PushBack(group.GetType(), alloc);
	groupRow.PushBack(group.GetCategory(), alloc);
	groupRow.PushBack(valModifiedDate, alloc);
	groupRow.PushBack(group.GetLastChanged(), alloc);
	groupRow.PushBack(valLink, alloc);

	// add the row to the document
	doc.PushBack(groupRow, alloc);	
}
