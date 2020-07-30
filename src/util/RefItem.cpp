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
//    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.

#include "stdafx.h"

#include "RefItem.h"
#include "Context.h"
#include "../ARInside.h"
#include "../core/ARServerObject.h"
#include "../core/ARSchema.h"
#include "../core/ARField.h"
#include "../core/ARVui.h"
#include "../core/ARActiveLink.h"
#include "../core/ARFilter.h"
#include "../core/AREscalation.h"
#include "../core/ARContainer.h"
#include "../core/ARCharMenu.h"
#include "../core/ARImage.h"
#include "../output/URLLink.h"

const char* IfElse(IfElseState state)
{
	if (state == IES_IF) return "If";
	else return "Else";
}

///////////////////////////////////////////////////////////////////
// bit mask for actionIndex variable of CRefItem
// 3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0 0 0
// 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//                                      | |_______________________|
//                                      |_|    IfElse + Action
//                                       OpenClose-Bit
//                                       Service In/Out Bit
const int ACTIONMASK_INDEX = 0x000007FF;
const int ACTIONMASK_OPENCLOSE = 0x00000800;
const int ACTIONMASK_SERVICE_IN_OR_OUT = 0x00000800;

CRefItem::CRefItem()
{
	this->arsStructItemType = AR_STRUCT_ITEM_XML_NONE;
	this->actionIndex = -1;
	this->objectId = -1;
	this->messageId = -1;
	this->subObjectId = -1;
}

CRefItem::CRefItem(const CARServerObject &obj, int dMessage)
{
	Init(obj, 0, -1, dMessage);
}

CRefItem::CRefItem(const CARServerObject &obj, int IfOrElse, int nAction, int dMessage)
{
	Init(obj, IfOrElse, nAction, dMessage);
}

CRefItem::CRefItem(Context &context, int dMessage)
{
	Init(context.getCurrentObject(), context.getIfElse(), context.getActionIndex(), dMessage);
}

CRefItem::CRefItem(const CARServerObject &obj, int IfOrElse, int nAction, int OpenOrClose, int dMessage)
{
	Init(obj, IfOrElse, nAction, dMessage);
	if (OpenOrClose > 0)
		this->actionIndex |= ACTIONMASK_OPENCLOSE;	// set open/close bit
}

CRefItem::CRefItem(const CRefItem& copyFrom, int dMessage)
{
	if (&copyFrom != NULL)
	{
		arsStructItemType = copyFrom.arsStructItemType;
		objectId = copyFrom.objectId;
		subObjectId = copyFrom.subObjectId;
		actionIndex = copyFrom.actionIndex;
		messageId = (copyFrom.messageId != -1 ? dMessage : copyFrom.messageId);
	}
	else 
	{
		arsStructItemType = AR_STRUCT_ITEM_XML_NONE;
		objectId = -1;
		subObjectId = -1;
		actionIndex = -1;
		messageId = -1;
	}
}

void CRefItem::Init(const CARServerObject &obj, int IfOrElse, int nAction, int dMessage)
{
	this->arsStructItemType = obj.GetServerObjectTypeXML();
	this->actionIndex = nAction;
	this->messageId = dMessage;

	if (IfOrElse > 0)
		this->actionIndex += 1000;

	// for special types .. fill subObjectId
	switch(this->arsStructItemType)
	{
	case AR_STRUCT_ITEM_XML_FIELD:
		this->objectId = (static_cast<const CARField*>(&obj))->GetSchema().GetInsideId();
		this->subObjectId = obj.GetInsideId();
		break;
	case AR_STRUCT_ITEM_XML_VUI:
		this->objectId = (static_cast<const CARVui*>(&obj))->GetSchema().GetInsideId();
		this->subObjectId = obj.GetInsideId();
		break;
	default:
		this->objectId = obj.GetInsideId();
		this->subObjectId = -1;
	}
}

const char* CRefItem::IfElse() const
{
	int action = actionIndex & ACTIONMASK_INDEX;
	if (action < 1000) 
		return ::IfElse(IES_IF);
	else
		return ::IfElse(IES_ELSE);
}

const char* CRefItem::OpenClose() const
{
	if ((actionIndex & ACTIONMASK_OPENCLOSE) == 0)
		return "Open Window";
	else
		return "Close Window";
}

