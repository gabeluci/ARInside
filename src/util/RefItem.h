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

#pragma once

/*
 * Storing references
 * ==================
 *
 * The old referencing object stored some redundant informations as well as the description text
 * of the reference. The problem with the description text is, that it could contain html-links
 * to other pages. If such a reference is not put on the desired page (sub-dir-level), e.g. the
 * "Missing Fields Validator", the contained html-link becomes invalid.
 * There are two solutions to this problem:
 *   a) all pages that would display that reference have to be in the same sub-dir level (all
 *      links become valid this way)
 *   b) the description is generated when the reference is placed on a page (the correct sub-dir
 *      level can be used during description-text generation)
 *
 * Solution b) has another advantage. Because the text is not stored within the reference (just
 * a message identifier) the memory usage of the reference object is reduced. On bigger servers
 * this can become a huge benefit.
 *
 * Data storage the "old way"
 * ==========================
 * The old object stored the following data:
 *	int arsStructItemType;
 *	string fromName;
 *	int fromFieldId;	// use this to create a reference between two field (e.g. a field used as column in a table); fromName should hold the schema name in this case
 *	string description;
 *	int fieldInsideId;
 *	int schemaInsideId;
 *
 * Because ARInside organizes all internal ARSystem data wihtin lists and uses array-index-like
 * ids to access those lists, it just needs a type and a id to reference the same object again.
 * So storing the fromName is not the best choise, because later you have to lookup the object
 * by its name again, which costs more than direct access by list-index.
 *
 * New Data storage
 * ================
 * Now we store the following data to support all kinds of references:
 *	int arsStructItemType;
 *	int objectId;
 *	int subObjectId;
 *	int actionIndex;
 *	int messageId;
 * 
 * So this uses 20 bytes per references. 50000 references would need only 1MB of memory. How the
 * above listed variables "subObjectId" and "actionIndex" are used, depends on the messageId. 
 * 
 */

// forward declaration
class CARServerObject;
class Context;

// Reference Types ////////////////////////////////////////////////////////////
// this values are returned by CRefItem::GetReferenceType to identify the
// underlying object type in case its necessary to cast to the real class.
const unsigned int REF_ITEM_TYPE_SERVEROBJECT = 1;
const unsigned int REF_ITEM_TYPE_WORKFLOW_ACTION = 2;
const unsigned int REF_ITEM_TYPE_OLD = 999; // just for compatibility; remove it later

// Messages ///////////////////////////////////////////////////////////////////
enum ReferenceMessages
{
	REFM_NONE = 0,

	// schema refs
	REFM_SCHEMA_INDEX,
	REFM_SCHEMA_RESULTLIST,
	REFM_SCHEMA_SORTLIST,
	REFM_SCHEMA_JOIN_QUALIFICATION,
	REFM_SCHEMA_AUDIT_QUALIFICATION,
	REFM_SCHEMA_ARCHIVE_QUALIFICATION,
	REFM_SCHEMA_FTS_WEIGHTED_RELEVANCY_FIELD,
	REFM_SCHEMA_AUDIT_SOURCE,
	REFM_SCHEMA_ARCHIVE_SOURCE,

	// basic workflow references
	REFM_RUNIF,
	REFM_CONTROLFIELD,
	REFM_FOCUSFIELD,

	// workflow action references
	REFM_PUSHFIELD_IF,
	REFM_PUSHFIELD_SERVER,
	REFM_PUSHFIELD_FORM,
	REFM_PUSHFIELD_TARGET,
	REFM_PUSHFIELD_VALUE,
	REFM_PUSHFIELD_TARGET_MATCHING,
	REFM_PUSHFIELD_VALUE_MATCHING,
	REFM_PUSHFIELD_HOVERFIELD,
	REFM_SETFIELDS_SERVER,
	REFM_SETFIELDS_FORM,
	REFM_SETFIELDS_QUALIFICATION,
	REFM_SETFIELDS_TARGET,
	REFM_SETFIELDS_VALUE,
	REFM_SETFIELDS_TARGET_MATCHING,
	REFM_SETFIELDS_VALUE_MATCHING,
	REFM_SETFIELDS_SQL_QUALIFICATION,
	REFM_SETFIELDS_WS_INPUT,
	REFM_SETFIELDS_WS_OUTPUT,
	REFM_SETFIELDS_HOVERFIELD,
	REFM_SETFIELDS_FILTERAPI_INPUT,
	REFM_SETFIELDS_FILTERAPI_PLUGINNAME,
	REFM_OPENWINDOW_SERVER,
	REFM_OPENWINDOW_FORM,
	REFM_OPENWINDOW_VIEW,
	REFM_OPENWINDOW_LOCATION,
	REFM_OPENWINDOW_LOCATION_VIEWFIELD,
	REFM_OPENWINDOW_REPORTTYPE,
	REFM_OPENWINDOW_REPORTNAME,
	REFM_OPENWINDOW_REPORTDESTINATION,
	REFM_OPENWINDOW_QUALIFICATION,
	REFM_OPENWINDOW_SORTBY,
	REFM_OPENWINDOW_ENTRYIDS,
	REFM_OPENWINDOW_QUERYOVERRIDE,
	REFM_OPENWINDOW_CHARENC,
	REFM_OPENWINDOW_TARGET,
	REFM_OPENWINDOW_VALUE,
	REFM_OPENWINDOW_HOVERFIELD,
	REFM_SERVICE_SERVER,
	REFM_SERVICE_FORM,
	REFM_SERVICE_CALL,
	REFM_SERVICE_REQUESTID,
	REFM_SERVICE_TARGET,
	REFM_SERVICE_VALUE,
	REFM_SERVICE_HOVERFIELD,
	REFM_RUN_PROCESS,
	REFM_DELETE_ENTRY_ACTION,
	REFM_MESSAGE,
	REFM_CHANGEFIELD,
	REFM_CHANGEFIELD_OF_FIELDS_VALUE,
	REFM_CHANGEFIELD_LABEL,
	REFM_DIRECTSQL,
	REFM_CALLCUIDE_SERVER,
	REFM_CALLGUIDE_NAME,
	REFM_CALLGUIDE_TABLELOOP,
	REFM_GOTO,
	REFM_CHARMENU_LABELFIELD,
	REFM_CHARMENU_VALUE,
	REFM_CHARMENU_QUALIFICATION,
	REFM_CHARMENU_SQL,
	REFM_CHARMENU_FORM,
	REFM_CHARMENU_SERVER,
	REFM_NOTIFY_TEXT,
	REFM_NOTIFY_USER,
	REFM_NOTIFY_SUBJECT,
	REFM_NOTIFY_FIELDLIST,
	REFM_NOTIFY_MAILBOX,
	REFM_NOTIFY_FROM,
	REFM_NOTIFY_REPLYTO,
	REFM_NOTIFY_CC,
	REFM_NOTIFY_BCC,
	REFM_NOTIFY_ORG,
	REFM_NOTIFY_TEMPL_HEADER,
	REFM_NOTIFY_TEMPL_CONTENT,
	REFM_NOTIFY_TEMPL_FOOTER,
	REFM_MACRO,

