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
#include "DocStatusHistoryField.h"
#include "../ARInside.h"
#include "../output/URLLink.h"

CDocStatusHistoryField::CDocStatusHistoryField(int schemaInsideId, const ARStatHistoryValue& statHistValue)
: CDocBasicField(schemaInsideId, AR_CORE_STATUS_HISTORY), statusHistory(statHistValue)
{
}

void CDocStatusHistoryField::GetResolvedAndLinkedField(std::ostream &strm, const CRefItem *refItem, int rootLevel)
{
	CDocBasicField::GetResolvedAndLinkedField(strm, refItem, rootLevel);

	CARInside* arIn = CARInside::GetInstance();
	int enumId = statusHistory.enumVal;
	string enumValue = arIn->GetFieldEnumValue(schemaId, AR_CORE_STATUS, enumId);

	strm << ".";
	if (enumValue.empty())
		strm << enumId;
	else
		strm << enumValue;

	strm << ".";
	strm << CAREnum::StatHistoryTag(statusHistory.userOrTime);
}
