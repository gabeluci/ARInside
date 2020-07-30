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
//    along with ARInside.  If not, see <http://www.gnu.org/licenses/>.

#include "stdafx.h"
#include "ObjectTable.h"
#include "rapidjson/genericwritestream.h"
#include "rapidjson/writer.h"

using namespace OUTPUT;
using namespace rapidjson;

CObjectTable::CObjectTable(const string &htmlId, const string &cssClass)
: tbl(htmlId, cssClass)
{
	doc.SetArray();
}

CObjectTable::~CObjectTable(void)
{	
}

void CObjectTable::SetDescription(const string& desc)
{
	this->tbl.description = desc;
}

int CObjectTable::NumRows()
{
	return tbl.NumRows();
}

string CObjectTable::Print()
{
	return this->tbl.ToXHtml();
}

void CObjectTable::Print(std::ostream& strm)
{
	if (!doc.Empty())
	{
		GenericWriteStream output(strm);
		Writer<GenericWriteStream> writer(output);

		strm << "<script type=\"text/javascript\">" << endl;
		strm << "var " << this->tbl.GetHtmId() << " = "; doc.Accept(writer); strm << ";" << endl;
		strm << "</script>" << endl;
	}
	strm << tbl;
}

void CObjectTable::RemoveEmptyMessageRow()
{
	tbl.SetEmptyMessage("");
}

std::ostream& operator<<(std::ostream& strm, OUTPUT::CObjectTable& oTbl)
{
	oTbl.Print(strm);
	return strm;
}
