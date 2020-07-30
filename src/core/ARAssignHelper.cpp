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

#include "stdafx.h"
#include "ARAssignHelper.h"
#include "../doc/DocCurrencyField.h"
#include "../doc/DocStatusHistoryField.h"
#include "../output/URLLink.h"
#include "../util/Context.h"

CARAssignHelper::CARAssignHelper(CARInside& arIn, int rootLevel, const CARServerObject &obj, const CARSchema& schema1, const CARSchema& schema2)
{
	this->arIn = &arIn;
	this->object = obj.Clone();
	this->schemaInsideId1 = schema1.GetInsideId();
	this->schemaInsideId2 = schema2.GetInsideId();
	this->rootLevel = rootLevel;
	this->pushFieldFlag = false;
}

CARAssignHelper::CARAssignHelper(CARInside &arIn, int rootLevel, const CARServerObject &obj, int schemaId1, int schemaId2)
{
	this->arIn = &arIn;
	this->object = obj.Clone();
	this->schemaInsideId1 = schemaId1;
	this->schemaInsideId2 = schemaId2;
	this->rootLevel = rootLevel;
	this->pushFieldFlag = false;
}

CARAssignHelper::CARAssignHelper(CARInside &arIn, int rootLevel, const CARServerObject &obj, const std::string &schemaName1, const std::string &schemaName2)
{
	CARSchema schema1(schemaName1);
	CARSchema schema2(schemaName2);

	this->arIn = &arIn;
	this->object = obj.Clone();
	this->schemaInsideId1 = schema1.GetInsideId();
	this->schemaInsideId2 = schema2.GetInsideId();
	this->rootLevel = rootLevel;
	this->pushFieldFlag = false;
}

CARAssignHelper::CARAssignHelper(MappingContext &context)
{
	this->arIn = &context.getInside();
	this->object = context.getCurrentObject().Clone();
	this->schemaInsideId1 = context.getCurrentSchemaId();
	this->schemaInsideId2 = context.getSecondarySchemaId();
	this->rootLevel = context.getRootLevel();
	this->pushFieldFlag = false;
}

CARAssignHelper::~CARAssignHelper(void)
{
	if (this->object != NULL)
		delete object;
}


string CARAssignHelper::PushFieldsAssignment(const ARPushFieldsActionStruct &action, int nAction, IfElseState ifElse)
{
	this->mode = AM_PUSHFIELD;

	stringstream strm;
	strm.str("");
	try
	{
		CTable tblFieldList("pushFieldsList", "TblObjectList");
		tblFieldList.AddColumn(30, "Field Name");
		tblFieldList.AddColumn(70, "Value");
		this->pushFieldFlag = true;

		for(unsigned int i=0; i< action.pushFieldsList.numItems; i++)
		{
			int nTargetFieldId = action.pushFieldsList.pushFieldsList[i].field.u.fieldId;

			//Add a reference to the target field 
			CRefItem refTarget(*this->object, ifElse, nAction, REFM_PUSHFIELD_TARGET);
			arIn->AddFieldReference(this->schemaInsideId2, nTargetFieldId, refTarget);

			CRefItem refValue(*this->object, ifElse, nAction, REFM_PUSHFIELD_VALUE);

			stringstream assignText;
			CheckAssignment(nTargetFieldId, NULL, ifElse, nAction, action.pushFieldsList.pushFieldsList[i].assign, assignText, refValue);

			CTableRow row("cssStdRow");
			row.AddCell(CTableCell(arIn->LinkToField(schemaInsideId2, nTargetFieldId, rootLevel)));
			row.AddCell(CTableCell(assignText.str()));
			tblFieldList.AddRow(row);	
		}

		strm << tblFieldList;
	}
	catch(exception& e)
	{
		cout << "EXCEPTION PushFieldsAssignment of '" << this->object->GetName() << "':" << e.what() << endl;
	}

	return strm.str();
}

