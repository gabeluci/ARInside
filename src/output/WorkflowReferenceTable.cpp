//Copyright (C) 2014 John Luthgers | jls17
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
//    along with ARInside.  If not, see <http://www.gnu.org/licenses/>.

#include "stdafx.h"
#include "WorkflowReferenceTable.h"
#include "../core/ARContainer.h"
#include "../core/AREnum.h"
#include "../core/ARFilter.h"
#include "../core/ARImage.h"
#include "../output/ImageTag.h"
#include "../output/URLLink.h"
#include "../ARInside.h"

using namespace OUTPUT;

#if AR_CURRENT_API_VERSION >= AR_API_VERSION_750
WorkflowReferenceTable::WorkflowReferenceTable(const CARImage &image)
: obj(image)
{
	InitIterators(image.GetReferences());
}
#endif

WorkflowReferenceTable::WorkflowReferenceTable(const CARContainer& container)
:obj(container)
{
	InitIterators(container.GetReferences());
}

void WorkflowReferenceTable::InitIterators(const CRefItemList &refs)
{
	curIt = refs.begin();
	endIt = refs.end();
}

string WorkflowReferenceTable::ToString(int rootLevel)
{
	stringstream strm;
	strm.str("");

	try
	{
		CTable tblRef("referenceList", "TblObjectList");
		tblRef.AddColumn(10, "Type");
		tblRef.AddColumn(45, "Server object");
		tblRef.AddColumn(5, "Enabled");
		tblRef.AddColumn(40, "Description");

		for ( ; curIt != endIt; ++curIt)
		{			
			CTableRow row("cssStdRow");		
			row.AddCell(CAREnum::XmlStructItem(curIt->GetObjectType()));				
			row.AddCell(this->LinkToObjByRefItem(*curIt, rootLevel));

			string tmpEnabled = "";
			string tmpCssEnabled = "";

			bool enabledSupported = false;
			int enabled = curIt->GetObjectEnabled(enabledSupported);

			if (enabledSupported)
			{
				tmpEnabled = CAREnum::ObjectEnable(enabled);
				if (!enabled) { tmpCssEnabled = "objStatusDisabled"; }
			}

			row.AddCell(CTableCell(tmpEnabled, tmpCssEnabled));
			row.AddCell(curIt->GetDescription(rootLevel));
			tblRef.AddRow(row);
		}

		stringstream tblDesc;
		tblDesc << ImageTag(ImageTag::Document, rootLevel) << "Workflow Reference";

		tblRef.description = tblDesc.str();

		strm << tblRef;
	}
	catch(exception& e)
	{
		cout << "EXCEPTION enumerating workflow references for object: " << obj.GetName() << " -- " << e.what() << endl;
	}	

	return strm.str();
}

string WorkflowReferenceTable::LinkToObjByRefItem(const CRefItem& refItem, int rootLevel)
{
	string result = EmptyValue;

	switch(refItem.GetObjectType())
	{
	case AR_STRUCT_ITEM_XML_ACTIVE_LINK: 
		{
			result = LinkToAlRef(refItem, rootLevel);
		}
		break;
	case AR_STRUCT_ITEM_XML_FILTER:
		{
			result = LinkToFilterRef(refItem, rootLevel);
		}
		break;
	case AR_STRUCT_ITEM_XML_SCHEMA:
		{
			result = CARInside::GetInstance()->LinkToSchema(refItem.GetObjectName(), rootLevel);
		}
		break;
	case AR_STRUCT_ITEM_XML_FIELD:
		{
			result = CARInside::GetInstance()->LinkToField(refItem.GetObjectId(), refItem.GetSubObjectId(), rootLevel);
		}
		break;
	case AR_STRUCT_ITEM_XML_VUI:
		{
			result = CARInside::GetInstance()->LinkToVui(refItem.GetObjectId(), refItem.GetSubObjectId(), rootLevel);
		}
		break;
	case AR_STRUCT_ITEM_XML_ESCALATION:
		{
			result = CARInside::GetInstance()->LinkToEscalation(refItem, rootLevel);
		}
		break;
	case AR_STRUCT_ITEM_XML_CHAR_MENU:
		{
			result = CWebUtil::LinkToMenu(refItem, rootLevel);
		}
		break;		
	case AR_STRUCT_ITEM_XML_CONTAINER:
		{
			result = CARInside::GetInstance()->LinkToContainer(refItem, rootLevel);
		}
		break;
//#if AR_CURRENT_API_VERSION >= AR_API_VERSION_750
//	case AR_STRUCT_ITEM_XML_IMAGE:
//		{
//			result = this->LinkToImage(objName, rootLevel);
//		}
//		break;
//#endif
	}

	return result;
}

string WorkflowReferenceTable::LinkToAlRef(const CRefItem& refItem, int rootLevel)
{
	CARActiveLink al(refItem.GetObjectId());
	if (!al.Exists())
		return EmptyValue;

	stringstream strmTmp;
	strmTmp << URLLink(al, rootLevel) << " (" << al.GetOrder() << ")";
	return strmTmp.str();
}

string WorkflowReferenceTable::LinkToFilterRef(const CRefItem& refItem, int rootLevel)
{
	CARFilter flt(refItem.GetObjectId());
	if (flt.Exists())
	{
		return LinkToFilterRef(&flt, rootLevel);
	}
	return EmptyValue;
}

string WorkflowReferenceTable::LinkToFilterRef(CARFilter* filter, int rootLevel)
{
	stringstream strmTmp;
	strmTmp.str("");

	if (filter != NULL)
		strmTmp << URLLink(*filter, rootLevel) << " (" << filter->GetOrder() << ")";

	return strmTmp.str();
}

