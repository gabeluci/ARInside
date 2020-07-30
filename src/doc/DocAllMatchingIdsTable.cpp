//Copyright (C) 2014 John Luthgers| jls17
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
//    along with ARInside.  If not, see <http://www.gnu.org/licenses/>.

#include "stdafx.h"
#include "DocAllMatchingIdsTable.h"
#include "../ARInside.h"

CDocAllMatchingIdsTable::CDocAllMatchingIdsTable(const string& targetForm, const string& sourceForm, CARServerObject& obj, AllMatchingMode mode, int nAction, IfElseState ifElse, int rootLevel)
: tableLeftTarget(targetForm), tableRightSource(sourceForm), obj(obj), matchMode(mode), nAction(nAction), ifElse(ifElse), rootLevel(rootLevel)
{
}

std::ostream& CDocAllMatchingIdsTable::ToStream(std::ostream &strm)
{
	try
	{
		CARInside& arIn = *CARInside::GetInstance();
		CARSchema schema1(tableLeftTarget);
		CARSchema schema2(tableRightSource);

		CTable tblListField("tblListMatchingIds", "TblObjectList");
		tblListField.AddColumn(0, "Id");
		tblListField.AddColumn(0, "Field Name");
		tblListField.AddColumn(0, "Value");

		if(schema1.Exists() && schema2.Exists())
		{
			int msgIdTarget = -1;
			int msgIdValue = -1;

			switch (matchMode)
			{
			case AMM_PUSHFIELDS:
				msgIdTarget = REFM_PUSHFIELD_TARGET_MATCHING;
				msgIdValue  = REFM_PUSHFIELD_VALUE_MATCHING;
				break;
			case AMM_SETFIELDS:
				msgIdTarget = REFM_SETFIELDS_TARGET_MATCHING;
				msgIdValue  = REFM_SETFIELDS_VALUE_MATCHING;
				break;
			}

			// Reference object for left field
			CRefItem refItemField1(obj, ifElse, nAction, msgIdTarget);

			// Reference object for right field
			CRefItem refItemField2(obj, ifElse, nAction, msgIdValue);

			// scan the fields
			unsigned int fieldCount1 = schema1.GetFields()->GetCount();
			for(unsigned int fieldIndex1 = 0; fieldIndex1 < fieldCount1; ++fieldIndex1)
			{
				CARField tmpField1(schema1.GetInsideId(), 0, fieldIndex1);

				if (tmpField1.GetDataType() <= AR_MAX_STD_DATA_TYPE)
				{
					CARField tmpField2(schema2.GetInsideId(), tmpField1.GetFieldId());

					if(tmpField2.Exists() && tmpField2.GetDataType() <= AR_MAX_STD_DATA_TYPE)
					{
						// add reference for left field
						arIn.AddFieldReference(schema1.GetInsideId(), tmpField1.GetInsideId(), refItemField1);
						
						// add reference for right field
						arIn.AddFieldReference(schema2.GetInsideId(), tmpField2.GetInsideId(), refItemField2);

						//Matching ID
						CTableRow row("cssStdRow");		
						row.AddCell(CTableCell(tmpField1.GetFieldId()));
						row.AddCell(CTableCell(arIn.LinkToField(schema1.GetInsideId(), tmpField1.GetInsideId(), rootLevel)));
						row.AddCell(CTableCell(arIn.LinkToField(schema2.GetInsideId(), tmpField2.GetInsideId(), rootLevel)));
						tblListField.AddRow(row);
					}
				}
			}
		}

		strm << tblListField;
	}
	catch(exception& e)
	{
		cout << "EXCEPTION in AllMatchingIds of " << tableLeftTarget << ", " << tableRightSource << ": " << e.what() << endl;
	}

	return strm;
}
