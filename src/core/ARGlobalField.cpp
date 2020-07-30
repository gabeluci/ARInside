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

#include "stdafx.h"
#include "ARGlobalField.h"
#include "ARField.h"

CARGlobalField::CARGlobalField(const CARField& field)
{
	this->schemaInsideId = field.GetSchema().GetInsideId();
	this->fieldId = field.GetFieldId();
}

CARGlobalField::~CARGlobalField(void)
{
}

bool CARGlobalField::operator<(const CARGlobalField& r)
{
	CARField left(this->schemaInsideId, this->fieldId);
	CARField right(r.schemaInsideId, r.fieldId);
	int lfid = left.GetFieldId();
	int rfid = right.GetFieldId();

	if (lfid == rfid) return (this->schemaInsideId < r.schemaInsideId);
	if (lfid < rfid) return true;

	return false;
}
