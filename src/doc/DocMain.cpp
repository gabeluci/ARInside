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
#include "DocMain.h"
#include "../output/IFileStructure.h"
#include "../output/ImageTag.h"
#include "../output/LetterFilterControl.h"
#include "../output/URLLink.h"
#include "../core/ARServerInfo.h"

#include "rapidjson/document.h"
#include "rapidjson/genericwritestream.h"
#include "rapidjson/writer.h"

using namespace rapidjson;

CDocMain::CDocMain()
{
}

CDocMain::~CDocMain(void)
{
}

int CDocMain::Index()
{
	try
	{
		CWebPage webPage("index", "Documentation Index", 0, this->pInside->appConfig);	
		webPage.AddContent("This space is intentionally left blank...");
		return webPage.SaveInFolder("");
	}
	catch(exception& e)
	{
		cout << "EXCEPTION Index: " << e.what() << endl;
	}
	return 0;
}

void CDocMain::ServerInfoList()
{
	CPageParams file(PAGE_SERVER_INFO);

	try
	{
		int rootLevel = file->GetRootLevel();
		CWebPage webPage(file->GetFileName(), "Server details", rootLevel, this->pInside->appConfig);
		CTable tbl("serverDetailList", "TblObjectList");
		tbl.AddColumn(40, "Operation");
		tbl.AddColumn(60, "Value");

		unsigned int count = this->pInside->serverInfoList.GetCount();
		for (unsigned int index = 0; index < count; ++index)
		{	
			CARServerInfo srvInfo(index, CARServerInfo::INDEX);
			ARValueStruct* val = srvInfo.GetValue();

			CTableRow row("cssStdRow");
			row.AddCell(CTableCell(CAREnum::ServerInfoApiCall(srvInfo.GetOperation())));
			row.AddCell(CTableCell(CARValue::ValueToString(*val)));
			tbl.AddRow(row);		
		}

		stringstream tblDesc;
		tblDesc << ImageTag(ImageTag::Document, rootLevel) << "Server informations";
		tbl.description = tblDesc.str();

		webPage.AddContent(tbl.ToXHtml());

		webPage.SaveInFolder(file->GetPath());
	}
	catch(exception& e)
	{
		cout << "EXCEPTION ServerInfoList: " << e.what() << endl;
	}
}

string CDocMain::ShortMenu(string curCharacter, const CPageParams &curPage, std::vector<int>& objCountPerLetter)
{
	stringstream strm;
	try
	{
		strm << "<table id='formLetterFilter'><tr>" << endl;

		string strValue = objectNameFirstCharLetters; // "abcdefghijklmnopqrstuvwxyz0123456789#"
		for (unsigned int i = 0; i < strValue.size(); ++i) 
		{
			if(std::string(1, strValue.at(i)) != curCharacter)
			{
				// copy all page params over and change the page we want to link to
				CPageParams linkTo(curPage, strValue.at(i));
				if (objCountPerLetter[i] > 0)
				{
					strm << "<td>";
					strm << URLLink( std::string(1, strValue.at(i)), linkTo , curPage->GetRootLevel());
				}
				else
				{
					strm << "<td class=\"disabledLetter\">";
					strm << strValue.at(i);
				}

				strm << "</td>" << endl;

			}
			else
				strm << "<td>" << std::string(1, strValue.at(i)) << "</td>" << endl;			
		}

		strm << "</tr></table>" << endl;
	}
	catch(exception& e)
	{
		cout << "EXCEPTION ShortMenu: " << e.what() << endl;
	}
	return strm.str();
}

unsigned int CDocMain::SchemaList()
{
	CPageParams file(PAGE_OVERVIEW, AR_STRUCT_ITEM_XML_SCHEMA);
	unsigned int objCount = 0;

	try
	{
		rootLevel = file->GetRootLevel();
		CSchemaTable tbl(*this->pInside);
		LetterFilterControl letterFilter;

		unsigned int schemaCount = this->pInside->schemaList.GetCount();
		for (unsigned int schemaIndex = 0; schemaIndex < schemaCount; ++schemaIndex)
		{	
			CARSchema schema(schemaIndex);

#if AR_CURRENT_API_VERSION >= AR_API_VERSION_764
			if (pInside->appConfig.bOverlaySupport && !IsVisibleObject(schema))
				continue;
#endif

			letterFilter.IncStartLetterOf(schema);
			objCount++;
		}
		if (objCount > 0)
		{
			tbl.RemoveEmptyMessageRow();
		}

		CWebPage webPage(file->GetFileName(), "Forms", rootLevel, this->pInside->appConfig);

		webPage.GetReferenceManager()
			.AddScriptReference("img/object_list.js")
			.AddScriptReference("img/schemaList.js")
			.AddScriptReference("img/jquery.timers.js")
			.AddScriptReference("img/jquery.address.min.js");

		stringstream strmTmp;
		strmTmp << "<span id='schemaListFilterResultCount'></span>" << CWebUtil::LinkToSchemaIndex(objCount, rootLevel);
		SchemaListJson(strmTmp);
		strmTmp << CreateSchemaFilterControl() << endl;
		strmTmp << letterFilter;
		strmTmp << tbl;
		webPage.AddContent(strmTmp.str());

		webPage.SaveInFolder(file->GetPath());
	}
	catch(exception& e)
	{
		cout << "EXCEPTION SchemaList: " << e.what() << endl;
	}
	return objCount;
}

unsigned int CDocMain::ActiveLinkList()
{
	CPageParams file(PAGE_OVERVIEW, AR_STRUCT_ITEM_XML_ACTIVE_LINK);
	unsigned int objCount = 0;

	try
	{
		rootLevel = file->GetRootLevel();

		CAlTable tbl(*this->pInside);
		LetterFilterControl letterFilter;

		unsigned int alCount = this->pInside->alList.GetCount();
		
		for (unsigned int alIdx = 0; alIdx < alCount; ++alIdx)
		{
			CARActiveLink actLink(alIdx);

#if AR_CURRENT_API_VERSION >= AR_API_VERSION_764
			if (pInside->appConfig.bOverlaySupport && !IsVisibleObject(actLink))
				continue;
#endif

			letterFilter.IncStartLetterOf(actLink);

			objCount++;
		}
		if (objCount > 0)
		{
			tbl.RemoveEmptyMessageRow();
		}

		CWebPage webPage(file->GetFileName(), "Active Link List", rootLevel, this->pInside->appConfig);
		
		webPage.GetReferenceManager()
			.AddScriptReference("img/object_list.js")
			.AddScriptReference("img/actlinkList.js")
			.AddScriptReference("img/jquery.timers.js")
			.AddScriptReference("img/jquery.address.min.js");

		stringstream strmTmp;
		strmTmp << "<span id='actlinkListFilterResultCount'></span>" << CWebUtil::LinkToActiveLinkIndex(objCount, rootLevel);
		ActiveLinkListJson(strmTmp);
		strmTmp << CreateActlinkFilterControl() << endl;
		strmTmp << letterFilter;
		strmTmp << tbl;
		webPage.AddContent(strmTmp.str());

		webPage.SaveInFolder(file->GetPath());
	}
	catch(exception& e)
	{
		cout << "EXCEPTION ActiveLinkList: " << e.what() << endl;
	}
	return objCount;
}

void CDocMain::ActiveLinkListJson(ostream &strm)
{
	Document document;
	Document::AllocatorType &alloc = document.GetAllocator();
	document.SetArray();

	unsigned int actlinkCount = this->pInside->alList.GetCount();
	for (unsigned int actlinkIndex = 0; actlinkIndex < actlinkCount; ++actlinkIndex)
	{	
		CARActiveLink actlink(actlinkIndex);
		
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_764
			if (pInside->appConfig.bOverlaySupport && !IsVisibleObject(actlink))
				continue;
#endif

			CARProplistHelper props(&actlink.GetPropList());
			CPageParams actlinkDetailPage(PAGE_DETAILS, &actlink);

			// create a new json row and make it an array
			Value actlinkRow;
			actlinkRow.SetArray();

			// now build the needed temporary variables
			string strName = actlink.GetName();
			string strModifiedDate = CUtil::DateTimeToString(actlink.GetTimestamp());
			string strLink = CWebUtil::GetRelativeURL(rootLevel, actlinkDetailPage);
			string strExecuteOn = actlink.GetExecuteOn(true, &props);

			// build the values
			Value valName(strName.c_str(), static_cast<SizeType>(strName.size()), alloc);
			Value valModifiedDate(strModifiedDate.c_str(), static_cast<SizeType>(strModifiedDate.size()), alloc);
			Value valLink(strLink.c_str(), static_cast<SizeType>(strLink.size()), alloc);
			Value valExecuteOn(strExecuteOn.c_str(), static_cast<SizeType>(strExecuteOn.size()), alloc);

			// add everything to the row
			actlinkRow.PushBack(valName, alloc);
			actlinkRow.PushBack(actlink.GetEnabled(), alloc);
			actlinkRow.PushBack(actlink.GetGroupList().numItems, alloc);
			actlinkRow.PushBack(actlink.GetOrder(), alloc);
			actlinkRow.PushBack(valExecuteOn, alloc);
			actlinkRow.PushBack(actlink.GetIfActions().numItems, alloc);
			actlinkRow.PushBack(actlink.GetElseActions().numItems, alloc);
			actlinkRow.PushBack(valModifiedDate, alloc);
			actlinkRow.PushBack(actlink.GetLastChanged(), alloc);
			actlinkRow.PushBack(valLink, alloc);
			actlinkRow.PushBack(actlink.GetOverlayType(), alloc);

			// add the row to the document
			document.PushBack(actlinkRow, alloc);
	}

	GenericWriteStream output(strm);
	Writer<GenericWriteStream> writer(output);

	strm << endl << "<script type=\"text/javascript\">" << endl;
	strm << "var alList = "; document.Accept(writer); strm << ";";
	strm << "var rootLevel = " << rootLevel << ";";
	strm << endl;
	strm << "</script>" << endl;
}

