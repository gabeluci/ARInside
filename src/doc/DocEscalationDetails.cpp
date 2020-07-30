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
#include "DocEscalationDetails.h"
#include "DocOverlayHelper.h"
#include "../output/ImageTag.h"

CDocEscalationDetails::CDocEscalationDetails(unsigned int escalInsideId)
: escalation(escalInsideId)
{
}

CDocEscalationDetails::~CDocEscalationDetails(void)
{
}

void CDocEscalationDetails::Documentation()
{
	CPageParams file(PAGE_DETAILS, &escalation);
	this->rootLevel = file->GetRootLevel();
	this->path = file->GetPath();

	try
	{
		FileSystemUtil fsUtil(this->pInside->appConfig);
		if(fsUtil.CreateSubDirectory(this->path)>=0)
		{
			CWebPage webPage(file->GetFileName(), this->escalation.GetName(), this->rootLevel, this->pInside->appConfig);
			CARProplistHelper props(&this->escalation.GetPropList());
			CDocOverlayHelper overlayHelper(escalation, rootLevel);

			//ContentHead informations
			stringstream strmHead;
			strmHead.str("");
			int overlayType = this->escalation.GetOverlayType();

			strmHead << CWebUtil::LinkToEscalationIndex(this->rootLevel) << MenuSeparator
			         << ImageTag(escalation, rootLevel) << CWebUtil::ObjName(this->escalation.GetName()) << CAREnum::GetOverlayTypeString(overlayType);

			if(!this->escalation.GetAppRefName().empty())
				strmHead << MenuSeparator << " Application " << this->pInside->LinkToContainer(this->escalation.GetAppRefName(), this->rootLevel);

			webPage.AddContentHead(strmHead.str(), overlayHelper.PlaceOverlayLink());
			webPage.AddContent(overlayHelper.PlaceOverlaidNotice());

			//Escalation Properties
			stringstream strmTmp;
			CTable tblObjProp("objProperties", "TblObjectList");
			tblObjProp.AddColumn(30, "Property");	
			tblObjProp.AddColumn(70, "Value");

			//Status
			CTableRow row("cssStdRow");		
			CTableCell cellProp("Status", "");				
			CTableCell cellPropValue(CAREnum::ObjectEnable(this->escalation.GetEnabled()), "");    
			row.AddCell(cellProp);
			row.AddCell(cellPropValue);
			tblObjProp.AddRow(row);

			// Pool for server version >= 7.1
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_710
			if (this->pInside->CompareServerVersion(7,1) >= 0)
			{				
				cellPropValue.content = escalation.GetPoolStr(&props);

				row.ClearCells();
				cellProp.content = "Pool Number";
				row.AddCell(cellProp);
				row.AddCell(cellPropValue);
				tblObjProp.AddRow(row);
			}
#endif

			//Time criteria
			row.ClearCells();
			cellProp.content = "Time Criteria";
			cellPropValue.content = this->escalation.GetTimeCriteria();
			row.AddCell(cellProp);
			row.AddCell(cellPropValue);
			tblObjProp.AddRow(row);

			//Workflow
			const ARWorkflowConnectStruct& schemas = this->escalation.GetSchemaList();
			if(schemas.u.schemaList->numItems > 0)
			{		
				for(unsigned int i=0; i< schemas.u.schemaList->numItems; i++)
				{
					//Workflowlink to each page	
					strmTmp.str("");
					row.ClearCells();
					cellProp.content = this->pInside->LinkToSchema(schemas.u.schemaList->nameList[i], rootLevel);

					cellPropValue.content = this->CreateSpecific(schemas.u.schemaList->nameList[i]);
					row.AddCell(cellProp);
					row.AddCell(cellPropValue);
					tblObjProp.AddRow(row);	
				}
			}
			else // Escalation is not related to any form
			{
				strmTmp.str("");
				row.ClearCells();
				cellProp.content = "No schema specified";

				cellPropValue.content = this->CreateSpecific("");
				row.AddCell(cellProp);
				row.AddCell(cellPropValue);
				tblObjProp.AddRow(row);	
			}	

			//Table description
			stringstream tblDesc;
			tblDesc << ImageTag(ImageTag::Document, rootLevel) << "Escalation Properties";
			tblObjProp.description = tblDesc.str();

			//Escalation used in container?
			row.ClearCells();
			cellProp.content = "Container References";
			cellPropValue.content = this->ContainerReferences();				
			row.AddCell(cellProp);
			row.AddCell(cellPropValue);
			tblObjProp.AddRow(row);

			//Add table to page
			webPage.AddContent(tblObjProp.ToXHtml());
			tblObjProp.Clear();

			//Properties
			webPage.AddContent(props.UnusedPropertiesToHTML(rootLevel));

			//History
			webPage.AddContent(this->pInside->ServerObjectHistory(&this->escalation, this->rootLevel));

			webPage.SaveInFolder(this->path);
		}
	}
	catch(exception& e)
	{
		cout << "EXCEPTION escalation details common props of '" << this->escalation.GetName() << "': " << e.what() << endl;
	}
}


