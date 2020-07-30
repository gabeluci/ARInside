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
#include "DocApplicationDetails.h"
#include "DocOverlayHelper.h"
#include "../output/URLLink.h"
#include "../output/WorkflowReferenceTable.h"

CDocApplicationDetails::CDocApplicationDetails(CARContainer &application)
: pApp(application)
{
}

CDocApplicationDetails::~CDocApplicationDetails(void)
{
}

void CDocApplicationDetails::Documentation()
{
	try
	{
		CPageParams file(PAGE_DETAILS, &pApp);
		this->rootLevel = file->GetRootLevel();
		string dir = file->GetPath();

		FileSystemUtil fsUtil(pInside->appConfig);
		if(fsUtil.CreateSubDirectory(dir)>=0)
		{
			CWebPage webPage(file->GetFileName(), this->pApp.GetName(), rootLevel, pInside->appConfig);
			CDocOverlayHelper overlayHelper(pApp, rootLevel);

			//ContentHead informations
			stringstream strmHead;
			int overlayType = this->pApp.GetOverlayType();
			strmHead << CWebUtil::LinkToApplicationIndex(this->rootLevel) << MenuSeparator
			         << ImageTag(pApp, rootLevel) << CWebUtil::ObjName(this->pApp.GetName())  << CAREnum::GetOverlayTypeString(overlayType);

			webPage.AddContentHead(strmHead.str(), overlayHelper.PlaceOverlayLink());
			webPage.AddContent(overlayHelper.PlaceOverlaidNotice());

			//Container Base Informations
			CDocContainerHelper *contHelper = new CDocContainerHelper(this->pApp, this->rootLevel);
			webPage.AddContent(contHelper->BaseInfo());
			delete contHelper;

			//Object specific documentation
			webPage.AddContent(ApplicationInformation());

			//Workflow Referenes
			{
				WorkflowReferenceTable wfRefTable(pApp);
				webPage.AddContent(wfRefTable.ToString(rootLevel));
			}

			//History
			webPage.AddContent(this->pInside->ServerObjectHistory(&this->pApp, this->rootLevel));

			//Save File
			webPage.SaveInFolder(dir);
		}
		else
			cout << "[Skipped] Directory '" << dir << "' already exists." << endl;
	}
	catch(exception& e)
	{
		cout << "EXCEPTION in ApplicationDetails_Documentation: " << e.what() << endl; 
	}
}

string CDocApplicationDetails::GetPrimaryForm()
{
	try
	{
		const ARReferenceList& refs = this->pApp.GetContent();
		for(unsigned int i=0; i< refs.numItems; i++)
		{
			switch(refs.referenceList[i].type)
			{						
			case ARREF_SCHEMA:
				return refs.referenceList[i].reference.u.name;
			}
		}
	}
	catch(exception& e)
	{
		cout << "EXCEPTION in ApplicationDetails_GetPrimaryForm: " << e.what() << endl; 
	}

	return EmptyValue;
}

// TODO: check all calls to this function for code/loop optimizations
bool CDocApplicationDetails::InList(string searchName, int nType)
{
	try
	{
		const ARReferenceList& refs = this->pApp.GetContent();
		for(unsigned int i=0; i< refs.numItems; i++)
		{
			if(refs.referenceList[i].type == nType)
			{	
				if(searchName == refs.referenceList[i].reference.u.name)
				{
					return true;
				}
			}
		}
	}
	catch(exception& e)
	{
		cout << "EXCEPTION in ApplicationDetails_InList: " << e.what() << endl; 
	}

	return false;
}