void CDocMain::ActiveLinkActionList()
{
	CPageParams file(PAGE_ACTION_OVERVIEW, AR_STRUCT_ITEM_XML_ACTIVE_LINK);
	
	try
	{
		int rootLevel = file->GetRootLevel();
		CWebPage webPage(file->GetFileName(), "Active Link Actions", rootLevel, this->pInside->appConfig);

		CTable tbl("alList", "TblObjectList");

		stringstream strmTmp;
		strmTmp << URLLink("Active Links", CPageParams(PAGE_OVERVIEW, AR_STRUCT_ITEM_XML_ACTIVE_LINK), ImageTag::ActiveLink, rootLevel) << " with a specified action in If/Else list:";

		tbl.description = strmTmp.str();
		tbl.AddColumn(100, "Active Link Action (Items count if/else)");

		//Search all possible action type
#if AR_CURRENT_API_VERSION > 12 // Version 7.1 and higher
#define LAST_ACTIVE_LINK_ACTION 18
#else
#define LAST_ACTIVE_LINK_ACTION 17
#endif
		for(int nActionType=AR_ACTIVE_LINK_ACTION_MACRO; nActionType<=LAST_ACTIVE_LINK_ACTION; nActionType++)
		{		
			int nCountIf = 0;
			int nCountElse = 0;

			//Create a new webpage for every action
			ActiveLinkActionDetails(nActionType, nCountIf, nCountElse);

			strmTmp.str("");
			strmTmp << URLLink(CAREnum::ActiveLinkAction(nActionType), CPageParams(PAGE_ACTION_OBJLIST, AR_STRUCT_ITEM_XML_ACTIVE_LINK, nActionType), ImageTag::Document, rootLevel) << " (" << nCountIf << "/" << nCountElse << ")";

			CTableRow row("");
			row.AddCell(CTableCell(strmTmp.str()));
			tbl.AddRow(row);
		}

		webPage.AddContent(tbl.ToXHtml());

		webPage.SaveInFolder(file->GetPath());
	}
	catch(exception& e)
	{
		cout << "EXCEPTION ActiveLinkActionList: " << e.what() << endl;
	}
}

void CDocMain::ActiveLinkActionDetails(int nActionType, int &ifCount, int &elseCount)
{
	CPageParams file(PAGE_ACTION_OBJLIST, AR_STRUCT_ITEM_XML_ACTIVE_LINK, nActionType);
	try
	{		
		int rootLevel = 1;

		//stringstream strmTmp;
		//strmTmp << "index_action_" << nActionType;
		CWebPage webPage(file->GetFileName(), "Active Link Actions", rootLevel, this->pInside->appConfig);

		CAlTable *tbl = new CAlTable(*this->pInside);	

		unsigned int alCount = pInside->alList.GetCount();
		for (unsigned int alIndex = 0; alIndex < alCount; ++alIndex )
		{
			CARActiveLink al(alIndex);

#if AR_CURRENT_API_VERSION >= AR_API_VERSION_764
			// Hide overlaid objects on the list
			if (pInside->appConfig.bOverlaySupport && !IsVisibleObject(al))
				continue;
#endif

			int nActionExists = 0;
			const ARActiveLinkActionList &ifActions = al.GetIfActions();
			const ARActiveLinkActionList &elseActions = al.GetElseActions();

			//actionList
			for(unsigned int nAction=0; nAction < ifActions.numItems; nAction++)
			{
				if(ifActions.actionList[nAction].action == nActionType)
				{
					++ifCount;
					++nActionExists;
				}
			}		

			//elseList
			for(unsigned int nAction=0; nAction < elseActions.numItems; nAction++)
			{
				if(elseActions.actionList[nAction].action == nActionType)
				{		
					++elseCount;			
					++nActionExists;
				}
			}		

			if(nActionExists > 0)
			{
				tbl->AddRow(alIndex, rootLevel);
			}
		}

		stringstream strmTmp;
		strmTmp << URLLink("Active Links", CPageParams(PAGE_ACTION_OVERVIEW, AR_STRUCT_ITEM_XML_ACTIVE_LINK), ImageTag::ActiveLink, rootLevel) << " with " << CAREnum::ActiveLinkAction(nActionType) << " action";
		tbl->SetDescription(strmTmp.str());

		webPage.AddContent(tbl->Print());
		delete tbl;

		webPage.SaveInFolder(file->GetPath());
	}
	catch(exception& e)
	{
		cout << "EXCEPTION ActiveLinkActionDetails: " << e.what() << endl;
	}
}


unsigned int CDocMain::FilterList()
{
	CPageParams file(PAGE_OVERVIEW, AR_STRUCT_ITEM_XML_FILTER);
	unsigned int objCount = 0;

	try
	{
		rootLevel = file->GetRootLevel();
		CFilterTable tbl(*this->pInside);
		LetterFilterControl letterFilter;

		unsigned int filterCount = this->pInside->filterList.GetCount();

		for (unsigned int filterIndex = 0; filterIndex < filterCount; ++filterIndex )
		{
			CARFilter filter(filterIndex);

#if AR_CURRENT_API_VERSION >= AR_API_VERSION_764
			if (pInside->appConfig.bOverlaySupport && !IsVisibleObject(filter))
				continue;
#endif

			letterFilter.IncStartLetterOf(filter);
			objCount++;
		}
		if (objCount > 0)
		{
			tbl.RemoveEmptyMessageRow();
		}

		CWebPage webPage(file->GetFileName(), "Filter List", file->GetRootLevel(), this->pInside->appConfig);

		webPage.GetReferenceManager()
			.AddScriptReference("img/object_list.js")
			.AddScriptReference("img/filterList.js")
			.AddScriptReference("img/jquery.timers.js")
			.AddScriptReference("img/jquery.address.min.js");

		stringstream strmTmp;
		strmTmp << "<span id='filterListFilterResultCount'></span>" << CWebUtil::LinkToFilterIndex(objCount, rootLevel);
		FilterListJson(strmTmp);
		strmTmp << CreateFilterFilterControl() << endl;
		strmTmp << letterFilter;
		strmTmp << tbl;
		webPage.AddContent(strmTmp.str());

		webPage.SaveInFolder(file->GetPath());
	}
	catch(exception& e)
	{
		cout << "EXCEPTION FilterList: " << e.what() << endl;
	}
	return objCount;
}

