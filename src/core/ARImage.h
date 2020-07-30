//Copyright (C) 2009 John Luthgers | jls17
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
#include "ARProplistHelper.h"
#include "../lists/ARImageList.h"

#if AR_CURRENT_API_VERSION >= AR_API_VERSION_750

class CARImageList; // forware declaration

class CARImage :
	public CARServerObject
{
public:
	CARImage();
	CARImage(int insideId) : CARServerObject(insideId) { }
	CARImage(const string& name);
	~CARImage() { }

	bool Exists() const;

	// implement function inherited from CARObject
	string GetName();
	string GetName() const;
	string GetNameFirstChar();
	bool NameStandardFirstChar();

	// implement function inherited from CARServerObject
	const char* GetHelpText() const;
	ARTimestamp GetTimestamp() const;
	const ARAccessNameType& GetOwner() const;
	const ARAccessNameType& GetLastChanged() const;
	const char* GetChangeDiary() const;

	// implement access functions
	char* GetType() const;
	char* GetDescription() const;
	const ARImageDataStruct& GetData() const;
	const ARPropList& GetPropList() const;

	// class type support
	int GetServerObjectTypeXML() const { return AR_STRUCT_ITEM_XML_IMAGE; }
	bool IsClonable() const;
	CARServerObject* Clone() const;

	// referencing functions
	void AddReference(const CRefItem &refItem);
	bool ReferenceExists(const CRefItem &refItem) const;
	const CRefItemList& GetReferences() const;

};

#endif // AR_CURRENT_API_VERSION >= AR_API_VERSION_750
