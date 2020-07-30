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
#include "MenuTable.h"
#include "URLLink.h"

using namespace OUTPUT;

CMenuTable::CMenuTable(CARInside &arIn)
: CObjectTable("menuList", "TblObjectList")
{
	this->pInside = &arIn;

	tbl.AddColumn(40, "CharMenu Name");
	tbl.AddColumn(10, "Type");
	tbl.AddColumn(10, "Refresh On");
	tbl.AddColumn(20, "Changed");
	tbl.AddColumn(20, "By");
}

CMenuTable::~CMenuTable(void)
{
}

void CMenuTable::AddRow(CARCharMenu &menu, int rootLevel)
{
	CTableRow tblRow("");

	string cellNameValue = URLLink(menu, rootLevel);
	if(!menu.IsUsedInWorkflow())
	{
		cellNameValue += " (<b>!</b>)";
	}

	tblRow.AddCell( CTableCell(cellNameValue));		
	tblRow.AddCell( CTableCell(CAREnum::MenuType(menu.GetDefinition().menuType)));
	tblRow.AddCell( CTableCell(CAREnum::MenuRefresh(menu.GetRefreshCode())));
	tblRow.AddCell( CTableCell(CUtil::DateTimeToHTMLString(menu.GetTimestamp())));
	tblRow.AddCell( CTableCell(this->pInside->LinkToUser(menu.GetLastChanged(), rootLevel)));

	this->tbl.AddRow(tblRow);
}