string CARAssignHelper::SetFieldsAssignment(const ARSetFieldsActionStruct &action, int nAction, IfElseState ifElse)
{
	this->mode = AM_SETFIELDS;

	stringstream strm;
	strm.str("");
	try
	{
		CTable tblFieldList("setFieldsList", "TblObjectList");
		tblFieldList.AddColumn(30, "Field Name");
		tblFieldList.AddColumn(70, "Value");

		for(unsigned int i=0; i< action.fieldList.numItems; i++)
		{
			int nTargetFieldId = action.fieldList.fieldAssignList[i].fieldId;

			//Add a reference to the target field 
			CRefItem refTarget(*this->object, ifElse, nAction, REFM_SETFIELDS_TARGET);
			arIn->AddFieldReference(this->schemaInsideId1, nTargetFieldId, refTarget);

			CRefItem refValue(*this->object, ifElse, nAction, REFM_SETFIELDS_VALUE);

			stringstream assignText;		
			CheckAssignment(nTargetFieldId, NULL, ifElse, nAction, action.fieldList.fieldAssignList[i].assignment, assignText, refValue);

			CTableRow row("cssStdRow");
			row.AddCell(CTableCell(arIn->LinkToField(schemaInsideId1, nTargetFieldId, rootLevel)));
			row.AddCell(CTableCell(assignText.str()));
			tblFieldList.AddRow(row);	
		}

		strm << tblFieldList;
	}
	catch(exception& e)
	{
		cout << "EXCEPTION SetFieldsAssignment of '" << this->object->GetName() << "': " << e.what() << endl;
	}

	return strm.str();
}

string CARAssignHelper::OpenWindowAssignment(const ARFieldAssignList &action, int nAction, IfElseState ifElse, OpenWindowMode openCloseInfo)
{
	this->mode = AM_OPENWINDOW;

	stringstream strm;
	strm.str("");
	try
	{
		CTable tblFieldList("setFieldsList", "TblObjectList");
		tblFieldList.AddColumn(30, "Field Name");
		tblFieldList.AddColumn(70, "Value");

		for(unsigned int i=0; i< action.numItems; i++)
		{
			int nTargetFieldId = action.fieldAssignList[i].fieldId;

			if (nTargetFieldId == AR_SET_DEFAULTS_ID)
				continue;

			//Add a reference to the target field 
			CRefItem refTarget(*this->object, ifElse, nAction, openCloseInfo, REFM_OPENWINDOW_TARGET);
			arIn->AddFieldReference(schemaInsideId1, nTargetFieldId, refTarget);

			CRefItem refValue(*this->object, ifElse, nAction, openCloseInfo, REFM_OPENWINDOW_VALUE);

			stringstream assignText;		
			CheckAssignment(nTargetFieldId, NULL, ifElse, nAction, action.fieldAssignList[i].assignment, assignText, refValue);

			CTableRow row("cssStdRow");
			row.AddCell(CTableCell(arIn->LinkToField(schemaInsideId1, nTargetFieldId, rootLevel)));
			row.AddCell(CTableCell(assignText.str()));
			tblFieldList.AddRow(row);	
		}

		strm << tblFieldList;
	}
	catch(exception& e)
	{
		cout << "EXCEPTION SetFieldsAssignment of '" << this->object->GetName() << "':" << e.what() << endl;
	}

	return strm.str();
}

string CARAssignHelper::ServiceAssignment(const ARFieldAssignList &action, int nAction, IfElseState ifElse, ServiceMappingMode serviceInfo)
{
	this->mode = AM_SERVICE;

	stringstream strm;
	strm.str("");
	try
	{
		CTable tblFieldList("setFieldsList", "TblObjectList");
		tblFieldList.AddColumn(30, "Field Name");
		tblFieldList.AddColumn(70, "Value");

		for(unsigned int i=0; i< action.numItems; i++)
		{
			int nTargetFieldId = action.fieldAssignList[i].fieldId;

			//Add a reference to the target field 
			CRefItem refTarget(*this->object, ifElse, nAction, serviceInfo, REFM_SERVICE_TARGET);
			arIn->AddFieldReference(schemaInsideId1, nTargetFieldId, refTarget);

			CRefItem refValue(*this->object, ifElse, nAction, serviceInfo, REFM_SERVICE_VALUE);

			stringstream assignText;		
			CheckAssignment(nTargetFieldId, NULL, ifElse, nAction, action.fieldAssignList[i].assignment, assignText, refValue);

			CTableRow row("cssStdRow");
			row.AddCell(CTableCell(arIn->LinkToField(schemaInsideId1, nTargetFieldId, rootLevel)));
			row.AddCell(CTableCell(assignText.str()));
			tblFieldList.AddRow(row);	
		}

		strm << tblFieldList;
	}
	catch(exception& e)
	{
		cout << "EXCEPTION ServiceAssignment of '" << this->object->GetName() << "': " << e.what() << endl;
	}

	return strm.str();
}