const char* CRefItem::ServiceInfo() const
{
	if ((actionIndex & ACTIONMASK_SERVICE_IN_OR_OUT) == 0)
		return "Service Input Mapping";
	else
		return "Service Output Mapping";
}

int CRefItem::ActionIndex() const
{
	int action = actionIndex & ACTIONMASK_INDEX;
	if (action < 1000)
		return action;
	else
		return action - 1000;
}

string CRefItem::LinkToSchemaIndex(int rootLevel) const
{
	CARSchema schema(objectId);
	if (schema.Exists())
	{
		const ARIndexList& indexList = schema.GetIndexList();
		return URLLink(indexList.indexList[actionIndex].indexName, CPageParams(PAGE_SCHEMA_INDEXES, &schema), rootLevel);
	}
	return "Index";
}

string CRefItem::LinkToSchemaResultList(int rootLevel) const
{
	const char* cResultList = "ResultList";
	CARSchema schema(objectId);
	if (schema.Exists())
	{
		return URLLink(cResultList, CPageParams(PAGE_SCHEMA_RESULTLIST, &schema), rootLevel);
	}
	return cResultList;
}

string CRefItem::LinkToSchemaSortList(int rootLevel) const
{
	const char* cSortList = "SortList";
	CARSchema schema(objectId);
	if (schema.Exists())
	{
		return URLLink(cSortList, CPageParams(PAGE_SCHEMA_SORTLIST, &schema), rootLevel);
	}
	return cSortList;
}

string CRefItem::LinkToSchema(int rootLevel) const
{
	switch (arsStructItemType)
	{
	case AR_STRUCT_ITEM_XML_SCHEMA:
	case AR_STRUCT_ITEM_XML_FIELD:
	case AR_STRUCT_ITEM_XML_VUI:
		{
			CARSchema schema(objectId);
			return URLLink(schema, rootLevel);
		}
		break;
	default: return "";
	}
}

void CRefItem::LinkToColumnParent(std::ostream& strm, int rootLevel) const
{
	// objectId contains schema id
	// subObjectId contains column field id,
	// actionIndex contains table field id
	CARSchema schema(objectId);
	CARField field(objectId, actionIndex);

	if (field.Exists())
	{
		strm << CARInside::GetInstance()->LinkToField(schema.GetInsideId(), actionIndex, rootLevel) << " of Form " << CARInside::GetInstance()->LinkToSchema(schema.GetInsideId(), rootLevel);
	}
}

bool CRefItem::operator ==(const CRefItem &r)
{
	if (this->arsStructItemType == r.arsStructItemType &&
		this->objectId == r.objectId &&
		this->messageId == r.messageId &&
		// jls17 NOTE/TODO: just a test to eliminate duplicate references when field is used in multiple action within the same object
		//this->actionIndex == r.actionIndex && 
		this->subObjectId == r.subObjectId)
	{
		return true;
	}
	return false;
}

int CRefItem::GetObjectType() const
{
	return this->arsStructItemType;
}

string CRefItem::GetObjectName() const
{
	switch (this->arsStructItemType)
	{
	case AR_STRUCT_ITEM_XML_SCHEMA:
	// the main object of field/vui is the schema. so in this case we have to
	// return the schema name, which is used as object name to LinkToXmlObjType
	case AR_STRUCT_ITEM_XML_FIELD:
	case AR_STRUCT_ITEM_XML_VUI:
		{
			CARSchema schema(this->objectId);
			return schema.GetName();
		}
		break;
	case AR_STRUCT_ITEM_XML_FILTER:
		{
			CARFilter filter(this->objectId);
			return filter.GetName();
		}
		break;
	case AR_STRUCT_ITEM_XML_ACTIVE_LINK:
		{
			CARActiveLink actlink(this->objectId);
			return actlink.GetName();
		}
		break;
	case AR_STRUCT_ITEM_XML_CHAR_MENU:
		{
			CARCharMenu charMenu(this->objectId);
			return charMenu.GetName();
		}
		break;
	case AR_STRUCT_ITEM_XML_ESCALATION:
		{
			CAREscalation esc(this->objectId);
			return esc.GetName();
		}
		break;
	// TODO: implement Distributed Mapping
	//case AR_STRUCT_ITEM_XML_DIST_MAP:
	//	{
	//	}
	//	break;
	case AR_STRUCT_ITEM_XML_CONTAINER:
		{
			CARContainer cont(this->objectId);
			return cont.GetName();
		}
		break;
	// TODO: implement Distributed Pool
	//case AR_STRUCT_ITEM_XML_DIST_POOL:
	//	{
	//	}
	//	break;
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_750
	case AR_STRUCT_ITEM_IMAGE:
		{
			CARImage img(this->objectId);
			return img.GetName();
		}
		break;
#endif
	default: return "";
	}
}

