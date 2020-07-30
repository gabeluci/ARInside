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
#include "DocSummaryInfo.h"
#include "../output/URLLink.h"

extern int nFilesCreated;

CDocSummaryInfo::CDocSummaryInfo(CARInside &arIn, string path)
{
	this->path = path;
	this->rootLevel = 0;
}

CDocSummaryInfo::~CDocSummaryInfo(void)
{
}

void CDocSummaryInfo::Documentation()
{
	try
	{		
		CWebPage webPage("index", "Documentation Index", rootLevel, this->pInside->appConfig);

		//ContentHead informations
		webPage.AddContentHead("Documentation index:");

		stringstream strm;
		strm.str("");

		CTable tblListObjectInfo("tblDocSummary", "TblObjectList");
		tblListObjectInfo.AddColumn(10, "Objects");		
		tblListObjectInfo.AddColumn(90, "Description");

		CTableRow row("cssStdRow");
		row.AddCell(CTableCell((int)this->activelinkCount));
		row.AddCell(CTableCell(URLLink("Active Links", CPageParams(PAGE_OVERVIEW, AR_STRUCT_ITEM_XML_ACTIVE_LINK), 0)));
		tblListObjectInfo.AddRow(row);


		row.ClearCells();
		row.AddCell(CTableCell((int)this->webserviceCount));
		row.AddCell(CTableCell(URLLink("Web Services", CPageParams(PAGE_OVERVIEW, AR_STRUCT_ITEM_XML_CONTAINER, ARCON_WEBSERVICE), 0)));
		tblListObjectInfo.AddRow(row);

		row.ClearCells();
		row.AddCell(CTableCell((int)this->alguideCount));
		row.AddCell(CTableCell(URLLink("Active Link Guides", CPageParams(PAGE_OVERVIEW, AR_STRUCT_ITEM_XML_CONTAINER, ARCON_GUIDE), 0)));
		tblListObjectInfo.AddRow(row);

		row.ClearCells();
		row.AddCell(CTableCell((int)this->fltguideCount));
		row.AddCell(CTableCell(URLLink("Filter Guides", CPageParams(PAGE_OVERVIEW, AR_STRUCT_ITEM_XML_CONTAINER, ARCON_FILTER_GUIDE), 0)));
		tblListObjectInfo.AddRow(row);

		row.ClearCells();
		row.AddCell(CTableCell((int)this->packlistCount));
		row.AddCell(CTableCell(URLLink("Packing Lists", CPageParams(PAGE_OVERVIEW, AR_STRUCT_ITEM_XML_CONTAINER, ARCON_PACK), 0)));
		tblListObjectInfo.AddRow(row);

		row.ClearCells();
		row.AddCell(CTableCell((int)this->applicationCount));
		row.AddCell(CTableCell(URLLink("Applications", CPageParams(PAGE_OVERVIEW, AR_STRUCT_ITEM_XML_CONTAINER, ARCON_APP), 0)));
		tblListObjectInfo.AddRow(row);

		row.ClearCells();
		row.AddCell(CTableCell((int)this->escalationCount));
		row.AddCell(CTableCell(URLLink("Escalations", CPageParams(PAGE_OVERVIEW, AR_STRUCT_ITEM_XML_ESCALATION), 0)));
		tblListObjectInfo.AddRow(row);

		row.ClearCells();
		row.AddCell(CTableCell((int)this->filterCount));
		row.AddCell(CTableCell(URLLink("Filters", CPageParams(PAGE_OVERVIEW, AR_STRUCT_ITEM_XML_FILTER), 0)));
		tblListObjectInfo.AddRow(row);

		row.ClearCells();
		row.AddCell(CTableCell((int)this->pInside->groupList.GetCount()));
		row.AddCell(CTableCell(URLLink("Groups", CPageParams(PAGE_OVERVIEW, AR_STRUCT_ITEM_XML_GROUP), 0)));
		tblListObjectInfo.AddRow(row);

		row.ClearCells();
		row.AddCell(CTableCell((int)this->menuCount));
		row.AddCell(CTableCell(URLLink("Menus", CPageParams(PAGE_OVERVIEW, AR_STRUCT_ITEM_XML_CHAR_MENU), 0)));
		tblListObjectInfo.AddRow(row);

		row.ClearCells();
		row.AddCell(CTableCell((int)this->pInside->roleList.GetCount()));
		row.AddCell(CTableCell(URLLink("Roles", CPageParams(PAGE_OVERVIEW, AR_STRUCT_ITEM_XML_ROLE), 0)));
		tblListObjectInfo.AddRow(row);

		row.ClearCells();
		row.AddCell(CTableCell((int)this->schemaCount));
		row.AddCell(CTableCell(URLLink("Forms", CPageParams(PAGE_OVERVIEW, AR_STRUCT_ITEM_XML_SCHEMA), 0)));
		tblListObjectInfo.AddRow(row);

		row.ClearCells();
		row.AddCell(CTableCell((int)this->pInside->userList.GetCount()));
		row.AddCell(CTableCell(URLLink("Users", CPageParams(PAGE_OVERVIEW, AR_STRUCT_ITEM_XML_USER), 0)));
		tblListObjectInfo.AddRow(row);

#if AR_CURRENT_API_VERSION >= AR_API_VERSION_750
		if (pInside->CompareServerVersion(7,5) >= 0)
		{
			row.ClearCells();
			row.AddCell(CTableCell(this->imageCount));
			row.AddCell(CTableCell(URLLink("Images", CPageParams(PAGE_OVERVIEW, AR_STRUCT_ITEM_XML_IMAGE), 0)));
			tblListObjectInfo.AddRow(row);
		}
#endif

		unsigned int nNumTotalObjects = (unsigned int)this->pInside->alList.GetCount();
		nNumTotalObjects += (unsigned int)this->pInside->containerList.GetCount();
		nNumTotalObjects += (unsigned int)this->pInside->escalationList.GetCount();
		nNumTotalObjects += (unsigned int)this->pInside->filterList.GetCount();
		nNumTotalObjects += (unsigned int)this->pInside->groupList.GetCount();
		nNumTotalObjects += (unsigned int)this->pInside->menuList.GetCount();
		nNumTotalObjects += (unsigned int)this->pInside->roleList.GetCount();
		nNumTotalObjects += (unsigned int)this->pInside->schemaList.GetCount();
		nNumTotalObjects += (unsigned int)this->pInside->userList.GetCount();
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_750
		nNumTotalObjects += this->pInside->imageList.GetCount();
#endif			

		unsigned int nNumTotalFields = 0;
		unsigned int schemaCount = this->pInside->schemaList.GetCount();
		for ( unsigned int schemaIndex = 0; schemaIndex < schemaCount; ++schemaIndex )
		{			
			CARSchema schema(schemaIndex);
			nNumTotalFields += schema.GetFields()->GetCount();
		}

		webPage.AddContent(tblListObjectInfo.ToXHtml());

		strm << nNumTotalObjects << " ARSystem objects and " << nNumTotalFields << " fields loaded in " << this->pInside->nDurationLoad << " seconds.<br/>" << endl;		
		strm << nFilesCreated << " files created in " << this->pInside->nDurationDocumentation << " seconds. <br/>" << endl;

		if (!this->pInside->appConfig.runNotes.empty()) {
			strm << "<br/>";
			strm << "Run Notes: " << this->pInside->appConfig.runNotes;
		}

		webPage.AddContent(strm.str());
		webPage.SaveInFolder(this->path);	
	}
	catch(exception& e)
	{
		cout << "EXCEPTION SummaryInfo: " << e.what() << endl;
	}
}
