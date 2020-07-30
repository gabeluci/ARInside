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
#include "TableColumn.h"

using namespace OUTPUT;

CTableColumn::CTableColumn(int width, const string &title)
{
	this->width = width;
	this->title = title;
}

CTableColumn::CTableColumn(int width, const string &title, const string &cssClass)
{
	this->width = width;
	this->title = title;
	this->cssClass = cssClass;
}

CTableColumn::~CTableColumn(void)
{
}

void CTableColumn::ColToXHtml(std::ostream& strm)
{
	strm << "<col width=\"" << this->width << "%\"/>" << endl;		
}

void CTableColumn::HeaderCellToXHtml(std::ostream& strm)
{
	if(this->cssClass.empty())
	{
		strm << "<th>" << this->title << "</th>" << endl;
	}
	else
	{
		strm << "<th class=\"" << this->cssClass << "\" width=\""<< this->width << "%\">" << this->title << "</th>" << endl;
	}
}

string CTableColumn::GetTitle()
{
	return this->title;
}