void CDocMain::FilterListJson(std::ostream &strm)
{
	Document document;
	Document::AllocatorType &alloc = document.GetAllocator();
	document.SetArray();

	unsigned int filterCount = this->pInside->filterList.GetCount();
	for (unsigned int filterIndex = 0; filterIndex < filterCount; ++filterIndex)
	{	
		CARFilter filter(filterIndex);
		
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_764
		if (pInside->appConfig.bOverlaySupport && !IsVisibleObject(filter))
			continue;
#endif

		CPageParams filterDetailPage(PAGE_DETAILS, &filter);

		// create a new json row and make it an array
		Value filterRow;
		filterRow.SetArray();

		// now build the needed temporary variables
		string strName = filter.GetName();
		string strExecuteOn = filter.GetExecuteOn(true);
		string strModifiedDate = CUtil::DateTimeToString(filter.GetTimestamp());
		string strLink = CWebUtil::GetRelativeURL(rootLevel, filterDetailPage);

		// build the values
		Value valName(strName.c_str(), static_cast<SizeType>(strName.size()), alloc);
		Value valExecOn(strExecuteOn.c_str(), static_cast<SizeType>(strExecuteOn.size()), alloc);		
		Value valModifiedDate(strModifiedDate.c_str(), static_cast<SizeType>(strModifiedDate.size()), alloc);
		Value valLink(strLink.c_str(), static_cast<SizeType>(strLink.size()), alloc);

		// add everything to the row
		filterRow.PushBack(valName,alloc);
		filterRow.PushBack(filter.GetEnabled(), alloc);
		filterRow.PushBack(filter.GetOrder(), alloc);
		filterRow.PushBack(valExecOn, alloc);
		filterRow.PushBack(filter.GetIfActions().numItems, alloc);
		filterRow.PushBack(filter.GetElseActions().numItems, alloc);
		filterRow.PushBack(valModifiedDate, alloc);
		filterRow.PushBack(filter.GetLastChanged(), alloc);
		filterRow.PushBack(valLink, alloc);
		filterRow.PushBack(filter.GetOperation(), alloc);
		filterRow.PushBack(filter.GetOverlayType(), alloc);

		document.PushBack(filterRow, alloc);
	}

	GenericWriteStream output(strm);
	Writer<GenericWriteStream> writer(output);

	strm << endl << "<script type=\"text/javascript\">" << endl;
	strm << "var filterList = "; document.Accept(writer); strm << ";";
	strm << "var rootLevel = " << rootLevel << ";";
	strm << endl;
	strm << "</script>" << endl;
}

void CDocMain::FilterActionList()
{
	CPageParams file(PAGE_ACTION_OVERVIEW, AR_STRUCT_ITEM_XML_FILTER);

	try
	{
		int rootLevel = file->GetRootLevel();
		CWebPage webPage(file->GetFileName(), "Filter Actions", rootLevel, this->pInside->appConfig);

		CTable tbl("filterList", "TblObjectList");

		stringstream strmTmp;
		strmTmp << URLLink("Filter", CPageParams(PAGE_OVERVIEW, AR_STRUCT_ITEM_XML_FILTER), ImageTag::Filter, rootLevel) << " with a specified action in If/Else list:";

		tbl.description = strmTmp.str();
		tbl.AddColumn(100, "Filter Action (Items count if/else)");

#if AR_CURRENT_API_VERSION >= AR_API_VERSION_750 // Version 7.5 and higher
#define LAST_FILTER_ACTION 12
#else
#define LAST_FILTER_ACTION 11
#endif

		//Search all possible actions
		for(int nActionType=AR_FILTER_ACTION_NOTIFY; nActionType<=LAST_FILTER_ACTION; nActionType++)
		{		
			int nCountIf = 0;
			int nCountElse = 0;

			// Create a new webpage for every action
			FilterActionDetails(nActionType, nCountIf, nCountElse);

			strmTmp.str("");
			strmTmp << URLLink(CAREnum::FilterAction(nActionType), CPageParams(PAGE_ACTION_OBJLIST, AR_STRUCT_ITEM_XML_FILTER, nActionType), ImageTag::Document, rootLevel) << " (" << nCountIf << "/" << nCountElse << ")";

			CTableRow row("");
			row.AddCell(CTableCell(strmTmp.str()));		
			tbl.AddRow(row);	
		}

		webPage.AddContent(tbl.ToXHtml());

		webPage.SaveInFolder(file->GetPath());
	}
	catch(exception& e)
	{
		cout << "EXCEPTION FilterActionList: " << e.what() << endl;
	}
}

void CDocMain::FilterActionDetails(int nActionType, int &ifCount, int &elseCount)
{
	CPageParams file(PAGE_ACTION_OBJLIST, AR_STRUCT_ITEM_XML_FILTER, nActionType);

	try
	{
		int rootLevel = file->GetRootLevel();

		//stringstream strmTmp;
		//strmTmp << "index_action_" << nActionType;
		CWebPage webPage(file->GetFileName(), "Filter Actions", rootLevel, this->pInside->appConfig);

		CFilterTable *tbl = new CFilterTable(*this->pInside);

		unsigned int filterCount = pInside->filterList.GetCount();
		for (unsigned int filterIndex = 0; filterIndex < filterCount; ++filterIndex )
		{	
			CARFilter flt(filterIndex);

#if AR_CURRENT_API_VERSION >= AR_API_VERSION_764
			// Hide overlaid objects on the list
			if (pInside->appConfig.bOverlaySupport && !IsVisibleObject(flt))
				continue;
#endif

			int nActionExists = 0;
			const ARFilterActionList &ifActions = flt.GetIfActions();
			const ARFilterActionList &elseActions = flt.GetElseActions();

			//actionList
			for(unsigned int nAction=0; nAction < ifActions.numItems; ++nAction)
			{
				if (ifActions.actionList[nAction].action == nActionType)
				{		
					++ifCount;
					nActionExists++;
				}
			}

			//elseList
			for(unsigned int nAction=0; nAction < elseActions.numItems; ++nAction)
			{
				if (elseActions.actionList[nAction].action == nActionType)
				{
					++elseCount;
					nActionExists++;
				}
			}

			if(nActionExists > 0)
			{
				tbl->AddRow(filterIndex, rootLevel);
			}
		}

		stringstream strmTmp;
		strmTmp << URLLink("Filter", CPageParams(PAGE_ACTION_OVERVIEW, AR_STRUCT_ITEM_XML_FILTER), ImageTag::Filter, rootLevel) << " with " << CAREnum::FilterAction(nActionType) << " action";
		tbl->SetDescription(strmTmp.str());

		webPage.AddContent(tbl->Print());
		delete tbl;

		webPage.SaveInFolder(file->GetPath());
	}
	catch(exception& e)
	{
		cout << "EXCEPTION FilterActionDetails: " << e.what() << endl;
	}
}

void CDocMain::FilterErrorHandlers()
{
	CPageParams file(PAGE_FILTER_ERRORHANDLERS);

	try
	{
		int rootLevel = file->GetRootLevel();
		CWebPage webPage(file->GetFileName(), "Filter Error Handlers", rootLevel, this->pInside->appConfig);

		CFilterTable tbl(*pInside);

		unsigned int filterCount = pInside->filterList.GetCount();
		for (unsigned int filterIndex = 0; filterIndex < filterCount; ++filterIndex)
		{
			CARFilter flt(filterIndex);
			
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_764
			// Hide overlaid objects on the list
			if (pInside->appConfig.bOverlaySupport && !IsVisibleObject(flt))
				continue;
#endif

			if (flt.ErrorCallers().size() > 0)
			{
				tbl.AddRow(filterIndex, rootLevel);
			}
		}

		stringstream strm;
		strm << CWebUtil::LinkToFilterIndex(tbl.NumRows(), rootLevel) << " used as Error Handler";

		tbl.SetDescription(strm.str());
		webPage.AddContent(tbl.Print());

		webPage.SaveInFolder(file->GetPath());
	}
	catch(exception& e)
	{
		cout << "EXCEPTION FilterErrorHandlers: " << e.what() << endl;
	}
}

unsigned int CDocMain::EscalationList()
{
	CPageParams file(PAGE_OVERVIEW, AR_STRUCT_ITEM_XML_ESCALATION);
	unsigned int objCount = 0;

	try
	{
		rootLevel = file->GetRootLevel();
		CEscalTable tbl(*this->pInside);
		LetterFilterControl letterFilter;

		unsigned int escalCount = pInside->escalationList.GetCount();
		for (unsigned int escalIndex = 0; escalIndex < escalCount; ++escalIndex)
		{
			CAREscalation escalation(escalIndex);

#if AR_CURRENT_API_VERSION >= AR_API_VERSION_764
			if (pInside->appConfig.bOverlaySupport && !IsVisibleObject(escalation))
				continue;
#endif

			letterFilter.IncStartLetterOf(escalation);
			objCount++;
		}
		if (objCount > 0)
		{
			tbl.RemoveEmptyMessageRow();
		}

		CWebPage webPage(file->GetFileName(), "Escalation List", rootLevel, this->pInside->appConfig);
		webPage.GetReferenceManager()
			.AddScriptReference("img/object_list.js")
			.AddScriptReference("img/escalationList.js")
			.AddScriptReference("img/jquery.timers.js")
			.AddScriptReference("img/jquery.address.min.js");

		stringstream strmTmp;
		strmTmp << "<span id='esclationListFilterResultCount'></span>" << CWebUtil::LinkToEscalationIndex(objCount, rootLevel);
		EscalationListJson(strmTmp);
		strmTmp << CreateEscalationFilterControl() << endl;
		strmTmp << letterFilter;
		strmTmp << tbl;
		webPage.AddContent(strmTmp.str());

		webPage.SaveInFolder(file->GetPath());
	}
	catch(exception& e)
	{
		cout << "EXCEPTION EscalationList: " << e.what() << endl;
	}
	return objCount;
}

