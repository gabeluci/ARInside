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

#pragma once
#include "ARObject.h"
#include "../output/WebUtil.h"

using namespace OUTPUT;

class CARServerObject : public CARObject
{
public:
	CARServerObject(int insideId) : CARObject(insideId) {}

	virtual bool Exists() const = 0;

	virtual const char* GetHelpText() const = 0;
	virtual ARTimestamp GetTimestamp() const = 0;
	virtual const ARAccessNameType& GetOwner() const = 0;
	virtual const ARAccessNameType& GetLastChanged() const = 0;
	virtual const char* GetChangeDiary() const = 0;
	virtual const ARPropList& GetPropList() const = 0;
	virtual int GetServerObjectTypeXML() const = 0;

	virtual CARServerObject* Clone() const = 0;
	virtual bool IsClonable() const = 0;

	// declarations for overlay support

	virtual int GetOverlayType() const;        // returns the type of the overlay (AR_OVERLAID_OBJECT, AR_OVERLAY_OBJECT, AR_CUSTOM_OBJECT)
	virtual int GetOverlayGroup() const;       // returns the level of the overlay (as of 7.6.04 there are: -1 (base), 0 (overlaid) and 1 (custom/overlay))
	virtual string GetOverlayBaseName() const; // returns the "internal" object name overlayed by the current object
	virtual string GetOverlayName() const;     // returns the "internal" object name, which overlays this object 
};

bool IsVisibleObject(const CARServerObject& obj); // checks if the object is visible; by default overlaid objects are hidden
bool IsOverlayOrCustom(const CARServerObject& obj); // returns true if the object's overlay type is AR_CUSTOM_OBJECT or AR_OVERLAY_OBJECT
