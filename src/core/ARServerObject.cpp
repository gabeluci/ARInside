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
#include "ARServerObject.h"
#include "../output/WebUtil.h"
#include "../ARInside.h"

using namespace OUTPUT;

int CARServerObject::GetOverlayType() const
{
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_764
	if (CARInside::GetInstance()->appConfig.bOverlaySupport)
	{
		ARValueStruct* overlayProp = CARProplistHelper::Find(GetPropList(), AR_SMOPROP_OVERLAY_PROPERTY);
		if (overlayProp != NULL && overlayProp->dataType == AR_DATA_TYPE_INTEGER)
		{
			return overlayProp->u.intVal;
		}
	}
#endif
	return 0; // AR_ORIGINAL_OBJECT
}

int CARServerObject::GetOverlayGroup() const
{
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_764
	if (CARInside::GetInstance()->appConfig.bOverlaySupport)
	{
		ARValueStruct* overlayProp = CARProplistHelper::Find(GetPropList(), AR_SMOPROP_OVERLAY_GROUP);
		if (overlayProp != NULL && overlayProp->dataType == AR_DATA_TYPE_INTEGER)
		{
			return overlayProp->u.intVal;
		}
	}
#endif
	return -1; // No Overlay Group / Base
}

// NOTE: those functions couldn't be used for sub-objects like fields or views.
string CARServerObject::GetOverlayBaseName() const
{
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_764
	return GetName() + (CARInside::GetInstance()->overlayMode == 1 ? AR_RESERV_OVERLAY_STRING : "");
#else
	return "";
#endif
}

string CARServerObject::GetOverlayName() const
{
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_764
	return GetName() + (CARInside::GetInstance()->overlayMode == 0 ? AR_RESERV_OVERLAY_STRING : "");
#else
	return "";
#endif
}

// ===== IsVisibleObject =====
// This function checks if a object should be visible on lists and such.
// Normally overlaid objects are hidden on lists (e.g. list of all actlinks). Because those objects
// aren't executed it's not helpful to have those on board.
// With the servers OverlayMode-property you can define up to which layer workflow is executed.
// The default value is 1 (as of ARS 7.6.04) and means all objects of layer 0 (base-layer) and 1
// (custom/overlay) are executed, except those of layer 0 which are overlaid by objects in layer 1.
// On the other hand, if you set OverlayMode to 0, only objects of layer 0 are executed. In that
// case ARInside will hide all objects of layer 1.
// 
bool IsVisibleObject(const CARServerObject& obj)
{
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_764
	int overlayType = obj.GetOverlayType();
	CARInside* pInside = CARInside::GetInstance();

	if (pInside->overlayMode == 1 && overlayType == AR_OVERLAID_OBJECT)
		// if the server has overlayMode enabled and the current object is overlaid, dont show it on the list
		return false;

	if (pInside->overlayMode == 0 && (overlayType == AR_OVERLAY_OBJECT || overlayType == AR_CUSTOM_OBJECT))
		// if the serve has overlayMode disabled and the current object is a overlay or custom, hide it.
		return false;
#endif
	return true;
}

bool IsOverlayOrCustom(const CARServerObject& obj)
{
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_764
	// TODO: 
	// We check directly for overlay or custom, but overlayType is a bitmask, and with more
	// overlay layers in mind, the overlayType of an object could be:
	//   AR_CUSTOM_OBJECT | AR_OVERLAID_OBJECT
	// ARInside has to be able to deal with such situations, but currently it isn't.
	int overlayType = obj.GetOverlayType();
	if ((overlayType & AR_CUSTOM_OBJECT) || (overlayType & AR_OVERLAY_OBJECT))
	{
		return true;
	}
#endif
	return false;
}
