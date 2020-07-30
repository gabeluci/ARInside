//Copyright (C) 2011 John Luthgers | jls17
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
#include "ScanFields.h"
#include "../ARInside.h"
#include "../core/ARQualification.h"
#include "../doc/DocFieldDetails.h"

CScanFields::CScanFields()
{
}

CScanFields::~CScanFields(void)
{
}

//Find references at startup
//This function is necessary because when we would try to add the reference at runtime for example
//Columns might be enumerated at a time when the datafield has been already saved to html file
void CScanFields::Start(CARField &field)
{
	CARInside *arIn = CARInside::GetInstance();

	try
	{
		int rootLevel = 2;

		stringstream strm;
		strm.str("");

		// global field list generation
		int fieldId = field.GetFieldId();

		if (fieldId >= 1000000 && fieldId < 2000000)
		{
			arIn->globalFieldList.push_back(CARGlobalField(field));
		}


		const ARFieldLimitStruct& objLimits = field.GetLimits();
		switch(objLimits.dataType)
		{		
		case AR_DATA_TYPE_COLUMN: //Find column references
			{
				const ARColumnLimitsStruct& fLimit = objLimits.u.columnLimits;

				// To create a link to the datafield we need to find the schema used by the column
				CARField  columnSource;			    // field within the source schema
				//string    columnSourceSchema;   // the name of the columns source form

				// now get source datafield (and the schema as well)
				CDocFieldDetails::GetColumnSourceField(field, columnSource, NULL /*columnSourceSchema*/);

				if (columnSource.Exists())
				{
					// if the columns source field exists, create a link (in the workflow references list) from the source field to the current column
					CRefItem refItem(field, 0, fLimit.parent, REFM_TABLEFIELD_COLUMN);
					arIn->AddFieldReference(columnSource.GetSchema().GetInsideId(), columnSource.GetInsideId(), refItem);
				}
			}
			break;
		case AR_DATA_TYPE_TABLE:
			{
				const ARTableLimitsStruct& fLimit = objLimits.u.tableLimits;

				string tableSchema;                    // the name of table source form

				tableSchema = fLimit.schema;

				if (!tableSchema.empty() && tableSchema[0] == '$')
					tableSchema = fLimit.sampleSchema;

				if (tableSchema.compare(AR_CURRENT_SCHEMA_TAG) == 0)
					tableSchema = field.GetSchema().GetARName();

						// now get the table source form (if exists)
				CARSchema tableSourceSchema(tableSchema);

				if (tableSourceSchema.Exists() && fLimit.qualifier.operation != AR_COND_OP_NONE)
				{		
					stringstream strmQuery;
					CRefItem refItem(field, REFM_TABLEFIELD_QUALIFICATION);
					int pFormId = field.GetSchema().GetInsideId();
					int sFormId = tableSourceSchema.GetInsideId();

					CARQualification arQual(*arIn, refItem, pFormId, sFormId, rootLevel);
					arQual.CheckQuery(&fLimit.qualifier, strmQuery);
				}
			}
			break;
		case AR_DATA_TYPE_CHAR:
			{
				const ARCharLimitsStruct& fLimit = objLimits.u.charLimits;
				if (fLimit.charMenu[0] != 0 && strncmp(fLimit.charMenu, "$NULL$", AR_MAX_NAME_SIZE) != 0)
				{
					CARCharMenu menu(fLimit.charMenu);

					CRefItem refItem(field, REFM_FIELD_CHARMENU);
					arIn->AddMenuReference(fLimit.charMenu, refItem);
				}
			}
			break;
		}
	}
	catch(exception& e)
	{
		cout << "EXCEPTION CScanFields::Start: " << e.what() << endl;
	}
}