unsigned int CRefItem::GetObjectEnabled(bool &supportsEnabled) const
{
	switch (GetObjectType())
	{
	case AR_STRUCT_ITEM_XML_FILTER:
		{
			supportsEnabled = true;
			CARFilter flt(this->objectId);
			return flt.GetEnabled();
		}
	case AR_STRUCT_ITEM_XML_ACTIVE_LINK:
		{
			supportsEnabled = true;
			CARActiveLink actlink(this->objectId);
			return actlink.GetEnabled();
		}
	case AR_STRUCT_ITEM_XML_ESCALATION:
		{
			supportsEnabled = true;
			CAREscalation esc(this->objectId);
			return esc.GetEnabled();
		}
	////case AR_STRUCT_ITEM_XML_DIST_MAP: // TODO: add DSO support
	//case AR_STRUCT_ITEM_XML_DIST_POOL:
		
	default:
		supportsEnabled = false;
		return false;
	}
}

int CRefItem::GetObjectOrder() const
{
	switch (GetObjectType())
	{
	case AR_STRUCT_ITEM_XML_ACTIVE_LINK:
		{
			CARActiveLink al(GetObjectId());
			return al.GetOrder();
		}
	case AR_STRUCT_ITEM_XML_FILTER:
		{
			CARFilter flt(GetObjectId());
			return flt.GetOrder();
		}
	default: return -1;
	}
}

string CRefItem::GetObjectExecuteOn() const
{
	switch (GetObjectType())
	{
	case AR_STRUCT_ITEM_XML_ACTIVE_LINK:
		{
			CARActiveLink al(GetObjectId());
			CARProplistHelper props(&al.GetPropList());
			return al.GetExecuteOn(true, &props);
		}
	case AR_STRUCT_ITEM_XML_FILTER:
		{
			CARFilter flt(GetObjectId());
			return flt.GetExecuteOn(true);
		}
	case AR_STRUCT_ITEM_XML_ESCALATION:
		{
			CAREscalation esc(GetObjectId());
			return esc.GetExecuteOn();
		}
	default: return "";
	}
}

unsigned int CRefItem::GetObjectEnabled() const
{
	bool se;
	return GetObjectEnabled(se);
}

string CRefItem::GetDescription(int rootLevel) const
{
	stringstream strm;
	GetDescription(strm, rootLevel);
	return strm.str();
}

