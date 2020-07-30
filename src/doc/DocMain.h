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
#include "DocBase.h"
#include "MessageItem.h"
#include "../output/Table.h"
#include "../output/TableRow.h"
#include "../output/FilterTable.h"
#include "../output/AlTable.h"
#include "../output/EscalTable.h"
#include "../output/ContainerTable.h"
#include "../output/MenuTable.h"
#include "../output/SchemaTable.h"
#include "../output/RoleTable.h"
#include "../output/GroupTable.h"
#include "../output/UserTable.h"
#include "../output/ImageTable.h"

using namespace OUTPUT;

class CDocMain :
	public CDocBase
{
public:
	CDocMain();
	~CDocMain(void);

	int Index();
	void ServerInfoList();

	unsigned int SchemaList();	
	unsigned int ActiveLinkList();	
	unsigned int FilterList();	
	unsigned int EscalationList();
	unsigned int CharMenuList();
	unsigned int ContainerList(int nType, string title);

	void GroupList();
	void RoleList();
	void UserList(string searchChar, std::vector<int>& objCountPerLetter);

	void GlobalFieldList();
	void MessageList();
	void NotificationList();

	void ActiveLinkActionList();
	void ActiveLinkActionDetails(int nActionType, int &ifCount, int &elseCount);

	void FilterActionList();
	void FilterActionDetails(int nActionType, int &ifCount, int &elseCount);
	void FilterErrorHandlers();

	void EscalationActionList();
	void EscalationActionDetails(int nActionType, int &ifCount, int &elseCount);


private:
	static void Sort(list<CMessageItem> &listResult);
	static bool SortByMsgNum(const CMessageItem& t1, const CMessageItem& t2 );

	static void AddGlobalFieldRow(OUTPUT::CTable& tbl, int fieldId, OUTPUT::CTable& fields);

public:
	static string ShortMenu(string curCharacter, const CPageParams &curPage, std::vector<int>& objCountPerLetter);
	
	static string CreateStandardFilterControl(const string &inputControlId, const string &htmlPlaceHolder = "search by name");
	static string CreateSchemaFilterControl();
	static string CreateActlinkFilterControl();
	static string CreateFilterFilterControl();
	static string CreateEscalationFilterControl();
	static string CreateMenuFilterControl();
	static string CreateContainerFilterControl();
	static string CreateImageFilterControl();
	static string CreateGroupFilterControl();
	static string CreateRoleFilterControl();
	static string CreateSchemaReferenceFilterControl();

private:
	void SchemaListJson(std::ostream &strm);
	void ActiveLinkListJson(std::ostream &strm);
	void FilterListJson(std::ostream &strm);
	void EscalationListJson(std::ostream &strm);
	void MenuListJson(std::ostream &strm);
};
