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
#include "DocAlActionStruct.h"
#include "DocAllMatchingIdsTable.h"
#include "../core/OpenWindowReportData.h"
#include "actions/DocOpenWindowAction.h"
#include "actions/DocAlMessageAction.h"
#include "../output/ImageTag.h"
#include "../output/ObjNotFound.h"
#include "../output/URLLink.h"
#include "../util/Context.h"

CDocAlActionStruct::CDocAlActionStruct(CARInside &arIn, CARActiveLink &obj, string schemaName, int rootLevel)
{
	this->arIn = &arIn;
	this->obj = &obj;	
	this->rootLevel = rootLevel;
	this->schemaName = schemaName;
	this->schemaInsideId = this->arIn->SchemaGetInsideId(this->schemaName);
	this->structItemType = AR_STRUCT_ITEM_XML_ACTIVE_LINK;
}

CDocAlActionStruct::~CDocAlActionStruct(void)
{
}


string CDocAlActionStruct::Get(IfElseState ifElse, const ARActiveLinkActionList &actList)
{
	stringstream strm;
	strm.str("");

	try
	{
		this->ifElse = ifElse;

		CTable tblListAction("tblListAlAction", "TblObjectList");
		tblListAction.AddColumn(5, "Position");	
		tblListAction.AddColumn(15, "Action Type");
		tblListAction.AddColumn(80, "Description");

		for(unsigned int nAction = 0; nAction < actList.numItems; nAction++)
		{
			ARActiveLinkActionStruct action = actList.actionList[nAction];

			CTableRow row("cssStdRow");		
			row.AddCell(CTableCell(nAction));				

			CPageParams file(PAGE_ACTION_OBJLIST, AR_STRUCT_ITEM_XML_ACTIVE_LINK, action.action);
			row.AddCell(CTableCell(URLLink(CAREnum::ActiveLinkAction(action.action), file, rootLevel)));			

			stringstream actionDesc;
			actionDesc.str("");

			switch(action.action)
			{
			case AR_ACTIVE_LINK_ACTION_NONE:
				{
					actionDesc << ActionNone(nAction);
				}
				break;
			case AR_ACTIVE_LINK_ACTION_MACRO:
				{
					ActionMacro(actionDesc, action.u.macro, nAction);					
				}
				break;
			case AR_ACTIVE_LINK_ACTION_FIELDP:
				{					
					ActionPushFields(actionDesc, action.u.pushFields, nAction);					
				}
				break;
			case AR_ACTIVE_LINK_ACTION_FIELDS:
				{
					ActionSetFields(actionDesc, action.u.setFields, nAction);	
				}
				break;
			case AR_ACTIVE_LINK_ACTION_PROCESS:
				{
					ActionProcess(actionDesc, action.u.process, nAction);	
				}
				break;
			case AR_ACTIVE_LINK_ACTION_MESSAGE:
				{
					ActionMessage(actionDesc, action.u.message, nAction);					
				}
				break;
			case AR_ACTIVE_LINK_ACTION_SET_CHAR:
				{
					ActionSetChar(actionDesc, action.u.characteristics, nAction);
				}
				break;
			case AR_ACTIVE_LINK_ACTION_DDE:
				{
					ActionDde(actionDesc, action.u.dde, nAction);
				}
				break;				
			case AR_ACTIVE_LINK_ACTION_SQL:
				{
					ActionSql(actionDesc, action.u.sqlCommand, nAction);
				}
				break;
			case AR_ACTIVE_LINK_ACTION_AUTO:
				{
					ActionAutomation(actionDesc, action.u.automation, nAction);
				}
				break;
			case AR_ACTIVE_LINK_ACTION_OPENDLG:
				{
					ActionOpenDlg(actionDesc, action.u.openDlg, nAction);
				}
				break;
			case AR_ACTIVE_LINK_ACTION_COMMITC:
				{
					ActionCommitChanges(actionDesc, action.u.commitChanges, nAction);
				}
				break;
			case AR_ACTIVE_LINK_ACTION_CLOSEWND:
				{
					ActionCloseWindow(actionDesc, action.u.closeWnd, nAction);		
				}
				break;
			case AR_ACTIVE_LINK_ACTION_CALLGUIDE:
				{
					ActionCallGuide(actionDesc, action.u.callGuide, nAction);
				}
				break;
			case AR_ACTIVE_LINK_ACTION_EXITGUIDE:
				{
					ActionExitGuide(actionDesc, action.u.exitGuide, nAction);
				}
				break;
			case AR_ACTIVE_LINK_ACTION_GOTOGUIDELABEL:
				{
					ActionGotoGuideLabel(actionDesc, action.u.gotoGuide, nAction);
				}
				break;
			case AR_ACTIVE_LINK_ACTION_WAIT:
				{
					ActionWait(actionDesc, action.u.waitAction, nAction);
				}
				break;
			case AR_ACTIVE_LINK_ACTION_GOTOACTION:
				{					
					ActionGotoAction(actionDesc, action.u.gotoAction, nAction);				
				}
				break;
#if AR_CURRENT_API_VERSION > 12 // Version 7.1 and higher
			case AR_ACTIVE_LINK_ACTION_SERVICE:
				{
					ActionService(actionDesc, action.u.service, nAction);
				}
				break;
#endif
			default:
				{
					actionDesc.str("");				
				}
				break;
			}

			row.AddCell(CTableCell(actionDesc.str()));
			tblListAction.AddRow(row);	
		}

		stringstream tblDesc;
		tblDesc.str("");
		tblDesc << ImageTag(ImageTag::Document, rootLevel) << IfElse(ifElse) << "-Actions";
		tblListAction.description = tblDesc.str();

		strm << tblListAction;
	}
	catch(exception& e)
	{
		cout << "EXCEPTION in CDocAlActionStruct of '" << this->obj->GetName() << "': " << e.what() << endl;
	}

	return strm.str();
}

