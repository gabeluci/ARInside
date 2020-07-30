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

#include "stdafx.h"
#include "DocActionSetFieldsHelper.h"
#include "DocAllMatchingIdsTable.h"
#include "../core/ARAssignHelper.h"
#include "../output/ObjNotFound.h"

CDocActionSetFieldsHelper::CDocActionSetFieldsHelper(CARInside &arInside, CARServerObject &arServerObject, const string& objAttachedToSchemaName, const ARSetFieldsActionStruct& sFieldStruct, int structItemType, IfElseState ifElseMode, int numAction, int rootLevel)
: arIn(arInside), obj(arServerObject), attachedSchemaName(objAttachedToSchemaName), setFieldsStruct(sFieldStruct), ifElse(ifElseMode), rootLevel(rootLevel)
{
	arStructItemType = structItemType;
	nAction = numAction;
	showServerNameInOutput = false;
	showFormNameInOutput = false;
}

CDocActionSetFieldsHelper::~CDocActionSetFieldsHelper(void)
{
}

void CDocActionSetFieldsHelper::ShowActionWithServerName(bool showIt)
{
	showServerNameInOutput = showIt;
}

ostream& CDocActionSetFieldsHelper::ToStream(std::ostream &writer)
{
	stringstream strmSchemaDisplay;
	stringstream strmServer;
	stringstream strmQual;

	bool useDefaultFieldMappingTable = true;
	showFormNameInOutput = true;

	CARSchema wfSchema(attachedSchemaName);
	if (wfSchema.Exists())
	{
		CARSetFieldHelper sfh(*CARInside::GetInstance(), wfSchema, setFieldsStruct, ifElse, nAction);

		writer << "Data Source: " << this->GetSetFieldsTypeName(sfh.GetType()) << "<br/>";

		switch (sfh.GetType())
		{
		case SFT_CURRENT:
			strmServer << arIn.LinkToServerInfo(arIn.appConfig.serverName, rootLevel);
			schemaNameActionIsReadingFrom = sfh.GetSchemaName();
			showFormNameInOutput = false;
			break;
		case SFT_SERVER:
		case SFT_SAMPLEDATA:
			{
				int pFormId = wfSchema.GetInsideId();
				int sFormId = -1;
				string readServer = sfh.GetServerName();
				string readSchema = sfh.GetSchemaName();

				if (readSchema.compare("@") == 0)
				{
					readSchema = attachedSchemaName;
				}

				if (sfh.GetType() == SFT_SAMPLEDATA)
				{
					int fieldId = sfh.GetServerFieldId();
					strmServer << "$" << (fieldId < 0 ? CAREnum::Keyword(abs(fieldId)) : arIn.LinkToField(wfSchema.GetInsideId(), fieldId, rootLevel)) << "$ (Sample Server: " << arIn.LinkToServerInfo(readServer, rootLevel) << ")";

					CRefItem refItemServer(obj, ifElse, nAction, REFM_SETFIELDS_SERVER);
					arIn.AddFieldReference(pFormId, fieldId, refItemServer);

					fieldId = sfh.GetSchemaFieldId();
					strmSchemaDisplay << "$" << (fieldId < 0 ? CAREnum::Keyword(abs(fieldId)) : arIn.LinkToField(wfSchema.GetInsideId(), fieldId, rootLevel)) << "$ (Sample Form: " << arIn.LinkToSchema(readSchema, rootLevel) << ")";
					schemaNameActionIsReadingFrom = (fieldId == (-AR_KEYWORD_SCHEMA) ? attachedSchemaName : readSchema);

					CRefItem refItemForm(obj, ifElse, nAction, REFM_SETFIELDS_FORM);
					arIn.AddFieldReference(pFormId, fieldId, refItemForm);
				}
				else
				{
					strmServer << arIn.LinkToServerInfo(readServer, rootLevel);

					strmSchemaDisplay << readSchema;
					schemaNameActionIsReadingFrom = readSchema;
				}

				// *************************************************************************

				CARSchema readFromSchemaObj(readSchema);
				sFormId = readFromSchemaObj.GetInsideId();

				strmQual << "<br/>Set Field If<br/>" << endl;
				stringstream strmTmpQual;
				CRefItem refItem(obj, ifElse, nAction, REFM_SETFIELDS_QUALIFICATION);

				CARQualification arQual(arIn, refItem, pFormId, sFormId, rootLevel);
				arQual.arsStructItemType = arStructItemType;
				arQual.CheckQuery(sfh.GetQualifier(), strmTmpQual);

				if(strmTmpQual.str().length() > 0)
				{
					strmQual << strmTmpQual.str() << "<br/><br/>" << endl;
				}
				else
				{
					strmQual << EmptyValue << "<br/><br/>" << endl;
				}

				strmQual << "If No Requests Match: " << CAREnum::NoMatchRequest(sfh.GetNoMatchOption()) << "<br/>" << endl;
				strmQual << "If Multiple Requests Match: " << CAREnum::MultiMatchRequest(sfh.GetMultiMatchOption()) << "<br/><br/>" << endl;
			}
			break;
		case SFT_SQL:
			{
				strmServer << arIn.LinkToServerInfo(sfh.GetServerName(), rootLevel);
				strmQual << "<br/>Query:<br/>" << endl;

				if(!sfh.GetSqlCommand().empty())
				{
					CRefItem refItem(obj, ifElse, nAction, REFM_SETFIELDS_SQL_QUALIFICATION);
					strmQual << arIn.TextFindFields(sfh.GetSqlCommand(), "$", wfSchema.GetInsideId(), rootLevel, true, &refItem) << "<br/><br/>" << endl;
				}
				else
					strmQual << EmptyValue << "<br/><br/>" << endl;

				strmQual << "If No Requests Match: " << CAREnum::NoMatchRequest(sfh.GetNoMatchOption()) << "<br/>" << endl;
				strmQual << "If Multiple Requests Match: " << CAREnum::MultiMatchRequest(sfh.GetMultiMatchOption()) << "<br/><br/>" << endl;	

				showFormNameInOutput = false;
			}
			break;
		case SFT_FILTERAPI:
			{
				string schemaName = sfh.GetSchemaName();
				schemaNameActionIsReadingFrom = sfh.GetSchemaName();

				if (schemaName.substr(0, 1) == "$")
				{
					CRefItem refItem(obj, ifElse, nAction, REFM_SETFIELDS_FILTERAPI_PLUGINNAME);
					schemaName = arIn.TextFindFields(sfh.GetSchemaName(), "$", wfSchema.GetInsideId(), rootLevel, true, &refItem);
				}

				// the html-documtation for this action is generated directly here
				writer << "Plugin-Name: " << schemaName << "<br/><br/>" << endl;

				writer << "Input-Mapping: " << "<br/>";
				CARAssignHelper docInput(arIn, rootLevel, obj, wfSchema, wfSchema);
				writer << docInput.FilterApiInputAssignment(sfh.GetFilterAPIInputs(), sfh.GetFilterAPINumItems(), nAction, ifElse);

				writer << "Output-Mapping: " << "<br/>";
				CARAssignHelper assignHelper(arIn, rootLevel, obj, wfSchema, wfSchema);
				writer << assignHelper.SetFieldsAssignment(setFieldsStruct, nAction, ifElse);
			
				// we've generated our own html-table with input/output mapping. So avoid default table.
				useDefaultFieldMappingTable = false;
			}
			break;
		case SFT_WEBSERVICE:
			{
				//NumItems = action.fieldList.fieldAssignList[0].assignment.u.filterApi->numItems;
				//action.fieldList.fieldAssignList[0].assignment.u.filterApi->inputValues[X].u.value
				//0 = Unknown
				//1 = Unknown
				//2 = Unknown
				//3 = Unknown
				//4 = WSDL Location
				//5 = Web Service
				//6 = Operation
				//7 = URI
				//8 = URN
				//9 = Input Mappings
				//10 = Output Mappings
				//11 = Port

				//populate operation string from input #6
				string operation = "";

				TiXmlDocument operationXML;
				operationXML.Parse(setFieldsStruct.fieldList.fieldAssignList[0].assignment.u.filterApi->inputValues[6].u.value.u.charVal, 0, TIXML_DEFAULT_ENCODING);
				TiXmlHandle opHandle(&operationXML);
				TiXmlElement *opElement = opHandle.FirstChild("operation").FirstChild("inputMapping").ToElement();
				if (opElement)
					operation = opElement->Attribute("name");

				writer << "WSDL Location: " << (setFieldsStruct.fieldList.fieldAssignList[0].assignment.u.filterApi->numItems > 4 ? CARValue::ValueToString(setFieldsStruct.fieldList.fieldAssignList[0].assignment.u.filterApi->inputValues[4].u.value) : "") << "<br/>"; 
				writer << "Web Service: " << (setFieldsStruct.fieldList.fieldAssignList[0].assignment.u.filterApi->numItems > 5 ? CARValue::ValueToString(setFieldsStruct.fieldList.fieldAssignList[0].assignment.u.filterApi->inputValues[5].u.value) : "") << "<br/>"; 
				writer << "Port: " << (setFieldsStruct.fieldList.fieldAssignList[0].assignment.u.filterApi->numItems > 11 ? CARValue::ValueToString(setFieldsStruct.fieldList.fieldAssignList[0].assignment.u.filterApi->inputValues[11].u.value) : "") << "<br/>"; 
				writer << "Operation: " << operation << "<br/>";
				writer << "URI: " << (setFieldsStruct.fieldList.fieldAssignList[0].assignment.u.filterApi->numItems > 7 ? CARValue::ValueToString(setFieldsStruct.fieldList.fieldAssignList[0].assignment.u.filterApi->inputValues[7].u.value) : "") << "<br/>"; 
				writer << "URN: " << (setFieldsStruct.fieldList.fieldAssignList[0].assignment.u.filterApi->numItems > 8 ? CARValue::ValueToString(setFieldsStruct.fieldList.fieldAssignList[0].assignment.u.filterApi->inputValues[8].u.value) : "") << "<br/>"; 

				//process input mapping
				if (setFieldsStruct.fieldList.fieldAssignList[0].assignment.u.filterApi->numItems > 9)
				{
					stringstream input;
					input.str("");

					TiXmlDocument inputXML;
					inputXML.Parse(setFieldsStruct.fieldList.fieldAssignList[0].assignment.u.filterApi->inputValues[9].u.value.u.charVal, 0, TIXML_DEFAULT_ENCODING);

					// TODO: this is just a quick and dirty workarround, which might work in some but not all cases. See test/TinyXmlTests.cpp for
					//       more details. Full UTF-8 support might be needed for a real solution.
					if (inputXML.Error())
					{
						cout << "WARN: parsing input xml of filter '" << obj.GetName() << "' failed with: " << inputXML.ErrorDesc() << "!" << endl;						
					}

					TiXmlHandle inputHandle(&inputXML);
					TiXmlNode *element = inputHandle.FirstChild("arDocMapping").FirstChild("formMapping").ToNode();

					CTable tblInputMappingList("pushFieldsList", "TblObjectList");
					tblInputMappingList.AddColumn(30, "Element");
					tblInputMappingList.AddColumn(70, "Field");

					input << processMappingXML(element, "", tblInputMappingList, "", WMM_INPUT);
					input << tblInputMappingList;
					if (inputXML.Error())
					{
						ObjNotFound notFound(input);
						notFound << "<p>Parsing webservice input mapping failed! " << inputXML.ErrorDesc() << " (" << inputXML.ErrorRow() << "," << inputXML.ErrorCol() << ")" << " Mapping might be incomplete!" << "</p>";
						notFound.End();
					}
					writer << "<BR/>";
					writer << "Input Mapping: " << input.str() << "<BR/>";
				}

				//process output mapping
				if (setFieldsStruct.fieldList.fieldAssignList[0].assignment.u.filterApi->numItems > 10)
				{
					stringstream output;
					output.str("");

					TiXmlDocument outputXML;
					outputXML.Parse(setFieldsStruct.fieldList.fieldAssignList[0].assignment.u.filterApi->inputValues[10].u.value.u.charVal, 0, TIXML_DEFAULT_ENCODING);

					if (outputXML.Error())
					{
						cout << "WARN: parsing output xml of filter '" << obj.GetName() << "' failed with: " << outputXML.ErrorDesc() << "!" << endl;
					}

					TiXmlHandle outputHandle(&outputXML);
					TiXmlNode *element = outputHandle.FirstChild("arDocMapping").FirstChild("formMapping").ToNode();

					CTable tblOutputMappingList("pushFieldsList", "TblObjectList");
					tblOutputMappingList.AddColumn(30, "Element");
					tblOutputMappingList.AddColumn(70, "Field");

					output << processMappingXML(element, "", tblOutputMappingList, "", WMM_OUTPUT);
					output << tblOutputMappingList;
					if (outputXML.Error())
					{
						ObjNotFound notFound(output);
						notFound << "<p>Parsing webservice output mapping failed! " << outputXML.ErrorDesc() << " (" << outputXML.ErrorRow() << "," << outputXML.ErrorCol() << ")" << " Mapping might be incomplete!" << "</p>";
						notFound.End();
					}
					writer << "Output Mapping: " << output.str();
				}

				// we've generated our own html-table with input/output mapping. So avoid default table.
				useDefaultFieldMappingTable = false;
			}
			break;
		case SFT_ATRIUM_ORCHESTRATOR:
			{
				// TODO: implement Atrium Orchestrator actions correctly
				strmServer << arIn.LinkToServerInfo(AR_CURRENT_SERVER_TAG, rootLevel);
				schemaNameActionIsReadingFrom = sfh.GetSchemaName();
				strmSchemaDisplay << sfh.GetSchemaName();

				useDefaultFieldMappingTable = false;
			}
			break;
		}
	}

	if (useDefaultFieldMappingTable)
	{
		GenerateDefaultMappingTable(writer, strmSchemaDisplay, strmServer, strmQual);
	}

	return writer;
}