string CARAssignHelper::FilterApiInputAssignment(const ARAssignStruct* assignList, int numItems, int nAction, IfElseState ifElse)
{
	this->mode = AM_FILTERAPI_INPUT;

	stringstream strm;
	strm.str("");
	try
	{
		CTable tblFieldList("setFieldsList", "TblObjectList");
		tblFieldList.AddColumn(30, "Position");
		tblFieldList.AddColumn(70, "Value");

		for(int i=0; i< numItems; i++)
		{
			stringstream position;
			position << (i+1);

			CRefItem refItem(*this->object, ifElse, nAction, REFM_SETFIELDS_FILTERAPI_INPUT);
			
			stringstream assignText;
			CheckAssignment(0, NULL, ifElse, nAction, const_cast<ARAssignStruct&>(assignList[i]), assignText, refItem);

			CTableRow row("cssStdRow");
			row.AddCell(position.str());
			row.AddCell(assignText.str());
			tblFieldList.AddRow(row);	
		}
		strm << tblFieldList;
	}
	catch(exception& e)
	{
		cout << "EXCEPTION in FilterAPIAssignment of '" << this->object->GetName() << "': " << e.what() << endl;
	}

	return strm.str();
}

unsigned int CARAssignHelper::CheckAssignment(int targetFieldId, ARAssignStruct* parentAssignment, IfElseState ifElse, int nAction, ARAssignStruct &assignment, stringstream &assignText, const CRefItem& refItem)
{
	unsigned int assignType = assignment.assignType;
	try
	{
		switch(assignType)
		{
		case AR_ASSIGN_TYPE_VALUE:
			{					
				AssignValue(targetFieldId, ifElse, assignment.u.value, assignText, refItem);
			}
			break;
		case AR_ASSIGN_TYPE_FIELD:
			{	
				switch (assignment.u.field->tag)
				{
				case AR_FIELD:
					AssignField(ifElse, nAction, *assignment.u.field, assignText, refItem);
					break;
				case AR_STAT_HISTORY:
					{
						assignText << "$";

						CDocStatusHistoryField docStatusHistory(schemaInsideId2, assignment.u.field->u.statHistory);
						docStatusHistory.GetResolvedAndLinkedField(assignText, &refItem, rootLevel);

						assignText << "$";
					}
					break;
				case AR_CURRENCY_FLD:
					{
						CDocCurrencyField docCurrency(schemaInsideId2, *assignment.u.field->u.currencyField);

						assignText << "$";
						docCurrency.GetResolvedAndLinkedField(assignText, &refItem, rootLevel);
						assignText << "$";
					}
					break;
				}
			}
			break;
		case AR_ASSIGN_TYPE_PROCESS:
			{
				AssignProcess(ifElse, assignment.u.process, assignText, refItem);
			}
			break;
		case AR_ASSIGN_TYPE_ARITH:
			{
				// Rule 1: 
				// if the parent has a higher precedence (in this case a lower value), we have to add parentheses
				// Example 1: 2 * (3 + 4)      Original: (2 * (3 + 4))
				// Example 2: 2 + 3 * 4        Original: (2 + (3 * 4))
				// Example 3: (2 + 3) * 4      Original: ((2 + 3) * 4)
				//
				// Rule 2: 
				// if the parent and the current operand have the same precedence (mul, div and modulo use the
				// same, at least in C) and the current modulo operation is at the right side of the parent
				// operand, only then parentheses are needed. (If the modulo is on the left side, the operation
				// is executed from left to right and doesn't need any parentheses.)
				// Example 1: 2 * (3 mod 4)    Original: (2 * (3 mod 4))
				// Example 2: 2 * 3 mod 4      Original: ((2 * 3) mod 4)
				// Example 3: 2 mod 3 * 4      Original: ((2 mod 3) * 4)
				// Example 4: 2 mod (3 * 4)    Original: (2 mod (3 * 4))

				bool addBracket = false;
				if (parentAssignment != NULL && parentAssignment->assignType == assignment.assignType)
				{
					unsigned int parentPrecedence = CAREnum::OperandPrecedence(parentAssignment->u.arithOp->operation);
					unsigned int currentPrecedence = CAREnum::OperandPrecedence(assignment.u.arithOp->operation);

					if (parentPrecedence < currentPrecedence || assignment.u.arithOp->operation == AR_ARITH_OP_MODULO &&
					    parentPrecedence == currentPrecedence && &parentAssignment->u.arithOp->operandRight == &assignment)
						addBracket = true;
				}

				switch (assignment.u.arithOp->operation) 
				{
				case AR_ARITH_OP_ADD:
					if (addBracket) assignText << "(";
					CheckAssignment(targetFieldId, &assignment, ifElse, nAction, assignment.u.arithOp->operandLeft, assignText, refItem);
					assignText << CAREnum::Operand(AR_ARITH_OP_ADD);
					CheckAssignment(targetFieldId, &assignment, ifElse, nAction, assignment.u.arithOp->operandRight, assignText, refItem);
					if (addBracket) assignText << ")";
					break;
				case AR_ARITH_OP_SUBTRACT:
					if (addBracket) assignText << "(";
					CheckAssignment(targetFieldId, &assignment, ifElse, nAction, assignment.u.arithOp->operandLeft, assignText, refItem);
					assignText << CAREnum::Operand(AR_ARITH_OP_SUBTRACT);
					CheckAssignment(targetFieldId, &assignment, ifElse, nAction, assignment.u.arithOp->operandRight, assignText, refItem);
					if (addBracket) assignText << ")";
					break;
				case AR_ARITH_OP_MULTIPLY:
					if (addBracket) assignText << "(";
					CheckAssignment(targetFieldId, &assignment, ifElse, nAction, assignment.u.arithOp->operandLeft, assignText, refItem);
					assignText << CAREnum::Operand(AR_ARITH_OP_MULTIPLY);
					CheckAssignment(targetFieldId, &assignment, ifElse, nAction, assignment.u.arithOp->operandRight, assignText, refItem);
					if (addBracket) assignText << ")";
					break;
				case AR_ARITH_OP_DIVIDE:
					if (addBracket) assignText << "(";
					CheckAssignment(targetFieldId, &assignment, ifElse, nAction, assignment.u.arithOp->operandLeft, assignText, refItem);
					assignText << CAREnum::Operand(AR_ARITH_OP_DIVIDE);
					CheckAssignment(targetFieldId, &assignment, ifElse, nAction, assignment.u.arithOp->operandRight, assignText, refItem);
					if (addBracket) assignText << ")";
					break;
				case AR_ARITH_OP_MODULO:
					if (addBracket) assignText << "(";
					CheckAssignment(targetFieldId, &assignment, ifElse, nAction, assignment.u.arithOp->operandLeft, assignText, refItem);
					assignText << CAREnum::Operand(AR_ARITH_OP_MODULO);
					CheckAssignment(targetFieldId, &assignment, ifElse, nAction, assignment.u.arithOp->operandRight, assignText, refItem);
					if (addBracket) assignText << ")";
					break;
				case AR_ARITH_OP_NEGATE:
					assignText << CAREnum::Operand(AR_ARITH_OP_NEGATE);
					CheckAssignment(targetFieldId, &assignment, ifElse, nAction, assignment.u.arithOp->operandRight, assignText, refItem);
					break;
				}

			}
			break;
		case AR_ASSIGN_TYPE_FUNCTION:
			{
				AssignFunction(targetFieldId, ifElse, nAction, *assignment.u.function, assignText, refItem);
			}
			break;
		case AR_ASSIGN_TYPE_DDE:
			{
				AssignDDE(ifElse, *assignment.u.dde, assignText, refItem);
			}
			break;
		case AR_ASSIGN_TYPE_SQL:
			{
				AssignSQL(ifElse, *assignment.u.sql, assignText, refItem);
			}
			break;
		case AR_ASSIGN_TYPE_FILTER_API:
			{
				AssignFilterApi(ifElse, *assignment.u.filterApi, assignText, refItem);
			}
			break;
		}	
	}
	catch(exception& e)
	{
		cout << "EXCEPTION in ActiveLink CheckAssignment of '" << this->object->GetName() << "': " << e.what() << endl;
	}
	return assignType;
}