string CDocEscalationDetails::ContainerReferences()
{
	stringstream strm;
	strm.str("");
	try
	{
		CContainerTable *contTable = new CContainerTable(*this->pInside);

		unsigned int cntCount = this->pInside->containerList.GetCount();
		for ( unsigned int cntIndex = 0; cntIndex < cntCount; ++cntIndex )
		{
			CARContainer cont(cntIndex);
			
			if (pInside->appConfig.bOverlaySupport && !IsVisibleObject(cont))
				continue;

			if(cont.GetType() != ARCON_APP)
			{
				const ARReferenceList& refs = cont.GetContent();
				for(unsigned int nCnt = 0; nCnt < refs.numItems; nCnt++)
				{
					if(refs.referenceList[nCnt].type == ARREF_ESCALATION)
					{
						if(refs.referenceList[nCnt].reference.u.name != NULL && 
							 this->escalation.GetName() == refs.referenceList[nCnt].reference.u.name)
						{
							contTable->AddRow(cont, rootLevel);
						}
					}
				}
			}
		}		

		strm << *contTable;
		delete contTable;
	}
	catch(exception& e)
	{
		cout << "EXCEPTION enumerating escalation container references of '" << this->escalation.GetName() << "': " << e.what() << endl;
	}

	return strm.str();
}

string CDocEscalationDetails::CreateSpecific(string schemaName)
{
	stringstream pgStrm;
	pgStrm.str("");

	try
	{
		//Query
		stringstream strmQuery;
		if(this->escalation.GetRunIf().operation != AR_COND_OP_NONE)
		{		
			int pFormId = this->pInside->SchemaGetInsideId(schemaName);

			CRefItem refItem(this->escalation, REFM_RUNIF);
			CARQualification arQual(*this->pInside, refItem, pFormId, rootLevel);
			arQual.CheckQuery(&this->escalation.GetRunIf(), strmQuery);
		}
		else
		{
			strmQuery << EmptyRunIf << endl;
		}

		pgStrm << "Run If Qualification: <br/>" << strmQuery.str();

		//If-Actions		
		CDocFilterActionStruct actionStruct(*this->pInside, this->escalation, schemaName, this->rootLevel, AR_STRUCT_ITEM_XML_ESCALATION);
		pgStrm << actionStruct.Get(IES_IF, this->escalation.GetIfActions());

		//Else-Actions
		pgStrm << actionStruct.Get(IES_ELSE, this->escalation.GetElseActions());
	}
	catch(exception& e)
	{
		cout << "EXCEPTION escalation details specific props of '" << this->escalation.GetName() << "': " << e.what() << endl;
	}

	return pgStrm.str();
}