void CRefItem::GetDescription(std::ostream &strm, int rootLevel) const
{
	switch (messageId)
	{
	case REFM_PUSHFIELD_TARGET:
		strm << "Target in 'Push Fields' " << IfElse() << "-Action " << ActionIndex();
		break;
	case REFM_PUSHFIELD_VALUE:
		strm << "Value in 'Push Fields' " << IfElse() << "-Action " << ActionIndex();
		break;
	case REFM_SETFIELDS_TARGET:
		strm << "Target in 'Set Fields' " << IfElse() << "-Action " << ActionIndex();
		break;
	case REFM_SETFIELDS_VALUE:
		strm << "Value in 'Set Fields' " << IfElse() << "-Action " << ActionIndex();
		break;
	case REFM_OPENWINDOW_TARGET:
		strm << "Target in '" << OpenClose() << "' " << IfElse() << "-Action " << ActionIndex();
		break;
	case REFM_OPENWINDOW_VALUE:
		strm << "Value in '" << OpenClose() << "' " << IfElse() << "-Action " << ActionIndex();
		break;
	case REFM_SERVICE_TARGET:
		strm << "Target in '" << ServiceInfo() << "' " << IfElse() << "-Action " << ActionIndex();
		break;
	case REFM_SERVICE_VALUE:
		strm << "Value in '" << ServiceInfo() << "' " << IfElse() << "-Action " << ActionIndex();
		break;
	case REFM_SETFIELDS_FORM:
		strm << "Form Name in 'SetFields' " << IfElse() << "-Action " << ActionIndex();
		break;
	case REFM_SETFIELDS_SERVER:
		strm << "Server Name in 'SetFields' " << IfElse() << "-Action " << ActionIndex();
		break;
	case REFM_SETFIELDS_QUALIFICATION:
		strm << "Set Field If Qualification " << IfElse() << "-Action " << ActionIndex();
		break;
	case REFM_SETFIELDS_SQL_QUALIFICATION:
		strm << "SQL Set Field If Qualification" << IfElse() << "-Action " << ActionIndex();
		break;
	case REFM_PUSHFIELD_TARGET_MATCHING:
		strm << "Target in 'Push Fields' (All Matching Ids) " << IfElse() << "-Action " << ActionIndex();
		break;
	case REFM_PUSHFIELD_VALUE_MATCHING:
		strm << "Value in 'Push Fields' (All Matching Ids) " << IfElse() << "-Action " << ActionIndex();
		break;
	case REFM_SETFIELDS_TARGET_MATCHING:
		strm << "Target in 'Set Fields' (All Matching Ids) " << IfElse() << "-Action " << ActionIndex();
		break;
	case REFM_SETFIELDS_VALUE_MATCHING:
		strm << "Value in 'Set Fields' (All Matching Ids) " << IfElse() << "-Action " << ActionIndex();
		break;
	case REFM_SETFIELDS_HOVERFIELD:
		strm << "Hover-Field in 'SetFields' " << IfElse() << "-Action " << ActionIndex();
		break;
	case REFM_SETFIELDS_FILTERAPI_INPUT:
		strm << "Value in FilterAPI-Input-Mapping " << IfElse() << "-Action " << ActionIndex();
		break;
	case REFM_SETFIELDS_FILTERAPI_PLUGINNAME:
		strm << "Plugin-Name in FilterAPI-Call " << IfElse() << "-Action " << ActionIndex();
		break;
	case REFM_PUSHFIELD_HOVERFIELD:
		strm << "Hover-Field in 'PushFields' " << IfElse() << "-Action " << ActionIndex();
		break;
	case REFM_OPENWINDOW_HOVERFIELD:
		strm << "Hover-Field in 'OpenWindow' " << IfElse() << "-Action " << ActionIndex();
		break;
	case REFM_SERVICE_HOVERFIELD:
		strm << "Hover-Field in 'Service' " << IfElse() << "-Action " << ActionIndex();
		break;
	case REFM_RUN_PROCESS:
		strm << "Field in Run Process " << IfElse() << "-Action " << ActionIndex();
		break;
	case REFM_DELETE_ENTRY_ACTION:
		strm << "Application-Delete Command in " << IfElse() << "-Action " << ActionIndex();
		break;
	case REFM_MESSAGE:
		strm << "Message " << IfElse() << "-Action " << ActionIndex();
		break;
	case 	REFM_CHANGEFIELD:
		strm << "Change Field " << IfElse() << "-Action " << ActionIndex();
		break;
	case REFM_CHANGEFIELD_OF_FIELDS_VALUE:
		strm << "Change Field of Fields Value " << IfElse() << "-Action " << ActionIndex();
		break;
	case REFM_CHANGEFIELD_LABEL:
		strm << "Change Field Label " << IfElse() << "-Action " << ActionIndex();
		break;
	case REFM_PUSHFIELD_SERVER:
		strm << "Server Name in 'Push Fields' " << IfElse() << "-Action " << ActionIndex();
		break;
	case REFM_PUSHFIELD_FORM:
		strm << "Form Name in 'Push Fields' " << IfElse() << "-Action " << ActionIndex();
		break;
	case REFM_PUSHFIELD_IF:
		strm << "Push Field If Qualification " << IfElse() << "-Action " << ActionIndex();
		break;
	case REFM_DIRECTSQL:
		strm << "Value in Direct SQL " << IfElse() << "-Action " << ActionIndex();
		break;
	case REFM_OPENWINDOW_LOCATION:
		strm << "Window Open Location " << IfElse() << "-Action " << ActionIndex();
		break;
	case REFM_OPENWINDOW_LOCATION_VIEWFIELD:
		strm << "OpenWindow Location ViewField in " << IfElse() << "-Action " << ActionIndex();
		break;
	case REFM_OPENWINDOW_SERVER:
		strm << "Window Open Server Name " << IfElse() << "-Action " << ActionIndex();
		break;
	case REFM_OPENWINDOW_FORM:
		strm << "Window Open Form Name " << IfElse() << "-Action " << ActionIndex();
		break;
	case REFM_OPENWINDOW_VIEW:
		strm << "Window Open View Name " << IfElse() << "-Action " << ActionIndex();
		break;
	case REFM_OPENWINDOW_REPORTTYPE:
		strm << "Window Open Report Type " << IfElse() << "-Action " << ActionIndex();
		break;
	case REFM_OPENWINDOW_REPORTNAME:
		strm << "Window Open Report Name " << IfElse() << "-Action " << ActionIndex();
		break;
	case REFM_OPENWINDOW_REPORTDESTINATION:
		strm << "Window Open Report Destination " << IfElse() << "-Action " << ActionIndex();
		break;
	case REFM_OPENWINDOW_QUALIFICATION:
		strm << "Open Window Qualification " << IfElse() << "-Action " << ActionIndex();
		break;
	case REFM_OPENWINDOW_SORTBY:
		strm << "Open Window SortBy " << IfElse() << "-Action " << ActionIndex();
		break;
	case REFM_OPENWINDOW_ENTRYIDS:
		strm << "Window Open EntryIDs " << IfElse() << "-Action " << ActionIndex();
		break;
	case REFM_OPENWINDOW_QUERYOVERRIDE:
		strm << "Window Open Query Override " << IfElse() << "-Action " << ActionIndex();
		break;
	case REFM_OPENWINDOW_CHARENC:
		strm << "Window Open Character Encoding " << IfElse() << "-Action " << ActionIndex();
		break;
	case REFM_CALLCUIDE_SERVER:
		strm << "Used as CallGuide Server in " << IfElse() << "-Action " << ActionIndex();
		break;
	case REFM_CALLGUIDE_NAME:
		strm << "Used as CallGuide Name in " << IfElse() << "-Action " << ActionIndex();
		break;
	case REFM_CALLGUIDE_TABLELOOP:
		strm << "Guide Table Loop " << IfElse() << "-Action " << ActionIndex();
		break;
	case REFM_GOTO:
		strm << "Used as Goto-Value in " << IfElse() << "-Action " << ActionIndex();
		break;
	case REFM_SERVICE_SERVER:
		strm << "Used as Service Server in " << IfElse() << "-Action " << ActionIndex();
		break;
	case REFM_SERVICE_FORM:
		strm << "Used as Service Form in " << IfElse() << "-Action " << ActionIndex();
		break;
	case REFM_SERVICE_CALL:
		strm << "Start Service Call in " << IfElse() << "-Action " << ActionIndex();
		break;
	case REFM_SERVICE_REQUESTID:
		strm << "Service Request-Id " << IfElse() << "-Action " << ActionIndex();
		break;
	case REFM_TABLEFIELD_SERVER:
		strm << "Used as Server of Table Field";
		break;
	case REFM_TABLEFIELD_FORM:
		strm << "Used as Schema of Table Field";
		break;
	case REFM_TABLEFIELD_COLUMN:
		strm << "Column in Table "; LinkToColumnParent(strm, rootLevel);
		break;
	case REFM_TABLEFIELD_QUALIFICATION:
		strm << "Table Qualification";
		break;
	case REFM_CHARMENU_LABELFIELD:
		strm << "Menu Label Field";
		break;
	case REFM_CHARMENU_VALUE:
		strm << "Menu Value Field";
		break;
	case REFM_CHARMENU_QUALIFICATION:
		strm << "Search Menu Qualification";
		break;
	case REFM_NOTIFY_TEXT:
		strm << "Field in Notify Action (Text)";
		break;
	case REFM_NOTIFY_USER:
		strm << "Field in Notify Action (User Name)";
		break;
	case REFM_NOTIFY_SUBJECT:
		strm << "Field in Notify Action (Subject)";
		break;
	case REFM_NOTIFY_FIELDLIST:
		strm << "Field in Notify Action (Field List)";
		break;
	case REFM_NOTIFY_MAILBOX:
		strm << "Field in Notify Action (Mailbox Name)";
		break;
	case REFM_NOTIFY_FROM:
		strm << "Field in Notify Action (From)";
		break;
	case REFM_NOTIFY_REPLYTO:
		strm << "Field in Notify Action (Reply To)";
		break;
	case REFM_NOTIFY_CC:
		strm << "Field in Notify Action (CC)";
		break;
	case REFM_NOTIFY_BCC:
		strm << "Field in Notify Action (BCC)";
		break;
	case REFM_NOTIFY_ORG:
		strm << "Field in Notify Action (Organisation)";
		break;
	case REFM_NOTIFY_TEMPL_HEADER:
		strm << "Field in Notify Action (Header Template)";
		break;
	case REFM_NOTIFY_TEMPL_CONTENT:
		strm << "Field in Notify Action (Content Template)";
		break;
	case REFM_NOTIFY_TEMPL_FOOTER:
		strm << "Field in Notify Action (Footer Template)";
		break;
	case REFM_SETFIELDS_WS_INPUT:
		strm << "Web Service Set Fields Input Mapping";
		break;
	case REFM_SETFIELDS_WS_OUTPUT:
		strm << "Web Service Set Fields Output Mapping";
		break;
	case REFM_SCHEMA_INDEX:
		strm << "Field in " << LinkToSchemaIndex(rootLevel);
		break;
	case REFM_SCHEMA_RESULTLIST:
		strm << "Field in " << LinkToSchemaResultList(rootLevel);
		break;
	case REFM_SCHEMA_SORTLIST:
		strm << "Field in " << LinkToSchemaSortList(rootLevel);
		break;
	case REFM_SCHEMA_JOIN_QUALIFICATION:
		strm << "Join Qualification";
		break;
	case REFM_SCHEMA_AUDIT_QUALIFICATION:
		strm << "Audit Qualification";
		break;
	case REFM_SCHEMA_ARCHIVE_QUALIFICATION:
		strm << "Archive Qualification";
		break;
	case REFM_SCHEMA_FTS_WEIGHTED_RELEVANCY_FIELD:
		strm << "FTS Weighted Relevancy Field";
		break;
	case REFM_SCHEMA_AUDIT_SOURCE:
		strm << "Audit Source Form";
		break;
	case REFM_SCHEMA_ARCHIVE_SOURCE:
		strm << "Archive Source Form";
		break;
	case REFM_WEBSERVICE_PROPERTY:
		strm << "Webservice Property";
		break;
	case REFM_WEBSERVICE_OPERATION:
		strm << "Webservice Operation";
		break;
	case REFM_WEBSERVICE_FIELDMAP:
		strm << "Webservice Field Mapping";
		break;
	case REFM_RUNIF:
		strm << "Run If";
		break;
	case REFM_CONTROLFIELD:
		strm << "Control Field";
		break;
	case REFM_FOCUSFIELD:
		strm << "Focus Field";
		break;
	case REFM_MACRO:
		strm << "Field in Macro " << IfElse() << "-Action " << ActionIndex();
		break;
	case REFM_BACKGROUND_IMAGE:
		strm << "Image on field of form " << LinkToSchema(rootLevel);
		break;
	case REFM_TITLE_BAR_ICON:
		strm << "Title Bar Icon in VUI of Form " << LinkToSchema(rootLevel);
		break;
	case REFM_VUI_BACKGROUND:
		strm << "Background in VUI of Form " << LinkToSchema(rootLevel);
		break;
	case REFM_PACKINGLIST:
		strm << "Contained in packing list";
		break;
	case REFM_FIELD_CHARMENU:
		strm << "Field Menu on Form " << LinkToSchema(rootLevel);
		break;
	case REFM_CHARMENU_SQL:
		strm << "Field in Menus SQL-Command";
		break;
	case REFM_CHARMENU_FORM:
		strm << "Form-Value in Menu";
		break;
	case REFM_CHARMENU_SERVER:
		strm << "Server-Value in Menu";
		break;
	default:
		assert(false);
	}
}
