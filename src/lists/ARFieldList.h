//Copyright (C) 2010 John Luthgers | jls17
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
//    along with ARInside.  If not, see <http://www.gnu.org/licenses/>.#pragma once
#pragma once
#include "../ARApi.h"
#include "../util/Uncopyable.h"
#include "../util/RefItem.h"
#include "ARListHelpers.h"
#include <assert.h>

// forward declarations
class CARSchemaList;

///////////////////////////////////////////////////////////////////////////////
// CARFieldList - interface definition
class CARFieldList : Uncopyable
{
public:
	// no special constructor here ... but a virtual destructor to make sure the correct one is called
	virtual ~CARFieldList(void) { };

	// no loading here ... abstract class!

	// list functions
	virtual unsigned int GetCount() = 0;
	virtual int Find(const char *name) = 0;
	virtual int Find(unsigned int fieldId) = 0;
	virtual void Sort() = 0;

	// data access
	virtual const ARNameType& FieldGetName(unsigned int index) const = 0;
	virtual ARInternalId FieldGetFieldId(unsigned int index) = 0;
	virtual const ARFieldMappingStruct& FieldGetMapping(unsigned int index) const = 0;
	virtual unsigned int FieldGetDataType(unsigned int index) = 0;
	virtual unsigned int FieldGetOption(unsigned int index) = 0;
	virtual unsigned int FieldGetCreateMode(unsigned int index) = 0;
	virtual unsigned int FieldGetFieldOption(unsigned int index) = 0;
	virtual const ARValueStruct& FieldGetDefaultValue(unsigned int index) const = 0;
	virtual const ARPermissionList& FieldGetPermissions(unsigned int index) const = 0;
	virtual const ARFieldLimitStruct& FieldGetLimits(unsigned int index) const = 0;
	virtual const ARDisplayInstanceList& FieldGetDisplayInstances(unsigned int index) const = 0;
	virtual char* FieldGetHelptext(unsigned int index) const = 0;
	virtual const ARTimestamp& FieldGetTimestamp(unsigned int index) const = 0;
	virtual const ARAccessNameType& FieldGetOwner(unsigned int index) const = 0;
	virtual const ARAccessNameType& FieldGetModifiedBy(unsigned int index) const = 0;
	virtual const char* FieldGetChangeDiary(unsigned int index) const = 0;
	virtual const ARPropList& FieldGetPropList(unsigned int index) const = 0;

	// types used for workflow references
	typedef list<CRefItem> ReferenceList;
	// Workflow references
	bool FieldReferenceExists(unsigned int index, const CRefItem& refItem);
	bool FieldReferenceAdd(unsigned int index, const CRefItem& refItem);
	size_t FieldReferenceCount(unsigned int index);
	const ReferenceList& FieldReferenceList(unsigned int index);

protected:
	vector<ReferenceList> workflowReferences;	// this list holds the workflow references
};

///////////////////////////////////////////////////////////////////////////////
// CARFieldListXML - field list support for XML files
class CARFieldListXML : public CARFieldList
{
public:
	CARFieldListXML(void) { ARZeroMemory(&fieldInfo); }
	virtual ~CARFieldListXML(void) { }

	// loading
	void FinishLoading();

	// list functions
	virtual unsigned int GetCount() { return fieldInfo.numItems; }
	virtual int Find(const char *name);
	virtual int Find(unsigned int fieldId);
	virtual void Sort();

	// data access
	virtual const ARNameType& FieldGetName(unsigned int index) const { return fieldInfo.fieldList[sortedList[index]].fieldName; }
	virtual ARInternalId FieldGetFieldId(unsigned int index) { return fieldInfo.fieldList[sortedList[index]].fieldId; }
	virtual const ARFieldMappingStruct& FieldGetMapping(unsigned int index) const { return fieldInfo.fieldList[sortedList[index]].fieldMap; }
	virtual unsigned int FieldGetDataType(unsigned int index) { return fieldInfo.fieldList[sortedList[index]].dataType; }
	virtual unsigned int FieldGetOption(unsigned int index) { return fieldInfo.fieldList[sortedList[index]].option; }
	virtual unsigned int FieldGetCreateMode(unsigned int index) { return fieldInfo.fieldList[sortedList[index]].createMode; }
	virtual unsigned int FieldGetFieldOption(unsigned int index) { return fieldInfo.fieldList[sortedList[index]].fieldOption; }
	virtual const ARValueStruct& FieldGetDefaultValue(unsigned int index) const { return fieldInfo.fieldList[sortedList[index]].defaultVal; }
	virtual const ARPermissionList& FieldGetPermissions(unsigned int index) const { return fieldInfo.fieldList[sortedList[index]].permList; }
	virtual const ARFieldLimitStruct& FieldGetLimits(unsigned int index) const { return fieldInfo.fieldList[sortedList[index]].limit; }
	virtual const ARDisplayInstanceList& FieldGetDisplayInstances(unsigned int index) const { return fieldInfo.fieldList[sortedList[index]].dInstanceList; }
	virtual char* FieldGetHelptext(unsigned int index) const { return fieldInfo.fieldList[sortedList[index]].helpText; }
	virtual const ARTimestamp& FieldGetTimestamp(unsigned int index) const { return fieldInfo.fieldList[sortedList[index]].timestamp; }
	virtual const ARAccessNameType& FieldGetOwner(unsigned int index) const { return fieldInfo.fieldList[sortedList[index]].owner; }
	virtual const ARAccessNameType& FieldGetModifiedBy(unsigned int index) const { return fieldInfo.fieldList[sortedList[index]].lastChanged; }
	virtual const char* FieldGetChangeDiary(unsigned int index) const { return fieldInfo.fieldList[sortedList[index]].changeDiary; }
	virtual const ARPropList& FieldGetPropList(unsigned int index) const;
	