void CARAssignHelper::AssignValue(int targetFieldId, IfElseState ifElse, ARValueStruct &v, stringstream &assignText, const CRefItem& refItem)
{	
	try
	{
		stringstream strmValue;

		switch(v.dataType)
		{
		case AR_DATA_TYPE_NULL:
			{
				strmValue << "$NULL$";
			}
			break;
		case AR_DATA_TYPE_CHAR:
			{
				strmValue << "\"" << CWebUtil::Validate(CARValue::ValueToString(v)) << "\"";
			}
			break;
		case AR_DATA_TYPE_REAL:
		case AR_DATA_TYPE_ULONG:
			{
				strmValue << CARValue::ValueToString(v);
			}
			break;
		case AR_DATA_TYPE_KEYWORD:
			{
				strmValue << "$" << CARValue::ValueToString(v) << "$";
			}
			break;
		case AR_DATA_TYPE_INTEGER:
		case AR_DATA_TYPE_ENUM:
			{
				int nTmpActionSchemaId = schemaInsideId1;

				if(this->pushFieldFlag==true)
					nTmpActionSchemaId = schemaInsideId2;

				string tmp = arIn->GetFieldEnumValue(nTmpActionSchemaId, targetFieldId, v.u.enumVal);

				if(!tmp.empty())
					strmValue << "\"" << tmp << "\"";
				else
					strmValue << v.u.enumVal;
			}
			break;
		default:
			{
				strmValue << "\"" << CWebUtil::Validate(CARValue::ValueToString(v)) << "\"";
			}
			break;
		}

		assignText << strmValue.str();
	}
	catch(exception& e)
	{
		cout << "EXCEPTION in AssignValue of '" << this->object->GetName() << "': " << e.what() << endl;
	}
}

