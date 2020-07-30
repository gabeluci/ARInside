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

class CARGroup :
	public CARServerObject
{
public:
	CARGroup(int insideId, int groupId = -1);
	~CARGroup(void);

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

	// data-access functions
	const string& GetRequestId() const;
	const string& GetLongName() const;
	ARULong32 GetGroupId() const;
	int GetType() const;
	int GetCategory() const;
	const string& GetComputedQualification() const;

	// class type support
	int GetServerObjectTypeXML() const { return AR_STRUCT_ITEM_XML_GROUP; }
	bool IsClonable() const;
	CARServerObject* Clone() const;
};
