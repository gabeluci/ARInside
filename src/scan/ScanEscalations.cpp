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
#include "ScanEscalations.h"
#include "../ARInside.h"
#include "../core/ARSetFieldHelper.h"

CScanEscalations::CScanEscalations(CAREscalation& escalation)
: escal(escalation)
{
}

CScanEscalations::~CScanEscalations(void)
{
}

void CScanEscalations::Start()
{
	cout << "Checking escalation references";

	CARInside* pInside = CARInside::GetInstance();
	unsigned int escalCount = pInside->escalationList.GetCount();
	for (unsigned int escalIndex = 0; escalIndex < escalCount; ++escalIndex)
	{
		CAREscalation	escal(escalIndex);
		if (pInside->appConfig.bOverlaySupport && !IsVisibleObject(escal))
			continue;

		if (IsOverlayOrCustom(escal))
		{
			pInside->escalationList.AddOverlayOrCustom(escal.GetInsideId());
		}

		CScanEscalations scanEsc(escal);
		scanEsc.Scan();
	}

	cout << endl;
}

void CScanEscalations::Scan()
{
	const ARWorkflowConnectStruct& connectList = escal.GetSchemaList();

	if (connectList.type == AR_WORKFLOW_CONN_SCHEMA_LIST)
	{
		for (unsigned int connectIndex = 0; connectIndex < connectList.u.schemaList->numItems; ++connectIndex)
		{
			CARSchema schema(connectList.u.schemaList->nameList[connectIndex]);
			if (schema.Exists())
			{
				schema.AddEscalation(escal);
			}
		}
	}

	ScanActions(escal.GetIfActions(), IES_IF);
	ScanActions(escal.GetElseActions(), IES_ELSE);
}

void CScanEscalations::ScanActions(const ARFilterActionList& actions, IfElseState ifElse)
{
	for (unsigned int actionIndex = 0; actionIndex < actions.numItems; ++actionIndex)
	{
		switch (actions.actionList[actionIndex].action)
		{
		case AR_FILTER_ACTION_FIELDS:
			{
				const ARSetFieldsActionStruct& setFieldAction = actions.actionList[actionIndex].u.setFields;

				const ARWorkflowConnectStruct &wfConnList = this->escal.GetSchemaList();
				if (wfConnList.type == AR_WORKFLOW_CONN_SCHEMA_LIST && wfConnList.u.schemaList->numItems > 0)
				{
					// we simply use the first schema here, thats enough
					CARSchema schema(wfConnList.u.schemaList->nameList[0]);
					if (schema.Exists())
					{
						CARSetFieldHelper sfh(*CARInside::GetInstance(), schema, setFieldAction, ifElse, actionIndex);

						SetFieldType sfType = sfh.GetType();
						switch (sfType)
						{
						case SFT_SERVER:
						case SFT_SAMPLEDATA:
							{
								CARSchema readSchema(sfh.GetSchemaName());
								if (readSchema.Exists())
								{
									CRefItem ref(escal, ifElse, actionIndex, REFM_SETFIELDS_FORM);
									if (!readSchema.ReferenceExists(ref))
										readSchema.AddReference(ref);
								}
							}
							break;
						}
					}
				}
			}
			break;
		}
	}	
}
