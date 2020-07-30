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
#include "../ARInside.h"
#include "../output/Table.h"
#include "../output/TableRow.h"
#include "../output/UList.h"
#include "../output/UListItem.h"

using namespace OUTPUT;

class CDocBase
{
public:
	CDocBase(void);
	~CDocBase(void);

	// some helper functions
	string PlaceOverlayLink(int currentType, CARServerObject& target);

protected:
	CARInside *pInside;
	string path; // TODO: this should be remove completly. This is an abstract class .. derived class can use IFileStructure
	int rootLevel; // TODO: this should be remove completly. This is an abstract class .. derived class can use IFileStructure
};
