//Copyright (C) 2012 John Luthgers | jls17
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
#pragma once

#include "../ARInside.h"

class CDocCustomWorkflow
{
public:
	CDocCustomWorkflow(void);
	~CDocCustomWorkflow(void);

	void Documentation();

private:
	int rootLevel;
	CARInside* pInside;

private:
	void AddTableRow(CTable& tbl, CARSchema& schema);
	void AddTableRow(CTable& tbl, CARField& field);
	void AddTableRow(CTable& tbl, CARVui& vui);
	void AddTableRow(CTable& tbl, CARActiveLink& al);
	void AddTableRow(CTable& tbl, CARFilter& flt);
	void AddTableRow(CTable& tbl, CAREscalation& escal);
	void AddTableRow(CTable& tbl, CARCharMenu& menu);
	void AddTableRow(CTable& tbl, CARContainer& container);
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_750
	void AddTableRow(CTable& tbl, CARImage& image);
#endif
};
