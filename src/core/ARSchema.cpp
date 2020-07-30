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
#include "ARSchema.h"
#include "../lists/ARSchemaList.h"
#include "ARField.h"
#include "ARVui.h"
#include "../ARInside.h"

CARSchema::CARSchema()
: CARServerObject(-1)
{
}

CARSchema::CARSchema(int insideId)
: CARServerObject(insideId)
{	
}

CARSchema::CARSchema(const string& schemaName)
: CARServerObject(-1)
{
	insideId = CARInside::GetInstance()->schemaList.Find(schemaName.c_str());
}

CARSchema::~CARSchema(void)
{
}

bool CARSchema::Exists() const
{
	return (insideId >= 0 && (unsigned int)insideId < CARInside::GetInstance()->schemaList.GetCount());
}

bool CARSchema::IsClonable() const
{
	return true;
}

CARServerObject* CARSchema::Clone() const
{
	return new CARSchema(*this);
}

string CARSchema::WebAlias()
{
	stringstream strm;
	strm.str("");

	try
	{
		const ARPropList& propList = this->GetPropList();
		for(unsigned int i=0; i < propList.numItems; ++i)
		{
			if (propList.props[i].prop == AR_OPROP_FORM_NAME_WEB_ALIAS)
			{
				if(propList.props[i].value.dataType == AR_DATA_TYPE_CHAR && propList.props[i].value.u.charVal != NULL)
				{
					strm << propList.props[i].value.u.charVal;
					break;
				}
			}
		}
	}
	catch(exception& e)
	{
		cout << "EXCEPTION enumerating web alias: " << e.what() << endl;
	}

	return strm.str();
}

string CARSchema::GetName()
{
	return CARInside::GetInstance()->schemaList.SchemaGetName(GetInsideId());
}

string CARSchema::GetName() const
{
	return CARInside::GetInstance()->schemaList.SchemaGetName(GetInsideId());
}

string CARSchema::GetNameFirstChar()
{
	return CARObject::GetNameFirstChar(CARInside::GetInstance()->schemaList.SchemaGetName(GetInsideId()));
}

bool CARSchema::NameStandardFirstChar()
{
	return CARObject::NameStandardFirstChar(GetNameFirstChar());
}

const char* CARSchema::GetHelpText() const
{
	return CARInside::GetInstance()->schemaList.SchemaGetHelptext(GetInsideId());
}

ARTimestamp CARSchema::GetTimestamp() const
{
	return CARInside::GetInstance()->schemaList.SchemaGetTimestamp(GetInsideId());
}

const ARAccessNameType& CARSchema::GetOwner() const
{
	return CARInside::GetInstance()->schemaList.SchemaGetOwner(GetInsideId());
}

const ARAccessNameType& CARSchema::GetLastChanged() const
{
	return CARInside::GetInstance()->schemaList.SchemaGetModifiedBy(GetInsideId());
}

const char* CARSchema::GetChangeDiary() const
{
	return CARInside::GetInstance()->schemaList.SchemaGetChangeDiary(GetInsideId());
}

const ARNameType& CARSchema::GetARName() const
{
	return CARInside::GetInstance()->schemaList.SchemaGetName(GetInsideId());
}

const ARCompoundSchema& CARSchema::GetCompound() const
{
	return CARInside::GetInstance()->schemaList.SchemaGetCompound(GetInsideId());
}

const ARPermissionList& CARSchema::GetPermissions() const
{
	return CARInside::GetInstance()->schemaList.SchemaGetPermissions(GetInsideId());
}

const ARInternalIdList& CARSchema::GetSubadmins() const
{
	return CARInside::GetInstance()->schemaList.SchemaGetSubadmins(GetInsideId());
}

const AREntryListFieldList& CARSchema::GetResultFields() const
{
	return CARInside::GetInstance()->schemaList.SchemaGetResultFields(GetInsideId());
}

const ARSortList& CARSchema::GetSortList() const
{
	return CARInside::GetInstance()->schemaList.SchemaGetSortList(GetInsideId());
}

const ARIndexList& CARSchema::GetIndexList() const
{
	return CARInside::GetInstance()->schemaList.SchemaGetIndexList(GetInsideId());
}

const ARArchiveInfoStruct& CARSchema::GetArchiveInfo() const
{
	return CARInside::GetInstance()->schemaList.SchemaGetArchiveInfo(GetInsideId());
}

const ARAuditInfoStruct& CARSchema::GetAuditInfo() const
{
	return CARInside::GetInstance()->schemaList.SchemaGetAuditInfo(GetInsideId());
}

const ARNameType& CARSchema::GetDefaultVUI() const
{
	return CARInside::GetInstance()->schemaList.SchemaGetDefaultVUI(GetInsideId());
}

const ARPropList& CARSchema::GetPropList() const
{
	return CARInside::GetInstance()->schemaList.SchemaGetPropList(GetInsideId());
}

const string& CARSchema::GetAppRefName() const
{
	return CARInside::GetInstance()->schemaList.SchemaGetAppRefName(GetInsideId());
}

void CARSchema::SetAppRefName(const string& appName)
{
	return CARInside::GetInstance()->schemaList.SchemaSetAppRefName(GetInsideId(), appName);
}

int CARSchema::GetDbTableId() const
{
	return CARInside::GetInstance()->schemaList.SchemaGetDbTableId(GetInsideId());
}