	// field refs
	REFM_TABLEFIELD_SERVER,
	REFM_TABLEFIELD_FORM,
	REFM_TABLEFIELD_COLUMN,
	REFM_TABLEFIELD_QUALIFICATION,

	// webservice
	REFM_WEBSERVICE_PROPERTY,
	REFM_WEBSERVICE_OPERATION,
	REFM_WEBSERVICE_FIELDMAP,

	// image refs
	REFM_BACKGROUND_IMAGE,
	REFM_TITLE_BAR_ICON,
	REFM_VUI_BACKGROUND,
	REFM_PACKINGLIST,

	// menu references
	REFM_FIELD_CHARMENU,
};

// maybe there is a better place for the following enums and functions //

// if or else mode enum
enum IfElseState
{
	IES_IF,
	IES_ELSE,
};

// returns string of the if/else state
const char* IfElse(IfElseState state);

enum ServiceMappingMode
{
	SMM_INPUT,
	SMM_OUTPUT,
};

enum OpenWindowMode
{
	OWM_OPEN,
	OWM_CLOSE,
};

// class for storing references
class CRefItem
{
public:
	CRefItem();	// constructor for reference to nothing
	CRefItem(const CARServerObject& obj, int dMessage);
	CRefItem(const CARServerObject& obj, int IfOrElse, int nAction, int dMessage);
	CRefItem(Context &context, int dMessage);
	CRefItem(const CRefItem& copyFrom, int dMessage); // to copy the referenced object, but change the message at the same time
	// the following constructor is for openwindow-action references
	CRefItem(const CARServerObject& obj, int IfOrElse, int nAction, int OpenOrClose, int dMessage);
	~CRefItem(void) { }

public:
	// returns a value to identify the reference class .. see REF_ITEM_TYPE_...
	//int GetReferenceType();
	// returns the message id of the description
	int GetMessageId() const { return messageId; }
	int GetObjectId() const { return objectId; }
	int GetSubObjectId() const { return subObjectId; }

	bool operator==(const CRefItem &r);

	// for reference table output we need ...

	// returns the referenced xml object type (AR_STRUCT_ITEM_XML_...)
	int GetObjectType() const;
	// returns the name of the referenced object
	string GetObjectName() const;
	// returns the enabled state of the referenced object
	unsigned int GetObjectEnabled(bool &supportsEnabled) const; // supportsEnabled is set to false, if the object doesn't support the enabled/disabled state
	// returns the enabled state of the referenced object
	unsigned int GetObjectEnabled() const;
	// returns the description text of the reference
	string GetDescription(int rootLevel) const;
	// writes the description text to an output stream
	void GetDescription(std::ostream& strm, int rootLevel) const;
	// returns the order of AL or FLT or -1 if the object doesnt have a order number
	int GetObjectOrder() const;
	// return the execute-on string of the object (in a single line)
	string GetObjectExecuteOn() const;

	// additional public helpers
	const char* IfElse() const;
	int ActionIndex() const;

private:
	void Init(const CARServerObject& obj, int IfOrElse, int nAction, int dMessage);

	// output helper functions
	const char* OpenClose() const;
	const char* ServiceInfo() const;
	string LinkToSchemaIndex(int rootLevel) const;
	string LinkToSchemaResultList(int rootLevel) const;
	string LinkToSchemaSortList(int rootLevel) const;
	string LinkToSchema(int rootLevel) const;
	void LinkToColumnParent(std::ostream& strm, int rootLevel) const;

protected:
	int arsStructItemType;
	int objectId;
	int subObjectId;
	int actionIndex;
	int messageId;
};

typedef vector<CRefItem> CRefItemList;
