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

#pragma once

#include "../ARApi.h"

// forward declarations
class CARServerObject;
class CARInside;

enum OverlayLinkDirection
{
	UP, // goes the object tree one layer UP .. the base layer is level 0
	DOWN // goes the object tree one layer DOWN .. the base layer is level 0
};

class CDocOverlayHelper
{
public:
	CDocOverlayHelper(const CARServerObject& srvObj, int rootLevel);

	bool IsOverlayOrCustom(); // returns true if the object's overlay type is AR_CUSTOM_OBJECT or AR_OVERLAY_OBJECT
	string PlaceOverlayLink();
	string PlaceOverlaidNotice();

	bool IsOriginal() const { return (m_OverlayType & AR_ORIGINAL_OBJECT) != 0; }
	bool IsCustom() const { return (m_OverlayType & AR_CUSTOM_OBJECT) != 0; }

private:
	CARInside* pInside;
	const CARServerObject& m_Object;
	CARServerObject* m_Target;
	int m_OverlayType;
	int rootLevel;

private:
	CARServerObject* GetNextObject(OverlayLinkDirection direction);
};