void CDocMain::EscalationListJson(std::ostream &strm)
{
	Document document;
	Document::AllocatorType &alloc = document.GetAllocator();
	document.SetArray();

	unsigned int escalCount = this->pInside->escalationList.GetCount();
	for (unsigned int escalIndex = 0; escalIndex < escalCount; ++escalIndex)
	{	
		CAREscalation escalation(escalIndex);

#if AR_CURRENT_API_VERSION >= AR_API_VERSION_764
		if (pInside->appConfig.bOverlaySupport && !IsVisibleObject(escalation))
			continue;
#endif

		CARProplistHelper props(&escalation.GetPropList());
		CPageParams escalDetailPage(PAGE_DETAILS, &escalation);

		// create a new json row and make it an array
		Value escalRow;
		escalRow.SetArray();

		// now build the needed temporary variables
		string strName = escalation.GetName();			
		string strExecuteOn = escalation.GetExecuteOn();
		string strModifiedDate = CUtil::DateTimeToString(escalation.GetTimestamp());
		string strLink = CWebUtil::GetRelativeURL(rootLevel, escalDetailPage);
		
		// build the values
		Value valName(strName.c_str(), static_cast<SizeType>(strName.size()), alloc);
		Value valExecuteOn(strExecuteOn.c_str(), static_cast<SizeType>(strExecuteOn.size()), alloc);
		Value valModifiedDate(strModifiedDate.c_str(), static_cast<SizeType>(strModifiedDate.size()), alloc);
		Value valLink(strLink.c_str(), static_cast<SizeType>(strLink.size()), alloc);

		// add everything to the row
		escalRow.PushBack(valName, alloc);
		escalRow.PushBack(escalation.GetEnabled(), alloc);
		escalRow.PushBack(valExecuteOn, alloc);
		escalRow.PushBack(escalation.GetIfActions().numItems, alloc);
		escalRow.PushBack(escalation.GetElseActions().numItems, alloc);
		escalRow.PushBack(valModifiedDate, alloc);
		escalRow.PushBack(escalation.GetLastChanged(), alloc);
		escalRow.PushBack(valLink, alloc);
		escalRow.PushBack(escalation.GetPool(), alloc);
		escalRow.PushBack(escalation.GetOverlayType(), alloc);

		// add the row to the document
		document.PushBack(escalRow, alloc);
	}

	GenericWriteStream output(strm);
	Writer<GenericWriteStream> writer(output);

	strm << endl << "<script type=\"text/javascript\">" << endl;
	strm << "var escalationList = "; document.Accept(writer); strm << ";";
	strm << "var rootLevel = " << rootLevel << ";";
	strm << endl;
	strm << "</script>" << endl;
}

void CDocMain::EscalationActionList()
{
	CPageParams file(PAGE_ACTION_OVERVIEW, AR_STRUCT_ITEM_XML_ESCALATION);

	try
	{
		int rootLevel = file->GetRootLevel();
		CWebPage webPage(file->GetFileName(), "Escalation Actions", rootLevel, this->pInside->appConfig);

		CTable tbl("escalList", "TblObjectList");

		stringstream strmTmp;
		strmTmp << URLLink("Escalation", CPageParams(PAGE_OVERVIEW, AR_STRUCT_ITEM_XML_ESCALATION), ImageTag::Escalation, rootLevel) << " with a specified action in If/Else list:";

		tbl.description = strmTmp.str();
		tbl.AddColumn(100, "Escalation Action (Items count if/else)");

#if AR_CURRENT_API_VERSION >= AR_API_VERSION_750 // Version 7.5 and higher
#define LAST_ESCLATION_ACTION 12
#else
#define LAST_ESCLATION_ACTION 11
#endif

		//Search all possible actions
		for(int nActionType=AR_FILTER_ACTION_NOTIFY; nActionType<=LAST_ESCLATION_ACTION; nActionType++)
		{
			switch (nActionType)
			{
			case AR_FILTER_ACTION_GOTOACTION:
			case AR_FILTER_ACTION_CALLGUIDE:
			case AR_FILTER_ACTION_EXITGUIDE:
			case AR_FILTER_ACTION_GOTOGUIDELABEL:
				continue;
			}

			int nCountIf = 0;
			int nCountElse = 0;

			//Create a new webpage for every action
			EscalationActionDetails(nActionType, nCountIf, nCountElse);

			strmTmp.str("");
			strmTmp << URLLink(CAREnum::FilterAction(nActionType), CPageParams(PAGE_ACTION_OBJLIST, AR_STRUCT_ITEM_XML_ESCALATION, nActionType), ImageTag::Document, rootLevel) << " (" << nCountIf << "/" << nCountElse << ")";

			CTableRow row("");
			row.AddCell(CTableCell(strmTmp.str()));
			tbl.AddRow(row);
		}

		webPage.AddContent(tbl.ToXHtml());

		webPage.SaveInFolder(file->GetPath());
	}
	catch(exception& e)
	{
		cout << "EXCEPTION EscalationActionList: " << e.what() << endl;
	}
}


void CDocMain::EscalationActionDetails(int nActionType, int &ifCount, int &elseCount)
{
	CPageParams file(PAGE_ACTION_OBJLIST, AR_STRUCT_ITEM_XML_ESCALATION, nActionType);

	try
	{
		int rootLevel = file->GetRootLevel();

		//stringstream strmTmp;
		//strmTmp << "index_action_" << nActionType;
		CWebPage webPage(file->GetFileName(), "Escalation Actions", rootLevel, this->pInside->appConfig);

		CEscalTable *tbl = new CEscalTable(*this->pInside);

		unsigned int escalCount = pInside->escalationList.GetCount();
		for (unsigned int escalIndex = 0; escalIndex < escalCount; ++escalIndex)
		{	
			CAREscalation esc(escalIndex);

#if AR_CURRENT_API_VERSION >= AR_API_VERSION_764
			// Hide overlaid objects on the list
			if (pInside->appConfig.bOverlaySupport && !IsVisibleObject(esc))
				continue;
#endif

			int nActionExists = 0;
			const ARFilterActionList &ifActions = esc.GetIfActions();
			const ARFilterActionList &elseActions = esc.GetElseActions();

			//actionList
			for(unsigned int nAction=0; nAction < ifActions.numItems; ++nAction)
			{
				if(ifActions.actionList[nAction].action == nActionType)
				{
					++ifCount;
					++nActionExists;
				}
			}		

			//elseList
			for(unsigned int nAction=0; nAction < elseActions.numItems; ++nAction)
			{
				if(elseActions.actionList[nAction].action == nActionType)
				{
					++elseCount;
					nActionExists++;
				}
			}		

			if(nActionExists > 0)
			{
				tbl->AddRow(escalIndex, rootLevel);
			}
		}

		stringstream strmTmp;
		strmTmp << URLLink("Escalation", CPageParams(PAGE_ACTION_OVERVIEW, AR_STRUCT_ITEM_XML_ESCALATION), ImageTag::Escalation, rootLevel) << " with " << CAREnum::FilterAction(nActionType) << " action";
		tbl->SetDescription(strmTmp.str());

		webPage.AddContent(tbl->Print());
		delete tbl;

		webPage.SaveInFolder(file->GetPath());
	}
	catch(exception& e)
	{
		cout << "EXCEPTION EscalationActionDetails: " << e.what() << endl;
	}
}


unsigned int CDocMain::CharMenuList()
{
	CPageParams file(PAGE_OVERVIEW, AR_STRUCT_ITEM_XML_CHAR_MENU);
	unsigned int objCount = 0;

	try
	{
		rootLevel = file->GetRootLevel();
		CMenuTable tbl(*this->pInside);
		LetterFilterControl letterFilter;

		unsigned int menuCount = this->pInside->menuList.GetCount();
		for ( unsigned int menuIndex = 0; menuIndex < menuCount; ++menuIndex )
		{	
			CARCharMenu menu(menuIndex);

#if AR_CURRENT_API_VERSION >= AR_API_VERSION_764
			if (pInside->appConfig.bOverlaySupport && !IsVisibleObject(menu))
				continue;
#endif

			letterFilter.IncStartLetterOf(menu);
			objCount++;
		}
		if (objCount > 0)
		{
			tbl.RemoveEmptyMessageRow();
		}

		CWebPage webPage(file->GetFileName(), "Menu List", 1, this->pInside->appConfig);

		webPage.GetReferenceManager()
			.AddScriptReference("img/object_list.js")
			.AddScriptReference("img/menuList.js")
			.AddScriptReference("img/jquery.timers.js")
			.AddScriptReference("img/jquery.address.min.js");

		stringstream strmTmp;
		strmTmp << "<span id='menuListFilterResultCount'></span>" << CWebUtil::LinkToMenuIndex(objCount, rootLevel);
		MenuListJson(strmTmp);
		strmTmp << CreateMenuFilterControl() << endl;
		strmTmp << letterFilter;
		strmTmp << tbl;

		webPage.AddContent(strmTmp.str());
		webPage.AddContent("(!) Menu is not attached to a character field and no Active Link \"Change Field\" Action sets the menu to a field.");

		webPage.SaveInFolder(file->GetPath());
	}
	catch(exception& e)
	{
		cout << "EXCEPTION CharMenuList: " << e.what() << endl;
	}
	return objCount;
}