// AR_ACTIVE_LINK_ACTION_NONE
string CDocAlActionStruct::ActionNone(int nAction)
{
	return "None";
}

// AR_ACTIVE_LINK_ACTION_MACRO
void CDocAlActionStruct::ActionMacro(std::ostream& strm, const ARActiveLinkMacroStruct &action, int nAction)
{
	try
	{
		if(action.macroName != NULL)
		{
			if(action.macroName != NULL)
			{
				strm << "Macro Name: " << action.macroName << "<br/>" << endl;
			}
			else
			{
				strm << "Macro Name: <Unknown><br/>" << endl;
			}
		}

		if(action.macroParms.parms != NULL)
		{
			CTable tblMacro("tblMacroParameter", "TblObjectList");
			tblMacro.AddColumn(50, "Parameter Name");	
			tblMacro.AddColumn(50, "Value");

			for(unsigned int nCnt = 0; nCnt < action.macroParms.numItems; nCnt++)
			{
				if(action.macroParms.parms[nCnt].name != NULL
					&& action.macroParms.parms[nCnt].value != NULL)
				{
					const char* pName = action.macroParms.parms[nCnt].name;
					const char* pValue = action.macroParms.parms[nCnt].value;

					// create reference item description
					CRefItem refItemTmp(*this->obj, ifElse, nAction, REFM_MACRO);

					// find field references
					string parameterValue = arIn->TextFindFields(pValue, "$", schemaInsideId, rootLevel, true, &refItemTmp);

					// add the al action row
					CTableRow mRow("cssStdRow");		
					mRow.AddCell(CTableCell(pName));
					mRow.AddCell(CTableCell(parameterValue));
					tblMacro.AddRow(mRow);	
				}
			}
			strm << tblMacro;
			strm << "<br/>Macro Text: <br/>" << action.macroText << endl;
		}
	}
	catch(exception& e)
	{
		cout << "EXCEPTION in AlActionMacro of '" << this->obj->GetName() << "': " << e.what() << endl;
	}
}

// AR_ACTIVE_LINK_ACTION_FIELDS
void CDocAlActionStruct::ActionSetFields(std::ostream& strm, const ARSetFieldsActionStruct &action, int nAction)
{
	try
	{
		CDocActionSetFieldsHelper setFieldHelper(*arIn, *obj, schemaName, action, structItemType, ifElse, nAction, rootLevel);
		setFieldHelper.ShowActionWithServerName(true);
		setFieldHelper.ToStream(strm);
	}
	catch(exception& e)
	{
		cout << "EXCEPTION in AlActionSetFields of '" << this->obj->GetName() << "': " << e.what() << endl;
	}
}

