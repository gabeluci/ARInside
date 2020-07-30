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
#include "../lists/ARRoleList.h"

class CARRole :
	public CARServerObject
{
public:
	CARRole(int insideId);
	CARRole(int roleId, const string& appName);
	~CARRole(void);

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

	// export typedefs
	typedef CARRoleList::GroupList GroupList;

	// data-access functions
	const string& GetRequestId() const;
	const string& GetApplicationName() const;
	int GetRoleId() const;
	const GroupList& GetGroupsTest() const;
	const GroupList& GetGroupsProd() const;
	ARTimestamp GetCreateDate() const;

	// class type support
	int GetServerObjectTypeXML() const { return AR_STRUCT_ITEM_XML_ROLE; }
	bool IsClonable() const;
	CARServerObject* Clone() const;
};
