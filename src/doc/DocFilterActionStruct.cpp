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
#include "DocFilterActionStruct.h"
#include "DocAllMatchingIdsTable.h"
#include "../output/ImageTag.h"
#include "../output/URLLink.h"

CDocFilterActionStruct::CDocFilterActionStruct(CARInside &arIn, CARServerObject &obj, string schemaName, int rootLevel, int structItemType)
{
	this->arIn = &arIn;
	this->obj = &obj;	
	this->rootLevel = rootLevel;
	this->schemaName = schemaName;
	this->schemaInsideId = this->arIn->SchemaGetInsideId(this->schemaName);
	this->structItemType = structItemType;
}

CDocFilterActionStruct::~CDocFilterActionStruct(void)
{
}


string CDocFilterActionStruct::Get(IfElseState ifElse, const ARFilterActionList &actList)
{
	stringstream strm;
	strm.str("");

	try
	{
		CTable tblListAction("tblListAlAction", "TblObjectList");
		tblListAction.AddColumn(5, "Position");	
		tblListAction.AddColumn(15, "Action Type");
		tblListAction.AddColumn(80, "Description");
		this->ifElse = ifElse;

		for(unsigned int nAction = 0; nAction < actList.numItems; nAction++)
		{
			ARFilterActionStruct action = actList.actionList[nAction];

			CTableRow row("cssStdRow");		
			CTableCell cellPosition(nAction, "");				

			string tmpActionType = CAREnum::FilterAction(action.action);
			if(this->structItemType == AR_STRUCT_ITEM_XML_FILTER)
			{
				CPageParams file(PAGE_ACTION_OBJLIST, AR_STRUCT_ITEM_XML_FILTER, action.action);
				tmpActionType = URLLink(CAREnum::FilterAction(action.action), file, rootLevel);
			}
			CTableCell cellActionType(tmpActionType.c_str(), "");			

			stringstream actionDesc;
			actionDesc.str("");

			switch(action.action)
			{
			case AR_FILTER_ACTION_NONE:
				{					
					actionDesc << FilterActionNone(nAction);
				}
				break;
			case AR_FILTER_ACTION_NOTIFY:
				{
					actionDesc << FilterActionNotify(action.u.notify, nAction);
				}
				break;
			case AR_FILTER_ACTION_MESSAGE:
				{
					actionDesc << FilterActionMessage(action.u.message, nAction);
				}
				break;
			case AR_FILTER_ACTION_LOG:
				{
					actionDesc << FilterActionLog(action.u.logFile, nAction);					
				}
				break;
			case AR_FILTER_ACTION_FIELDS:
				{
					actionDesc << FilterActionSetFields(action.u.setFields, nAction);	
				}
				break;
			case AR_FILTER_ACTION_PROCESS:
				{
					actionDesc << FilterActionProcess(action.u.process, nAction);
				}
				break;
			case AR_FILTER_ACTION_FIELDP:
				{
					actionDesc << FilterActionPushFields(action.u.pushFields, nAction);
				}
				break;
			case AR_FILTER_ACTION_SQL:
				{
					actionDesc << FilterActionSql(action.u.sqlCommand, nAction);
				}
				break;
			case AR_FILTER_ACTION_GOTOACTION:
				{
					actionDesc << FilterActionGotoAction(action.u.gotoAction, nAction);
				}
				break;
			case AR_FILTER_ACTION_CALLGUIDE:
				{
					actionDesc << FilterActionCallGuide(action.u.callGuide, nAction);
				}
				break;
			case AR_FILTER_ACTION_EXITGUIDE:
				{
					actionDesc << FilterActionExitGuide(action.u.exitGuide, nAction);
				}
				break;
			case AR_FILTER_ACTION_GOTOGUIDELABEL:
				{
					actionDesc << FilterActionGotoGuideLabel(action.u.gotoGuide, nAction);
				}
				break;
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_750
			case AR_FILTER_ACTION_SERVICE:
				{
					actionDesc << FilterActionService(action.u.serviceAction, nAction);
				}
				break;
#endif
			default:
				{
					actionDesc.str("");				
				}
				break;
			}

			CTableCell cellActionDesc(actionDesc.str(), "");
			row.AddCell(cellPosition);
			row.AddCell(cellActionType);
			row.AddCell(cellActionDesc);
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
		cout << "EXCEPTION enumerating filter action struct of '" << this->obj->GetName() << "': " << e.what() << endl;
	}

	return strm.str();
}

// AR_FILTER_ACTION_NONE
string CDocFilterActionStruct::FilterActionNone(int nAction)
{
	return "None";
}

// AR_FILTER_ACTION_NOTIFY
string CDocFilterActionStruct::FilterActionNotify(ARFilterActionNotify &action, int nAction)
{
	stringstream strm;
	strm.str("");

	try
	{
		if(action.notifyText != NULL)
		{
			CRefItem refItem(*this->obj, ifElse, nAction, REFM_NOTIFY_TEXT);
			strm << "Notify Text: " << arIn->TextFindFields(action.notifyText, "$", schemaInsideId, rootLevel, true, &refItem) << "<br/>" << endl;
		}
		else
			strm << "Notify Text: " << EmptyValue << "<br/>" << endl;


		if(action.user != NULL)
		{
			CRefItem refItem(*this->obj, ifElse, nAction, REFM_NOTIFY_USER);
			strm << "User Name: " << arIn->TextFindFields(action.user, "$", schemaInsideId, rootLevel, true, &refItem) << "<br/>" << endl;
		}
		else
			strm << "User Name: " << EmptyValue << "<br/>" << endl;


		strm << "Priority: " << action.notifyPriority << "<br/>" << endl;
		strm << "Mechanism: " << CAREnum::NotifyMechanism(action.notifyMechanism) << "<br/>" << endl;		

		if(action.notifyMechanism != AR_NOTIFY_VIA_NOTIFIER)
		{
			if(action.subjectText != NULL)
			{
				CRefItem refItem(*this->obj, ifElse, nAction, REFM_NOTIFY_SUBJECT);
				strm << "Subject: " << arIn->TextFindFields(action.subjectText, "$", schemaInsideId, rootLevel, true, &refItem) << "<br/>" << endl;
			}

			//Fields
			strm << "<br/>Include Fields: " << CAREnum::NotifyFieldList(action.fieldIdListType) << "<br/>" << endl;
			for(unsigned int i=0; i<action.fieldIdList.numItems; i++)
			{
				CRefItem refItem(*this->obj, ifElse, nAction, REFM_NOTIFY_FIELDLIST);
				arIn->AddFieldReference(schemaInsideId, action.fieldIdList.internalIdList[i], refItem);

				strm << arIn->LinkToField(schemaInsideId, action.fieldIdList.internalIdList[i], rootLevel) << "<br/>" << endl;
			}

			//Messages
			if(action.notifyAdvanced != NULL)
			{
				ARFilterActionNotifyAdvanced *adv = action.notifyAdvanced;

				strm << "<br/><br/>" << endl;

				if(adv->mailboxName != NULL)
				{
					CRefItem refItemMbName(*this->obj, ifElse, nAction, REFM_NOTIFY_MAILBOX);
					strm << "Mailbox Name: " << arIn->TextFindFields(adv->mailboxName, "$", schemaInsideId, rootLevel, true, &refItemMbName) << "<br/>" << endl;
				}

				if(adv->from != NULL)
				{
					CRefItem refItemFrom(*this->obj, ifElse, nAction, REFM_NOTIFY_FROM);
					strm << "From: " << arIn->TextFindFields(adv->from, "$", schemaInsideId, rootLevel, true, &refItemFrom) << "<br/>" << endl;
				}

				if(adv->replyTo != NULL)
				{
					CRefItem refItemReplTo(*this->obj, ifElse, nAction, REFM_NOTIFY_REPLYTO);
					strm << "Reply To: " << arIn->TextFindFields(adv->replyTo, "$", schemaInsideId, rootLevel, true, &refItemReplTo) << "<br/>" << endl;
				}

				if(adv->cc != NULL)
				{
					CRefItem refItemCc(*this->obj, ifElse, nAction, REFM_NOTIFY_CC);
					strm << "CC: " << arIn->TextFindFields(adv->cc, "$", schemaInsideId, rootLevel, true, &refItemCc) << "<br/>" << endl;
				}

				if(adv->bcc != NULL)
				{
					CRefItem refItemBcc(*this->obj, ifElse, nAction, REFM_NOTIFY_BCC);
					strm << "BCC: " << arIn->TextFindFields(adv->bcc, "$", schemaInsideId, rootLevel, true, &refItemBcc) << "<br/>" << endl;
				}

				if(adv->organization != NULL)
				{
					CRefItem refItemOrg(*this->obj, ifElse, nAction, REFM_NOTIFY_ORG);
					strm << "Organisation: " << arIn->TextFindFields(adv->organization, "$", schemaInsideId, rootLevel, true, &refItemOrg) << "<br/>" << endl;
				}

				if(adv->headerTemplate != NULL)
				{
					CRefItem refItemTmplHead(*this->obj, ifElse, nAction, REFM_NOTIFY_TEMPL_HEADER);
					strm << "Header Template: " << arIn->TextFindFields(adv->headerTemplate, "$", schemaInsideId, rootLevel, true, &refItemTmplHead) << "<br/>" << endl;
				}

				if(adv->contentTemplate != NULL)
				{
					CRefItem refItemTmplCont(*this->obj, ifElse, nAction, REFM_NOTIFY_TEMPL_CONTENT);
					strm << "Content Template: " << arIn->TextFindFields(adv->contentTemplate, "$", schemaInsideId, rootLevel, true, &refItemTmplCont) << "<br/>" << endl;
				}

				if(adv->footerTemplate != NULL)
				{
					CRefItem refItemTmplFooter(*this->obj, ifElse, nAction, REFM_NOTIFY_TEMPL_FOOTER);
					strm << "Footer Template: " << arIn->TextFindFields(adv->footerTemplate, "$", schemaInsideId, rootLevel, true, &refItemTmplFooter) << "<br/>" << endl;
				}
			}
		}
	}
	catch(exception& e)
	{
		cout << "EXCEPTION in FilterActionNotify of '" << this->obj->GetName() << "': " << e.what() << endl;
	}

	return strm.str();
}


// AR_FILTER_ACTION_MESSAGE
string CDocFilterActionStruct::FilterActionMessage(ARFilterStatusStruct &action, int nAction)
{
	stringstream strm;
	strm.str("");

	try
	{
		strm << "Message Number: " << action.messageNum << "<br/>" << endl;
		strm << "Message Type: " << CAREnum::MessageType(action.messageType) << "<br/>" << endl;

		if(action.messageText != NULL)
		{
			CRefItem refItemTmp(*this->obj, ifElse, nAction, REFM_MESSAGE);
			strm << "Message Text: <br/>" << arIn->TextFindFields(action.messageText, "$", this->schemaInsideId, rootLevel, true, &refItemTmp) << "<br/>" << endl;
		}
	}
	catch(exception& e)
	{
		cout << "EXCEPTION in FilterActionMessage of '" << this->obj->GetName() << "': " << e.what() << endl;
	}

	return strm.str();
}

// AR_FILTER_ACTION_LOG
string CDocFilterActionStruct::FilterActionLog(char* action, int nAction)
{
	stringstream strm;
	strm.str("");

	try
	{
		if(action != NULL)
		{
			strm << "File Name: " << action << endl; 
		}
		else
		{
			strm << "File Name: " << EmptyValue << endl; 
		}
	}
	catch(exception& e)
	{
		cout << "EXCEPTION in FilterActionLog of '" << this->obj->GetName() << "': " << e.what() << endl;
	}

	return strm.str();
}

// AR_FILTER_ACTION_FIELDS
string CDocFilterActionStruct::FilterActionSetFields(ARSetFieldsActionStruct &action, int nAction)
{
	stringstream strm;
	strm.str("");

	try
	{
		CDocActionSetFieldsHelper setFieldsHelper(*arIn, *obj, schemaName, action, structItemType, ifElse, nAction, rootLevel);
		setFieldsHelper.ToStream(strm);
	}
	catch(exception& e)
	{
		cout << "EXCEPTION in FilterActionSetFields of '" << this->obj->GetName() << "': " << e.what() << endl;
	}

	return strm.str();
}

// AR_FILTER_ACTION_PROCESS
string CDocFilterActionStruct::FilterActionProcess(char *action, int nAction)
{
	stringstream strm;
	strm.str("");

	try
	{
		if(action != NULL)
		{
			CRefItem refItem(*this->obj, ifElse, nAction, REFM_RUN_PROCESS);
			strm << arIn->TextFindFields(action, "$", schemaInsideId, rootLevel, true, &refItem) << endl;
		}
		else
		{
			strm << "No Run Process command specified." << endl;
		}
	}
	catch(exception& e)
	{
		cout << "EXCEPTION in FilterActionProcess of '" << this->obj->GetName() << "': " << e.what() << endl;
	}

	return strm.str();
}

// AR_FILTER_ACTION_FIELDP
string CDocFilterActionStruct::FilterActionPushFields(ARPushFieldsActionStruct &action, int nAction)
{
	stringstream strm;
	strm.str("");

	try
	{
		string pushSchema;

		// target form ******************************************
		strm << "Push Value To: ";
		if (action.pushFieldsList.pushFieldsList[0].field.schema[0] == '$' && action.sampleSchema[0] != 0)
		{
			int fieldId = atoi(&action.pushFieldsList.pushFieldsList[0].field.schema[1]);

			pushSchema = (fieldId == (-AR_KEYWORD_SCHEMA) ? schemaName : action.sampleSchema);
			strm << "$" << (fieldId < 0 ? CAREnum::Keyword(abs(fieldId)) : arIn->LinkToField(schemaInsideId, fieldId, rootLevel)) << "$ (Sample Schema: " << arIn->LinkToSchema(action.sampleSchema, rootLevel) << ")";

			// create field reference
			CRefItem refItem(*this->obj, ifElse, nAction, REFM_PUSHFIELD_FORM);
			arIn->AddFieldReference(schemaInsideId, fieldId, refItem);
		}
		else
		{
			pushSchema = action.pushFieldsList.pushFieldsList[0].field.schema;
			strm << arIn->LinkToSchema(pushSchema, rootLevel);
		}
		strm << "<br/>" << endl;

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
		stringstream strmTmpQual;

		int pFormId = this->arIn->SchemaGetInsideId(schemaName);
		int sFormId = this->arIn->SchemaGetInsideId(pushSchema);

		CRefItem refItem(*this->obj, ifElse, nAction, REFM_PUSHFIELD_IF);
		CARQualification arQual(*arIn, refItem, pFormId, sFormId, rootLevel);
		arQual.arsStructItemType = AR_STRUCT_ITEM_XML_FILTER;

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
		if(action.pushFieldsList.pushFieldsList[0].field.tag == AR_FIELD && action.pushFieldsList.pushFieldsList[0].field.u.fieldId == AR_LIKE_ID)
		{
			strm << " All Matching Ids<br/>" << endl;
			CDocAllMatchingIdsTable allMatchingFieldsTbl(pushSchema, schemaName, *obj, CDocAllMatchingIdsTable::AMM_PUSHFIELDS, nAction, ifElse, rootLevel);
			allMatchingFieldsTbl.ToStream(strm);
		}
		else
		{
			strm << "<br/>" << endl;

			CARAssignHelper assignHelper(*arIn, rootLevel, *this->obj, schemaName, pushSchema);
			strm << assignHelper.PushFieldsAssignment(action, nAction, ifElse);
		}
	}
	catch(exception& e)
	{
		cout << "EXCEPTION in FilterActionPushFields of '" << this->obj->GetName() << "': " << e.what() << endl;
	}

	return strm.str();
}

// AR_FILTER_ACTION_SQL
string CDocFilterActionStruct::FilterActionSql(ARSQLStruct &action, int nAction)
{
	stringstream strm;
	strm.str("");

	try
	{
		if(action.server != NULL)
			strm << "Server: " << arIn->LinkToServerInfo(action.server, rootLevel) << "<br/>" << endl;

		if(action.command != NULL)
		{
			CRefItem refItem(*this->obj, ifElse, nAction, REFM_DIRECTSQL);
			strm << "SQL command: <br/>" << arIn->TextFindFields(action.command, "$", schemaInsideId, rootLevel, true, &refItem) << endl;
		}
		
	}
	catch(exception& e)
	{
		cout << "EXCEPTION in FilterActionSql of '" << this->obj->GetName() << "': " << e.what() << endl;
	}

	return strm.str();
}

// AR_FILTER_ACTION_GOTOACTION 
string CDocFilterActionStruct::FilterActionGotoAction(ARGotoActionStruct &action, int nAction)
{
	stringstream strm;
	strm.str("");

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
		cout << "EXCEPTION in FilterActionGotoAction of '" << this->obj->GetName() << "': " << e.what() << endl;
	}

	return strm.str();
}

