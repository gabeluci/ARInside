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
//    along with ARInside.  If not, see <http://www.gnu.org/licenses/>.
#pragma once
#include "../ARApi.h"
#include "../util/Uncopyable.h"
#include "ARListHelpers.h"
#include "ARFieldList.h"
#include "ARVUIList.h"
#include <assert.h>

// forward declarations
class CARActiveLink;
class CARFilter;
class CAREscalation;
class CARContainer;

struct ARSchemaDbValues
{
	unsigned int schemaId;
	ARNameType viewName;
	ARNameType shViewName;
};

class CARSchemaList : Uncopyable
{
public:
	CARSchemaList(void);
	~CARSchemaList(void);

	// loading...
	bool LoadFromServer();
	int AddSchemaFromXML(ARXMLParsedStream& stream, const char* schemaName, unsigned int *arDocVersion = NULL);

	// list functions
	inline unsigned int GetCount() { return names.numItems; }
	int Find(const char *name);
	void Reserve(unsigned int size);
	void Sort();
	void SortReferences();

	// data-access functions
	const ARNameType& SchemaGetName(unsigned int index) const { assert(index < names.numItems); return names.nameList[sortedList[index]]; }
	const ARCompoundSchema& SchemaGetCompound(unsigned int index) const { assert(index < compounds.numItems); return compounds.compoundSchema[sortedList[index]]; }
	const ARPermissionList& SchemaGetPermissions(unsigned int index) const { assert(index < permissions.numItems); return permissions.permissionList[sortedList[index]]; }
	const ARInternalIdList& SchemaGetSubadmins(unsigned int index) const { assert(index < subAdmins.numItems); return subAdmins.internalIdListList[sortedList[index]]; }
	const AREntryListFieldList& SchemaGetResultFields(unsigned int index) const { assert(index < resultFields.numItems); return resultFields.listFieldList[sortedList[index]]; }
	const ARSortList& SchemaGetSortList(unsigned int index) const { assert(index < sortings.numItems); return sortings.sortListList[sortedList[index]]; }
	const ARIndexList& SchemaGetIndexList(unsigned int index) const { assert(index < indexes.numItems); return indexes.indexListList[sortedList[index]]; }
	const ARArchiveInfoStruct& SchemaGetArchiveInfo(unsigned int index) const { assert(index < archives.numItems); return archives.archiveInfoList[sortedList[index]]; }
	const ARAuditInfoStruct& SchemaGetAuditInfo(unsigned int index) const { assert(index < audits.numItems); return audits.auditInfoList[sortedList[index]]; }
	const ARNameType& SchemaGetDefaultVUI(unsigned int index) const { assert(index < defaultVUIs.numItems); return defaultVUIs.nameList[sortedList[index]]; }
	char* SchemaGetHelptext(unsigned int index) const { assert(index < helpTexts.numItems); return helpTexts.stringList[sortedList[index]]; }
	const ARTimestamp& SchemaGetTimestamp(unsigned int index) const { return changedTimes.timestampList[sortedList[index]]; }
	const ARAccessNameType& SchemaGetOwner(unsigned int index) const { assert(index < owners.numItems); return owners.nameList[sortedList[index]]; }
	const ARAccessNameType& SchemaGetModifiedBy(unsigned int index) const { assert(index < changedUsers.numItems); return changedUsers.nameList[sortedList[index]]; }
	const char* SchemaGetChangeDiary(unsigned int index) const { assert(index < changeDiary.numItems); return changeDiary.stringList[sortedList[index]]; }
	const ARPropList& SchemaGetPropList(unsigned int index) const { assert(index < objProps.numItems); return objProps.propsList[sortedList[index]]; }

	const string& SchemaGetAppRefName(unsigned int index) const { assert(index < appRefNames.size()); return appRefNames[sortedList[index]]; }
	void SchemaSetAppRefName(unsigned int index, const string& appName) { assert(index < appRefNames.size()); appRefNames[sortedList[index]] = appName; }

	int SchemaGetDbTableId(unsigned int index) const { assert(index < schemaDbValues.size()); return schemaDbValues[sortedList[index]].schemaId; }
	const ARNameType& SchemaGetDbViewName(unsigned int index) const { assert(index < schemaDbValues.size()); return schemaDbValues[sortedList[index]].viewName; }
	const ARNameType& SchemaGetDbShViewName(unsigned int index) const { assert(index < schemaDbValues.size()); return schemaDbValues[sortedList[index]].shViewName; }

