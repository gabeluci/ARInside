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
#include "DocBase.h"
#include "../core/ARValue.h"
#include "../core/ARProplistHelper.h"

class CDocFieldDetails :
	public CDocBase
{
public:
	CDocFieldDetails(unsigned int SchemaInsideId, const CARField& fieldObj, int rootLevel);
	~CDocFieldDetails(void);

	void Documentation();

	static bool GetColumnSourceField(const CARField& col, CARField& source, std::string* colSourceSchemaName);

private:
	CARSchema schema;
	CARField field;

	string DefaultValue();
	string FieldLimits();
	string FieldMapping();
	string Permisssions();
	string DisplayProperties();
	string JoinFormReferences();
	string WorkflowReferences();
	string WorkflowAttached();
	int AttachmentFieldGetPool(const CARField& fldObj);
};
