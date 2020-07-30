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
#include "ARServerObject.h"
#include "ARSchema.h"

class CARVui :
	public CARServerObject
{
public:
	CARVui();
	CARVui(unsigned int schemaInsideId, unsigned int vuiId, int SchemaVuiIndex = -1);
	CARVui(unsigned int schemaInsideId, const std::string& vuiLabel);
	~CARVui(void);

	bool Exists() const;

	// implement functions inherited from CARObject
	string GetName();
	string GetName() const;
	string GetNameFirstChar();
	bool NameStandardFirstChar();

	// implement functions inherited from CARServerObject
	const char* GetHelpText() const;
	ARTimestamp GetTimestamp() const;
	const ARAccessNameType& GetOwner() const;
	const ARAccessNameType& GetLastChanged() const;
	const char* GetChangeDiary() const;
	const ARPropList& GetPropList() const;

	// other data access functions
	ARInternalId GetId();
	const ARLocaleType& GetLocale() const;
	int GetType();
	const ARPropList& GetDisplayProps() const;
	const CARSchema& GetSchema() const;

	// some helpers
	string Label();
	string webAlias();

	// class type support
	int GetServerObjectTypeXML() const { return AR_STRUCT_ITEM_XML_VUI; }
	bool IsClonable() const;
	CARServerObject* Clone() const;

private:
	CARSchema schema;
	CARVUIList *vuiList;
	int vuiIndex;
};
