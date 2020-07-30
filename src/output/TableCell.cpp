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
#include "TableCell.h"

using namespace OUTPUT;

CTableCell::CTableCell()
{
	this->content = "";
	this->cssClass = "";
}

CTableCell::CTableCell(int content)
{
	stringstream strm;
	strm << content;
	this->content = strm.str();
}

CTableCell::CTableCell(const string &content)
{
	this->content = content;
}

CTableCell::CTableCell(const string& content, const string& cssClass)
{
	this->content = content;

	if(!cssClass.empty())
		this->cssClass = cssClass;
}

CTableCell::CTableCell(int content, const string &cssClass)
{
	stringstream strm;
	strm << content;
	this->content = strm.str();

	if(!cssClass.empty())
		this->cssClass = cssClass;
}


CTableCell::~CTableCell()
{
	this->content = "";
	this->cssClass = "";
}

void CTableCell::ToXHtml(std::ostream& strm)
{
	if(this->cssClass.empty())
	{
		strm << "<td>" << this->content << "</td>" << endl;
	}
	else
	{
		strm << "<td class=\"" << this->cssClass << "\">" << this->content << "</td>" << endl;
	}
}

void CTableCell::ToCsv(std::ostream& strm)
{
	strm << this->content << "\t";
}