void CDocMain::MenuListJson(std::ostream &strm)
{
	Document document;
	Document::AllocatorType &alloc = document.GetAllocator();
	document.SetArray();

	unsigned int menuCount = this->pInside->menuList.GetCount();
	for (unsigned int menuIndex = 0; menuIndex < menuCount; ++menuIndex)
	{
		CARCharMenu menu(menuIndex);

#if AR_CURRENT_API_VERSION >= AR_API_VERSION_764
		if (pInside->appConfig.bOverlaySupport && !IsVisibleObject(menu))
			continue;
#endif

		CPageParams menuDetailPage(PAGE_DETAILS, &menu);

		// create a new json row and make it an array
		Value menuRow;
		menuRow.SetArray();

		// now build the needed temporary variables
		string strName = menu.GetName();
		string strModifiedDate = CUtil::DateTimeToString(menu.GetTimestamp());
		string strLink = CWebUtil::GetRelativeURL(rootLevel, menuDetailPage);

		// build the values
		Value valName(strName.c_str(), static_cast<SizeType>(strName.size()), alloc);
		Value valModifiedDate(strModifiedDate.c_str(), static_cast<SizeType>(strModifiedDate.size()), alloc);
		Value valLink(strLink.c_str(), static_cast<SizeType>(strLink.size()), alloc);

		// add everything to the row
		menuRow.PushBack(valName, alloc);
		menuRow.PushBack(menu.GetDefinition().menuType, alloc);
		menuRow.PushBack(menu.GetRefreshCode(), alloc);
		menuRow.PushBack(valModifiedDate, alloc);
		menuRow.PushBack(menu.GetLastChanged(), alloc);
		menuRow.PushBack(valLink, alloc);
		menuRow.PushBack(menu.GetOverlayType(), alloc);
		menuRow.PushBack((menu.IsUsedInWorkflow() ? 1 : 0), alloc);

		// add the row to the document
		document.PushBack(menuRow, alloc);
	}

	GenericWriteStream output(strm);
	Writer<GenericWriteStream> writer(output);

	strm << endl << "<script type=\"text/javascript\">" << endl;
	strm << "var menuList = "; document.Accept(writer); strm << ";";
	strm << "var rootLevel = " << rootLevel << ";";
	strm << endl;
	strm << "</script>" << endl;
}

unsigned int CDocMain::ContainerList(int nType, string title)
{
	unsigned int objCount = 0;
	CPageParams file(PAGE_OVERVIEW, AR_STRUCT_ITEM_XML_CONTAINER, nType);

	try
	{
		rootLevel = file->GetRootLevel();
		CContainerTable tbl(*this->pInside, false);
		LetterFilterControl letterFilter;

		unsigned int cntCount = this->pInside->containerList.GetCount();
		for ( unsigned int cntIndex = 0; cntIndex < cntCount; ++cntIndex )
		{	
			CARContainer cont(cntIndex);

#if AR_CURRENT_API_VERSION >= AR_API_VERSION_764
			if (pInside->appConfig.bOverlaySupport && !IsVisibleObject(cont))
				continue;
#endif

			if (cont.GetType() == nType)	// the type must match
			{
				letterFilter.IncStartLetterOf(cont);
				tbl.AddRowJson(cont, rootLevel);
				objCount++;
			}
		}
		if (objCount > 0)
		{
			tbl.RemoveEmptyMessageRow();
		}

		CWebPage webPage(file->GetFileName(), title, rootLevel, this->pInside->appConfig);
		
		webPage.GetReferenceManager()
			.AddScriptReference("img/object_list.js")
			.AddScriptReference("img/containerList.js")
			.AddScriptReference("img/jquery.timers.js")
			.AddScriptReference("img/jquery.address.min.js");

		stringstream strmTmp;
		strmTmp << "<span id='containerListResultCount'></span>" << CWebUtil::LinkToContainer(objCount, rootLevel, nType) << endl;
		strmTmp << "<script type=\"text/javascript\">" << endl;
		strmTmp << "var rootLevel = " << rootLevel << ";";
		strmTmp << "var containerType = " << nType << ";";
		strmTmp << endl;
		strmTmp << "</script>" << endl;
		strmTmp << CreateContainerFilterControl() << endl;
		strmTmp << letterFilter;
		strmTmp << tbl;
		webPage.AddContent(strmTmp.str());

		if (nType == ARCON_GUIDE || nType == ARCON_FILTER_GUIDE)
		{
			webPage.AddContent("(!) No Active Link / Filter \"CallGuide\" Action uses this Guide.");
		}

		webPage.SaveInFolder(file->GetPath());
	}
	catch(exception& e)
	{
		cout << "EXCEPTION ContainerList: " << e.what() << endl;
	}
	return objCount;
}

void CDocMain::RoleList()
{
	CPageParams file(PAGE_OVERVIEW, AR_STRUCT_ITEM_XML_ROLE);

	try
	{
		int rootLevel = file->GetRootLevel();
		CRoleTable tbl(*this->pInside);
		LetterFilterControl letterFilter;

		unsigned int roleCount = this->pInside->roleList.GetCount();
		for (unsigned int roleIndex = 0; roleIndex < roleCount; ++roleIndex)
		{	
			CARRole role(roleIndex);

			letterFilter.IncStartLetterOf(role);
			tbl.AddRowJson(role, rootLevel);
		}
		if (roleCount > 0)
		{
			tbl.RemoveEmptyMessageRow();
		}

		CWebPage webPage(file->GetFileName(), "Role List", rootLevel, this->pInside->appConfig);

		webPage.GetReferenceManager()
			.AddScriptReference("img/object_list.js")
			.AddScriptReference("img/roleList.js")
			.AddScriptReference("img/jquery.timers.js")
			.AddScriptReference("img/jquery.address.min.js");

		stringstream strmTmp;
		strmTmp << "<span id='roleListFilterResultCount'></span>" << CWebUtil::LinkToRoleIndex(roleCount, rootLevel);
		strmTmp << CreateRoleFilterControl();
		strmTmp << letterFilter;
		strmTmp << tbl;
		webPage.AddContent(strmTmp.str());

		webPage.SaveInFolder(file->GetPath());
	}
	catch(exception& e)
	{
		cout << "EXCEPTION RoleList: " << e.what() << endl;
	}
}

void CDocMain::GroupList()
{
	CPageParams file(PAGE_OVERVIEW, AR_STRUCT_ITEM_XML_GROUP);

	try
	{
		int rootLevel = file->GetRootLevel();
		CGroupTable tbl(*this->pInside);
		LetterFilterControl letterFilter;

		unsigned int groupCount = pInside->groupList.GetCount();
		for (unsigned int groupIndex = 0; groupIndex < groupCount; ++groupIndex)
		{	
			CARGroup grp(groupIndex);
			letterFilter.IncStartLetterOf(grp);
			tbl.AddRowJson(grp, rootLevel);
		}
		if (groupCount > 0)
		{
			tbl.RemoveEmptyMessageRow();
		}

		CWebPage webPage(file->GetFileName(), "Group List", rootLevel, this->pInside->appConfig);

		webPage.GetReferenceManager()
			.AddScriptReference("img/object_list.js")
			.AddScriptReference("img/groupList.js")
			.AddScriptReference("img/jquery.timers.js")
			.AddScriptReference("img/jquery.address.min.js");

		stringstream strmTmp;
		strmTmp << "<span id='groupListFilterResultCount'></span>" << CWebUtil::LinkToGroupIndex(groupCount, rootLevel);
		strmTmp << CreateGroupFilterControl() << endl;
		strmTmp << letterFilter;
		strmTmp << tbl;
		webPage.AddContent(strmTmp.str());

		webPage.SaveInFolder(file->GetPath());
	}
	catch(exception& e)
	{
		cout << "EXCEPTION GroupList: " << e.what() << endl;
	}
}

