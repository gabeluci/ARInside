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
#include "../lists/ARUserList.h"

class CARUser :
	public CARServerObject
{
public:
	CARUser(int insideId);
	CARUser(const string& userName);
	~CARUser(void);

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

	// needed typedefs
	typedef CARUserList::GroupList GroupList;

	// data-access functions
	const string& GetRequestId() const;
	const string& GetEmail() const;
	const GroupList& GetGroups() const;
	const string& GetFullName() const;
	int GetDefaultNotify() const;
	int GetLicenseType() const;
	int GetFTLicenseType() const;
	ARTimestamp GetCreateDate() const;

	// class type support
	int GetServerObjectTypeXML() const { return AR_STRUCT_ITEM_XML_USER; }
	bool IsClonable() const;
	CARServerObject* Clone() const;
};
