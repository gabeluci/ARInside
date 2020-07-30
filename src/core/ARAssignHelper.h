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
#include "ARValue.h"
#include "../output/Table.h"
#include "../output/TableRow.h"
#include "../ARInside.h"

using namespace OUTPUT;

class MappingContext;

class CARAssignHelper
{
public:
	CARAssignHelper(CARInside& arIn, int rootLevel, const CARServerObject& obj, const CARSchema& schema1, const CARSchema& schema2);
	CARAssignHelper(CARInside& arIn, int rootLevel, const CARServerObject& obj, int schemaId1, int schemaId2);
	CARAssignHelper(CARInside& arIn, int rootLevel, const CARServerObject& obj, const string& schemaName1, const string& schemaName2);
	CARAssignHelper(MappingContext &context);

	~CARAssignHelper(void);

	bool pushFieldFlag;

	string PushFieldsAssignment(const ARPushFieldsActionStruct &action, int nAction, IfElseState ifElse);
	string SetFieldsAssignment(const ARSetFieldsActionStruct &action, int nAction, IfElseState ifElse);
	string OpenWindowAssignment(const ARFieldAssignList &action, int nAction, IfElseState ifElse, OpenWindowMode openCloseInfo);
	string ServiceAssignment(const ARFieldAssignList &action, int nAction, IfElseState ifElse, ServiceMappingMode serviceInfo);
	string FilterApiInputAssignment(const ARAssignStruct* assignList, int numItems, int nAction, IfElseState ifElse);

private:
	unsigned int CheckAssignment(int targetFieldId, ARAssignStruct* parentAssignment, IfElseState ifElse, int nAction, ARAssignStruct &assignment, stringstream &assignText, const CRefItem& refItem);

	void AssignValue(int targetFieldId, IfElseState ifElse, ARValueStruct &v, stringstream &assignText, const CRefItem& refItem);	
	void AssignField(IfElseState ifElse, int nAction, ARAssignFieldStruct &v, stringstream &assignText, const CRefItem& refItem);
	void AssignProcess(IfElseState ifElse, char *v, stringstream &assignText, const CRefItem& refItem);
	void AssignFunction(int targetFieldId, IfElseState ifElse, int nAction, ARFunctionAssignStruct &v, stringstream &assignText, const  CRefItem& refItem);
	void AssignDDE(IfElseState ifElse, ARDDEStruct &v, stringstream &assignText, const CRefItem& refItem);
	void AssignSQL(IfElseState ifElse, ARAssignSQLStruct &v, stringstream &assignText, const CRefItem& refItem);	
	void AssignFilterApi(IfElseState ifElse, ARAssignFilterApiStruct &v, stringstream &assignText, const CRefItem& refItem);	

private:
	enum AssignmentMode
	{
		AM_SETFIELDS,
		AM_PUSHFIELD,
		AM_OPENWINDOW,
		AM_SERVICE,
		AM_FILTERAPI_INPUT,
	};

	CARInside *arIn;
	CARServerObject* object;

	int schemaInsideId1;
	int schemaInsideId2;
	int rootLevel;
	AssignmentMode mode;
};
