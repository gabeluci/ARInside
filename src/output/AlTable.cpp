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
#include "AlTable.h"
#include "URLLink.h"

using namespace OUTPUT;

CAlTable::CAlTable(CARInside &arIn)
: CObjectTable("alList", "TblObjectList")
{
	this->pInside = &arIn;

	tbl.AddColumn(0, "Active Link Name");
	tbl.AddColumn(0, "Enabled");	
	tbl.AddColumn(0, "Groups");
	tbl.AddColumn(0, "Order");	
	tbl.AddColumn(0, "Execute On");
	tbl.AddColumn(0, "If");
	tbl.AddColumn(0, "Else");
	tbl.AddColumn(0, "Changed");
	tbl.AddColumn(0, "By");
}

CAlTable::~CAlTable(void)
{	
}

void CAlTable::AddRow(int alInsideId, int rootLevel)
{
	CARActiveLink al(alInsideId);

	CARProplistHelper props(&al.GetPropList());
	CTableRow tblRow("");
	tblRow.AddCell( CTableCell(URLLink(al, rootLevel)));

	string tmpCssEnabled = "";
	if(al.GetEnabled()==0)
		tmpCssEnabled = "objStatusDisabled";
	tblRow.AddCell( CTableCell(CAREnum::ObjectEnable(al.GetEnabled()), tmpCssEnabled));

	stringstream strmNumGroup;
	strmNumGroup << al.GetGroupList().numItems;
	tblRow.AddCell(	CTableCell(strmNumGroup.str(), ""));
	tblRow.AddCell(	CTableCell(al.GetOrder()));
	tblRow.AddCell(	CTableCell(al.GetExecuteOn(true,&props)));
	tblRow.AddCell(	CTableCell(al.GetIfActions().numItems));
	tblRow.AddCell(	CTableCell(al.GetElseActions().numItems));
	tblRow.AddCell(	CTableCell(CUtil::DateTimeToHTMLString(al.GetTimestamp())));
	tblRow.AddCell(	CTableCell(this->pInside->LinkToUser(al.GetLastChanged(), rootLevel)));
	this->tbl.AddRow(tblRow);
}
