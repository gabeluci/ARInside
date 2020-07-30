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
#include "DocBase.h"
#include "../core/ARProplistHelper.h"
#include "../core/ARVui.h"

class CDocVuiDetails :
	public CDocBase, public CARProplistHelper::CARPropertyCallback
{
public:
	CDocVuiDetails(unsigned int SchemaInsideId, const CARVui& vuiObj, int rootLevel);
	~CDocVuiDetails(void);

	void Documentation();

	// CARPropertyCallback implementation
	bool SpecialPropertyCallback(ARULong32 propId, const ARValueStruct& value, string &displayValue);

private:
	CARSchema schema;
	CARVui vui;

	CTable FieldProperties();
	void FieldPropertiesCsv();
};