string CDocApplicationDetails::ApplicationInformation()
{
	//Container specific properties
	CTable tblProp("specificPropList", "TblObjectList");
	tblProp.AddColumn(20, "Type");
	tblProp.AddColumn(80, "Server Object");

	try
	{
		CTableRow row("");		

		//Get the primary form of this application		
		row.ClearCells();
		CTableCell cellSrvType("Primary Form", "");
		CTableCell cellSrvObj(this->pInside->LinkToSchema(this->GetPrimaryForm(), this->rootLevel), "");
		if(cellSrvObj.content.empty())
			cellSrvObj.content = EmptyValue;

		row.AddCell(cellSrvType);
		row.AddCell(cellSrvObj);
		tblProp.AddRow(row);


		int nResult = 0;
		string strResult = "";

		//Forms in Applications
		nResult = 0;
		strResult = SearchForms(nResult);

		row.ClearCells();
		cellSrvType.content = CWebUtil::LinkToSchemaIndex(nResult, this->rootLevel);
		cellSrvObj.content = strResult;
		if(cellSrvObj.content.size()==0)
			cellSrvObj.content = EmptyValue;

		row.AddCell(cellSrvType);
		row.AddCell(cellSrvObj);
		tblProp.AddRow(row);


		//Search related ActiveLinks		
		strResult = SearchActiveLinks(nResult);
		row.ClearCells();
		cellSrvType.content = CWebUtil::LinkToActiveLinkIndex(nResult,this->rootLevel);
		cellSrvObj.content = strResult;
		if(cellSrvObj.content.size()==0)
			cellSrvObj.content = EmptyValue;

		row.AddCell(cellSrvType);
		row.AddCell(cellSrvObj);
		tblProp.AddRow(row);

		//Search related Filters
		strResult = SearchFilters(nResult);
		row.ClearCells();
		cellSrvType.content = CWebUtil::LinkToFilterIndex(nResult, this->rootLevel);
		cellSrvObj.content = strResult;
		if(cellSrvObj.content.size()==0)
			cellSrvObj.content = EmptyValue;

		row.AddCell(cellSrvType);
		row.AddCell(cellSrvObj);
		tblProp.AddRow(row);

		//Search related Escalations
		strResult = SearchEscalations(nResult);
		row.ClearCells();
		cellSrvType.content = CWebUtil::LinkToEscalationIndex(nResult, this->rootLevel);
		cellSrvObj.content = strResult;
		if(cellSrvObj.content.size()==0)
			cellSrvObj.content = EmptyValue;

		row.AddCell(cellSrvType);
		row.AddCell(cellSrvObj);
		tblProp.AddRow(row);


		//Related containers
		for(int nType = ARCON_GUIDE; nType <= ARCON_WEBSERVICE; nType++)
		{			
			if(nType != ARCON_APP) //Application cannot be embedded in another app
			{
				strResult = SearchContainer(nResult, nType);
				row.ClearCells();
				cellSrvType.content = CWebUtil::LinkToContainer(nResult, this->rootLevel, nType);
				cellSrvObj.content = strResult;
				if(cellSrvObj.content.empty())
					cellSrvObj.content = EmptyValue;

				row.AddCell(cellSrvType);
				row.AddCell(cellSrvObj);
				tblProp.AddRow(row);
			}
		}

		//Search CharMenus
		strResult = SearchMenus(nResult);
		row.ClearCells();
		cellSrvType.content = CWebUtil::LinkToMenuIndex(nResult, this->rootLevel);
		cellSrvObj.content = strResult;
		if(cellSrvObj.content.size()==0)
			cellSrvObj.content = EmptyValue;

		row.AddCell(cellSrvType);
		row.AddCell(cellSrvObj);
		tblProp.AddRow(row);
	}
	catch(exception& e)
	{
		cout << "EXCEPTION in ApplicationDetails_BaseDocumentation: " << e.what() << endl; 
	}

	tblProp.description = "Application Content";
	return tblProp.ToXHtml();
}

string CDocApplicationDetails::SearchForms(int &nResult)
{
	stringstream strmResult;
	strmResult.str("");

	nResult = 0;

	try
	{
		list<int> schemaList;
		//Update the schema informations
		const ARReferenceList& refs = this->pApp.GetContent();
		for ( unsigned int refIndex = 0; refIndex < refs.numItems; ++refIndex )
		{
			if (refs.referenceList[refIndex].type == ARREF_SCHEMA && refs.referenceList[refIndex].reference.dataType == ARREF_DATA_ARSREF)
			{
				CARSchema schema(refs.referenceList[refIndex].reference.u.name);
				if (schema.Exists())
				{
					schema.SetAppRefName(this->pApp.GetName());
					schemaList.push_back(schema.GetInsideId());
				}
			}
		}

		schemaList.sort();
		schemaList.unique();
		nResult = (int)schemaList.size();

		list<int>::iterator curIt = schemaList.begin();
		list<int>::iterator endIt = schemaList.end();
		for (; curIt != endIt; ++curIt)
		{
			CARSchema schema(*curIt);
			strmResult << URLLink(schema, this->rootLevel) << "<br/>" << endl;
		}
	}
	catch(exception& e)
	{
		cout << "EXCEPTION in ApplicationDetails_SearchForms: " << e.what() << endl; 
	}

	return strmResult.str();
}

