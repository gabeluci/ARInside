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
#include "SchemaTable.h"
#include "URLLink.h"

using namespace OUTPUT;

CSchemaTable::CSchemaTable(CARInside &arIn)
: CObjectTable("schemaList", "TblObjectList")
{
	this->pInside = &arIn;

	tbl.AddColumn(30, "Form Name");
	tbl.AddColumn(20, "Web Alias");
	tbl.AddColumn(5, "Fields");
	tbl.AddColumn(5, "Views");
	tbl.AddColumn(10, "Type");
	tbl.AddColumn(15, "Modified");
	tbl.AddColumn(15, "By");
}

CSchemaTable::~CSchemaTable(void)
{
}

void CSchemaTable::AddRow(CARSchema &schema, int rootLevel)
{
	CTableRow tblRow("");

	tblRow.AddCell( CTableCell(URLLink(schema, rootLevel)));
	tblRow.AddCell( CTableCell(schema.WebAlias()));
	tblRow.AddCell( CTableCell(schema.GetFields()->GetCount()));
	tblRow.AddCell( CTableCell(schema.GetVUIs()->GetCount()));
	tblRow.AddCell( CTableCell(CAREnum::SchemaType(schema.GetCompound().schemaType)));
	tblRow.AddCell( CTableCell(CUtil::DateTimeToHTMLString(schema.GetTimestamp())));
	tblRow.AddCell( CTableCell(this->pInside->LinkToUser(schema.GetLastChanged(), rootLevel)));

	this->tbl.AddRow(tblRow);
}
