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
#include "DocFilterGuideDetails.h"
#include "DocOverlayHelper.h"
#include "../output/URLLink.h"
#include "../output/WorkflowReferenceTable.h"

CDocFilterGuideDetails::CDocFilterGuideDetails(CARContainer &fltGuide)
: filterGuide(fltGuide)
{
}

CDocFilterGuideDetails::~CDocFilterGuideDetails(void)
{
}

void CDocFilterGuideDetails::Documentation()
{	
	CPageParams file(PAGE_DETAILS, &filterGuide);
	this->rootLevel = file->GetRootLevel();

	try
	{
		string dir = file->GetPath(); // CAREnum::ContainerDir(ARCON_FILTER_GUIDE)+"/"+pFilterGuide->FileID();

		FileSystemUtil fsUtil(this->pInside->appConfig);
		if(fsUtil.CreateSubDirectory(dir)>=0)
		{
			CWebPage webPage(file->GetFileName(), filterGuide.GetName(), rootLevel, this->pInside->appConfig);
			CDocOverlayHelper overlayHelper(filterGuide, rootLevel);

			//ContentHead informations
			stringstream strmHead;
			strmHead.str("");
			int overlayType = this->filterGuide.GetOverlayType();

			strmHead << CWebUtil::LinkToFilterGuideIndex(this->rootLevel) << MenuSeparator
			         << ImageTag(filterGuide, rootLevel) << CWebUtil::ObjName(this->filterGuide.GetName()) << CAREnum::GetOverlayTypeString(overlayType);

			if(!this->filterGuide.GetAppRefName().empty())
				strmHead << MenuSeparator << " Application " << this->pInside->LinkToContainer(this->filterGuide.GetAppRefName(), this->rootLevel);

			webPage.AddContentHead(strmHead.str(), overlayHelper.PlaceOverlayLink());
			webPage.AddContent(overlayHelper.PlaceOverlaidNotice());

			//Container Base Informations
			CDocContainerHelper *contHelper = new CDocContainerHelper(this->filterGuide, this->rootLevel);
			webPage.AddContent(contHelper->BaseInfo());
			delete contHelper;

			//Object specific documentation
			webPage.AddContent(FilterActions());

			//Workflow References
			{
				WorkflowReferenceTable wfRefTable(filterGuide);
				webPage.AddContent(wfRefTable.ToString(rootLevel));
			}

			//History
			webPage.AddContent(this->pInside->ServerObjectHistory(&this->filterGuide, this->rootLevel));

			//Save File
			webPage.SaveInFolder(dir);
		}
	}
	catch(exception& e)
	{
		cout << "EXCEPTION in FilterGuideDetails_GetPrimaryForm: " << e.what() << endl; 
	}
}

string CDocFilterGuideDetails::FilterActions()
{	
	//Get a list of filter that trigger this filter guide
	CTable tblPropEx("exuteInfoList", "TblObjectList");
	tblPropEx.AddColumn(20, "Action");
	tblPropEx.AddColumn(80, "Filter");

	try
	{
		// TODO: Move this loop to the scan phase
		unsigned int filterCount = pInside->filterList.GetCount();
		for (unsigned int filterIndex = 0; filterIndex < filterCount; ++filterIndex )
		{
			CARFilter filter(filterIndex);

			// skip this object in case it's overlaid (hidden)
			if (pInside->appConfig.bOverlaySupport && !IsVisibleObject(filter))
				continue;

			//Search if-actions
			const ARFilterActionList& IfActions =	filter.GetIfActions();
			for(unsigned int nAction = 0; nAction < IfActions.numItems; ++nAction)
			{
				const ARFilterActionStruct& action = IfActions.actionList[nAction];
				if(action.action == AR_FILTER_ACTION_CALLGUIDE)
				{
					if(strcmp(action.u.callGuide.guideName, filterGuide.GetName().c_str())==0)
					{
						stringstream tmp;
						tmp << "If-Action " << nAction;
						CTableCell cellActionInfo(tmp.str(), "");
						CTableCell cellFilter(URLLink(filter, this->rootLevel), "");

						CTableRow row("");
						row.AddCell(cellActionInfo);
						row.AddCell(cellFilter);
						tblPropEx.AddRow(row);
					}
				}				
			}

			//Search else-actions
			const ARFilterActionList& ElseActions =	filter.GetElseActions();
			for(unsigned int nAction = 0; nAction < ElseActions.numItems; nAction++)
			{
				ARFilterActionStruct action = ElseActions.actionList[nAction];
				if(action.action == AR_FILTER_ACTION_CALLGUIDE)
				{
					if(strcmp(action.u.callGuide.guideName, filterGuide.GetName().c_str())==0)
					{
						stringstream tmp;
						tmp << "Else-Action " << nAction;
						CTableCell cellActionInfo(tmp.str(), "");
						CTableCell cellFilter(URLLink(filter, this->rootLevel), "");

						CTableRow row("");
						row.AddCell(cellActionInfo);
						row.AddCell(cellFilter);
						tblPropEx.AddRow(row);
					}
				}				
			}
		}
	}
	catch(exception& e)
	{
		cout << "EXCEPTION in FilterGuideDetails_FilterActions: " << e.what() << endl; 
	}

	tblPropEx.description = "Filters calling this guide";
	return tblPropEx.ToXHtml();
}
