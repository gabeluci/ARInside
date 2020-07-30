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
#include "WebControl.h"
#include "TableCell.h"

namespace OUTPUT
{
	class CTableRow :
		public CWebControl
	{
	public:
		CTableRow();
		CTableRow(const string &cssClass);
		~CTableRow(void);

		void ToXHtml(std::ostream& strm);
		void ToCsv(std::ostream& strm);

		string Name;
		void AddCell(const string& cellText);
		void AddCell(const CTableCell& cell);

		void AddCellList(const string& cellText0, const string& cellText1);
		void AddCellList(const CTableCell& cell0, const CTableCell& cell1);

		void AddCellList(const CTableCell& cell0, const CTableCell& cell1, const CTableCell& cell2);	
		void AddCellList(const string& cellText0, const string& cellText1, const string& cellText2);
		void ClearCells();
	private:
		void GetCells(std::ostream& strm);
		list<CTableCell> listCells;

	};
}
