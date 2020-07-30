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
#include "../core/ARValue.h"
#include "EscalTable.h"
#include "URLLink.h"

using namespace OUTPUT;

CEscalTable::CEscalTable(CARInside &arIn)
: CObjectTable("escalationList", "TblObjectList")
{
	this->pInside = &arIn;

	tbl.AddColumn(30, "Escalation Name");
	tbl.AddColumn(10, "Enabled");
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_710
	if (pInside->CompareServerVersion(7, 1) >= 0)
		tbl.AddColumn(5, "Pool");
#endif
	tbl.AddColumn(10, "ExecuteOn");
	tbl.AddColumn(5, "If");
	tbl.AddColumn(5, "Else");
	tbl.AddColumn(20, "Changed");
	tbl.AddColumn(20, "By");
}

CEscalTable::~CEscalTable(void)
{
}

void CEscalTable::AddRow(CAREscalation &escal, int rootLevel)
{
	CTableRow tblRow("");
	tblRow.AddCell( CTableCell(URLLink(escal, rootLevel)));

#if AR_CURRENT_API_VERSION >= AR_API_VERSION_710
	string escalPool = escal.GetPoolStr();
#endif

	string tmpCssEnabled = "";
	if(escal.GetEnabled()==0)
		tmpCssEnabled = "objStatusDisabled";
	tblRow.AddCell( CTableCell(CAREnum::ObjectEnable(escal.GetEnabled()), tmpCssEnabled));
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_710
	if (pInside->CompareServerVersion(7, 1) >= 0)
		tblRow.AddCell( CTableCell(escalPool));
#endif
	tblRow.AddCell( CTableCell(escal.GetExecuteOn()));
	tblRow.AddCell( CTableCell(escal.GetIfActions().numItems));
	tblRow.AddCell( CTableCell(escal.GetElseActions().numItems));
	tblRow.AddCell( CTableCell(CUtil::DateTimeToHTMLString(escal.GetTimestamp())));
	tblRow.AddCell( CTableCell(this->pInside->LinkToUser(escal.GetLastChanged(), rootLevel)));
	this->tbl.AddRow(tblRow);
}