const ARNameType& CARSchema::GetDbViewName() const
{
	return CARInside::GetInstance()->schemaList.SchemaGetDbViewName(GetInsideId());
}

const ARNameType& CARSchema::GetDbShViewName() const
{
	return CARInside::GetInstance()->schemaList.SchemaGetDbShViewName(GetInsideId());
}

CARFieldList* CARSchema::GetFields()
{
	return CARInside::GetInstance()->schemaList.SchemaGetFields(GetInsideId());
}

CARVUIList* CARSchema::GetVUIs()
{
	return CARInside::GetInstance()->schemaList.SchemaGetVUIs(GetInsideId());
}

void CARSchema::AddFilter(const CARFilter &filter)
{
	CARInside::GetInstance()->schemaList.SchemaAddFilter(GetInsideId(), filter);
}

void CARSchema::AddActiveLink(const CARActiveLink& actlink)
{
	CARInside::GetInstance()->schemaList.SchemaAddActiveLink(GetInsideId(), actlink);
}

void CARSchema::AddEscalation(const CAREscalation& escalation)
{
	CARInside::GetInstance()->schemaList.SchemaAddEscalation(GetInsideId(), escalation);
}

void CARSchema::AddActLinkGuide(const CARContainer& alGuide)
{
	CARInside::GetInstance()->schemaList.SchemaAddActLinkGuide(GetInsideId(), alGuide);
}

void CARSchema::AddFilterGuide(const CARContainer& fltGuide)
{
	CARInside::GetInstance()->schemaList.SchemaAddFilterGuide(GetInsideId(), fltGuide);
}

void CARSchema::AddPackingList(const CARContainer &packList)
{
	CARInside::GetInstance()->schemaList.SchemaAddPackingList(GetInsideId(), packList);
}

void CARSchema::AddWebservice(const CARContainer& webservice)
{
	CARInside::GetInstance()->schemaList.SchemaAddWebservice(GetInsideId(), webservice);
}

void CARSchema::AddMissingFieldReference(int fieldId, const CRefItem &refItem)
{
	CARInside::GetInstance()->schemaList.SchemaAddMissingFieldReference(GetInsideId(), fieldId, refItem);
}

const CARSchema::MissingReferenceList* CARSchema::GetMissingReferences()
{
	return CARInside::GetInstance()->schemaList.SchemaGetMissingReferences(GetInsideId());
}

const CARSchemaList::ObjectRefList& CARSchema::GetActiveLinks()
{
	return CARInside::GetInstance()->schemaList.SchemaGetALReferences(GetInsideId());
}

const CARSchemaList::ObjectRefList& CARSchema::GetFilters()
{
	return CARInside::GetInstance()->schemaList.SchemaGetFilterReferences(GetInsideId());
}

const CARSchemaList::ObjectRefList& CARSchema::GetEscalations()
{
	return CARInside::GetInstance()->schemaList.SchemaGetEscalationReferences(GetInsideId());
}

const CARSchemaList::ObjectRefList& CARSchema::GetActLinkGuides()
{
	return CARInside::GetInstance()->schemaList.SchemaGetActLinkGuideReferences(GetInsideId());
}

const CARSchemaList::ObjectRefList& CARSchema::GetFilterGuides()
{
	return CARInside::GetInstance()->schemaList.SchemaGetFilterGuideReferences(GetInsideId());
}

const CARSchemaList::ObjectRefList& CARSchema::GetPackingLists()
{
	return CARInside::GetInstance()->schemaList.SchemaGetPackingListReferences(GetInsideId());
}

const CARSchemaList::ObjectRefList& CARSchema::GetWebservices()
{
	return CARInside::GetInstance()->schemaList.SchemaGetWebserviceReferences(GetInsideId());
}

void CARSchema::AddReference(const CRefItem &refItem)
{
	return CARInside::GetInstance()->schemaList.AddReference(GetInsideId(), refItem);
}

bool CARSchema::ReferenceExists(const CRefItem &refItem) const
{
	return CARInside::GetInstance()->schemaList.ReferenceExists(GetInsideId(), refItem);
}

const CARSchema::ReferenceList& CARSchema::GetReferences() const
{
	return CARInside::GetInstance()->schemaList.GetReferences(GetInsideId());
}

bool CARSchema::IsAuditTarget()
{
	const ReferenceList &references = GetReferences();
	CARSchema::ReferenceList::const_iterator curIt = references.begin();
	CARSchema::ReferenceList::const_iterator endIt = references.end();

	for (; curIt != endIt; ++curIt)
	{
		if (curIt->GetMessageId() == REFM_SCHEMA_AUDIT_SOURCE)
			return true;
	}
	return false;
}

bool CARSchema::IsArchiveTarget()
{
	const ARArchiveInfoStruct &archive = GetArchiveInfo();
	return (archive.archiveType == AR_ARCHIVE_NONE && archive.archiveFrom[0] != 0);
}

unsigned int CARSchema::GetInternalSchemaType()
{
	unsigned int schemaType = GetCompound().schemaType;

	if (IsAuditTarget())
	{
		schemaType = AR_SCHEMA_AUDIT;
	}
	else if (IsArchiveTarget())
	{
		schemaType = AR_SCHEMA_ARCHIVE;
	}

	return schemaType;
}