void CARAssignHelper::AssignField(IfElseState ifElse, int nAction, ARAssignFieldStruct &v, stringstream &assignText, const CRefItem& refItem)
{
	try
	{
		int nTmpActionSchemaId = schemaInsideId1;

		if(schemaInsideId1 != schemaInsideId2 && this->pushFieldFlag == false)
		{
			nTmpActionSchemaId = schemaInsideId2;
		}

		arIn->AddFieldReference(nTmpActionSchemaId, v.u.fieldId, refItem);

		assignText << "$" << arIn->LinkToField(nTmpActionSchemaId, v.u.fieldId, rootLevel) << "$";

	}
	catch(exception& e)
	{
		cout << "EXCEPTION in AssignField of '" << this->object->GetName() << "': " << e.what() << endl;
	}
}

void CARAssignHelper::AssignProcess(IfElseState ifElse, char *v, stringstream &assignText, const CRefItem& refItem)
{
	try
	{
		if(v != NULL)
		{
			assignText << "$PROCESS$ "<< arIn->TextFindFields(v, "$", this->schemaInsideId2, rootLevel, true, &refItem) << endl;
		}
	}
	catch(exception& e)
	{
		cout << "EXCEPTION in AssignProcess of '" << this->object->GetName() << "': " << e.what() << endl;
	}
}