// AR_ACTIVE_LINK_ACTION_PROCESS
void CDocAlActionStruct::ActionProcess(std::ostream& strm, const char *action, int nAction)
{
	try
	{
		if(action != NULL)
		{
			CRefItem refItemTmp(*this->obj, ifElse, nAction, REFM_RUN_PROCESS);
			strm << arIn->TextFindFields(action, "$", schemaInsideId, rootLevel, true, &refItemTmp) << endl;
		}
		else
		{
			strm << "No Run Process command specified." << endl;
		}
	}
	catch(exception& e)
	{
		cout << "EXCEPTION in AlActionProcess of '" << this->obj->GetName() << "': " << e.what() << endl;
	}
}

// AR_ACTIVE_LINK_ACTION_MESSAGE
void CDocAlActionStruct::ActionMessage(std::ostream& strm, const ARMessageStruct &action, int nAction)
{
	Context context(*this->obj, ifElse, nAction, schemaInsideId, rootLevel);
	DocAlMessageAction alMessageAction(context, action);
	alMessageAction.ToStream(strm);
}

// AR_ACTIVE_LINK_ACTION_SET_CHAR
void CDocAlActionStruct::ActionSetChar(std::ostream& strm, const ARFieldCharacteristics &action, int nAction)
{
	try
	{
		//FieldName
		strm << "Field ";
		if (action.option == AR_FIELD_CHAR_OPTION_REFERENCE)
		{
			strm << "(Use Value Of): $" << arIn->LinkToField(schemaInsideId, action.fieldId, rootLevel) << "$<br/>" << endl;
		}
		else
		{
			strm << "Name: " << arIn->LinkToField(schemaInsideId, action.fieldId, rootLevel) << "<br/>" << endl;
		}

		//Access Option
		strm << "Field Access: " << CAREnum::SetCharFieldAccess(action.accessOption) << "<br/>" << endl;					


		//Font
		bool fontPropFound = false;
		for(unsigned int i=0; i< action.props.numItems; i++)
		{	
			if(action.props.props[i].prop == AR_DPROP_LABEL_FONT_STYLE && action.props.props[i].value.dataType == AR_DATA_TYPE_CHAR)
			{
				strm << "Field Font: " << action.props.props[i].value.u.charVal << "<br/>" << endl;
				fontPropFound = true;
				break;
			}
		}
		if (!fontPropFound)
			strm << "Field Font: Unchanged<br/>" << endl;


		//Visibility
		bool visibilityPropFound = false;
		for(unsigned int i=0; i< action.props.numItems; i++)
		{	
			if(action.props.props[i].prop == AR_DPROP_VISIBLE && 
				action.props.props[i].value.dataType == AR_DATA_TYPE_ENUM || action.props.props[i].value.dataType == AR_DATA_TYPE_INTEGER)
			{
				strm << "Visibility: " << CAREnum::SetCharFieldVisibility(action.props.props[i].value.u.intVal) << "<br/>" << endl;
				visibilityPropFound = true;
				break;
			}
		}
		if(!visibilityPropFound)
			strm << "Visibility: Unchanged<br/>" << endl;



		//CharMenu
		if(action.charMenu != NULL)
		{
			if(strcmp(action.charMenu, "") != 0)
			{
				strm << "Menu: " << CWebUtil::LinkToMenu(action.charMenu, rootLevel) << "<br/>" << endl;
			}
		}

		//Set focus to field
		if(action.focus == AR_FOCUS_SET_TO_FIELD)
		{
			strm << "<input type=\"checkbox\" name=\"fieldSetFocus\" value=\"fieldSetFocus\" checked>Set Focus to Field" << "<br/>" << endl;
		}	


		for(unsigned int i=0; i< action.props.numItems; i++)
		{	
			switch(action.props.props[i].prop)
			{
			case AR_DPROP_LABEL_COLOR_TEXT:
				{
					bool colorUnknown = true;
					char color[7];
					size_t colorStrLen = 0;

					if (action.props.props[i].value.dataType == AR_DATA_TYPE_CHAR)
					{
						colorStrLen = strlen(action.props.props[i].value.u.charVal);
					}

					if (action.props.props[i].value.dataType == AR_DATA_TYPE_CHAR && strncmp(action.props.props[i].value.u.charVal,"0x",2) == 0 && colorStrLen == 8)
					{
						color[0] = action.props.props[i].value.u.charVal[6];
						color[1] = action.props.props[i].value.u.charVal[7];
						color[2] = action.props.props[i].value.u.charVal[4];
						color[3] = action.props.props[i].value.u.charVal[5];
						color[4] = action.props.props[i].value.u.charVal[2];
						color[5] = action.props.props[i].value.u.charVal[3];
						color[6] = 0;
						colorUnknown = false;
					}

					strm << "Label Color: ";

					if(colorStrLen > 0)
					{
						if (colorUnknown)
						{
							strm << CARValue::ValueToString(action.props.props[i].value);
						}
						else
						{
							strm << "<span style='background-color:#" << color << "; width:16px; height:16px;'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>";
						}
					}
					else
						strm << "Default";

					strm << "<br/>" << endl;
				}
				break;
			case AR_DPROP_REFRESH:
				{
					strm << "<input type=\"checkbox\" name=\"refTableFieldInAl\" value=\"refrTblField\" checked>Refresh Table Field" << endl;
				}
				break;
			case AR_DPROP_LABEL:
				{	
					string value = CARValue::ValueToString(action.props.props[i].value);
					if(!value.empty())
					{
						CRefItem refItemTmp(*this->obj, ifElse, nAction, REFM_CHANGEFIELD_LABEL);
						strm << "Field Label: " << arIn->TextFindFields(value, "$", schemaInsideId, rootLevel, true, &refItemTmp)  << "<br/>" << endl;					
					}
				}
				break;

			}
		}
	}
	catch(exception& e)
	{
		cout << "EXCEPTION in AlActionSetChar of '" << this->obj->GetName() << "': " << e.what() << endl;
	}
}

