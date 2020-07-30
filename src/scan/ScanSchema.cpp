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
#include "ScanSchema.h"
#include "../ARInside.h"
#include "ScanFields.h"

CScanSchema::CScanSchema(CARSchema& schema)
: schema(schema)
{
}

CScanSchema::~CScanSchema(void)
{
}

void CScanSchema::Start()
{
	try
	{
		cout << "Checking field references [";

		CARInside* pInside = CARInside::GetInstance();
		unsigned int schemaCount = pInside->schemaList.GetCount();
		for (unsigned int schemaIndex = 0; schemaIndex < schemaCount; ++schemaIndex)
		{			
			CARSchema schema(schemaIndex);
			if (pInside->appConfig.bOverlaySupport && !IsVisibleObject(schema))
				continue;

			if (IsOverlayOrCustom(schema))
			{
				pInside->schemaList.AddOverlayOrCustom(schema.GetInsideId());
			}

			CScanSchema scanSchema(schema);
			scanSchema.Scan();
		}

		cout << "]" << endl;
	}
	catch(exception& e)
	{
		cout << "EXCEPTION SearchCustomFieldReferences: " << e.what() << endl;
	}
}

void CScanSchema::Scan()
{
	unsigned int fieldCount = schema.GetFields()->GetCount();
	for (unsigned int fieldIndex = 0; fieldIndex < fieldCount; ++fieldIndex)
	{
		CARField field(schema.GetInsideId(), 0, fieldIndex);
		CScanFields scanFld;
		scanFld.Start(field);
	}

	ScanAuditReference();
	cout << ".";
}

void CScanSchema::ScanAuditReference()
{
	if (CARInside::GetInstance()->CompareServerVersion(7,0) < 0) return;

	const ARAuditInfoStruct &audit = schema.GetAuditInfo();
	if (audit.style != AR_AUDIT_NONE && audit.formName[0] != 0)
	{
		CARSchema auditForm(audit.formName);
		if (auditForm.Exists())
		{
			CRefItem refItem(schema, REFM_SCHEMA_AUDIT_SOURCE);
			auditForm.AddReference(refItem);
		}
	}
}
