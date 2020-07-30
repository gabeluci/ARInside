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
#include "ContainerTable.h"
#include "URLLink.h"

using namespace OUTPUT;
using namespace rapidjson;

CContainerTable::CContainerTable(CARInside &arIn, bool includeObjTypeColumn)
: CObjectTable("containerList", "TblObjectList")
{
	this->pInside = &arIn;

	tbl.AddColumn((includeObjTypeColumn?40:60), "Name");
	if (includeObjTypeColumn)
	{
		tbl.AddColumn(20, "Type");
	}
	tbl.AddColumn(20, "Modified");
	tbl.AddColumn(20, "By");

	hasObjTypeColumn = includeObjTypeColumn;
}

CContainerTable::~CContainerTable(void)
{
}

void CContainerTable::AddRow(CARContainer &cont, int rootLevel)
{
	string cellNameValue = URLLink(cont, rootLevel);
	if (IsUnusedContainer(cont))
	{ 
		cellNameValue += " (<b>!</b>)"; 
	}

	CTableRow tblRow("");
	tblRow.AddCell( CTableCell(cellNameValue));
	if (this->hasObjTypeColumn) { tblRow.AddCell( CTableCell(CAREnum::ContainerType(cont.GetType()))); }
	tblRow.AddCell( CTableCell(CUtil::DateTimeToHTMLString(cont.GetTimestamp())));
	tblRow.AddCell( CTableCell(this->pInside->LinkToUser(cont.GetLastChanged(), rootLevel)));
	this->tbl.AddRow(tblRow);
}

void CContainerTable::AddRowJson(CARContainer &cont, int rootLevel)
{
	CPageParams containerDetailPage(PAGE_DETAILS, &cont);
	Document::AllocatorType &alloc = doc.GetAllocator();

	unsigned int contType = cont.GetType();
	bool unused = IsUnusedContainer(cont);

	// create a new json row and make it an array
	Value containerRow;
	containerRow.SetArray();

	// now build the needed temporary variables
	string strName = cont.GetName();
	string strModifiedDate = CUtil::DateTimeToString(cont.GetTimestamp());
	string strLink = CWebUtil::GetRelativeURL(rootLevel, containerDetailPage);

	// build the values
	Value valName(strName.c_str(), static_cast<SizeType>(strName.size()), alloc);
	Value valModifiedDate(strModifiedDate.c_str(), static_cast<SizeType>(strModifiedDate.size()), alloc);
	Value valLink(strLink.c_str(), static_cast<SizeType>(strLink.size()), alloc);

	// add everything to the row
	containerRow.PushBack(valName, alloc);
	containerRow.PushBack(valModifiedDate, alloc);
	containerRow.PushBack(cont.GetLastChanged(), alloc);
	containerRow.PushBack(valLink, alloc);
	containerRow.PushBack(cont.GetOverlayType(), alloc);
	if (contType == ARCON_GUIDE || contType == ARCON_FILTER_GUIDE)
	{
		containerRow.PushBack((unused?0:1), alloc);
	}

	doc.PushBack(containerRow, alloc);
}

bool CContainerTable::IsUnusedContainer(CARContainer &obj)
{
	switch(obj.GetType())
	{
	case ARCON_FILTER_GUIDE:
		{
			if(NumRelatedFilters(obj)==0)
			{
				return true;
			}
		}
		break;
	case ARCON_GUIDE:
		{
			if(NumRelatedActiveLinks(obj)==0)
			{
				return true;
			}
		}
		break;
	}
	return false;
}

// TODO: optimize related workflow scanning
// The following two methods scan for activelinks and filters calling the current container, just to add a sign
// to unused containers. The same scanning is done during the container documentation to show all objects calling
// this guide. The code should be moved to the scanning phase to add all callers to the container. Later we can
// check if there are no callers an put the sign in front of the object link.

int CContainerTable::NumRelatedActiveLinks(CARContainer &obj)
{
	int nResult = 0;
	try
	{
		unsigned int alCount = this->pInside->alList.GetCount();
		for (unsigned int alIndex = 0; alIndex < alCount; ++alIndex )
		{
			CARActiveLink al(alIndex);

			// skip this object in case it's overlaid (hidden)
			if (pInside->appConfig.bOverlaySupport && !IsVisibleObject(al))
				continue;

			//Search if-actions
			for(unsigned int nAction = 0; nAction < al.GetIfActions().numItems; nAction++)
			{
				const ARActiveLinkActionStruct &action = al.GetIfActions().actionList[nAction];
				if(action.action == AR_ACTIVE_LINK_ACTION_CALLGUIDE)
				{
					if(strcmp(action.u.callGuide.guideName, obj.GetARName())==0)
					{
						nResult++;
					}
				}				
			}

			//Search else-actions
			for(unsigned int nAction = 0; nAction < al.GetElseActions().numItems; nAction++)
			{
				const ARActiveLinkActionStruct &action = al.GetElseActions().actionList[nAction];
				if(action.action == AR_ACTIVE_LINK_ACTION_CALLGUIDE)
				{
					if(strcmp(action.u.callGuide.guideName, obj.GetARName())==0)
					{
						nResult++;
					}
				}				
			}
		}
	}
	catch(exception& e)
	{
		cout << "EXCEPTION enumerating NumRelatedActiveLinks() in container '" << obj.GetName() << "': " << e.what() << endl;
	}

	return nResult;
}

int CContainerTable::NumRelatedFilters(CARContainer &obj)
{
	int nResult = 0;
	try
	{
		unsigned int filterCount = pInside->filterList.GetCount();
		for (unsigned int filterIndex = 0; filterIndex < filterCount; ++filterIndex )
		{
			CARFilter filter(filterIndex);

			// skip this object in case it's overlaid (hidden)
			if (pInside->appConfig.bOverlaySupport && !IsVisibleObject(filter))
				continue;

			//Search if-actions
			for(unsigned int nAction = 0; nAction < filter.GetIfActions().numItems; nAction++)
			{
				ARFilterActionStruct &action = filter.GetIfActions().actionList[nAction];
				if(action.action == AR_FILTER_ACTION_CALLGUIDE)
				{
					if(strcmp(action.u.callGuide.guideName, obj.GetARName())==0)
					{
						nResult++;
					}
				}				
			}

			//Search else-actions
			for(unsigned int nAction = 0; nAction < filter.GetElseActions().numItems; nAction++)
			{
				ARFilterActionStruct action = filter.GetElseActions().actionList[nAction];
				if(action.action == AR_FILTER_ACTION_CALLGUIDE)
				{
					if(strcmp(action.u.callGuide.guideName, obj.GetARName())==0)
					{
						nResult++;
					}
				}				
			}
		}
	}
	catch(exception& e)
	{
		cout << "EXCEPTION enumerating NumRelatedFilters() in container '" << obj.GetName() << "': " << e.what() << endl;
	}

	return nResult;
}
