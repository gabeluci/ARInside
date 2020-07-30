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
#include "TableRow.h"
#include "TableColumn.h"

namespace OUTPUT
{
	class CTable :
		public CWebControl
	{
	public:
		CTable();
		CTable(const string& htmId, const string& cssClass);
		~CTable(void);

		string description;	

		void ToXHtml(std::ostream& strm);
		string ToXHtml();
		string ToCsv();

		void Clear();
		void ClearRows();
		void ClearColumns();
		std::string GetHtmId();
		void SetCssClass(const string& htmId);
		void SetEmptyMessage(const string& msg);
		int NumRows();
		void AddColumn(int width, const string& text);
		void AddColumn(int width, const string& text, const string& cssClass);	
		void AddRow(const CTableRow& tableRow);

		void DisableHeader() { hideHeader = true; }
		void EnableHeader() { hideHeader = false; }

	private:	
		list<CTableRow> listRows;
		list<CTableColumn> listColumns;
		string htmId;
		string emptyMessage;
		bool hideHeader;
		void Init();
		void GetHtmlRows(std::ostream& strm);
		void GetCsvRows(std::ostream& strm);
		void GetColumnDefinition(std::ostream& strm);
		void GetHeaderDefinition(std::ostream& strm);
		void GetCsvHeaderDefinition(std::ostream& strm);
		void GetEmptyMessageRow(std::ostream& strm);
	};

	ostream& operator<<(ostream& strm, OUTPUT::CTable& tbl);
}

