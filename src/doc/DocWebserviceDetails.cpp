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
#include "DocWebserviceDetails.h"
#include "DocOverlayHelper.h"
#include "../output/ImageTag.h"

CDocWebserviceDetails::CDocWebserviceDetails(CARContainer &obj)
: ws(obj)
{
}

CDocWebserviceDetails::~CDocWebserviceDetails(void)
{
}

void CDocWebserviceDetails::Documentation()
{
	CPageParams file(PAGE_DETAILS, &ws);
	this->rootLevel = file->GetRootLevel();

	try
	{
		string dir = file->GetPath();

		FileSystemUtil fsUtil(this->pInside->appConfig);
		if(fsUtil.CreateSubDirectory(dir)>=0)	// TODO: depending on the file structure there might be more or less directories to create .. move this to an Init function in IFileStructure
		{
			CWebPage webPage(file->GetFileName(), ws.GetName(), rootLevel, pInside->appConfig);
			CDocOverlayHelper overlayHelper(ws, rootLevel);

			//ContentHead informations
			stringstream strmHead;
			strmHead << CWebUtil::LinkToWebServiceIndex(this->rootLevel) << MenuSeparator
			         << ImageTag(ws, rootLevel) << CWebUtil::ObjName(this->ws.GetName())
			         << CAREnum::GetOverlayTypeString(ws.GetOverlayType());

			webPage.AddContentHead(strmHead.str(), overlayHelper.PlaceOverlayLink());
			webPage.AddContent(overlayHelper.PlaceOverlaidNotice());

			//Container Base Informations
			CDocContainerHelper *contHelper = new CDocContainerHelper(this->ws, this->rootLevel);
			webPage.AddContent(contHelper->BaseInfo());
			delete contHelper;

			//Object specific documentation
			webPage.AddContent(WSInformation());

			//History
			webPage.AddContent(this->pInside->ServerObjectHistory(&this->ws, this->rootLevel));

			//Save File
			webPage.SaveInFolder(dir);
		}
	}
	catch(exception& e)
	{
		cout << "EXCEPTION in WebserviceDetails_Documentation: " << e.what() << endl; 
	}
}

