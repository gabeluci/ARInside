//Copyright (C) 2014 John Luthgers | jls17
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
#include "RootPath.h"

namespace OUTPUT 
{

	RootPath::RootPath(int currentRootLevel)
	{
		rootLevel = currentRootLevel;
	}

	const char* RootPath::GetRootPath() const
	{
		switch(rootLevel)
		{
		case 1: return "../";
		case 2: return "../../";
		case 3: return "../../../";
		default: return "";
		}	
	}

	ostream& operator <<(ostream &stream, const OUTPUT::RootPath &rootLevelObj)
	{
		stream << rootLevelObj.GetRootPath();
		return stream;
	}
}; // end namespace OUTPUT;