void CARAssignHelper::AssignFunction(int targetFieldId, IfElseState ifElse, int nAction, ARFunctionAssignStruct &v, stringstream &assignText, const CRefItem& refItem)
{
	try
	{				
		assignText << CAREnum::Function(v.functionCode) << "(";

		switch (v.functionCode)
		{
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_750
		case AR_FUNCTION_HOVER:
			{
				for(unsigned int i=0; i< v.numItems; ++i)
				{
					if(i > 0) assignText << ", ";

					if (i == 0 && v.parameterList[i].assignType == AR_ASSIGN_TYPE_VALUE)
					{
						int fieldId = 0;
						stringstream tmpStrm;

						switch (v.parameterList[i].u.value.dataType)
						{
						case AR_DATA_TYPE_INTEGER:
							fieldId = v.parameterList[i].u.value.u.intVal;
							tmpStrm << fieldId;
							break;
						case AR_DATA_TYPE_CHAR:
							if (v.parameterList[i].u.value.u.charVal != NULL && v.parameterList[i].u.value.u.charVal[0] != 0)
							{
								fieldId = atoi(v.parameterList[i].u.value.u.charVal);
								tmpStrm << "\"" << v.parameterList[i].u.value.u.charVal << "\"";
							}
							break;
						}

						if (fieldId > 0)
						{
							int msgId = -1;
							switch (this->mode)
							{
							case AM_SETFIELDS:
								msgId = REFM_SETFIELDS_HOVERFIELD;
								break;
							case AM_PUSHFIELD:
								msgId = REFM_PUSHFIELD_HOVERFIELD;
								break;
							case AM_OPENWINDOW:
								msgId = REFM_OPENWINDOW_HOVERFIELD;
								break;
							case AM_SERVICE:
								msgId = REFM_SERVICE_HOVERFIELD;
								break;
							}
							CRefItem refItemHover(*this->object, ifElse, nAction, msgId);
							arIn->AddFieldReference(this->schemaInsideId1, fieldId, refItemHover);
							assignText << arIn->LinkToField(this->schemaInsideId1, fieldId, tmpStrm.str(), rootLevel);
							continue;
						}
					}

					CheckAssignment(targetFieldId, NULL, ifElse, nAction, v.parameterList[i], assignText, refItem);
				}
			}
			break;
#endif
		default:
			{
				for(unsigned int i=0; i< v.numItems; ++i)
				{
					if(i > 0)	assignText << ", ";

					CheckAssignment(targetFieldId, NULL, ifElse, nAction, v.parameterList[i], assignText, refItem);
				}
			}
			break;
		}
		assignText << ")";
	}
	catch(exception& e)
	{
		cout << "EXCEPTION in AssignFunction of '" << this->object->GetName() << "': " << e.what() << endl;
	}
}

void CARAssignHelper::AssignDDE(IfElseState ifElse, ARDDEStruct &v, stringstream &assignText, const CRefItem& refItem)
{
	try
	{
		if(v.command != NULL)
		{
			assignText <<"Command: " << CWebUtil::Validate(v.command) << "<br/>" << endl;
		}

		if(v.item != NULL)
		{
			assignText <<"Item: " << CWebUtil::Validate(v.item) << "<br/>" << endl;
		}

		if(v.pathToProgram != NULL)
		{
			assignText << "Path to Program: " << CWebUtil::Validate(v.pathToProgram) << "<br/>" << endl;
		}

		if(v.serviceName != NULL)
		{
			assignText << "Server Name: " << CWebUtil::Validate(v.serviceName) << "<br/" << endl;
		}

		if(v.topic != NULL)
		{
			assignText << "Topic: " << CWebUtil::Validate(v.topic) << "<br/>" << endl;
		}
	}
	catch(exception& e)
	{
		cout << "EXCEPTION in AssignDDE of '" << this->object->GetName() << "': " << e.what() << endl;
	}
}

void CARAssignHelper::AssignSQL(IfElseState ifElse, ARAssignSQLStruct &v, stringstream &assignText, const CRefItem& refItem)
{
	try
	{
		assignText << "$" << v.valueIndex << "$";
	}
	catch(exception& e)
	{
		cout << "EXCEPTION in AssignSQL of '" << this->object->GetName() << "': " << e.what() << endl;
	}
}

void CARAssignHelper::AssignFilterApi(IfElseState ifElse, ARAssignFilterApiStruct &v, stringstream &assignText, const CRefItem& refItem)
{
	try
	{
		assignText << "$" << v.valueIndex << "$";		
	}
	catch(exception& e)
	{
		cout << "EXCEPTION in AssignFilterApi of '" << this->object->GetName() << "': " << e.what() << endl;
	}
}