string CDocWebserviceDetails::WSInformation()
{
	//Container specific properties
	CTable tblProp("specificPropList", "TblObjectList");
	tblProp.AddColumn(20, "Description");
	tblProp.AddColumn(80, "Value");

	//Label
	try
	{
		if(ws.GetLabel() != NULL)
		{
			CTableCell cellWsDesc("Label", "");
			CTableCell cellWsValue(ws.GetLabel(), "");

			CTableRow row("");
			row.AddCell(cellWsDesc);
			row.AddCell(cellWsValue);
			tblProp.AddRow(row);
		}
	}
	catch(exception& e)
	{
		cout << "EXCEPTION in WebserviceDetails_BaseDocumentation (Label): " << e.what() << endl; 
	}

	//Description
	try
	{
		if(ws.GetDescription() != NULL)
		{
			CTableCell cellWsDesc("Description", "");
			CTableCell cellWsValue(ws.GetDescription(), "");

			CTableRow row("");
			row.AddCell(cellWsDesc);
			row.AddCell(cellWsValue);
			tblProp.AddRow(row);
		}
	}
	catch(exception& e)
	{
		cout << "EXCEPTION in WebserviceDetails_BaseDocumentation (Description): " << e.what() << endl; 
	}


	//Properties
	try
	{
		const ARReferenceList& refs = this->ws.GetContent();
		CARSchema wsOwnerSchema;

		const ARContainerOwnerObjList &wsOwners = ws.GetOwnerObjects();
		if (wsOwners.numItems > 0)
		{
			wsOwnerSchema = CARSchema(wsOwners.ownerObjList[0].ownerName);
		}

		for(unsigned int i=0; i< refs.numItems; i++)
		{
			stringstream strmWsDesc, strmWsValue;
			strmWsDesc.str("");
			strmWsValue.str("");

			const ARReferenceStruct& ref = refs.referenceList[i];
			switch(ref.type)
			{
			case ARREF_WS_PROPERTIES:
				{
					strmWsDesc << "Property";
					switch(ref.reference.u.extRef.value.dataType)
					{
					case AR_DATA_TYPE_CHAR:
						{

							try
							{
								CRefItem refItem(this->ws, REFM_WEBSERVICE_PROPERTY);
								string tmpValue = CWebUtil::Validate(ref.reference.u.extRef.value.u.charVal);
								strmWsValue << "<pre class=\"preWsInfo\">" << pInside->XMLFindFields(tmpValue, wsOwnerSchema.GetInsideId(), rootLevel, &refItem) << "</pre>";
							}
							catch(...)
							{
							}

						}
						break;
					}
				}
				break;
			case ARREF_WS_OPERATION:
				{
					strmWsDesc << "Operation";
					switch(ref.reference.u.extRef.value.dataType)
					{
					case AR_DATA_TYPE_CHAR:
						{
							try
							{
								CRefItem refItem(this->ws, REFM_WEBSERVICE_OPERATION);
								string tmpValue = CWebUtil::Validate(ref.reference.u.extRef.value.u.charVal);
								strmWsValue << "<pre class=\"preWsInfo\">" << pInside->XMLFindFields(tmpValue, wsOwnerSchema.GetInsideId(), rootLevel, &refItem) << "</pre>";								
							}
							catch(...)
							{
							}
						}
						break;
					}
				}
				break;
			case ARREF_WS_ARXML_MAPPING:
				{
					strmWsDesc << "Mapping";
					switch(ref.reference.u.extRef.value.dataType)
					{
					case AR_DATA_TYPE_CHAR:
						{
							try
							{
								CRefItem refItem(this->ws, REFM_WEBSERVICE_FIELDMAP);
								string tmpValue = CWebUtil::Validate(ref.reference.u.extRef.value.u.charVal);
								strmWsValue << "<pre class=\"preWsInfo\">" << pInside->XMLFindFields(tmpValue, wsOwnerSchema.GetInsideId(), rootLevel, &refItem) << "</pre>";
							}
							catch(...)
							{
							}
						}
						break;
					}
				}
				break;
			case ARREF_WS_WSDL:
				{
					strmWsDesc << "WSDL";
					switch(ref.reference.u.extRef.value.dataType)
					{
					case AR_DATA_TYPE_CHAR:
						{
							if(ref.reference.u.extRef.value.u.charVal != NULL)
							{
								strmWsValue << "<pre class=\"preWsInfo\">" << CWebUtil::Validate(ref.reference.u.extRef.value.u.charVal) << "</pre>";
							}
						}
						break;
					}
				}
				break;
			case ARREF_WS_PUBLISHING_LOC:
				{
					strmWsDesc << "Publishing Location";
					switch(ref.reference.u.extRef.value.dataType)
					{
					case AR_DATA_TYPE_CHAR:
						{
							if(ref.reference.u.extRef.value.u.charVal != NULL)
							{
								strmWsValue << "<pre class=\"preWsInfo\">" << CWebUtil::Validate(ref.reference.u.extRef.value.u.charVal) << "</pre>";
							}
						}
						break;
					}
				}
				break;
			case ARREF_WS_XML_SCHEMA_LOC:
				{
					strmWsDesc << "XML Schema";
					switch(ref.reference.u.extRef.value.dataType)
					{
					case AR_DATA_TYPE_CHAR:
						{
							if(ref.reference.u.extRef.value.u.charVal != NULL)
							{
								strmWsValue << "<pre class=\"preWsInfo\">" << CWebUtil::Validate(ref.reference.u.extRef.value.u.charVal) << "</pre>";
							}
						}
						break;
					}
				}
				break;
			}

			CTableRow row("");
			row.AddCell(CTableCell(strmWsDesc.str()));
			row.AddCell(CTableCell(strmWsValue.str()));
			tblProp.AddRow(row);
		}
	}
	catch(exception& e)
	{
		cout << "EXCEPTION in WebserviceDetails_BaseDocumentation: " << e.what() << endl; 
	}

	return tblProp.ToXHtml();
}