void CDocMain::UserList(string searchChar, std::vector<int>& objCountPerLetter)
{
	unsigned int page = (unsigned int)searchChar[0];
	CPageParams file(page, AR_STRUCT_ITEM_XML_USER);

	try
	{
		int rootLevel = file->GetRootLevel();
		CUserTable tbl(*this->pInside);

		unsigned int userCount = this->pInside->userList.GetCount();
		for (unsigned int userIndex = 0; userIndex < userCount; ++userIndex)
		{	
			CARUser user(userIndex);

			bool bInsert = false;
			if(searchChar == "*")  //All objecte
			{
				// the first call to this function holds always "*" as search char. That's the
				// best time to sum up the object count per letter.
				string firstChar = user.GetNameFirstChar();
				if (firstChar.empty()) firstChar = "*";
				int index = CARObject::GetFirstCharIndex(firstChar[0]);
				++(objCountPerLetter[index]);
				bInsert = true;
			}
			else if(searchChar == "#")
			{
				if(!user.NameStandardFirstChar())
				{
					bInsert = true;
				}
			}
			else
			{
				if(user.GetNameFirstChar() == searchChar)
				{
					bInsert = true;
				}
			}

			if(bInsert)
			{	
				tbl.AddRow(user, rootLevel);
			}
		}

		if (tbl.NumRows() > 0 || searchChar == "*")
		{
			CWebPage webPage(file->GetFileName(), "User List", rootLevel, this->pInside->appConfig);

			stringstream strmTmp;
			strmTmp << CWebUtil::LinkToUserIndex(tbl.NumRows(), rootLevel) << ShortMenu(searchChar, file, objCountPerLetter);

			tbl.SetDescription(strmTmp.str());
			webPage.AddContent(tbl.Print());

			webPage.SaveInFolder(file->GetPath());
		}
	}
	catch(exception& e)
	{
		cout << "EXCEPTION UserList: " << e.what() << endl;
	}
}

void CDocMain::GlobalFieldList()
{
	CPageParams file(PAGE_GLOBALFIELS);

	try
	{
		int rootLevel = file->GetRootLevel();
		CWebPage webPage(file->GetFileName(), "Global Fields", rootLevel, this->pInside->appConfig);	

		// outer table
		CTable tbl("fieldListAll", "TblObjectList");
		tbl.AddColumn(20, "GlobalFieldId");
		tbl.AddColumn(80, "References");

		// inner table; reused per global field id
		CTable innerTbl("refList", "TblObjectList");
		innerTbl.AddColumn(50, "Schema Name");
		innerTbl.AddColumn(50, "Field Name");

		int currentGlobalFieldId = 0;

		//Search all global fields
		list<CARGlobalField>::iterator listIter = this->pInside->globalFieldList.begin();
		list<CARGlobalField>::iterator listEnd = this->pInside->globalFieldList.end();
		for (; listIter != listEnd; ++listIter )
		{	
			CARGlobalField &glField = (*listIter);
			CARField fld(glField.schemaInsideId, glField.fieldId);

			if (currentGlobalFieldId != fld.GetFieldId())
			{
				// add the previous global field to the table before resetting
				if (currentGlobalFieldId != 0)
					AddGlobalFieldRow(tbl, currentGlobalFieldId, innerTbl);

				// reset for current field
				currentGlobalFieldId = fld.GetFieldId();
				innerTbl.ClearRows();
			}

			CTableRow innerTblRow("");
			innerTblRow.AddCellList(
				this->pInside->LinkToSchema(glField.schemaInsideId, rootLevel),
				this->pInside->LinkToField(glField.schemaInsideId, fld.GetFieldId(), rootLevel));

			innerTbl.AddRow(innerTblRow);
		}
		if (innerTbl.NumRows() > 0)
			AddGlobalFieldRow(tbl, currentGlobalFieldId, innerTbl);

		stringstream strmTmp;
		strmTmp << ImageTag(ImageTag::Document, rootLevel) << tbl.NumRows() << " Global Fields" << endl;
		tbl.description = strmTmp.str();

		webPage.AddContent(tbl.ToXHtml());
		webPage.SaveInFolder(file->GetPath());
	}
	catch(exception& e)
	{
		cout << "EXCEPTION GlobalFieldList: " << e.what() << endl;
	}
}

void CDocMain::AddGlobalFieldRow(OUTPUT::CTable &tbl, int fieldId, OUTPUT::CTable &fields)
{
	CTableRow row("");
	row.AddCell(CTableCell(fieldId));
	row.AddCell(fields.ToXHtml());
	tbl.AddRow(row);
}

void CDocMain::MessageList()
{
	CPageParams file(PAGE_MESSAGES);

	try
	{
		int rootLevel = file->GetRootLevel();
		list<CMessageItem> listMsgItem;

		//Search all activelinks
		unsigned int alCount = pInside->alList.GetCount();
		for (unsigned int alIndex = 0; alIndex < alCount; ++alIndex)
		{
			CARActiveLink al(alIndex);

#if AR_CURRENT_API_VERSION >= AR_API_VERSION_764
			if (pInside->appConfig.bOverlaySupport && !IsVisibleObject(al))
				continue;
#endif

			CARSchema schema(al.GetSchemaList().u.schemaList[0].nameList[0]);

			for (unsigned int ifElse = 0; ifElse < 2; ++ifElse)
			{
				const ARActiveLinkActionList &actions = (ifElse == 0 ? al.GetIfActions() : al.GetElseActions());

				//actionList
				for(unsigned int nAction=0; nAction < actions.numItems; nAction++)
				{
					if(actions.actionList[nAction].action == AR_ACTIVE_LINK_ACTION_MESSAGE)
					{
						stringstream strmTmp;
						strmTmp.str("");
						strmTmp << (ifElse == 0 ? "If" : "Else") << "-Action " << nAction;

						ARMessageStruct &msg = actions.actionList[nAction].u.message;

						CMessageItem msgItem;
						msgItem.msgDetails = strmTmp.str();
						msgItem.msgNumber = msg.messageNum;
						msgItem.msgText = (schema.Exists() ? pInside->TextFindFields(msg.messageText, "$", schema.GetInsideId(), rootLevel, true, NULL) : msg.messageText);
						msgItem.msgType = msg.messageType;
						msgItem.objectLink = URLLink(al, rootLevel);
						listMsgItem.push_back(msgItem);
					}
				}
			}
		}


		//Search all filter
		unsigned int filterCount = pInside->filterList.GetCount();
		for (unsigned int filterIndex = 0; filterIndex < filterCount; ++filterIndex )
		{
			CARFilter flt(filterIndex);

#if AR_CURRENT_API_VERSION >= AR_API_VERSION_764
			if (pInside->appConfig.bOverlaySupport && !IsVisibleObject(flt))
				continue;
#endif

			CARSchema schema(flt.GetSchemaList().u.schemaList[0].nameList[0]);

			for (unsigned int ifElse = 0; ifElse < 2; ++ifElse)
			{
				const ARFilterActionList &actions = (ifElse == 0 ? flt.GetIfActions() : flt.GetElseActions());

				//actionList
				for(unsigned int nAction=0; nAction < actions.numItems; ++nAction)
				{
					if(actions.actionList[nAction].action == AR_FILTER_ACTION_MESSAGE)
					{
						stringstream strmTmp;
						strmTmp.str("");
						strmTmp << (ifElse == 0 ? "If" : "Else") << "-Action " << nAction;

						const ARFilterStatusStruct &msg = actions.actionList[nAction].u.message;

						CMessageItem msgItem;
						msgItem.msgDetails = strmTmp.str();
						msgItem.msgNumber = msg.messageNum;
						msgItem.msgText = (schema.Exists() ? pInside->TextFindFields(msg.messageText, "$", schema.GetInsideId(), rootLevel, true, NULL) : msg.messageText);
						msgItem.msgType = msg.messageType;
						msgItem.objectLink = URLLink(flt, rootLevel);
						listMsgItem.push_back(msgItem);
					}
				}
			}
		}


		CWebPage webPage(file->GetFileName(), "Messages", rootLevel, this->pInside->appConfig);
		if(listMsgItem.size() > 0)
		{
			Sort(listMsgItem);

			//Print all Messages		
			CTable tbl("fieldListAll", "TblObjectList");
			tbl.AddColumn(5, "Number");
			tbl.AddColumn(25, "Object Name");
			tbl.AddColumn(5, "Details");
			tbl.AddColumn(5, "Type");	
			tbl.AddColumn(60, "Text");

			list<CMessageItem>::iterator msgIter;	
			CMessageItem *msg;
			for ( msgIter = listMsgItem.begin(); msgIter != listMsgItem.end(); msgIter++ )
			{
				msg = &(*msgIter);

				CTableRow row("");
				row.AddCell( CTableCell(msg->msgNumber));
				row.AddCell( CTableCell(msg->objectLink));
				row.AddCell( CTableCell(msg->msgDetails));
				row.AddCell( CTableCell(CAREnum::MessageType(msg->msgType)));
				row.AddCell( CTableCell(msg->msgText));

				tbl.AddRow(row);
			}

			webPage.AddContent(tbl.ToXHtml());
		}
		else
		{
			webPage.AddContent("No messages loaded.");
		}

		webPage.SaveInFolder(file->GetPath());
	}
	catch(exception& e)
	{
		cout << "EXCEPTION MessageList: " << e.what() << endl;
	}
}

