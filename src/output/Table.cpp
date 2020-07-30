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
#include "Table.h"

using namespace OUTPUT;

CTable::CTable()
{
	Init();
}

CTable::CTable(const string& htmId, const string& cssClass)
{
	this->htmId = htmId;
	this->cssClass = cssClass;
	this->hideHeader = false;
	Init();
}

CTable::~CTable(void)
{
}

void CTable::Init()
{
	emptyMessage = "Table contains no data";
}

int CTable::NumRows()
{
	return (int)this->listRows.size();
}

void CTable::AddColumn(int width, const string& text)
{
	CTableColumn col(width, text, "colStdClass");
	this->listColumns.push_back(col);
}

void CTable::AddColumn(int width, const string& text, const string& cssClass)
{
	CTableColumn col(width, text, cssClass);
	this->listColumns.push_back(col);
}

void CTable::AddRow(const CTableRow& tableRow)
{
	this->listRows.push_back(tableRow);
}

string CTable::GetHtmId()
{
	return htmId;
}

void CTable::SetCssClass(const string& cssClass)
{
	this->cssClass = cssClass;
}

void CTable::SetEmptyMessage(const string& msg)
{
	this->emptyMessage = msg;
}

void CTable::Clear()
{
	this->ClearColumns();
	this->ClearRows();
}

void CTable::ClearRows()
{
	this->listRows.clear();
}

void CTable::ClearColumns()
{
	this->listColumns.clear();
}

void CTable::GetHtmlRows(std::ostream& strm)
{
	list<CTableRow>::iterator rowIter;
	list<CTableRow>::iterator endIter = listRows.end();
	for ( rowIter = listRows.begin(); rowIter != endIter; ++rowIter )
	{	
		CTableRow *rowItem = &(*rowIter);
		rowItem->ToXHtml(strm);
	}
}

void CTable::GetCsvRows(std::ostream& strm)
{	
	list<CTableRow>::iterator rowIter;
	for ( rowIter = listRows.begin(); rowIter != listRows.end(); ++rowIter )
	{	
		CTableRow *rowItem = &(*rowIter);
		rowItem->ToCsv(strm);
		strm << "\n";
	}
}

void CTable::GetColumnDefinition(std::ostream& strm)
{
	strm << "<colgroup>" << endl;
	list<CTableColumn>::iterator colIter;
	CTableColumn *colItem;

	for ( colIter = listColumns.begin(); colIter != listColumns.end(); ++colIter )
	{	
		colItem = &(*colIter);
		colItem->ColToXHtml(strm);
	}

	strm << "</colgroup>" << endl;
}

void CTable::GetCsvHeaderDefinition(std::ostream& strm)
{
	list<CTableColumn>::iterator colIter;
	CTableColumn *colItem;	
	for ( colIter = listColumns.begin(); colIter != listColumns.end(); ++colIter )
	{	
		colItem = &(*colIter);
		strm << colItem->GetTitle() << "\t";
	}
	strm << "\n";
}

void CTable::GetHeaderDefinition(std::ostream& strm)
{
	strm << "<tr>" << endl;

	list<CTableColumn>::iterator colIter;
	CTableColumn *colItem;	
	for ( colIter = listColumns.begin(); colIter != listColumns.end(); ++colIter )
	{	
		colItem = &(*colIter);
		colItem->HeaderCellToXHtml(strm);
	}

	strm << "</tr>" << endl;   
}

string CTable::ToXHtml()
{
	stringstream strm;	    
	ToXHtml(strm);
	return strm.str();
}

void CTable::ToXHtml(std::ostream &strm)
{
	if(!this->description.empty())
	{
		strm << "<h2>" << endl;
		strm << description << endl;
		strm << "</h2>" << endl;
	}

	strm << "<table id=\"" << this->htmId << "\"";

	if(!this->cssClass.empty())
	{
		strm << " class=\"" << this->cssClass << "\"" << endl;
	}

	strm << ">" << endl; // closing table tag here

	this->GetColumnDefinition(strm);
	if (!hideHeader)
	{
		strm << "<thead>";
		this->GetHeaderDefinition(strm);
		strm << "</thead>";
	}

	strm << "<tbody>";
	if(listRows.size() > 0)
	{
		this->GetHtmlRows(strm);
	}
	else
	{
		this->GetEmptyMessageRow(strm);
	}
	strm << "</tbody>";

	strm << "</table>" << endl;
}

string CTable::ToCsv()
{
	stringstream strm;
	strm.str("");	

	this->GetCsvHeaderDefinition(strm);

	if(listRows.size() > 0)
	{
		this->GetCsvRows(strm);
	}

	return strm.str();	
}

void CTable::GetEmptyMessageRow(std::ostream& strm)
{
	if (emptyMessage.size() > 0)
	{
		size_t nColspan = listColumns.size();
		strm << "<tr>" << endl << "<td colspan=\"" << (unsigned int)nColspan << "\">";
		strm << emptyMessage;
		strm << "</td>" << endl << "</tr>" << endl;
	}
}

ostream& OUTPUT::operator<<(ostream& strm, OUTPUT::CTable& tbl)
{ 
	tbl.ToXHtml(strm);
	return strm;
}