// AR_FILTER_ACTION_CALLGUIDE
string CDocFilterActionStruct::FilterActionCallGuide(ARCallGuideStruct &action, int nAction)
{
	stringstream strm;
	strm.str("");

	try
	{
		if (action.guideName[0] == '$' && action.guideName[1] != 0)
		{
			int fieldId = atoi(&action.guideName[1]);
			strm << "Guide: $" << (fieldId < 0 ? CAREnum::Keyword(abs(fieldId)) : arIn->LinkToField(this->schemaName, fieldId, rootLevel)) << "$<br/>" << endl;

			CRefItem refItem(*this->obj, ifElse, nAction, REFM_CALLGUIDE_NAME);
			arIn->AddFieldReference(this->schemaInsideId, fieldId, refItem);
		}
		else 
		{
			strm << "Guide: " << arIn->LinkToContainer(action.guideName, rootLevel) << "<br/>" << endl;
		}

		if(action.guideTableId > 0)
		{
			strm << "Table Loop: " << arIn->LinkToField(schemaInsideId, action.guideTableId, rootLevel) << "<br/>" << endl;

			CRefItem refItem(*this->obj, ifElse, nAction, REFM_CALLGUIDE_TABLELOOP);
			arIn->AddFieldReference(schemaInsideId, action.guideTableId, refItem);
		}
	}
	catch(exception& e)
	{
		cout << "EXCEPTION in FilterActionCallGuide of '" << this->obj->GetName() << "': " << e.what() << endl;
	}

	return strm.str();
}