void CDocMain::NotificationList()
{
	CPageParams file(PAGE_NOTIFICATIONS);

	try
	{
		int rootLevel = file->GetRootLevel();

		//Print all Messages		
		CTable tbl("fieldListAll", "TblObjectList");
		tbl.AddColumn(25, "Object Name");
		tbl.AddColumn(5, "Details");
		tbl.AddColumn(5, "Type");	
		tbl.AddColumn(60, "Text");

		//Search all filter
		unsigned int filterCount = pInside->filterList.GetCount();
		for (unsigned int filterIndex = 0; filterIndex < filterCount; ++filterIndex)
		{
			CARFilter flt(filterIndex);

#if AR_CURRENT_API_VERSION >= AR_API_VERSION_764
			// Hide overlaid objects on the list
			if (pInside->appConfig.bOverlaySupport && !IsVisibleObject(flt))
				continue;
#endif

			CARSchema schema(flt.GetSchemaList().u.schemaList[0].nameList[0]);

			for (unsigned int ifElse = 0; ifElse < 2; ++ifElse)
			{
				const ARFilterActionList &actions = (ifElse == 0 ? flt.GetIfActions() : flt.GetElseActions());

				//actionList
				for(unsigned int nAction=0; nAction < actions.numItems; ++nAction)
				{
					if(actions.actionList[nAction].action == AR_FILTER_ACTION_NOTIFY)
					{
						if (!schema.Exists()) 
							continue;

						const ARFilterActionNotify& notifyAction = actions.actionList[nAction].u.notify;

						stringstream strm;
						strm << (ifElse == 0 ? "If" : "Else") << "-Action " << nAction;

						stringstream text;
						if (notifyAction.subjectText != NULL && notifyAction.subjectText[0] != 0)
							text << pInside->TextFindFields(notifyAction.subjectText, "$", schema.GetInsideId(), rootLevel, true, NULL) << "<BR/>";
						if (notifyAction.notifyText != NULL)
							text << pInside->TextFindFields(notifyAction.notifyText, "$", schema.GetInsideId(), rootLevel, true, NULL);

						CTableRow row("");
						row.AddCell(URLLink(flt, rootLevel));
						row.AddCell(strm.str());
						row.AddCell(CAREnum::NotifyMechanism(notifyAction.notifyMechanism)); // Type of Notifcation
						row.AddCell(text.str());

						tbl.AddRow(row);
					}
				}
			}
		}

		//Search all escalations
		unsigned int escalCount = pInside->escalationList.GetCount();
		for (unsigned int escalIndex = 0; escalIndex < escalCount; ++escalIndex)
		{
			CAREscalation esc(escalIndex);

#if AR_CURRENT_API_VERSION >= AR_API_VERSION_764
			// Hide overlaid objects on the list
			if (pInside->appConfig.bOverlaySupport && !IsVisibleObject(esc))
				continue;
#endif

			CARSchema schema(esc.GetSchemaList().u.schemaList[0].nameList[0]);

			for (unsigned int ifElse = 0; ifElse < 2; ++ifElse)
			{
				const ARFilterActionList &actions = (ifElse == 0 ? esc.GetIfActions() : esc.GetElseActions());

				//actionList
				for(unsigned int nAction=0; nAction < actions.numItems; ++nAction)
				{
					if(actions.actionList[nAction].action == AR_FILTER_ACTION_NOTIFY)
					{
						if (!schema.Exists()) 
							continue;

						const ARFilterActionNotify& notifyAction = actions.actionList[nAction].u.notify;

						stringstream strm;
						strm << (ifElse == 0 ? "If" : "Else") << "-Action " << nAction;

						stringstream text;
						if (notifyAction.subjectText != NULL && notifyAction.subjectText[0] != 0)
							text << pInside->TextFindFields(notifyAction.subjectText, "$", schema.GetInsideId(), rootLevel, true, NULL) << "<BR/>";
						if (notifyAction.notifyText != NULL)
							text << pInside->TextFindFields(notifyAction.notifyText, "$", schema.GetInsideId(), rootLevel, true, NULL);

						CTableRow row("");
						row.AddCell(URLLink(esc, rootLevel));
						row.AddCell(strm.str());
						row.AddCell(CAREnum::NotifyMechanism(notifyAction.notifyMechanism)); // Type of Notifcation
						row.AddCell(text.str());

						tbl.AddRow(row);
					}
				}
			}
		}

		CWebPage webPage(file->GetFileName(), "Notifications", rootLevel, this->pInside->appConfig);
		if(tbl.NumRows() > 0)
		{
			webPage.AddContent(tbl.ToXHtml());
		}
		else
		{
			webPage.AddContent("No notifications loaded.");
		}

		webPage.SaveInFolder(file->GetPath());
	}
	catch(exception& e)
	{
		cout << "EXCEPTION NotificationList: " << e.what() << endl;
	}
}

void CDocMain::Sort(list<CMessageItem> &listResult)
{
	listResult.sort(SortByMsgNum);
}

bool CDocMain::SortByMsgNum(const CMessageItem& t1, const CMessageItem& t2 )
{	
	return ( t1.msgNumber < t2.msgNumber);
}

string CDocMain::CreateStandardFilterControl(const string &inputControlId, const string &htmlPlaceHolder)
{
	stringstream content;
	content << "<span class='clearable'><label for='" << inputControlId << "'>Filter: </label><input id='" << inputControlId << "' class='data_field' type='text' ";
	if (!htmlPlaceHolder.empty()) { content << "placeholder='" << htmlPlaceHolder << "'"; }
	content << "/></span>";
	return content.str();
}

string CDocMain::CreateSchemaFilterControl()
{
	stringstream content;	
	content << "<div>" 
		<< "<div id='search'>" << CreateStandardFilterControl("formFilter", "search by name or id") << "</div>"
		<< "<div class='restrictions' style='max-width: 750px;'>"
			<< "<div id='clearButton'><button id='typeFilterNone'>Clear All</button>" << "</div>"
			<< "<div id='listMultiFilter'>"
				<< "<div class='left ptop'>Restrict results to: " << "</div>"
				<< "<div class='filterOpts'>"
					<< "<div class='checkbox-sl'><input id='typeFilterRegular' type='checkbox' value='1'/><label for='typeFilterRegular'>&nbsp;Regular</label>" << "</div>"
					<< "<div class='checkbox-sl'><input id='typeFilterJoin' type='checkbox' value='2'/><label for='typeFilterJoin'>&nbsp;Join</label>" << "</div>"
					<< "<div class='checkbox-sl'><input id='typeFilterView' type='checkbox' value='3'/><label for='typeFilterView'>&nbsp;View</label>" << "</div>"
					<< "<div class='checkbox-sl'><input id='typeFilterDialog' type='checkbox' value='4'/><label for='typeFilterDialog'>&nbsp;Dialog</label>" << "</div>"
					<< "<div class='checkbox-sl'><input id='typeFilterVendor' type='checkbox' value='5'/><label for='typeFilterVendor'>&nbsp;Vendor</label>" << "</div>"
					<< "<div class='checkbox-sl'><input id='typeFilterAudit' type='checkbox' value='100'/><label for='typeFilterAudit'>&nbsp;Audit</label>" << "</div>"
					<< "<div class='checkbox-sl'><input id='typeFilterArchive' type='checkbox' value='101'/><label for='typeFilterArchive'>&nbsp;Archive</label>" << "</div>"
				<< "</div>"
			<< "</div>"
		<< "</div>"
	<< "</div>";

	return content.str();
}

string CDocMain::CreateActlinkFilterControl()
{
	stringstream content;
	content << "<div>"
		<< CreateStandardFilterControl("actlinkFilter")
	<< "</div>";
	return content.str();
}