	friend class CARSchemaList;
private:
	ARFieldInfoList fieldInfo;
	vector<unsigned int> sortedList;  // sorted by field name
};

///////////////////////////////////////////////////////////////////////////////
// CARFieldListServer - field list support for direct server access
class CARFieldListServer : public CARFieldList
{
public:
	CARFieldListServer(unsigned int schemaInsideId);
	virtual ~CARFieldListServer(void);

	// loading ...
	bool LoadFromServer();

	// list functions
	virtual unsigned int GetCount() { return names.numItems; }
	virtual int Find(const char *name);
	virtual int Find(unsigned int fieldId);
	virtual void Sort();

	// data access
	virtual const ARNameType& FieldGetName(unsigned int index) const { return names.nameList[sortedList[index]]; }
	virtual ARInternalId FieldGetFieldId(unsigned int index) { return fieldIds.internalIdList[sortedList[index]]; }
	virtual const ARFieldMappingStruct& FieldGetMapping(unsigned int index) const { return fieldMaps.mappingList[sortedList[index]]; }
	virtual unsigned int FieldGetDataType(unsigned int index) { return dataTypes.intList[sortedList[index]]; }
	virtual unsigned int FieldGetOption(unsigned int index) { return options.intList[sortedList[index]]; }
	virtual unsigned int FieldGetCreateMode(unsigned int index) { return createModes.intList[sortedList[index]]; }
	virtual unsigned int FieldGetFieldOption(unsigned int index) { return fieldOptions.intList[sortedList[index]]; }
	virtual const ARValueStruct& FieldGetDefaultValue(unsigned int index) const { return defaultValues.valueList[sortedList[index]]; }
	virtual const ARPermissionList& FieldGetPermissions(unsigned int index) const { return permLists.permissionList[sortedList[index]]; }
	virtual const ARFieldLimitStruct& FieldGetLimits(unsigned int index) const { return limits.fieldLimitList[sortedList[index]]; }
	virtual const ARDisplayInstanceList& FieldGetDisplayInstances(unsigned int index) const { return dInstanceLists.dInstanceList[sortedList[index]]; }
	virtual char* FieldGetHelptext(unsigned int index) const { return helpTexts.stringList[sortedList[index]]; }
	virtual const ARTimestamp& FieldGetTimestamp(unsigned int index) const { return changedTimes.timestampList[sortedList[index]]; }
	virtual const ARAccessNameType& FieldGetOwner(unsigned int index) const { return owners.nameList[sortedList[index]]; }
	virtual const ARAccessNameType& FieldGetModifiedBy(unsigned int index) const { return changedUsers.nameList[sortedList[index]]; }
	virtual const char* FieldGetChangeDiary(unsigned int index) const { return changeDiary.stringList[sortedList[index]]; }
	virtual const ARPropList& FieldGetPropList(unsigned int index) const;

private:
	void Reserve(unsigned int amount);
	void SetNumItems(unsigned int amount);
	void BuildIndex();

private:
	unsigned int schemaId;

	ARNameList names;
	ARInternalIdList fieldIds;
	ARFieldMappingList fieldMaps;
	ARUnsignedIntList dataTypes;
	ARUnsignedIntList options;
	ARUnsignedIntList createModes;
	ARUnsignedIntList fieldOptions;
	ARValueList defaultValues;
	ARPermissionListList permLists;
	ARFieldLimitList limits;
	ARDisplayInstanceListList dInstanceLists;
	ARTextStringList helpTexts;
	ARTimestampList changedTimes;
	ARAccessNameList owners;
	ARAccessNameList changedUsers;
	ARTextStringList changeDiary;
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_763
	ARPropListList objProps;
#endif

	vector<unsigned int> sortedList;  // sorted by field name
};