// AR_FILTER_ACTION_EXITGUIDE
string CDocFilterActionStruct::FilterActionExitGuide(ARExitGuideStruct &action, int nAction)
{
	stringstream strm;
	strm.str("");

	try
	{
		if(action.closeAll == TRUE)
			strm << "<input type=\"checkbox\" name=\"exitGuide\" value=\"exitGuideCloseAll\" checked>Close all guides on exit" << endl;
		else
			strm << "<input type=\"checkbox\" name=\"exitGuide\" value=\"exitGuideCloseAll\">Close all guides on exit" << endl;
	}
	catch(exception& e)
	{
		cout << "EXCEPTION in FilterActionExitGuide of '" << this->obj->GetName() << "': " << e.what() << endl;
	}

	return strm.str();
}

// AR_FILTER_ACTION_GOTOGUIDELABEL
string CDocFilterActionStruct::FilterActionGotoGuideLabel(ARGotoGuideLabelStruct &action, int nAction)
{
	stringstream strm;
	strm.str("");

	try
	{
		if(action.label != NULL)
		{
			strm << "Guide Label: " << action.label << endl;
		}
		else
		{
			strm << "Guide Label: " << EmptyValue << endl;
		}
	}
	catch(exception& e)
	{
		cout << "EXCEPTION in FilterActionGotoGuideLabel of '" << this->obj->GetName() << "': " << e.what() << endl;
	}

	return strm.str();
}