string CDocMain::CreateFilterFilterControl()
{
	stringstream content;
	content << "<div>"
		<< CreateStandardFilterControl("filterFilter")
		<< "<span class='multiFilter' id='multiFilter'>Restrict results to: "
		<< "<input id='typeFilterOnlyNone' type='checkbox' value='N'/><label for='typeFilterOnlyNone'>&nbsp;None</label>"
		<< "<input id='typeFilterModify' type='checkbox' value='2'/><label for='typeFilterModify'>&nbsp;Modify</label>"
		<< "<input id='typeFilterSubmit' type='checkbox' value='4'/><label for='typeFilterSubmit'>&nbsp;Submit</label>"
		<< "<input id='typeFilterDelete' type='checkbox' value='8'/><label for='typeFilterDelete'>&nbsp;Delete</label>"
		<< "<input id='typeFilterGetEntry' type='checkbox' value='1'/><label for='typeFilterGetEntry'>&nbsp;Get&nbsp;Entry</label>"
		<< "<input id='typeFilterMerge' type='checkbox' value='16'/><label for='typeFilterMerge'>&nbsp;Merge</label>"
		<< "<input id='typeFilterService' type='checkbox' value='64'/><label for='typeFilterService'>&nbsp;Service</label>"
		<< " <button id='typeFilterNone'>Clear All</button>"
		<< "</span>"
	<< "</div>";
	return content.str();
}

string CDocMain::CreateEscalationFilterControl()
{
	stringstream content;
	content << "<div>"
		<< CreateStandardFilterControl("escalationFilter")
	<< "</div>";
	return content.str();
}

string CDocMain::CreateMenuFilterControl()
{
	stringstream content;
	content << "<div>"
		<< CreateStandardFilterControl("menuFilter")
		<< "<span class='multiFilter' id='multiFilter'>Restrict results to: "
		<< "<input id='typeFilterCharacter' type='checkbox' value='1'/><label for='typeFilterCharacter'>&nbsp;Character</label>"
		<< "<input id='typeFilterSearch' type='checkbox' value='2'/><label for='typeFilterSearch'>&nbsp;Search</label>"
		<< "<input id='typeFilterFile' type='checkbox' value='3'/><label for='typeFilterFile'>&nbsp;File</label>"
		<< "<input id='typeFilterSQL' type='checkbox' value='4'/><label for='typeFilterSQL'>&nbsp;SQL</label>"
		<< "<input id='typeFilterDD' type='checkbox' value='6'/><label for='typeFilterDD'>&nbsp;Data&nbsp;Dictionary</label>"
		<< " <button id='typeFilterNone'>Clear All</button>"
		<< "</span>"
	<< "</div>";
	return content.str();
}

string CDocMain::CreateContainerFilterControl()
{
	stringstream content;
	content << "<div>"
		<< CreateStandardFilterControl("containerFilter")
	<< "</div>";
	return content.str();
}

string CDocMain::CreateImageFilterControl()
{
	stringstream content;
	content << "<div>"
		<< CreateStandardFilterControl("imageFilter")
	<< "</div>";
	return content.str();
}

string CDocMain::CreateGroupFilterControl()
{
	stringstream content;
	content << "<div>"
		<< CreateStandardFilterControl("groupFilter", "search by name or id") << " &nbsp;&nbsp;&nbsp; "
		<< "<span class='multiFilter' id='multiFilter'>Restrict results to: "
		<< "<input id='typeFilterRegular' type='checkbox' value='0'/><label for='typeFilterRegular'>&nbsp;Regular</label>"
		<< "<input id='typeFilterDynamic' type='checkbox' value='1'/><label for='typeFilterDynamic'>&nbsp;Dynamic</label>"
		<< "<input id='typeFilterComputed' type='checkbox' value='2'/><label for='typeFilterComputed'>&nbsp;Computed</label>"
		<< " <button id='typeFilterNone'>Clear All</button>"
		<< "</span>"
	<< "</div>";
	return content.str();
}

string CDocMain::CreateRoleFilterControl()
{
	stringstream content;
	content << "<div>"
		<< CreateStandardFilterControl("roleFilter", "search by name or id")
	<< "</div>";
	return content.str();
}

string CDocMain::CreateSchemaReferenceFilterControl()
{
	stringstream content;
	content << "<div>"
		<< "<div id='search'>" << CreateStandardFilterControl("workflowFilter") << "</div>"
		<< "<div class='restrictions' style='max-width: 1230px;'>"
			<< "<div id='clearButton'><button id='typeFilterNone'>Clear All</button>" << "</div>"
			<< "<div id='referenceMultiFilter'>"
				<< "<div class='left ptop'>Restrict results to: " << "</div>"
				<< "<div class='filterOpts'>"
					<< "<div class='checkbox-sref'><input id='typeFilterActiveLink' type='checkbox' value='1'/><label for='typeFilterActiveLink'>&nbsp;ActiveLink</label>" << "</div>"
					<< "<div class='checkbox-sref'><input id='typeFilterFilter' type='checkbox' value='2'/><label for='typeFilterFilter'>&nbsp;Filter</label>" << "</div>"
					<< "<div class='checkbox-sref'><input id='typeFilterEscalation' type='checkbox' value='3'/><label for='typeFilterEscalation'>&nbsp;Escalation</label>" << "</div>"
					<< "<div class='checkbox-sref'><input id='typeFilterALGuide' type='checkbox' value='4'/><label for='typeFilterALGuide'>&nbsp;ActiveLinkGuide</label>" << "</div>"
					<< "<div class='checkbox-sref'><input id='typeFilterFilterGuide' type='checkbox' value='5'/><label for='typeFilterFilterGuide'>&nbsp;FilterGuide</label>" << "</div>"
					<< "<div class='checkbox-sref'><input id='typeFilterApplication' type='checkbox' value='6'/><label for='typeFilterApplication'>&nbsp;Application</label>" << "</div>"
					<< "<div class='checkbox-sref'><input id='typeFilterPackList' type='checkbox' value='7'/><label for='typeFilterPackList'>&nbsp;PackingList</label>" << "</div>"
					<< "<div class='checkbox-sref'><input id='typeFilterWebservice' type='checkbox' value='8'/><label for='typeFilterWebservice'>&nbsp;Webservice</label>" << "</div>"
				<< "</div>"
			<< "</div>"
		<< "</div>"
	<< "</div>";
	return content.str();
}

void CDocMain::SchemaListJson(std::ostream &strm)
{
	Document document;
	Document::AllocatorType &alloc = document.GetAllocator();
	document.SetArray();

	unsigned int schemaCount = this->pInside->schemaList.GetCount();
	for (unsigned int schemaIndex = 0; schemaIndex < schemaCount; ++schemaIndex)
	{	
		CARSchema schema(schemaIndex);
		CPageParams schemaDetailPage(PAGE_DETAILS, &schema);
		
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_764
			if (pInside->appConfig.bOverlaySupport && !IsVisibleObject(schema))
				continue;
#endif

			// create a new json row and make it an array
			Value schemaRow;
			schemaRow.SetArray();

			// now build the needed temporary variables
			string strName = schema.GetName();
			string strWebAlias = schema.WebAlias();			
			string strModifiedDate = CUtil::DateTimeToString(schema.GetTimestamp());
			string strLink = CWebUtil::GetRelativeURL(rootLevel, schemaDetailPage);

			//// try to reduce data size
			//if (strLink.compare(strName) == 0)
			//	strLink == "";

			Value valName(strName.c_str(), static_cast<SizeType>(strName.size()), alloc);
			Value valWebAlias(strWebAlias.c_str(), static_cast<SizeType>(strWebAlias.size()), alloc);
			Value valModifiedDate(strModifiedDate.c_str(), static_cast<SizeType>(strModifiedDate.size()), alloc);
			Value valLink(strLink.c_str(), static_cast<SizeType>(strLink.size()), alloc);

			// add everything to the row
			schemaRow.PushBack(schema.GetDbTableId(), alloc);
			schemaRow.PushBack(valName, alloc);
			schemaRow.PushBack(valWebAlias, alloc);
			schemaRow.PushBack(static_cast<int>(schema.GetFields()->GetCount()), alloc);
			schemaRow.PushBack(static_cast<int>(schema.GetVUIs()->GetCount()), alloc);
			schemaRow.PushBack(static_cast<int>(schema.GetInternalSchemaType()), alloc);
			schemaRow.PushBack(valModifiedDate, alloc);
			schemaRow.PushBack(schema.GetLastChanged(), alloc);
			schemaRow.PushBack(valLink, alloc);
			schemaRow.PushBack(schema.GetOverlayType(), alloc);

			// add the row to the document
			document.PushBack(schemaRow, alloc);
	}

	GenericWriteStream output(strm);
	Writer<GenericWriteStream> writer(output);

	strm << endl << "<script type=\"text/javascript\">" << endl;
	strm << "var schemaList = "; document.Accept(writer); strm << ";";
	strm << "var rootLevel = " << rootLevel << ";";
	strm << endl;
	strm << "</script>" << endl;	
}