string CDocApplicationDetails::SearchActiveLinks(int &nResult)
{
	stringstream strmResult;
	nResult = 0;

	try
	{
		list<int> appALList;
		const ARReferenceList& refs = this->pApp.GetContent();
		for(unsigned int i=0; i< refs.numItems; ++i)
		{
			if (refs.referenceList[i].type == ARREF_SCHEMA && refs.referenceList[i].reference.dataType == ARREF_DATA_ARSREF)
			{
				CARSchema schema(refs.referenceList[i].reference.u.name);
				if (schema.Exists())
				{
					const CARSchemaList::ObjectRefList& schemaALList = schema.GetActiveLinks();
					CARSchemaList::ObjectRefList::const_iterator curIt = schemaALList.begin();
					CARSchemaList::ObjectRefList::const_iterator endIt = schemaALList.end();
					
					for (; curIt != endIt; ++curIt)
					{
						CARActiveLink al(*curIt);
						al.SetAppRefName(this->pApp.GetName());
						appALList.push_back(*curIt);
					}
				}
			}
		}

		// make the al list unique
		appALList.sort();
		appALList.unique();
		nResult = (int)appALList.size();

		list<int>::iterator curIt = appALList.begin();
		list<int>::iterator endIt = appALList.end();
		for (; curIt != endIt; ++curIt)
		{
			CARActiveLink al(*curIt);
			strmResult << URLLink(al, rootLevel) << "<br/>" << endl;
		}
	}
	catch(exception& e)
	{
		cout << "EXCEPTION in ApplicationDetails_SearchActiveLinks: " << e.what() << endl; 
	}
	return strmResult.str();
}

string CDocApplicationDetails::SearchFilters(int &nResult)
{
	stringstream strmResult;

	nResult = 0;

	try
	{
		list<int> appFltList;
		const ARReferenceList& refs = this->pApp.GetContent();
		for(unsigned int i=0; i< refs.numItems; ++i)
		{
			if (refs.referenceList[i].type == ARREF_SCHEMA && refs.referenceList[i].reference.dataType == ARREF_DATA_ARSREF)
			{
				CARSchema schema(refs.referenceList[i].reference.u.name);
				if (schema.Exists())
				{
					const CARSchemaList::ObjectRefList& schemaFltList = schema.GetFilters();
					CARSchemaList::ObjectRefList::const_iterator curIt = schemaFltList.begin();
					CARSchemaList::ObjectRefList::const_iterator endIt = schemaFltList.end();
					
					for (; curIt != endIt; ++curIt)
					{
						CARFilter flt(*curIt);
						flt.SetAppRefName(this->pApp.GetName());
						appFltList.push_back(*curIt);
					}
				}
			}
		}

		// make the filter list unique
		appFltList.sort();
		appFltList.unique();
		nResult = (int)appFltList.size();

		list<int>::iterator curIt = appFltList.begin();
		list<int>::iterator endIt = appFltList.end();
		for (; curIt != endIt; ++curIt)
		{
			CARFilter flt(*curIt);
			strmResult << URLLink(flt, rootLevel) << "<br/>" << endl;
		}
	}
	catch(exception& e)
	{
		cout << "EXCEPTION in ApplicationDetails_SearchFilters: " << e.what() << endl; 
	}

	return strmResult.str();
}

string CDocApplicationDetails::SearchEscalations(int &nResult)
{
	stringstream strmResult;
	strmResult.str("");

	nResult = 0;

	try
	{
		list<int> appEscList;
		const ARReferenceList& refs = this->pApp.GetContent();
		for(unsigned int i=0; i< refs.numItems; ++i)
		{
			if (refs.referenceList[i].type == ARREF_SCHEMA && refs.referenceList[i].reference.dataType == ARREF_DATA_ARSREF)
			{
				CARSchema schema(refs.referenceList[i].reference.u.name);
				if (schema.Exists())
				{
					const CARSchemaList::ObjectRefList& schemaEscList = schema.GetEscalations();
					CARSchemaList::ObjectRefList::const_iterator curIt = schemaEscList.begin();
					CARSchemaList::ObjectRefList::const_iterator endIt = schemaEscList.end();
					
					for (; curIt != endIt; ++curIt)
					{
						CAREscalation esc(*curIt);
						esc.SetAppRefName(this->pApp.GetName());
						appEscList.push_back(*curIt);
					}
				}
			}
		}

		// make the escalation list unique
		appEscList.sort();
		appEscList.unique();
		nResult = (int)appEscList.size();

		list<int>::iterator curIt = appEscList.begin();
		list<int>::iterator endIt = appEscList.end();
		for (; curIt != endIt; ++curIt)
		{
			CAREscalation esc(*curIt);
			strmResult << URLLink(esc, rootLevel) << "<br/>" << endl;
		}
	}
	catch(exception& e)
	{
		cout << "EXCEPTION in ApplicationDetails_SearchEscalations: " << e.what() << endl; 
	}

	return strmResult.str();
}


