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
#include "ObjectTable.h"
#include "../ARInside.h"
#include "../output/Table.h"
#include "../output/TableRow.h"

namespace OUTPUT
{
	class CEscalTable:
		public CObjectTable
	{
	public:
		CEscalTable(CARInside &arIn);
		~CEscalTable(void);

		void AddRow(unsigned int escalationInsideId, int rootLevel) { CAREscalation esc(escalationInsideId); AddRow(esc, rootLevel); }
		void AddRow(CAREscalation &escal, int rootLevel);
	};
}
