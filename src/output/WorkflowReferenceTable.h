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

#pragma once

#include "../util/RefItem.h"

class CARFilter;
class CARImage;
class CARServerObject;
class CARContainer;

namespace OUTPUT
{
	class WorkflowReferenceTable
	{
	public:
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_750
		WorkflowReferenceTable(const CARImage& image);
#endif
		WorkflowReferenceTable(const CARContainer& container);
	
		std::string ToString(int rootLevel);

	private:
		CRefItemList::const_iterator curIt;
		CRefItemList::const_iterator endIt;
		const CARServerObject &obj;

		void InitIterators(const CRefItemList &refItemList);

	public:
		static string LinkToObjByRefItem(const CRefItem& refItem, int rootLevel);
		static string LinkToFilterRef(CARFilter* filter, int rootLevel);
	private:
		static string LinkToAlRef(const CRefItem& refItem, int rootLevel);
		static string LinkToFilterRef(int filterInsideId, int rootLevel);	
		static string LinkToFilterRef(const CRefItem& refItem, int rootLevel);
	};
};
