//Copyright (C) 2012 John Luthgers | jls17
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
#include "ARSetFieldHelper.h"

CARSetFieldHelper::CARSetFieldHelper(CARInside &arInside, const CARSchema& wfConnectedSchema, const ARSetFieldsActionStruct& sFieldStruct, IfElseState ifElseMode, int numAction)
: arIn(arInside), connectedSchema(wfConnectedSchema), setFieldsStruct(sFieldStruct), ifElse(ifElseMode)
{
	nAction = numAction;

	serverFromFieldId = 0;
	schemaFromFieldId = 0;
	qualifier = NULL;
	noMatchValue = 0;
	multiMatchValue = 0;
	type = SFT_CURRENT;
	filterApiInputValues = NULL;
	filterApiInputNumItems = 0;

	Parse();
}

CARSetFieldHelper::~CARSetFieldHelper(void)
{
}

void CARSetFieldHelper::Parse()
{
	for(unsigned int i=0; i < setFieldsStruct.fieldList.numItems; ++i)
	{
		if (this->CheckAssignment(setFieldsStruct.fieldList.fieldAssignList[i].assignment))
			return;
	}

	type = SFT_CURRENT;
	schemaName = this->connectedSchema.GetName();
}

bool CARSetFieldHelper::CheckAssignment(const ARAssignStruct &assignment)
{
	try
	{
		switch(assignment.assignType)
		{
		case AR_ASSIGN_TYPE_FIELD:
			{
				if((assignment.u.field->schema[0] == '@' ||  // AR_CURRENT_SCHEMA_TAG
				    assignment.u.field->schema[0] == '*') && // AR_CURRENT_SCREEN_TAG / AR_CURRENT_TRAN_TAG
				    assignment.u.field->schema[1] == 0)
				{
					// if this assignment uses a field from current screen, we are not interested
					return false;
				}

				if ((assignment.u.field->server[0] == '$' && assignment.u.field->server[1] != 0 ||
					   assignment.u.field->server[0] == '@' && assignment.u.field->server[1] == 0) &&
					   assignment.u.field->schema[0] == '$' && assignment.u.field->schema[1] != 0)
				{
					type = SFT_SAMPLEDATA;
					
					this->serverFromFieldId = atoi(&assignment.u.field->server[1]);
					this->schemaFromFieldId = atoi(&assignment.u.field->schema[1]);

					this->serverName = setFieldsStruct.sampleServer;
					this->schemaName = setFieldsStruct.sampleSchema;
				}
				else
				{
					type = SFT_SERVER;

					this->serverName = assignment.u.field->server;
					this->schemaName = assignment.u.field->schema;
				}

				noMatchValue = assignment.u.field->noMatchOption;
				multiMatchValue = assignment.u.field->multiMatchOption;

				qualifier = &assignment.u.field->qualifier;

				return true;
			}
		case AR_ASSIGN_TYPE_ARITH:
			{			
				switch (assignment.u.arithOp->operation) 
				{
				case AR_ARITH_OP_ADD:			
				case AR_ARITH_OP_SUBTRACT:						
				case AR_ARITH_OP_MULTIPLY:						
				case AR_ARITH_OP_DIVIDE:						
				case AR_ARITH_OP_MODULO:						
					if (CheckAssignment(assignment.u.arithOp->operandLeft)) return true;
					if (CheckAssignment(assignment.u.arithOp->operandRight)) return true;
					break;
				case AR_ARITH_OP_NEGATE:						
					if (CheckAssignment(assignment.u.arithOp->operandRight)) return true;
					break;
				}

			}
			break;
		case AR_ASSIGN_TYPE_FUNCTION:
			{
				for(unsigned int i=0; i< assignment.u.function->numItems; ++i)
				{
					if (CheckAssignment(assignment.u.function->parameterList[i]))
						return true;
				}
			}
			break;
		case AR_ASSIGN_TYPE_SQL:
			{
				type = SFT_SQL;

				sqlCommand = assignment.u.sql->sqlCommand;
				serverName = assignment.u.sql->server;

				noMatchValue = assignment.u.sql->noMatchOption;
				multiMatchValue = assignment.u.sql->multiMatchOption;
				return true;
			}
		case AR_ASSIGN_TYPE_FILTER_API:
			{
				// Note: serviceName can hold a fieldId which is used to read the plugin-name from.
				// TODO: add a reference to this field later.
				if (strcmp(assignment.u.filterApi->serviceName, "ARSYS.ARF.WEBSERVICE")==0)
				{
					type = SFT_WEBSERVICE;
				}
				// TODO: add support for SFT_ATRIUM_ORCHESTRATOR
				else 
				{
					type = SFT_FILTERAPI;
				}
				filterApiInputValues = assignment.u.filterApi->inputValues;
				filterApiInputNumItems = assignment.u.filterApi->numItems;
				this->schemaName = assignment.u.filterApi->serviceName;
				return true;
			}
		}	
	}
	catch(exception& e)
	{
		cout << "EXCEPTION in CARSetFieldHelper::CheckAssignment: " << e.what() << endl;
	}
	return false;
}

SetFieldType CARSetFieldHelper::GetType()
{
	return type;
}

const string& CARSetFieldHelper::GetServerName() const
{
	return serverName;
}

const string& CARSetFieldHelper::GetSchemaName() const
{
	return schemaName;
}

int CARSetFieldHelper::GetServerFieldId()
{
	return serverFromFieldId;
}

int CARSetFieldHelper::GetSchemaFieldId()
{
	return schemaFromFieldId;
}

int CARSetFieldHelper::GetNoMatchOption()
{
	return noMatchValue;
}

int CARSetFieldHelper::GetMultiMatchOption()
{
	return multiMatchValue;
}

ARQualifierStruct* CARSetFieldHelper::GetQualifier()
{
	return qualifier;
}

const string& CARSetFieldHelper::GetSqlCommand() const
{
	return sqlCommand;
}

int CARSetFieldHelper::GetFilterAPINumItems() const
{
	return filterApiInputNumItems;
}

const ARAssignStruct* CARSetFieldHelper::GetFilterAPIInputs() const
{
	return filterApiInputValues;
}
