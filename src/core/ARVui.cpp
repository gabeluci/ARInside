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
#include "ARVui.h"
#include "../lists/ARVUIList.h"
#include "ARProplistHelper.h"

CARVui::CARVui()
: CARServerObject(-1)
{
	vuiList = NULL;
	vuiIndex = -1;
}

// TODO: write a description about how to use both types of calling this constructor
CARVui::CARVui(unsigned int SchemaInsideId, unsigned int vuiId, int SchemaVuiIndex)
: CARServerObject(vuiId), schema(SchemaInsideId)
{
	if (!schema.Exists())
	{
		insideId = -1;
		vuiIndex = -1;
		vuiList = NULL;
		return;
	}

	// look up and store the vui index for faster access	
	vuiList = schema.GetVUIs();

	// if the vui is accessed via SchemaVuiIndex (and has a valid range) .. use it
	if (vuiId == 0 && SchemaVuiIndex >= 0 && (unsigned int)SchemaVuiIndex < vuiList->GetCount())
	{
		vuiIndex = SchemaVuiIndex;
		insideId = GetId();
	}
	// ok ... accessing by vuiId ... look up the index
	else if (vuiId > 0)
	{
		vuiIndex = vuiList->Find(vuiId);
	}
	// default .. this could be a out of bounds. the caller should know what to do!
	else
	{
		vuiIndex = SchemaVuiIndex;
	}
}

// this searches for a VUI with the specified label
CARVui::CARVui(unsigned int schemaInsideId, const string& vuiLabel)
: CARServerObject(-1), schema(schemaInsideId)
{
	if (!schema.Exists())
	{
		insideId = -1;
		vuiIndex = -1;
		vuiList = NULL;
		return;
	}

	// look up and store the vui index for faster access	
	vuiList = schema.GetVUIs();

	for (unsigned int vuiPos = 0; vuiPos < vuiList->GetCount(); ++vuiPos)
	{
		ARValueStruct* val = CARProplistHelper::Find(vuiList->VUIGetDisplayProps(vuiPos), AR_DPROP_LABEL);
		if (val != NULL && val->dataType == AR_DATA_TYPE_CHAR && vuiLabel == val->u.charVal)
		{
			vuiIndex = vuiPos;
			insideId = GetId();
			break;
		}
	}	
}

CARVui::~CARVui(void)
{
}

bool CARVui::Exists() const
{
	return (vuiIndex >= 0 && (unsigned int)vuiIndex < vuiList->GetCount() && insideId > 0);
}

bool CARVui::IsClonable() const
{
	return true;
}

CARServerObject* CARVui::Clone() const
{
	return new CARVui(*this);
}

string CARVui::webAlias()
{
	try
	{
		const ARPropList& propList = GetDisplayProps();

		for(unsigned int i=0; i< propList.numItems; ++i)
		{
			if (propList.props[i].prop == AR_OPROP_VIEW_LABEL_WEB_ALIAS &&
			    propList.props[i].value.dataType == AR_DATA_TYPE_CHAR)
			{
				return propList.props[i].value.u.charVal;
			}
		}
	}
	catch(exception& e)
	{
		cout << "EXCEPTION enumerating view web alias: " << e.what() << endl;
	}
	return "";
}


string CARVui::Label()
{
	stringstream strm;
	strm.str("");

	try
	{
		const ARPropList& propList = GetDisplayProps();

		for(unsigned int i=0; i< propList.numItems; ++i)
		{
			if (propList.props[i].prop == AR_DPROP_LABEL &&
			    propList.props[i].value.dataType == AR_DATA_TYPE_CHAR)
			{
				return propList.props[i].value.u.charVal;
			}
		}
	}
	catch(exception& e)
	{
		cout << "EXCEPTION enumerating view label: " << e.what() << endl;
	}

	return strm.str();
}

string CARVui::GetName()
{
	return vuiList->VUIGetName(vuiIndex);
}

string CARVui::GetName() const
{
	return vuiList->VUIGetName(vuiIndex);
}

string CARVui::GetNameFirstChar()
{
	return CARObject::GetNameFirstChar(vuiList->VUIGetName(vuiIndex));
}

bool CARVui::NameStandardFirstChar()
{
	return CARObject::NameStandardFirstChar(GetNameFirstChar());
}

const char* CARVui::GetHelpText() const
{
	return vuiList->VUIGetHelptext(vuiIndex);
}

ARTimestamp CARVui::GetTimestamp() const
{
	return vuiList->VUIGetTimestamp(vuiIndex);
}

const ARAccessNameType& CARVui::GetOwner() const
{
	return vuiList->VUIGetOwner(vuiIndex);
}

const ARAccessNameType& CARVui::GetLastChanged() const
{
	return vuiList->VUIGetModifiedBy(vuiIndex);
}

const char* CARVui::GetChangeDiary() const
{
	return vuiList->VUIGetChangeDiary(vuiIndex);
}

const ARPropList& CARVui::GetPropList() const
{
	return vuiList->VUIGetPropList(vuiIndex);
}

ARInternalId CARVui::GetId()
{
	return vuiList->VUIGetId(vuiIndex);
}

const ARLocaleType& CARVui::GetLocale() const
{
	return vuiList->VUIGetLocale(vuiIndex);
}

int CARVui::GetType()
{
	return vuiList->VUIGetType(vuiIndex);
}

const ARPropList& CARVui::GetDisplayProps() const
{
	return vuiList->VUIGetDisplayProps(vuiIndex);
}

const CARSchema& CARVui::GetSchema() const
{
	return this->schema;
}