	// referencing
	typedef vector<CRefItem> ReferenceList;
	void AddReference(unsigned int index, const CRefItem& refItem);
	bool ReferenceExists(unsigned int index, const CRefItem& refItem);
	const ReferenceList& GetReferences(unsigned int index);

	// workflow reference functions
	typedef pair<int, CRefItem> MissingReferenceItem;
	typedef vector<MissingReferenceItem> MissingReferenceList;
	void SchemaAddMissingFieldReference(unsigned int index, int fieldId, const CRefItem &refItem);
	const MissingReferenceList* SchemaGetMissingReferences(unsigned int index);

	typedef vector<int> ObjectRefList;
	void SchemaAddActiveLink(unsigned int index, const CARActiveLink& actlink);
	void SchemaAddFilter(unsigned int index, const CARFilter& filter);
	void SchemaAddEscalation(unsigned int index, const CAREscalation& escalation);
	void SchemaAddActLinkGuide(unsigned int index, const CARContainer& alGuide);
	void SchemaAddFilterGuide(unsigned int index, const CARContainer& fltGuide);
	void SchemaAddPackingList(unsigned int index, const CARContainer& packingList);
	void SchemaAddWebservice(unsigned int index, const CARContainer& webservice);

	const ObjectRefList& SchemaGetALReferences(unsigned int index) { return activeLinks[index]; }
	const ObjectRefList& SchemaGetFilterReferences(unsigned int index) { return filters[index]; }
	const ObjectRefList& SchemaGetEscalationReferences(unsigned int index) { return escalations[index]; }
	const ObjectRefList& SchemaGetActLinkGuideReferences(unsigned int index) { return alGuides[index]; }
	const ObjectRefList& SchemaGetFilterGuideReferences(unsigned int index) { return fltGuides[index]; }
	const ObjectRefList& SchemaGetPackingListReferences(unsigned int index) { return packLists[index]; }
	const ObjectRefList& SchemaGetWebserviceReferences(unsigned int index) { return webservices[index]; }

	// access for contained lists
	CARFieldList* SchemaGetFields(unsigned int index) { assert(index < fieldLists.size()); return fieldLists[sortedList[index]]; }
	CARVUIList* SchemaGetVUIs(unsigned int index) { assert(index < vuiLists.size()); return vuiLists[sortedList[index]]; }

	void AddOverlayOrCustom(unsigned int index);
	const ObjectRefList& GetOverlayAndCustomWorkflow();

private:
	void InitDatabaseDetails();
	void LoadDatabaseDetails();

	int TryFindSchemaInNameList(const char* schemaName);
	void StoreDatabaseDetails(ARValueListList &valList);
	void StoreSingleDatabaseRow(ARValueList &row, int storeToSchemaIndex);


private:
	// allocation state of internal structures
	enum SchemaListState { EMPTY, ARAPI_ALLOC, INTERNAL_ALLOC };
	bool apiBug;

	unsigned int reservedSize;
	ARNameList names;
	ARCompoundSchemaList compounds;
	//ARSchemaInheritanceListList *schemaInheritanceListList; // reserved
	ARPermissionListList permissions;
	ARInternalIdListList subAdmins;
	AREntryListFieldListList resultFields;
	ARSortListList sortings;
	ARIndexListList indexes;
	ARArchiveInfoList archives;
	ARAuditInfoList audits;
	ARNameList defaultVUIs;
	ARTextStringList helpTexts;
	ARTimestampList changedTimes;
	ARAccessNameList owners;
	ARAccessNameList changedUsers;
	ARTextStringList changeDiary;
	ARPropListList objProps;
	vector<string> appRefNames;
	vector<ARSchemaDbValues> schemaDbValues;

	vector<CARFieldList*> fieldLists;
	vector<CARVUIList*> vuiLists;

	SchemaListState internalListState;
	vector<int> sortedList;	// a index, sorted by schema names
	vector<MissingReferenceList*> missingFieldReferences;
	vector<ReferenceList> references;

	vector<ObjectRefList> activeLinks;
	vector<ObjectRefList> filters;
	vector<ObjectRefList> escalations;
	vector<ObjectRefList> alGuides;
	vector<ObjectRefList> fltGuides;
	vector<ObjectRefList> packLists;
	vector<ObjectRefList> webservices;

	typedef map<string,int> CMapType;
	CMapType searchList;
	vector<int> overlayAndCustomList;
};