#if AR_CURRENT_API_VERSION >= AR_API_VERSION_750
// AR_FILTER_ACTION_SERVICE
string CDocFilterActionStruct::FilterActionService(ARSvcActionStruct &action, int nAction)
{
	stringstream strm;
	strm.str("");

	try
	{
		strm << "<p>";
		// check for SAMPLE DATA
		string serviceSchema;
		if (action.serviceSchema[0] == '$' && action.sampleSchema[0] != 0)
		{
			int fieldId = atoi(&action.serviceSchema[1]);
			serviceSchema = action.sampleSchema;
			strm << "Service Form: " << "$" << (fieldId < 0 ? CAREnum::Keyword(abs(fieldId)) : arIn->LinkToField(this->schemaName, fieldId, rootLevel)) 
			     << "$ (Sample Form: " << arIn->LinkToSchema(serviceSchema, rootLevel) << ")<br/>" << endl;

			CRefItem refItem(*this->obj, ifElse, nAction, REFM_SERVICE_FORM);
			arIn->AddFieldReference(schemaInsideId, fieldId, refItem);

			if (fieldId == (-AR_KEYWORD_SCHEMA)) serviceSchema = schemaName;
		}
		else
		{
			serviceSchema = action.serviceSchema;
			strm << "Service Form: " << arIn->LinkToSchema(action.serviceSchema, rootLevel) << "<br/>" << endl;
		}

		CARSchema schemaToCall(serviceSchema);
		if (schemaToCall.Exists() && (!arIn->appConfig.bOverlaySupport || IsVisibleObject(*obj)))
		{
			CRefItem refItem(*this->obj, ifElse, nAction, REFM_SERVICE_CALL);
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
			CARAssignHelper assignHelper(*arIn, rootLevel, *this->obj, schemaName, serviceSchema);
			strm << assignHelper.ServiceAssignment(action.outputFieldMapping, nAction, ifElse, SMM_OUTPUT);
		}
	}
	catch (...)
	{
		cout << "EXCEPTION in FilterActionService: " << this->obj->GetName() << endl;
	}

	return strm.str();
}
#endif
