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
#include "ARActiveLink.h"
#include "../ARInside.h"
#include "../output/IFileStructure.h"

CARActiveLink::CARActiveLink()
: CARServerObject(-1)
{
}

CARActiveLink::CARActiveLink(int insideId)
: CARServerObject(insideId)
{
}

CARActiveLink::CARActiveLink(const string& name)
: CARServerObject(-1)
{
	insideId = CARInside::GetInstance()->alList.Find(name.c_str());
}

bool CARActiveLink::IsClonable() const
{
	return true;
}

CARServerObject* CARActiveLink::Clone() const
{
	return new CARActiveLink(*this);
}

CARActiveLink::~CARActiveLink(void)
{
}

bool CARActiveLink::Exists() const
{
	return (insideId >= 0 && (unsigned int)insideId < CARInside::GetInstance()->alList.GetCount());
}

/// Builds a ExecuteOn-string
string CARActiveLink::GetExecuteOn(bool singleLine, CARProplistHelper* props)
{		
	stringstream strm;
	strm.str("");
	bool strmHasContent = false; // use a local var to avoid use of 'strm.str().empty', because this make a copy of the string buffer evrytime

	try
	{		
		typedef	struct ARInsideExecOnStruct {
			unsigned int exec;
			const char   *text;
		} ARInsideExecOnStruct;

		const ARInsideExecOnStruct executeText[] = {
			AR_EXECUTE_ON_BUTTON, "Button/MenuField",
			AR_EXECUTE_ON_RETURN, "Return",
			AR_EXECUTE_ON_SUBMIT, "Submit",
			AR_EXECUTE_ON_MODIFY, "Modify",
			AR_EXECUTE_ON_DISPLAY, "Display",
			//AR_EXECUTE_ON_MODIFY_ALL, "Modify All", // its now a $OPERATION$
			//AR_EXECUTE_ON_MENU_OPEN, "OPEN",        // unsupported
			AR_EXECUTE_ON_MENU_CHOICE, "Menu Choice",
			AR_EXECUTE_ON_LOSE_FOCUS, "Loose Focus",
			AR_EXECUTE_ON_SET_DEFAULT, "Set Default",
			AR_EXECUTE_ON_QUERY, "Search",
			AR_EXECUTE_ON_AFTER_MODIFY, "After Modify",
			AR_EXECUTE_ON_AFTER_SUBMIT, "After Submit",
			AR_EXECUTE_ON_GAIN_FOCUS, "Gain Focus",
			AR_EXECUTE_ON_WINDOW_OPEN, "Window Open",
			AR_EXECUTE_ON_WINDOW_CLOSE, "Window Close",
			AR_EXECUTE_ON_UNDISPLAY, "Un-Display",
			AR_EXECUTE_ON_COPY_SUBMIT, "Copy To New",
			AR_EXECUTE_ON_LOADED, "Window Loaded",			
			// AR_EXECUTE_ON_INTERVAL is obsolete; 7.5 handle this only as object property; 
			// and older servers use this flag AND the object property. so its not needed 
			// to check this at all
			AR_EXECUTE_ON_EVENT, "Event",

#if AR_CURRENT_API_VERSION >= AR_API_VERSION_750
			AR_EXECUTE_ON_TABLE_CONTENT_CHANGE, "Table Refresh",
			AR_EXECUTE_ON_HOVER_FIELD_LABEL, "Hover On Label",
			AR_EXECUTE_ON_HOVER_FIELD_DATA, "Hover On Data",
			AR_EXECUTE_ON_HOVER_FIELD, "Hover On Field",
			AR_EXECUTE_ON_PAGE_EXPAND, "Expand",
			AR_EXECUTE_ON_PAGE_COLLAPSE, "Collapse",
#endif
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_763
			AR_EXECUTE_ON_DRAG, "Drag",
			AR_EXECUTE_ON_DROP, "Drop",
#endif
			0,NULL
		};

		for (unsigned int k = 0; true; ++k)
		{
			if (executeText[k].exec == 0) break;

			if ( (this->GetExecuteMask() & executeText[k].exec) != 0)
			{
				if (!singleLine && strmHasContent) strm << "<br/>";
				if (singleLine && strmHasContent) strm << ", ";
				strm << executeText[k].text;
				strmHasContent = true;
			}
		}
		if (props != NULL)
		{
			// now check for special execution properties
			ARValueStruct* val = props->GetAndUseValue(AR_OPROP_INTERVAL_VALUE);
			if (val != NULL)
				if (val->dataType == AR_DATA_TYPE_INTEGER)
				{
					if (!singleLine && strmHasContent) strm << "<br/>";
					if (singleLine && strmHasContent) strm << ", ";
					strm << "Interval";
					if (!singleLine) strm << ": " << val->u.intVal;
					strmHasContent = true;
				}
		}
		if(!strmHasContent)
		{
			strm << "None";
		}
	}
	catch(exception& e)
	{
		cout << "EXCEPTION in ActiveLink GetExecuteOn: " << e.what() << endl;
	}
	return strm.str();
}

