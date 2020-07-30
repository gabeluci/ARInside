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
#include "../lists/ARMenuList.h"

class CARCharMenu :
	public CARServerObject
{
public:
	CARCharMenu();
	CARCharMenu(int insideId);
	CARCharMenu(const string& name);
	~CARCharMenu(void);

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

	// other data retrieval functions
	const ARNameType& GetARName() const;
	unsigned int GetRefreshCode() const;
	const ARCharMenuStruct& GetDefinition() const;
	const ARPropList& GetPropList() const;

	const string& GetAppRefName() const;
	void SetAppRefName(const string& appName);

	// helpers
	bool IsUsedInWorkflow() const;

	// class type support
	static const unsigned int XmlTypeDef = AR_STRUCT_ITEM_XML_CHAR_MENU ;
	int GetServerObjectTypeXML() const { return XmlTypeDef; }
	bool IsClonable() const;
	CARServerObject* Clone() const;

	// references
	typedef CARMenuList::ReferenceList ReferenceList;
	void AddReference(const CRefItem& refItem);
	bool ReferenceExists(const CRefItem& refItem) const;
	const ReferenceList& GetReferences() const;
};
