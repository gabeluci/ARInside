//Copyright (C) 2014 John Lutghers | jls17
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
#include "../ARInside.h"
#include "../output/URLLink.h"
#include "DocBasicField.h"

CDocBasicField::CDocBasicField(int schemaInsideId, int refFieldId)
: schemaId(schemaInsideId), fieldId(refFieldId)
{
}

void CDocBasicField::GetResolvedAndLinkedField(std::ostream &strm, const CRefItem *refItem, int rootLevel)
{
	if (fieldId <= 0)
	{
		// keyword support
		int iKeyword = abs(fieldId);
		strm << CAREnum::Keyword(iKeyword);
		return;
	}

	CARField fieldObj(schemaId, fieldId);
	if (fieldObj.Exists())
	{
		strm << URLLink(fieldObj, rootLevel);
		
		if (refItem)
		{
			CARInside* arIn = CARInside::GetInstance();
			arIn->AddFieldReference(schemaId, fieldId, *refItem);
		}
	}
	else
		strm << fieldId;  // TODO: missing fields are normally maked red (see CARInside::LinkToField)
}