string CARActiveLink::GetName()
{
	return CARInside::GetInstance()->alList.ActiveLinkGetName(GetInsideId());
}

string CARActiveLink::GetName() const
{
	return CARInside::GetInstance()->alList.ActiveLinkGetName(GetInsideId());
}

string CARActiveLink::GetNameFirstChar()
{
	return CARObject::GetNameFirstChar(CARInside::GetInstance()->alList.ActiveLinkGetName(GetInsideId()));
}

bool CARActiveLink::NameStandardFirstChar()
{
	return CARObject::NameStandardFirstChar(GetNameFirstChar());
}

unsigned int CARActiveLink::GetOrder() const
{ 
	return CARInside::GetInstance()->alList.ActiveLinkGetOrder(GetInsideId());
}

const ARWorkflowConnectStruct& CARActiveLink::GetSchemaList() const 
{ 
	return CARInside::GetInstance()->alList.ActiveLinkGetSchemaList(GetInsideId());
}

const ARInternalIdList& CARActiveLink::GetGroupList() const 
{ 
	return CARInside::GetInstance()->alList.ActiveLinkGetGroupList(GetInsideId());
}

unsigned int CARActiveLink::GetExecuteMask() const
{ 
	return CARInside::GetInstance()->alList.ActiveLinkGetExecuteMask(GetInsideId());
}

const ARInternalId& CARActiveLink::GetControlField() const 
{ 
	return CARInside::GetInstance()->alList.ActiveLinkGetControlField(GetInsideId());
}

const ARInternalId& CARActiveLink::GetFocusField() const 
{ 
	return CARInside::GetInstance()->alList.ActiveLinkGetFocusField(GetInsideId());
}

unsigned int CARActiveLink::GetEnabled() const
{ 
	return CARInside::GetInstance()->alList.ActiveLinkGetEnabled(GetInsideId());
}
	
const ARQualifierStruct& CARActiveLink::GetRunIf() const 
{ 
	return CARInside::GetInstance()->alList.ActiveLinkGetRunIf(GetInsideId()); 
}

const ARActiveLinkActionList& CARActiveLink::GetIfActions() const
{ 
	return CARInside::GetInstance()->alList.ActiveLinkGetIfActions(GetInsideId());
}

const ARActiveLinkActionList& CARActiveLink::GetElseActions() const
{
	return CARInside::GetInstance()->alList.ActiveLinkGetElseActions(GetInsideId());
}

const ARPropList& CARActiveLink::GetPropList() const
{
	return CARInside::GetInstance()->alList.ActiveLinkGetPropList(GetInsideId());
}

const string& CARActiveLink::GetAppRefName() const
{
	return CARInside::GetInstance()->alList.ActiveLinkGetAppRefName(GetInsideId());
}

void CARActiveLink::SetAppRefName(const string &appName)
{
	return CARInside::GetInstance()->alList.ActiveLinkSetAppRefName(GetInsideId(), appName);
}

const char* CARActiveLink::GetHelpText() const
{
	return CARInside::GetInstance()->alList.ActiveLinkGetHelptext(GetInsideId());
}

ARTimestamp CARActiveLink::GetTimestamp() const
{
	return CARInside::GetInstance()->alList.ActiveLinkGetTimestamp(GetInsideId());
}

const ARAccessNameType& CARActiveLink::GetOwner() const
{
	return CARInside::GetInstance()->alList.ActiveLinkGetOwner(GetInsideId());
}

const ARAccessNameType& CARActiveLink::GetLastChanged() const
{
	return CARInside::GetInstance()->alList.ActiveLinkGetModifiedBy(GetInsideId());
}

const char* CARActiveLink::GetChangeDiary() const
{
	return CARInside::GetInstance()->alList.ActiveLinkGetChangeDiary(GetInsideId());
}
