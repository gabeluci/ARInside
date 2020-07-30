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
#include "DocActionSetFieldsHelper.h"
#include "../core/ARAssignHelper.h"
#include "../core/ARQualification.h"

using namespace OUTPUT;

class CDocFilterActionStruct
{
public:
	CDocFilterActionStruct(CARInside &arIn, CARServerObject &obj, string schemaName, int rootLevel, int structItemType);
	~CDocFilterActionStruct(void);

public:
	string Get(IfElseState ifElse, const ARFilterActionList &actList);

private:
	CARInside *arIn;
	CARServerObject *obj;
	string schemaName;
	int schemaInsideId;
	int rootLevel;
	int structItemType;
	IfElseState ifElse;

	//AR_FILTER_ACTION_NONE
	string FilterActionNone(int nAction);

	// AR_FILTER_ACTION_NOTIFY
	string FilterActionNotify(ARFilterActionNotify &action, int nAction);

	// AR_FILTER_ACTION_MESSAGE
	string FilterActionMessage(ARFilterStatusStruct &action, int nAction);

	// AR_FILTER_ACTION_LOG
	string FilterActionLog(char *action, int nAction);

	// AR_FILTER_ACTION_FIELDS
	string FilterActionSetFields(ARSetFieldsActionStruct &action, int nAction);

	// AR_FILTER_ACTION_PROCESS
	string FilterActionProcess(char *action, int nAction);

	// AR_FILTER_ACTION_FIELDP
	string FilterActionPushFields(ARPushFieldsActionStruct &action, int nAction);

	// AR_FILTER_ACTION_SQL
	string FilterActionSql(ARSQLStruct &action, int nAction);

	// AR_FILTER_ACTION_GOTOACTION 
	string FilterActionGotoAction(ARGotoActionStruct &action, int nAction);

	// AR_FILTER_ACTION_CALLGUIDE
	string FilterActionCallGuide(ARCallGuideStruct &action, int nAction);

	// AR_FILTER_ACTION_EXITGUIDE
	string FilterActionExitGuide(ARExitGuideStruct &action, int nAction);

	// AR_FILTER_ACTION_GOTOGUIDELABEL
	string FilterActionGotoGuideLabel(ARGotoGuideLabelStruct &action, int nAction);

#if AR_CURRENT_API_VERSION >= AR_API_VERSION_750
	// AR_FILTER_ACTION_SERVICE
	string FilterActionService(ARSvcActionStruct &action, int nAction);
#endif
};