void CDocActionSetFieldsHelper::GenerateDefaultMappingTable(ostream &writer, stringstream &strmSchemaDisplay, stringstream &strmServer, stringstream &strmQual)
{
	string tmpDisplayName = strmSchemaDisplay.str();
	if(tmpDisplayName.size()==0)
		tmpDisplayName = schemaNameActionIsReadingFrom;

	if (this->showServerNameInOutput)
		writer << "Server: " << strmServer.str() << "<br/>" << endl;

	if (this->showFormNameInOutput)
		writer << "From: " << arIn.LinkToSchema(tmpDisplayName, rootLevel) << "<br/>" << endl;

	//Qualification
	writer << strmQual.str() << endl;

	// set field mapping
	writer << "Field Mapping:";
	if (setFieldsStruct.fieldList.fieldAssignList[0].fieldId == AR_LIKE_ID)
	{
		writer << " All Matching Ids<br/>";
		CDocAllMatchingIdsTable allMatchingFieldsTable(attachedSchemaName, schemaNameActionIsReadingFrom, obj, CDocAllMatchingIdsTable::AMM_SETFIELDS, nAction, ifElse, rootLevel);
		allMatchingFieldsTable.ToStream(writer);
	}
	else
	{
		writer << "<br/>" << endl;
		CARAssignHelper assignHelper(arIn, rootLevel, obj, attachedSchemaName, schemaNameActionIsReadingFrom);
		writer << assignHelper.SetFieldsAssignment(setFieldsStruct, nAction, ifElse);
	}
}

