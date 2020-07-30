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
#include "../core/ARProplistHelper.h"
#include "../output/Table.h"
#include "../output/TableRow.h"
#include "../output/FilterTable.h"
#include "../output/AlTable.h"
#include "../output/EscalTable.h"
#include "../output/ContainerTable.h"
#include "../output/MenuTable.h"
#include "../output/SchemaTable.h"

class CDocSchemaDetails :
	public CDocBase
{
public:
	CDocSchemaDetails(unsigned int schemaInsideId, int rootLevel);
	~CDocSchemaDetails(void);

	void Documentation();
private:
	CARSchema schema;
	int overlayType;

	void ShowIndexProperties(std::ostream &strm, CARProplistHelper *propIndex);
	void ShowResultListProperties(std::ostream &strm, CARProplistHelper *propIndex);
	void ShowSortListProperties(std::ostream &strm, CARProplistHelper *propIndex);
	string ShowVuiList();
	void ShowPermissionProperties(std::ostream &strm, CARProplistHelper *propIndex);
	string WorkflowDoc();

	std::string GenerateReferencesTable(const ARCompoundSchema &compSchema);
	std::string AuditTargetReferences();

	string AllFields();
	void AllFieldsCsv();
	void AllFieldsJson(std::ostream &out);
	string AllFieldsSpecial();
	void AllFieldsSpecialCsv();
	string GenerateFieldTableDescription(CTable &tbl);

	string ShowGeneralInfo();
	string TypeDetails();
	string ContainerReferences();
	string TableFieldReferences();
	string AlWindowOpenReferences();
	string JoinFormReferences();
	string SearchMenuReferences();
	void WorkflowReferences(std::ostream &strm);
	
	string ShowProperties();
	void ShowBasicProperties(std::ostream& strm, CARProplistHelper* propIndex);
	void ShowEntryPointProperties(std::ostream& strm, CARProplistHelper* propIndex);
	void ShowAuditProperties(std::ostream& strm);
	void ShowArchiveProperties(std::ostream& strm);
	void ShowFTSMTSProperties(std::ostream& strm, CARProplistHelper *propIndex);
	void ShowChangeHistory(std::ostream &strm, CARProplistHelper *propIndex);

	bool InAlList(string objName);
	bool InFilterList(string objName);
	bool InEscalList(string objName);
	bool IsSchemaInWFConnectStruct(const ARWorkflowConnectStruct& wfCS);
	bool IsJoinViewOrVendorForm();
	list<string> uniqueAlList;
	list<string> uniqueFilterList;
	list<string> uniqueEscalList;

	string GetSchemaType();
};
