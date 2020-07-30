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
#include "FilterTable.h"
#include "URLLink.h"

using namespace OUTPUT;

CFilterTable::CFilterTable(CARInside &arIn)
: CObjectTable("filterList", "TblObjectList")
{
	this->pInside = &arIn;

	tbl.AddColumn(0, "Filter Name");
	tbl.AddColumn(0, "Enabled");
	tbl.AddColumn(0, "Order");
	tbl.AddColumn(0, "Execute On");
	tbl.AddColumn(0, "If");
	tbl.AddColumn(0, "Else");
	tbl.AddColumn(0, "Changed");
	tbl.AddColumn(0, "By");
}

CFilterTable::~CFilterTable(void)
{
}

void CFilterTable::AddRow(unsigned int filterIndex, int rootLevel)
{
	CARFilter filter(filterIndex);

	CTableRow tblRow("");
	tblRow.AddCell(CTableCell(URLLink(filter, rootLevel)));

	string tmpCssEnabled = "";
	if(filter.GetEnabled()==0)
		tmpCssEnabled = "objStatusDisabled";
	tblRow.AddCell( CTableCell(CAREnum::ObjectEnable(filter.GetEnabled()), tmpCssEnabled));

	tblRow.AddCell( CTableCell(filter.GetOrder()));
	tblRow.AddCell( CTableCell(filter.GetExecuteOn(true)));
	tblRow.AddCell( CTableCell(filter.GetIfActions().numItems));
	tblRow.AddCell( CTableCell(filter.GetElseActions().numItems));
	tblRow.AddCell( CTableCell(CUtil::DateTimeToHTMLString(filter.GetTimestamp())));
	tblRow.AddCell( CTableCell(this->pInside->LinkToUser(filter.GetLastChanged(), rootLevel)));

	this->tbl.AddRow(tblRow);
}
