//Copyright (C) 2009 John Luthgers | jls17
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
#include "../ARInside.h"
#include "../core/ARQualification.h"
#include "../core/ARSetFieldHelper.h"
#include <tinyxml/tinyxml.h>

class CDocActionSetFieldsHelper
{
public:
	CDocActionSetFieldsHelper(CARInside &arInside, CARServerObject &arServerObject, const string& objAttachedToSchemaName, const ARSetFieldsActionStruct& sFieldStruct, int structItemType, IfElseState ifElse, int numAction, int rootLevel);
	~CDocActionSetFieldsHelper(void);

	std::ostream& ToStream(std::ostream &writer);
	void ShowActionWithServerName(bool showIt);

	enum WebserviceMappingMode 
	{
		WMM_INPUT,
		WMM_OUTPUT
	};

private:
	CARInside& arIn;
	CARServerObject& obj;
	const std::string& attachedSchemaName;
	const ARSetFieldsActionStruct& setFieldsStruct;
	int arStructItemType;
	IfElseState ifElse;
	int nAction;
	int rootLevel;
	bool showServerNameInOutput;
	bool showFormNameInOutput;

	std::string schemaNameActionIsReadingFrom;

private:
	void GenerateDefaultMappingTable(std::ostream &writer, std::stringstream &strmSchemaDisplay, std::stringstream &strmServer, std::stringstream &strmQual);
	string processMappingXML( TiXmlNode* pParent, string sParent, CTable &tblFieldList, string form, WebserviceMappingMode type);
	const char* GetSetFieldsTypeName(SetFieldType type);
};
