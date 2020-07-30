//Copyright (C) 2012 John Luthgers | jls17
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

#include "../ARInside.h"

enum SetFieldType
{
	SFT_CURRENT,
	SFT_SERVER,
	SFT_SAMPLEDATA,
	SFT_SQL,
	SFT_FILTERAPI,
	SFT_WEBSERVICE,
	SFT_ATRIUM_ORCHESTRATOR,
};

// === CARSetFieldHelper ===
// This class is used to decode some of the informations needed for creating setfield documentation. It does
// not generate any documentation. It is used to recursively parse out some informations which are not directly
// available.

class CARSetFieldHelper
{
public:
	CARSetFieldHelper(CARInside &arInside, const CARSchema& wfConnectedSchema, const ARSetFieldsActionStruct& sFieldStruct, IfElseState ifElse, int numAction);
	~CARSetFieldHelper(void);

	SetFieldType GetType();
	const string& GetServerName() const;    // only for activelinks
	const string& GetSchemaName() const;    // the schema used in this action (in case GetType == SFT_CURRENT, this is the same as wfConnectSchema
	int GetSchemaFieldId();                 // schema from fieldid or keyword
	int GetServerFieldId();                 // server from fieldid or keyword
	int GetNoMatchOption();                 // noMatch option for supported actions (SERVER, SQL)
	int GetMultiMatchOption();              // multiMatch option for supported actions (SERVER, SQL)
	ARQualifierStruct* GetQualifier();      // qualifier struct
	const string& GetSqlCommand() const;    // the sql command in case type = SFT_SQL

	int GetFilterAPINumItems() const;       // in case of SFT_FILTERAPI, it returns the item count of the input mapping
	const ARAssignStruct* GetFilterAPIInputs() const; // in case of SFT_FILTERAPI, it returns the input mapping

private:
	void Parse();
	bool CheckAssignment(const ARAssignStruct &assignment);

private:
	CARInside& arIn;                                // reference to CARInside instance
	CARSchema connectedSchema;                      // the schema which the activelink is attached to and which is used for field id resolving
	const ARSetFieldsActionStruct& setFieldsStruct; // the action ifself
	IfElseState ifElse;                             // is the action a if- or else-action
	int nAction;                                    // action index

	// results after parsing
	SetFieldType type;
	
	string serverName;
	int serverFromFieldId;

	string schemaName;
	int schemaFromFieldId;

	int noMatchValue;
	int multiMatchValue;

	ARQualifierStruct* qualifier;
	string sqlCommand;

	ARAssignStruct* filterApiInputValues;
	int filterApiInputNumItems;
};