string CDocActionSetFieldsHelper::processMappingXML( TiXmlNode* pParent, string sParent, CTable &tblFieldList, string form, WebserviceMappingMode type)
{
	if ( !pParent )
		return "";

	stringstream strm;

	TiXmlNode* pChild;
	int t = pParent->Type();

	switch ( t )
	{
	case TiXmlNode::ELEMENT:
#ifdef _DEBUG
		{
			const TiXmlElement *pEl = pParent->ToElement();
			cout << "<" << pEl->Value() << endl;
			const TiXmlAttribute *pAttr = pEl->FirstAttribute();
			for (; pAttr != NULL; pAttr = pAttr->Next())
			{
				cout << "  Name: " << pAttr->Name() << " -- Value: " << pAttr->Value() << endl;
			}
			cout << ">" << endl;
		}
#endif
		if (strcmp("element",pParent->Value()) == 0)
		{
			const char* name = pParent->ToElement()->Attribute("name");
			if (name)
				sParent = name;
			else
				sParent.clear();
		}
		else if (strcmp("formMapping",pParent->Value()) == 0)
		{
			const char* formName = pParent->FirstChild("form")->ToElement()->Attribute("formName");
			if (formName)
				form = formName;
			else
				form.clear();
		}
		else if (strcmp("fieldMapping",pParent->Value()) == 0)
		{
			const char* arFieldId = pParent->ToElement()->Attribute("arFieldId");
			int fieldID = 0;
			if (arFieldId)
				fieldID = atoi(arFieldId);

			CTableRow row("cssStdRow");
			row.AddCell(CTableCell(sParent));
			row.AddCell(CTableCell(arIn.LinkToField(form, fieldID, rootLevel)));
			//row.AddCell(CTableCell(form + " - "+arIn->LinkToField(form, fieldID, rootLevel)));
			tblFieldList.AddRow(row);	

			int msgId = 0;
			switch (type)
			{
			case WMM_INPUT: msgId = REFM_SETFIELDS_WS_INPUT; break;
			case WMM_OUTPUT: msgId = REFM_SETFIELDS_WS_OUTPUT; break;
			}
			CRefItem refItem(this->obj, ifElse, 0, msgId);
			arIn.AddFieldReference(arIn.SchemaGetInsideId(form), fieldID, refItem);
		}
		break;
	}
	for ( pChild = pParent->FirstChild(); pChild != 0; pChild = pChild->NextSibling()) 
	{
		strm << processMappingXML( pChild, sParent, tblFieldList, form, type);
	}

	return strm.str();
}

const char* CDocActionSetFieldsHelper::GetSetFieldsTypeName(SetFieldType type)
{
	switch (type)
	{
	case SFT_CURRENT: return "CURRENT SCREEN";
	case SFT_SERVER: return "SERVER";
	case SFT_SAMPLEDATA: return "SAMPLE DATA";
	case SFT_SQL: return "SQL";
	case SFT_FILTERAPI: return "FILTER API";
	case SFT_WEBSERVICE: return "WEBSERVICE";
	case SFT_ATRIUM_ORCHESTRATOR: return "BMC ATRIUM ORCHESTRATOR";
	default: return EmptyValue;
	}
}
