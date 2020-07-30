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

#pragma once
#include "../output/Table.h"
#include "../output/TableRow.h"
#include "../ARInside.h"
#include "rapidjson/document.h"

namespace OUTPUT
{
	class CObjectTable
	{
	public:
		CObjectTable(const string &htmlId, const string &cssClass);
		~CObjectTable(void);

		string Print();
		void Print(std::ostream& strm);
		int NumRows();
		void SetDescription(const string& desc);
		void RemoveEmptyMessageRow();

	protected:
		CARInside *pInside;
		CTable tbl;
		rapidjson::Document doc;
	};
}

std::ostream& operator<<(std::ostream& strm, OUTPUT::CObjectTable& tbl);