// AR_ACTIVE_LINK_ACTION_DDE
void CDocAlActionStruct::ActionDde(std::ostream& strm, const ARDDEStruct &action, int nAction)
{
	try
	{
		strm << "Action: " << CAREnum::DDEAction(action.action) << "<br/>" << endl;					

		if(action.serviceName != NULL)
			strm << "Service Name: " << action.serviceName << "<br/>" << endl;

		if(action.topic != NULL)
			strm << "Topic: " << action.topic << "<br/>" << endl;

		if(action.item != NULL)
			strm << "Item: " << action.item << "<br/>" << endl;

		if(action.pathToProgram != NULL)
			strm << "Path: " << action.pathToProgram << "<br/>" << endl;

		if(action.command != NULL)
			strm << "Command: " << action.command << "<br/>" << endl;
	}
	catch(exception& e)
	{
		cout << "EXCEPTION in AlActionDde of '" << this->obj->GetName() << "': " << e.what() << endl;
	}
}

// AR_ACTIVE_LINK_ACTION_FIELDP
void CDocAlActionStruct::ActionPushFields(std::ostream& strm, const ARPushFieldsActionStruct &action, int nAction)
{
	try
	{
		string pushServer;
		string pushSchema;

		// target server **************************************
		strm << "Server Name: ";
		if (action.pushFieldsList.pushFieldsList[0].field.server[0] == '$' && action.sampleServer[0] != 0)
		{
			int fieldId = atoi(&action.pushFieldsList.pushFieldsList[0].field.server[1]);

			pushServer = action.sampleServer;
			strm << "$" << (fieldId < 0 ? CAREnum::Keyword(abs(fieldId)) : arIn->LinkToField(schemaInsideId, fieldId, rootLevel)) << "$ (Sample Server: " << arIn->LinkToServerInfo(action.sampleServer, rootLevel) << ")";

			// create field reference
			CRefItem refItem(*this->obj, ifElse, nAction, REFM_PUSHFIELD_SERVER);
			arIn->AddFieldReference(schemaInsideId, fieldId, refItem);
		}
		else
		{
			pushServer = action.pushFieldsList.pushFieldsList[0].field.server;
			strm << arIn->LinkToServerInfo(pushServer, rootLevel);
		}
		strm << "<br/>" << endl;

		// target form ******************************************
		strm << "Push Value To: ";		
		if (action.pushFieldsList.pushFieldsList[0].field.schema[0] == '$' && action.sampleSchema[0] != 0)
		{
			int fieldId = atoi(&action.pushFieldsList.pushFieldsList[0].field.schema[1]);

			if (action.sampleSchema[0] == '@' && action.sampleSchema[1] == 0)
			{
				pushSchema = schemaName;
			}
			else
			{
				pushSchema = action.sampleSchema;
			}
			strm << "$" << (fieldId < 0 ? CAREnum::Keyword(abs(fieldId)) : arIn->LinkToField(schemaInsideId, fieldId, rootLevel)) << "$ (Sample Schema: " << arIn->LinkToSchema(pushSchema, rootLevel) << ")";

			// create field reference
			CRefItem refItem(*this->obj, ifElse, nAction, REFM_PUSHFIELD_FORM);
			arIn->AddFieldReference(schemaInsideId, fieldId, refItem);

			if (fieldId == - AR_KEYWORD_SCHEMA)	pushSchema = schemaName;
		}
		else
		{
			pushSchema = action.pushFieldsList.pushFieldsList[0].field.schema;
			strm << arIn->LinkToSchema(pushSchema, rootLevel);
		}
		strm << "<br/>" << endl;

		// create schema reference
		if (!arIn->appConfig.bOverlaySupport || IsVisibleObject(*obj))
		{
			CARSchema targetSchema(pushSchema);
			if (targetSchema.Exists())
			{
				CRefItem refItem(*this->obj, ifElse, nAction, REFM_PUSHFIELD_TARGET);
				if (!targetSchema.ReferenceExists(refItem))
					targetSchema.AddReference(refItem);
			}
		}

		// push field if **************************************
		strm << "<br/>Push Field If<br/>" << endl;

		int pFormId = this->arIn->SchemaGetInsideId(schemaName);
		int sFormId = this->arIn->SchemaGetInsideId(pushSchema);

		stringstream strmTmpQual;
		CRefItem refItem(*this->obj, ifElse, nAction, REFM_PUSHFIELD_IF);
		CARQualification arQual(*arIn, refItem, pFormId, sFormId, rootLevel);

		arQual.CheckQuery(&action.pushFieldsList.pushFieldsList[0].field.qualifier, strmTmpQual);

		if(strmTmpQual.str().length() > 0)
		{
			strm << strmTmpQual.str() << "<br/><br/>" << endl;
		}
		else
		{
			strm << EmptyValue << "<br/><br/>" << endl;
		}

		strm << "If No Requests Match: " << CAREnum::NoMatchRequest(action.pushFieldsList.pushFieldsList[0].field.noMatchOption) << "<br/>" << endl;
		strm << "If Multiple Requests Match: " << CAREnum::MultiMatchRequest(action.pushFieldsList.pushFieldsList[0].field.multiMatchOption) << "<br/><br/>" << endl;

		// push field mapping *********************************
		strm << "Field Mapping:";
		if(action.pushFieldsList.pushFieldsList[0].field.u.fieldId == AR_LIKE_ID)
		{
			strm << " All Matching Ids<br/>";
			CDocAllMatchingIdsTable allMatchingFieldsTbl(pushSchema, schemaName, *obj, CDocAllMatchingIdsTable::AMM_PUSHFIELDS, nAction, ifElse, rootLevel);
			allMatchingFieldsTbl.ToStream(strm);
		}
		else
		{
			strm << "<br/>" << endl;
			CARAssignHelper assignHelper(*arIn, rootLevel, *obj, schemaName, pushSchema);
			strm << assignHelper.PushFieldsAssignment(action, nAction, ifElse);
		}
	}
	catch(exception& e)
	{
		cout << "EXCEPTION in AlActionPushFields of '" << this->obj->GetName() << "': " << e.what() << endl;
	}
}

