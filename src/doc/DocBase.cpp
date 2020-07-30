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
#include "DocBase.h"
#include "../output/URLLink.h"
#include "../output/ObjNotFound.h"

CDocBase::CDocBase(void)
{
	this->pInside = CARInside::GetInstance();
}

CDocBase::~CDocBase(void)
{
}

string CDocBase::PlaceOverlayLink(int currentType, CARServerObject& target)
{
	const char* missing_note = "object missing";

	switch (currentType)
	{
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_764
	case AR_OVERLAID_OBJECT:
		{
			stringstream tmpStrm;
			tmpStrm << "Overlay: ";
			if (target.Exists())
				tmpStrm << URLLink(target, rootLevel, false);
			else
			{
				ObjNotFound notFound(tmpStrm);
				notFound << missing_note;
				notFound.End();
				tmpStrm << endl;
			}
			return tmpStrm.str();
		}
		break;
	case AR_OVERLAY_OBJECT:
		{
			stringstream tmpStrm;
			tmpStrm << "Based on: ";
			if (target.Exists())
				tmpStrm << URLLink(target, rootLevel, false);
			else
			{
				ObjNotFound notFound(tmpStrm);
				notFound << missing_note;
				notFound.End();
				tmpStrm << endl;				
			}
			return tmpStrm.str();
		}
		break;
#endif
	default:
		return "";
	}
}
