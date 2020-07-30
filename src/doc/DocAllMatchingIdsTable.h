//Copyright (C) 2014 John Luthgers| jls17
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

#include "../util/RefItem.h"

// forward declarations
class CARServerObject;

// Generates html-table with all matching IDs of two forms
class CDocAllMatchingIdsTable
{
public:
	enum AllMatchingMode
	{
		AMM_PUSHFIELDS,
		AMM_SETFIELDS
	};

public:
	CDocAllMatchingIdsTable(const string& targetForm, const string& sourceForm, CARServerObject& obj, AllMatchingMode mode, int nAction, IfElseState ifElse, int rootLevel);
	std::ostream& ToStream(std::ostream& strm);

private:
	std::string tableLeftTarget;
	std::string tableRightSource;
	CARServerObject &obj;
	AllMatchingMode matchMode;
	int nAction;
	IfElseState ifElse;
	int rootLevel;
};
