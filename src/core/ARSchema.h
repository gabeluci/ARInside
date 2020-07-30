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
#include "ARServerObject.h"
#include "../lists/ARSchemaList.h"

class CARFieldList;
class CARVUIList;
class CARActiveLink;
class CARFilter;
class CAREscalation;

class CARSchema :
	public CARServerObject
{
public:
	CARSchema();
	CARSchema(int insideId);
	CARSchema(const string& schemaName);
	~CARSchema(void);

	bool Exists() const;

	// implement functions inherited from CARObject
	string GetName();
	string GetName() const;
	string GetNameFirstChar();
	bool NameStandardFirstChar();

	// implement functions inherited from CARServerObject
	const char* GetHelpText() const;
	ARTimestamp GetTimestamp() const;
	const ARAccessNameType& GetOwner() const;
	const ARAccessNameType& GetLastChanged() const;
	const char* GetChangeDiary() const;

	// other schema data access functions
	const ARNameType& GetARName() const;
	const ARCompoundSchema& GetCompound() const;
	const ARPermissionList& GetPermissions() const;
	const ARInternalIdList& GetSubadmins() const;
	const AREntryListFieldList& GetResultFields() const;
	const ARSortList& GetSortList() const;
	const ARIndexList& GetIndexList() const;
	const ARArchiveInfoStruct& GetArchiveInfo() const;
	const ARAuditInfoStruct& GetAuditInfo() const;
	const ARNameType& GetDefaultVUI() const;
	const ARPropList& GetPropList() const;

	const string& GetAppRefName() const;
	void SetAppRefName(const string& appName);

	int GetDbTableId() const;
	const ARNameType& GetDbViewName() const;
	const ARNameType& GetDbShViewName() const;

	CARFieldList* GetFields();
	CARVUIList* GetVUIs();

	// some helpers
	string WebAlias();

	// class type support
	int GetServerObjectTypeXML() const { return AR_STRUCT_ITEM_XML_SCHEMA; }
	bool IsClonable() const;
	CARServerObject* Clone() const;

	void AddFilter(const CARFilter& filter);
	void AddActiveLink(const CARActiveLink& actlink);
	void AddEscalation(const CAREscalation& escalation);
	void AddActLinkGuide(const CARContainer& alGuide);
	void AddFilterGuide(const CARContainer& fltGuide);
	void AddPackingList(const CARContainer& packList);
	void AddWebservice(const CARContainer& webservice);

	typedef CARSchemaList::ReferenceList ReferenceList;
	void AddReference(const CRefItem& refItem);
	bool ReferenceExists(const CRefItem& refItem) const;
	const ReferenceList& GetReferences() const;

	typedef CARSchemaList::MissingReferenceItem MissingReferenceItem;
	typedef CARSchemaList::MissingReferenceList MissingReferenceList;
	void AddMissingFieldReference(int fieldId, const CRefItem& refItem);
	const MissingReferenceList* GetMissingReferences();

	const CARSchemaList::ObjectRefList& GetActiveLinks();
	const CARSchemaList::ObjectRefList& GetFilters();
	const CARSchemaList::ObjectRefList& GetEscalations();
	const CARSchemaList::ObjectRefList& GetActLinkGuides();
	const CARSchemaList::ObjectRefList& GetFilterGuides();
	const CARSchemaList::ObjectRefList& GetPackingLists();
	const CARSchemaList::ObjectRefList& GetWebservices();

	bool IsArchiveTarget();
	bool IsAuditTarget();
	unsigned int GetInternalSchemaType();
};
