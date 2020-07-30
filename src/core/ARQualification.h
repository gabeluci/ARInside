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
#include "../ARInside.h"

class Context;
class MappingContext;

class CARQualification
{
public:
	// use this constructor in case only one form is involved (e.g. run if)
	CARQualification(CARInside &arIn, const CRefItem &referenceItem, int currentFormId, int rootLevel);
	CARQualification(Context &context, const CRefItem &referenceItem);

	// use this constructor in case two forms are involved (e.g. setfield-if, pushfield-if)
	CARQualification(CARInside &arIn, const CRefItem &referenceItem, int currentFormId, int otherFormId, int rootLevel);
	CARQualification(MappingContext &context, const CRefItem &referenceItem);

	~CARQualification(void);

	void CheckQuery(const ARQualifierStruct *query, stringstream &qText);

	int arsStructItemType;;

private:
	CARInside *arIn;
	CRefItem refItem;
	int primaryFormId;
	int secondaryFormId;
	int rootLevel;
	char primaryFormDelimiter;
	char secondaryFormDelimiter;

	void CheckOperand(ARFieldValueOrArithStruct *operand, ARFieldValueOrArithStruct *parent, stringstream &qText);
	int FindCurrentEnumFieldId();
	const char* getFieldPrefix(ARFieldValueOrArithStruct *operand);
	bool getFormIdAndDelimiter(ARFieldValueOrArithStruct *operand, int &formId, char &delimiter);

	int tmpFormId;
	vector<const ARQualifierStruct*> qualLevels;
};
