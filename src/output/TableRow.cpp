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
#include "TableRow.h"

using namespace OUTPUT;

CTableRow::CTableRow()
{
}

CTableRow::CTableRow(const string &cssClass)
{
	this->cssClass = cssClass;
}

CTableRow::~CTableRow(void)
{
	this->listCells.clear();
}

void CTableRow::ClearCells()
{
	this->listCells.clear();
}

void CTableRow::AddCell(const string& cellText)
{
	this->listCells.push_back(CTableCell(cellText));
}

void CTableRow::AddCell(const CTableCell& cell)
{
	this->listCells.push_back(cell);
}

void CTableRow::AddCellList(const string& cellText0, const string& cellText1)
{
	this->listCells.clear();
	this->listCells.push_back(CTableCell(cellText0));
	this->listCells.push_back(CTableCell(cellText1));
}

void CTableRow::AddCellList(const CTableCell& cell0, const CTableCell& cell1)
{
	this->listCells.clear();
	this->listCells.push_back(cell0);
	this->listCells.push_back(cell1);
}

void CTableRow::AddCellList(const CTableCell& cell0, const CTableCell& cell1, const CTableCell& cell2)
{
	this->listCells.clear();
	this->listCells.push_back(cell0);
	this->listCells.push_back(cell1);
	this->listCells.push_back(cell2);
}

void CTableRow::AddCellList(const string& cellText0, const string& cellText1, const string& cellText2)
{
	this->listCells.clear();
	this->listCells.push_back(CTableCell(cellText0));
	this->listCells.push_back(CTableCell(cellText1));
	this->listCells.push_back(CTableCell(cellText2));

}

void CTableRow::GetCells(std::ostream& strm)
{
	list<CTableCell>::iterator cellIter;
	list<CTableCell>::iterator endIter = listCells.end();
	for ( cellIter = listCells.begin(); cellIter != endIter; ++cellIter )
	{		
		CTableCell *cell = &(*cellIter);
		cell->ToXHtml(strm);
	}
}

void CTableRow::ToXHtml(std::ostream& strm)
{
	if(this->cssClass.empty())
	{
		strm << "<tr>" << endl; 
		this->GetCells(strm);
		strm << "</tr>" << endl;
	}
	else
	{
		strm << "<tr class=\"" << this->cssClass << "\">" << endl;
		this->GetCells(strm);
		strm << "</tr>" << endl;
	}
}

void CTableRow::ToCsv(std::ostream& strm)
{
	list<CTableCell>::iterator cellIter;
	for ( cellIter = listCells.begin(); cellIter != listCells.end(); ++cellIter )
	{		
		CTableCell *cell = &(*cellIter);
		cell->ToCsv(strm);
	}
}