// AR_ACTIVE_LINK_ACTION_SQL
void CDocAlActionStruct::ActionSql(std::ostream& strm, const ARSQLStruct &action, int nAction)
{
	try
	{		
		if(action.server != NULL)
			strm << "Server: " << arIn->LinkToServerInfo(action.server, rootLevel) << "<br/>" << endl;

		if(action.command != NULL)
		{			
			CRefItem refItemTmp(*this->obj, ifElse, nAction, REFM_DIRECTSQL);
			strm << "SQL command: <br/>" << arIn->TextFindFields(action.command, "$", schemaInsideId, rootLevel, true, &refItemTmp) << endl;
		}
	}
	catch(exception& e)
	{
		cout << "EXCEPTION in AlActionSql of '" << this->obj->GetName() << "': " << e.what() << endl;
	}
}

// AR_ACTIVE_LINK_ACTION_AUTO
void CDocAlActionStruct::ActionAutomation(std::ostream& strm, const ARAutomationStruct &action, int nAction)
{
	try
	{
		if(action.action != NULL)
			strm << "Action: " << action.action << "<br/>" << endl;

		if(action.autoServerName != NULL)
			strm << "Server Name: " << action.autoServerName << "<br/>" << endl;

		if(action.clsId != NULL)
			strm << "CLS Id: " << action.clsId << "<br/>" << endl;

		if(action.methodList.methodList != NULL)
		{
			CTable tblOleMethods("tblOleMethods", "TblObjectList");
			tblOleMethods.AddColumn(30, "Id");	
			tblOleMethods.AddColumn(30, "Name");

			for(unsigned int nCnt = 0; nCnt < action.methodList.numItems; nCnt++)
			{
				string mId, mName;

				if(action.methodList.methodList[nCnt].methodIId != NULL)
					mId = action.methodList.methodList[nCnt].methodIId;

				if(action.methodList.methodList[nCnt].methodName != NULL)
					mName = action.methodList.methodList[nCnt].methodName;

				CTableRow mRow("cssStdRow");
				mRow.AddCell( CTableCell(mId) );
				mRow.AddCell( CTableCell(mName) );
				tblOleMethods.AddRow(mRow);	
			}	
			strm << tblOleMethods;
		}
	}
	catch(exception& e)
	{
		cout << "EXCEPTION in AlActionAutomation of '" << this->obj->GetName() << "': " << e.what() << endl;
	}
}

