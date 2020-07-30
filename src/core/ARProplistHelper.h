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
#include "../output/Table.h"
#include "../output/TableRow.h"

using namespace OUTPUT;

class CARProplistHelper
{
public:
	/// This is a callback interface used to customize the html output of a property list.
	class CARPropertyCallback
	{
	public:
		/** 
		 * <summary>
		 * the following function is called by CARProplistHelper::GetList to allow the caller
		 * to ouput properties in a special format
		 * </summary>
		 * <param name="propId">contains the id of the property (AR_DPROP..., AR_OPROP..., ...)</param>
		 * <param name="value">contains the value of the property</param>
		 * <param name="displayValue">[out] should contain the customized html content of the property</param>
		 * <returns>Return true if the function has customized the current property. <paramref name="displayValue"/>
		 * should contain the output content in this case. Return false if the default output formating of the 
		 * property should take place.</returns>
		 */
		virtual bool SpecialPropertyCallback(ARULong32 propId, const ARValueStruct& value, /* out */ string &displayValue) = 0;
	};

public:
	CARProplistHelper(const ARPropList* propList);
	~CARProplistHelper(void);

	/// Returns the html for a table containing all properties and their values.
	static string GetList(const ARPropList &objPropList, CARPropertyCallback* pcbObj = NULL);
	static string GetLabel(ARULong32 nProp);
	static string GetValue(ARULong32 nProp, const ARValueStruct &arV);
	
	static ARValueStruct* Find(const ARPropList &objPropList, ARULong32 nProp);

	ARValueStruct* GetAndUseValue(ARULong32 nProp);
	ARValueStruct* GetValue(ARULong32 nProp);
	string UnusedPropertiesToHTML(int rootLevel);
	void UnusedPropertiesToHTML(std::ostream& strm, int rootLevel);

private:
	class PropHelpData
	{
	public:
		PropHelpData(void);
		PropHelpData(ARULong32 propId, ARValueStruct* value);
		~PropHelpData(void);

		operator ARULong32() { return pId; }
		friend bool operator<(const PropHelpData &l, const PropHelpData &r) { return l.pId < r.pId; }

		ARULong32       pId;    // property id
		ARValueStruct*  Value;  // value struct
		bool            isUsed; // used flag
	};
	std::vector<PropHelpData> properties;

};
