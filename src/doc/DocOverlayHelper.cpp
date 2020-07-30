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

#include "stdafx.h"
#include "DocOverlayHelper.h"
#include "../core/ARServerObject.h"
#include "../output/ObjNotFound.h"
#include "../output/URLLink.h"
#include "../ARInside.h"

CDocOverlayHelper::CDocOverlayHelper(const CARServerObject &srvObj, int rootLevel)
: m_Object(srvObj) , rootLevel(rootLevel)
{
	pInside = CARInside::GetInstance();
	m_OverlayType = m_Object.GetOverlayType();
}


bool CDocOverlayHelper::IsOverlayOrCustom()
{
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_764
	if ((m_OverlayType & AR_CUSTOM_OBJECT) || (m_OverlayType & AR_OVERLAY_OBJECT))
	{
		return true;
	}
#endif
	return false;
}

string CDocOverlayHelper::PlaceOverlayLink()
{
	const char* missing_note = "object missing";
	
	OverlayLinkDirection dir;
	if (m_OverlayType & AR_OVERLAY_OBJECT)
	{
		dir = DOWN;
	}
	else if (m_OverlayType & AR_OVERLAID_OBJECT)
	{
		dir = UP;
	}
	else
	{
		return "";
	}

	auto_ptr<CARServerObject> target(GetNextObject(dir));
	
	// if there is no target object found .. leave the function
	if (target.get() == NULL)
		return "";

	switch (m_OverlayType)
	{
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_764
	case AR_OVERLAID_OBJECT:
		{
			stringstream tmpStrm;
			tmpStrm << "Overlay: ";
			if (target->Exists())
				tmpStrm << URLLink(*target, rootLevel, false);
			else
			{
				ObjNotFound notFound(tmpStrm);
				notFound << missing_note;
				notFound.End();
			}
			return tmpStrm.str();
		}
		break;
	case AR_OVERLAY_OBJECT:
		{
			stringstream tmpStrm;
			tmpStrm << "Based on: ";
			if (target->Exists())
				tmpStrm << URLLink(*target, rootLevel, false);
			else
			{
				ObjNotFound notFound(tmpStrm);
				notFound << missing_note;
				notFound.End();
			}
			return tmpStrm.str();
		}
		break;
#endif
	default:
		return "";
	}
}

string CDocOverlayHelper::PlaceOverlaidNotice()
{
	if (!(pInside->overlayMode == 1 && m_OverlayType == AR_OVERLAID_OBJECT))
		return "";

	auto_ptr<CARServerObject> target(GetNextObject(UP));

	stringstream tmp;

	tmp << "<div id=\"ovlNote\">" << endl;
	tmp << "This object is currently not executed/used because it is overlaid by ";
	if (target.get() != NULL && target->Exists())
		tmp << URLLink(*target, rootLevel, false);
	else
	{
		ObjNotFound notFound(tmp);
		notFound << "object missing";
		notFound.End();
	}
	
	tmp << "</div>";

	return tmp.str();
}

CARServerObject* CDocOverlayHelper::GetNextObject(OverlayLinkDirection direction)
{
	const CARServerObject* workObject = &m_Object;
	int objectType = workObject->GetServerObjectTypeXML();
	
	if (objectType == AR_STRUCT_ITEM_XML_FIELD)
	{
		const CARField& field = static_cast<const CARField&>(m_Object);
		workObject = &field.GetSchema();
	}
	else if (objectType == AR_STRUCT_ITEM_XML_VUI)
	{			
		const CARVui& vui = static_cast<const CARVui&>(m_Object);
		workObject = &vui.GetSchema();
	}

	if (workObject == NULL || !workObject->Exists())
		return NULL;
	
	// now get the corresponding object name in the needed direction
	string correspondingName;

	if (direction == UP && (m_OverlayType & AR_OVERLAID_OBJECT))
	{
		correspondingName = workObject->GetOverlayName();
	}
	else if (direction == DOWN && (m_OverlayType & AR_OVERLAY_OBJECT))
	{
		correspondingName = workObject->GetOverlayBaseName();
	}
	else
	{
		// in this case the object is not overlaid in this direction
		// and thus there is no object available
		return NULL;
	}

	switch (objectType)
	{
	case AR_STRUCT_ITEM_XML_SCHEMA:
		{
			return new CARSchema(correspondingName);
		}
	case AR_STRUCT_ITEM_XML_FIELD:
		{
			CARSchema schema(correspondingName);
			if (schema.Exists())
			{
				return new CARField(schema.GetInsideId(), m_Object.GetInsideId());
			}
			break;
		}
	case AR_STRUCT_ITEM_XML_VUI:
		{
			CARSchema schema(correspondingName);
			if (schema.Exists())
			{
				return new CARVui(schema.GetInsideId(), m_Object.GetInsideId());
			}
			break;
		}
	case AR_STRUCT_ITEM_XML_ACTIVE_LINK:
		{
			return new CARActiveLink(correspondingName);
		}
	case AR_STRUCT_ITEM_XML_FILTER:
		{
			return new CARFilter(correspondingName);
		}
	case AR_STRUCT_ITEM_XML_ESCALATION:
		{
			return new CAREscalation(correspondingName);
		}
	case AR_STRUCT_ITEM_XML_CHAR_MENU:
		{
			return new CARCharMenu(correspondingName);
		}
	case AR_STRUCT_ITEM_XML_CONTAINER:
		{
			return new CARContainer(correspondingName);
		}
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_750
	case AR_STRUCT_ITEM_XML_IMAGE:
		{
			return new CARImage(correspondingName);
		}
#endif
	default:
#if _DEBUG
		cerr << "object type " << objectType << " not supported int GetNextObject" << endl;
#endif
		break;
	}

	// if we get to here, the object is not supported nor found
	return NULL;
}