// AR_ACTIVE_LINK_ACTION_OPENDLG
void CDocAlActionStruct::ActionOpenDlg(std::ostream& strm, const AROpenDlgStruct &action, int nAction)
{
	Context context(*this->obj, ifElse, nAction, schemaInsideId, rootLevel);
	DocOpenWindowAction docOpenWindow(context, action);
	docOpenWindow.ToStream(strm);
}

// AR_ACTIVE_LINK_ACTION_COMMITC
void CDocAlActionStruct::ActionCommitChanges(std::ostream& strm, const ARCommitChangesStruct &action, int nAction)
{
	try
	{
		strm << "Schema: " << arIn->LinkToSchema(action.schemaName, rootLevel) << "<br/>" << endl;
		strm << "The Commit Changes action is applicable to regular form, join form or dialog box. ";
		strm << "When the Open Window active link action is set to Dialog Window Type Commit Changes pushes predetermined values to fields in the parent form. ";
		strm << "The values for these fields are specified in the Open Window active link action when the Field Mapping Mode is set to On Close. ";
		strm << "When called within a regular form or join form, this action applies the changes." << endl;		
	}
	catch(exception& e)
	{
		cout << "EXCEPTION in AlActionCommitChanges of '" << this->obj->GetName() << "': " << e.what() << endl;
	}
}

// AR_ACTIVE_LINK_ACTION_CLOSEWND
void CDocAlActionStruct::ActionCloseWindow(std::ostream& strm, const ARCloseWndStruct &action, int nAction)
{
	try
	{		
		if(action.closeAll == TRUE)
			strm << "<input type=\"checkbox\" name=\"closeWnd\" value=\"closeWndAll\" checked>Close All Windows" << endl;
		else
			strm << "<input type=\"checkbox\" name=\"closeWnd\" value=\"closeWndAll\">Close All Windows" << endl;
	}
	catch(exception& e)
	{
		cout << "EXCEPTION in AlActionCloseWindow of '" << this->obj->GetName() << "': " << e.what() << endl;
	}
}

