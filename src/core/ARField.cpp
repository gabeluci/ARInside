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
//    along with ARInside.  If not, see <http://www.gnu.org/licenses/>.

#include "stdafx.h"
#include "ARField.h"
#include "../lists/ARFieldList.h"

CARField::CARField()
: CARServerObject(-1), schema(-1)
{
	fieldIndex = -1;
}

CARField::CARField(int SchemaInsideId, unsigned int fieldId, int SchemaFieldIndex)
: CARServerObject(fieldId), schema(SchemaInsideId)
{	
	if (!schema.Exists())
	{
		insideId = -1;
		fieldIndex = -1;
		return;
	}

	// look up and store the field index for faster access
	fieldList = schema.GetFields();

	if (fieldId == 0 && SchemaFieldIndex >= 0 && (unsigned int)SchemaFieldIndex < fieldList->GetCount())
	{
		fieldIndex = SchemaFieldIndex;
		insideId = GetFieldId();
	}
	else if (fieldId > 0)
	{
		fieldIndex = fieldList->Find(fieldId);
	}
	else
	{
		fieldIndex = SchemaFieldIndex;
	}

#ifdef _DEBUG
	if (Exists())
	{
		const ARNameType& tmp_name = fieldList->FieldGetName(fieldIndex);
		const ARAccessNameType& tmp_own = fieldList->FieldGetOwner(fieldIndex);
		const ARAccessNameType& tmp_mod = fieldList->FieldGetModifiedBy(fieldIndex);

		this->dbg_name = (ARNameType*)&tmp_name;
		this->dbg_fieldId = fieldList->FieldGetFieldId(fieldIndex);
		this->dbg_fieldMap = (ARFieldMappingStruct*)&fieldList->FieldGetMapping(fieldIndex);
		this->dbg_dataType = fieldList->FieldGetDataType(fieldIndex);
		this->dbg_option = fieldList->FieldGetOption(fieldIndex);
		this->dbg_createMode = fieldList->FieldGetCreateMode(fieldIndex);
		this->dbg_fieldOption = fieldList->FieldGetFieldOption(fieldIndex);
		this->dbg_defaultValue = (ARValueStruct*)&fieldList->FieldGetDefaultValue(fieldIndex);
		this->dbg_permissions = (ARPermissionList*)&fieldList->FieldGetPermissions(fieldIndex);
		this->dbg_limits = (ARFieldLimitStruct*)&fieldList->FieldGetLimits(fieldIndex);
		this->dbg_dinstList = (ARDisplayInstanceList*)&fieldList->FieldGetDisplayInstances(fieldIndex);
		this->dbg_helpText = fieldList->FieldGetHelptext(fieldIndex);
		this->dbg_timestamp = (ARTimestamp*)&fieldList->FieldGetTimestamp(fieldIndex);
		this->dbg_fieldOwner = (ARAccessNameType*)&tmp_own;
		this->dbg_modifiedBy = (ARAccessNameType*)&tmp_mod;
		this->dbg_changeDiary = fieldList->FieldGetChangeDiary(fieldIndex);
	}
#endif
}

bool CARField::Exists() const
{
	return (fieldIndex >= 0 && (unsigned int)fieldIndex < fieldList->GetCount());
}

bool CARField::IsClonable() const
{
	return true;
}

CARServerObject* CARField::Clone() const
{
	return new CARField(*this);
}

string CARField::GetName()
{
	return fieldList->FieldGetName(fieldIndex);
}

string CARField::GetName() const
{
	return fieldList->FieldGetName(fieldIndex);
}

string CARField::GetNameFirstChar()
{
	return CARObject::GetNameFirstChar(fieldList->FieldGetName(fieldIndex));
}

bool CARField::NameStandardFirstChar()
{
	return CARObject::NameStandardFirstChar(GetNameFirstChar());
}

const char* CARField::GetHelpText() const
{
	return fieldList->FieldGetHelptext(fieldIndex);
}

ARTimestamp CARField::GetTimestamp() const
{
	return fieldList->FieldGetTimestamp(fieldIndex);
}

const ARAccessNameType& CARField::GetOwner() const
{
	return fieldList->FieldGetOwner(fieldIndex);
}

const ARAccessNameType& CARField::GetLastChanged() const
{
	return fieldList->FieldGetModifiedBy(fieldIndex);
}

const char* CARField::GetChangeDiary() const
{
	return fieldList->FieldGetChangeDiary(fieldIndex);
}

const ARPropList& CARField::GetPropList() const
{
	return fieldList->FieldGetPropList(fieldIndex);
}

ARInternalId CARField::GetFieldId() const
{
	return fieldList->FieldGetFieldId(fieldIndex); 
}

const ARFieldMappingStruct& CARField::GetMapping() const
{ 
	return fieldList->FieldGetMapping(fieldIndex);
}

unsigned int CARField::GetDataType() const
{
	return fieldList->FieldGetDataType(fieldIndex);
}

unsigned int CARField::GetOption() const
{
	return fieldList->FieldGetOption(fieldIndex);
}

unsigned int CARField::GetCreateMode() const
{
	return fieldList->FieldGetCreateMode(fieldIndex);
}

unsigned int CARField::GetFieldOption() const
{
	return fieldList->FieldGetOption(fieldIndex);
}

const ARValueStruct& CARField::GetDefaultValue() const
{
	return fieldList->FieldGetDefaultValue(fieldIndex);
}

const ARPermissionList& CARField::GetPermissions() const
{
	return fieldList->FieldGetPermissions(fieldIndex);
}

const ARFieldLimitStruct& CARField::GetLimits() const
{
	return fieldList->FieldGetLimits(fieldIndex);
}

const ARDisplayInstanceList& CARField::GetDisplayInstances() const
{
	return fieldList->FieldGetDisplayInstances(fieldIndex);
}

const CARSchema& CARField::GetSchema() const
{
	return schema;
}

bool CARField::ReferenceExists(const CRefItem &refItem) const
{
	return fieldList->FieldReferenceExists(fieldIndex, refItem);
}

void CARField::AddReference(const CRefItem& refItem) const
{
	fieldList->FieldReferenceAdd(fieldIndex, refItem);
}

const CARFieldList::ReferenceList& CARField::GetReferences() const
{
	return fieldList->FieldReferenceList(fieldIndex);
}