string CDocApplicationDetails::SearchContainer(int &nResult, int nType)
{
	stringstream strmResult;
	strmResult.str("");

	nResult = 0;

	try
	{
		list<int> appCntList;
		const ARReferenceList& refs = this->pApp.GetContent();
		for(unsigned int i=0; i< refs.numItems; ++i)
		{
			switch (nType)
			{
			case ARCON_GUIDE:
			case ARCON_FILTER_GUIDE:
				{
					if (refs.referenceList[i].type == ARREF_SCHEMA && refs.referenceList[i].reference.dataType == ARREF_DATA_ARSREF)
					{
						CARSchema schema(refs.referenceList[i].reference.u.name);
						if (schema.Exists())
						{
							// define the iterators
							CARSchemaList::ObjectRefList::const_iterator curIt;
							CARSchemaList::ObjectRefList::const_iterator endIt;
							
							// now get the iterator based on the type
							switch (nType)
							{
							case ARCON_GUIDE:
								{
									const CARSchemaList::ObjectRefList& schemaALGList = schema.GetActLinkGuides(); 
									curIt = schemaALGList.begin();
									endIt = schemaALGList.end();
								}
								break;
							case ARCON_FILTER_GUIDE:
								{
									const CARSchemaList::ObjectRefList& schemaFLGList = schema.GetFilterGuides();
									curIt = schemaFLGList.begin();
									endIt = schemaFLGList.end();
								}
								break;
							}

							// loop over the containers
							for (; curIt != endIt; ++curIt)
							{
								CARContainer cnt(*curIt);
								cnt.SetAppRefName(this->pApp.GetName());
								appCntList.push_back(*curIt);
							}
						}
					}
				}
				break;
			case ARCON_PACK:
				{
					if (refs.referenceList[i].type == ARREF_CONTAINER && refs.referenceList[i].reference.dataType == ARREF_DATA_ARSREF)
					{
						CARContainer cnt(refs.referenceList[i].reference.u.name);
						if (cnt.Exists() && cnt.GetType() == nType)
						{
							cnt.SetAppRefName(this->pApp.GetName());
							appCntList.push_back(cnt.GetInsideId());
						}
					}
				}
				break;
			}
		}

		// make the container list unique
		appCntList.sort();
		appCntList.unique();
		nResult = (int)appCntList.size();

		list<int>::iterator curIt = appCntList.begin();
		list<int>::iterator endIt = appCntList.end();
		for (; curIt != endIt; ++curIt)
		{
			CARContainer cnt(*curIt);
			strmResult << URLLink(cnt, rootLevel) << "<br/>" << endl;
		}
	}
	catch(exception& e)
	{
		cout << "EXCEPTION in ApplicationDetails_SearchContainer:" << e.what() << endl; 
	}

	return strmResult.str();
}

string CDocApplicationDetails::SearchMenus(int &nResult)
{
	stringstream strmResult;
	strmResult.str("");

	nResult = 0;

	try
	{
		list<int> appMnuList;
		const ARReferenceList& refs = this->pApp.GetContent();
		for(unsigned int i=0; i< refs.numItems; ++i)
		{
			if (refs.referenceList[i].type == ARREF_SCHEMA && refs.referenceList[i].reference.dataType == ARREF_DATA_ARSREF)
			{
				CARSchema schema(refs.referenceList[i].reference.u.name);
				if (schema.Exists())
				{
					CARFieldList* fields = schema.GetFields();
					unsigned int fieldCount = fields->GetCount();

					for (unsigned int fieldIndex = 0; fieldIndex < fieldCount; ++fieldIndex)
					{
						CARField fld(schema.GetInsideId(), 0, fieldIndex);
						const ARFieldLimitStruct& limits = fld.GetLimits();

						if (fld.GetDataType() == AR_DATA_TYPE_CHAR && limits.dataType == AR_DATA_TYPE_CHAR && limits.u.charLimits.charMenu[0] != 0)
						{
							CARCharMenu mnu(limits.u.charLimits.charMenu);
							if (mnu.Exists())
							{
								mnu.SetAppRefName(this->pApp.GetName());
								appMnuList.push_back(mnu.GetInsideId());
							}
						}
					}
				}
			}
		}

		// make the escalation list unique
		appMnuList.sort();
		appMnuList.unique();
		nResult = (int)appMnuList.size();

		list<int>::iterator curIt = appMnuList.begin();
		list<int>::iterator endIt = appMnuList.end();
		for (; curIt != endIt; ++curIt)
		{
			CARCharMenu mnu(*curIt);
			strmResult << URLLink(mnu, rootLevel) << "<br/>" << endl;
		}
	}
	catch(exception& e)
	{
		cout << "EXCEPTION in ApplicationDetails_SearchMenu: " << e.what() << endl; 
	}

	return strmResult.str();
}