// AR_ACTIVE_LINK_ACTION_CALLGUIDE
void CDocAlActionStruct::ActionCallGuide(std::ostream& strm, const ARCallGuideStruct &action, int nAction)
{
	try
	{
		strm << "<p>";
		if (action.serverName[0] == '$' && action.serverName[1] != 0)
		{
			int fieldId = atoi(&action.serverName[1]);
			strm << "Server: " << "$" << (fieldId < 0 ? CAREnum::Keyword(abs(fieldId)) : arIn->LinkToField(this->schemaName, fieldId, rootLevel)) << "$<br/>" << endl;

			CRefItem refItem(*this->obj, ifElse, nAction, REFM_CALLCUIDE_SERVER);
			arIn->AddFieldReference(schemaInsideId, fieldId, refItem);
		}
		else
		{
			strm << "Server : " << arIn->LinkToServerInfo(action.serverName, rootLevel) << "<br/>" << endl;
		}

		if (action.guideName[0] == '$' && action.guideName[1] != 0)
		{
			int fieldId = atoi(&action.guideName[1]);
			strm << "Guide: $" << (fieldId < 0 ? CAREnum::Keyword(abs(fieldId)) : arIn->LinkToField(this->schemaName, fieldId, rootLevel)) << "$<br/>" << endl;

			CRefItem refItem(*this->obj, ifElse, nAction, REFM_CALLGUIDE_NAME);
			arIn->AddFieldReference(schemaInsideId, fieldId, refItem);
		}
		else
		{
			strm << "Guide: " << arIn->LinkToContainer(action.guideName, rootLevel) << "<br/>" << endl;
		}
		strm << "</p>";

		if(action.guideTableId > 0)
		{
			strm << "<p class='last'>" << "Table Loop: " << CAREnum::CallGuideMode(action.guideMode) << "<br/>" << endl;
			strm << "Table Field: " <<  arIn->LinkToField(schemaName, action.guideTableId, rootLevel);
			CRefItem refItem(*this->obj, ifElse, nAction, REFM_CALLGUIDE_TABLELOOP);
			arIn->AddFieldReference(schemaInsideId, action.guideTableId, refItem);
			strm << "</p>";
		}
	}
	catch(exception& e)
	{
		cout << "EXCEPTION in AlActionCallGuide of '" << this->obj->GetName() << "': " << e.what() << endl;
	}
}

// AR_ACTIVE_LINK_ACTION_EXITGUIDE
void CDocAlActionStruct::ActionExitGuide(std::ostream& strm, const ARExitGuideStruct &action, int nAction)
{
	try
	{
		strm << "<input type=\"checkbox\" name=\"exitGuide\" value=\"exitGuideCloseAll\"";
		if(action.closeAll == TRUE)
		{
			strm << " checked";
		}
		strm << ">Close all guides on exit" << endl;
	}
	catch(exception& e)
	{
		cout << "EXCEPTION in AlActionExitGuide of '" << this->obj->GetName() << "': " << e.what() << endl;
	}
}

// AR_ACTIVE_LINK_ACTION_GOTOGUIDELABEL
void CDocAlActionStruct::ActionGotoGuideLabel(std::ostream& strm, const ARGotoGuideLabelStruct &action, int nAction)
{
	try
	{
		strm << "Guide Label: " << (action.label != NULL ? action.label : EmptyValue) << endl;	
	}
	catch(exception& e)
	{
		cout << "EXCEPTION in AlActionGuideLabel of '" << this->obj->GetName() << "': " << e.what() << endl;
	}
}

// AR_ACTIVE_LINK_ACTION_WAIT
void CDocAlActionStruct::ActionWait(std::ostream& strm, const ARWaitStruct &action, int nAction)
{
	try
	{
		strm << "Label for Continue Button: " << (action.continueButtonTitle != NULL ? action.continueButtonTitle : EmptyValue) << endl;
	}
	catch(exception& e)
	{
		cout << "EXCEPTION in AlActionWait of '" << this->obj->GetName() << "': " << e.what() << endl;
	}
}

// AR_ACTIVE_LINK_ACTION_GOTOACTION
void CDocAlActionStruct::ActionGotoAction(std::ostream& strm, const ARGotoActionStruct &action, int nAction)
{
	try
	{
		strm << "FieldId or Value: ";
		switch (action.tag)
		{
		case AR_GOTO_FIELD_XREF:
			{
			// add new reference item to the field
			CRefItem refItem(*this->obj, ifElse, nAction, REFM_GOTO);
			arIn->AddFieldReference(schemaInsideId, action.fieldIdOrValue, refItem);

			// link to field in current page
			strm << arIn->LinkToField(schemaName, action.fieldIdOrValue, rootLevel) << endl;
			break;
			}
		case AR_GOTO_ABSOLUTE_ORDER:
			strm << action.fieldIdOrValue;
			break;
		case AR_GOTO_OFFSET_FORWARD:
			strm << "+" << action.fieldIdOrValue;
			break;
		case AR_GOTO_OFFSET_BACKWARD:
			strm << "-" << action.fieldIdOrValue;
			break;
		}
	}
	catch(exception& e)
	{
		cout << "EXCEPTION in AlActionGotoAction of '" << this->obj->GetName() << "': " << e.what() << endl;
	}
}

