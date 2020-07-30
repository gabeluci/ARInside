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

class CDocAlActionStruct
{
public:
	CDocAlActionStruct(CARInside &arIn, CARActiveLink &obj, string schemaName, int rootLevel);
	~CDocAlActionStruct(void);

public:
	string Get(IfElseState ifElse, const ARActiveLinkActionList &actList);	

private:
	CARInside *arIn;
	CARActiveLink *obj;
	string schemaName;
	int schemaInsideId;
	string dir;
	int rootLevel;
	int structItemType;
	IfElseState ifElse;

	// AR_ACTIVE_LINK_ACTION_NONE
	string ActionNone(int nAction);

	// AR_ACTIVE_LINK_ACTION_MACRO
	void ActionMacro(std::ostream& strm, const ARActiveLinkMacroStruct &action, int nAction);

	// AR_ACTIVE_LINK_ACTION_FIELDS
	void ActionSetFields(std::ostream& strm, const ARSetFieldsActionStruct &action, int nAction);

	// AR_ACTIVE_LINK_ACTION_PROCESS
	void ActionProcess(std::ostream& strm, const char *action, int nAction);

	// AR_ACTIVE_LINK_ACTION_MESSAGE
	void ActionMessage(std::ostream& strm, const ARMessageStruct &action, int nAction);

	// AR_ACTIVE_LINK_ACTION_SET_CHAR
	void ActionSetChar(std::ostream& strm, const ARFieldCharacteristics &action, int nAction);

	// AR_ACTIVE_LINK_ACTION_DDE
	void ActionDde(std::ostream& strm, const ARDDEStruct &action, int nAction);

	// AR_ACTIVE_LINK_ACTION_FIELDP
	void ActionPushFields(std::ostream& strm, const ARPushFieldsActionStruct &action, int nAction);

	// AR_ACTIVE_LINK_ACTION_SQL
	void ActionSql(std::ostream& strm, const ARSQLStruct &action, int nAction);

	// AR_ACTIVE_LINK_ACTION_AUTO
	void ActionAutomation(std::ostream& strm, const ARAutomationStruct &action, int nAction);

	// AR_ACTIVE_LINK_ACTION_OPENDLG
	void ActionOpenDlg(std::ostream& strm, const AROpenDlgStruct &action, int nAction);

	// AR_ACTIVE_LINK_ACTION_COMMITC
	void ActionCommitChanges(std::ostream& strm, const ARCommitChangesStruct &action, int nAction);

	// AR_ACTIVE_LINK_ACTION_CLOSEWND
	void ActionCloseWindow(std::ostream& strm, const ARCloseWndStruct &action, int nAction);

	// AR_ACTIVE_LINK_ACTION_CALLGUIDE
	void ActionCallGuide(std::ostream& strm, const ARCallGuideStruct &action, int nAction);

	// AR_ACTIVE_LINK_ACTION_EXITGUIDE
	void ActionExitGuide(std::ostream& strm, const ARExitGuideStruct &action, int nAction);

	// AR_ACTIVE_LINK_ACTION_GOTOGUIDELABEL
	void ActionGotoGuideLabel(std::ostream& strm, const ARGotoGuideLabelStruct &action, int nAction);

	// AR_ACTIVE_LINK_ACTION_WAIT
	void ActionWait(std::ostream& strm, const ARWaitStruct &action, int nAction);

	// AR_ACTIVE_LINK_ACTION_GOTOACTION
	void ActionGotoAction(std::ostream& strm, const ARGotoActionStruct &action, int nAction);

#if AR_CURRENT_API_VERSION > 12 // Version 7.1 and higher
	// AR_ACTIVE_LINK_ACTION_SERVICE
	void ActionService(std::ostream& strm, const ARActiveLinkSvcActionStruct &action, int nAction);
#endif
};