#if AR_CURRENT_API_VERSION >= AR_API_VERSION_710
// AR_ACTIVE_LINK_ACTION_SERVICE
void CDocAlActionStruct::ActionService(std::ostream& strm, const ARActiveLinkSvcActionStruct &action, int nAction)
{
	string serviceServer;
	string serviceSchema;

	try
	{
		strm << "<p>";
		// check for sample data for the server part
		if (action.serverName[0] == '$' && action.sampleServer[0] != 0)
		{
			int fieldId = atoi(&action.serverName[1]);
			serviceServer = action.sampleServer;			
			strm << "Server Name: " << "$" << (fieldId < 0 ? CAREnum::Keyword(abs(fieldId)) : arIn->LinkToField(this->schemaName, fieldId, rootLevel)) << "$ (Sample Server: " << arIn->LinkToServerInfo(action.sampleServer, rootLevel) << ")<br/>" << endl;

			CRefItem refItem(*this->obj, ifElse, nAction, REFM_SERVICE_SERVER);
			arIn->AddFieldReference(schemaInsideId, fieldId, refItem);
		}
		else
		{
			serviceServer = action.serverName;
			strm << "Server Name: " << arIn->LinkToServerInfo(action.serverName, rootLevel) << "<br/>" << endl;
		}

		if (action.serviceSchema[0] == '$' && action.sampleSchema[0] != 0)
		{
			int fieldId = atoi(&action.serviceSchema[1]);

			if (action.sampleSchema[0] == '@' && action.sampleSchema[1] == 0)
			{
				serviceSchema = schemaName;
			}
			else
			{
				serviceSchema = action.sampleSchema;
			}

			strm << "Service Form: " << "$" << (fieldId < 0 ? CAREnum::Keyword(abs(fieldId)) : arIn->LinkToField(this->schemaName, fieldId, rootLevel)) << "$ (Sample Form: " << arIn->LinkToSchema(serviceSchema, rootLevel) << ")<br/>" << endl;

			CRefItem refItem(*this->obj, ifElse, nAction, REFM_SERVICE_FORM);
			arIn->AddFieldReference(schemaInsideId, fieldId, refItem);

			if (fieldId == (-AR_KEYWORD_SCHEMA)) serviceSchema = schemaName;
		}
		else
		{
			serviceSchema = action.serviceSchema;
			strm << "Service Form: " << arIn->LinkToSchema(action.serviceSchema, rootLevel) << "<br/>" << endl;
		}

		// create schema reference
		CARSchema schemaToCall(serviceSchema);
		if (schemaToCall.Exists() && (!arIn->appConfig.bOverlaySupport || IsVisibleObject(*obj)))
		{
			CRefItem refItem(*this->obj, ifElse, nAction, REFM_SERVICE_CALL);
			if (!schemaToCall.ReferenceExists(refItem))
				schemaToCall.AddReference(refItem);
		}

		strm << "Request Id: ";
		if (action.requestIdMap != 0)
		{
			strm << arIn->LinkToField(schemaName, action.requestIdMap, rootLevel);
			
			CRefItem refItem(*this->obj, ifElse, nAction, REFM_SERVICE_REQUESTID);
			arIn->AddFieldReference(schemaInsideId, action.requestIdMap, refItem);
		}
		strm << "</p>" << endl;

		// input mapping
		strm << "Input Mapping: "; if (action.inputFieldMapping.numItems == 0) strm << "None"; strm << "<br/>" << endl;
		if (action.inputFieldMapping.numItems > 0)
		{
			CARAssignHelper assignHelper(*arIn, rootLevel, *this->obj, serviceSchema, schemaName);
			strm << assignHelper.ServiceAssignment(action.inputFieldMapping, nAction, ifElse, SMM_INPUT);
		}

		// output mapping
		strm << "Output Mapping: "; if (action.outputFieldMapping.numItems == 0) strm << "None"; strm << "<br/>" << endl;
		if (action.outputFieldMapping.numItems > 0)
		{
			CARSchema currentSchema(schemaName);

			CARAssignHelper assignHelper(*arIn, rootLevel, *this->obj, currentSchema, schemaToCall);
			strm << assignHelper.ServiceAssignment(action.outputFieldMapping, nAction, ifElse, SMM_OUTPUT);
		}
	}
	catch (...)
	{
		cout << "EXCEPTION in AlActionService: " << this->obj->GetName() << endl;
	}
}
#endif
