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
#include "DocAnalyzer.h"
#include "../output/URLLink.h"

CDocAnalyzer::CDocAnalyzer()
{
	//this->path = path;
	//this->rootLevel = 1;
}

CDocAnalyzer::~CDocAnalyzer(void)
{
}

void CDocAnalyzer::Documentation()
{
	try
	{
		CPageParams file(PAGE_ANALYZER_MAIN);
		int rootLevel = file->GetRootLevel();
		string path = file->GetPath();

		FileSystemUtil fsUtil(this->pInside->appConfig);
		if(fsUtil.CreateSubDirectory(path)>=0)
		{
			CWebPage webPage(file->GetFileName(), "Analyzer", rootLevel, this->pInside->appConfig);

			//ContentHead informations
			stringstream contHeadStrm;
			contHeadStrm << "Performance Analyzer" << endl;
			webPage.AddContentHead(contHeadStrm.str());

			CPageParams file(PAGE_ANALYZER_QBE_CHECK);
			webPage.AddContent(URLLink("Form Index Analyzer", file, ImageTag::Document, rootLevel));
			IndexAnalyzer();		

			webPage.SaveInFolder(path);
		}
	}
	catch(exception& e)
	{
		cout << "EXCEPTION Analyzer_Documentation: " << e.what() << endl;
	}
}

void CDocAnalyzer::IndexAnalyzer()
{
	try
	{
		CPageParams file(PAGE_ANALYZER_QBE_CHECK);
		int rootLevel = file->GetRootLevel();
		string path = file->GetPath();


		FileSystemUtil fsUtil(this->pInside->appConfig);
		if(fsUtil.CreateSubDirectory(path)>=0)
		{
			CWebPage webPage(file->GetFileName(), "Form Index Analyzer", rootLevel, this->pInside->appConfig);

			//ContentHead informations
			stringstream contHeadStrm;
			contHeadStrm << "Form Index Analyzer" << endl;
			webPage.AddContentHead(contHeadStrm.str());


			CTable tbl("fieldListAll", "TblObjectList");
			tbl.AddColumn(20, "Field");
			tbl.AddColumn(20, "Form");
			tbl.AddColumn(60, "Comment");


			unsigned int schemaCount = this->pInside->schemaList.GetCount();
			for ( unsigned int schemaIndex = 0; schemaIndex < schemaCount; ++schemaIndex )
			{			
				CARSchema schema(schemaIndex);

				if (pInside->appConfig.bOverlaySupport && !IsVisibleObject(schema))
					continue;

				const ARIndexList& indexes = schema.GetIndexList();

				for(unsigned int nIndex = 0; nIndex < indexes.numItems; nIndex++)
				{
					for (unsigned int nField = 0; nField < indexes.indexList[nIndex].numFields; ++nField)
					{
						CARField field(schemaIndex, indexes.indexList[nIndex].fieldIds[nField]);

						if(field.Exists() && field.GetDataType() == AR_DATA_TYPE_CHAR)
						{
							const ARCharLimitsStruct& fLimit = field.GetLimits().u.charLimits;
							if(fLimit.qbeMatchOperation == AR_QBE_MATCH_ANYWHERE)
							{
								CTableRow row("");
								row.AddCell(CTableCell(URLLink(field, rootLevel)));
								row.AddCell(CTableCell(URLLink(schema, rootLevel)));

								stringstream strmTmp;
								strmTmp.str("");

								strmTmp << "Inefficient index because of QBE match anywhere in Index " << endl;
								strmTmp << this->pInside->LinkToSchemaIndex(indexes.indexList[nIndex].indexName, schema.GetInsideId(), rootLevel) << endl;
								row.AddCell(CTableCell(strmTmp.str()));
								tbl.AddRow(row);
							}

							if(fLimit.maxLength > 255)
							{
								CTableRow row("");
								row.AddCell(CTableCell(URLLink(field, rootLevel)));
								row.AddCell(CTableCell(URLLink(schema, rootLevel)));

								stringstream strmTmp;
								strmTmp.str("");

								strmTmp << "Length of field is greater than 255 " << endl;
								strmTmp << this->pInside->LinkToSchemaIndex(indexes.indexList[nIndex].indexName, schema.GetInsideId(), rootLevel) << endl;
								row.AddCell(CTableCell(strmTmp.str()));
								tbl.AddRow(row);
							}
						}
					}
				}
			}

			tbl.description = "If the QBE Match property on a character field is set";
			tbl.description += " to Anywhere, the database will not be able to";
			tbl.description += " optimize its search and will perform a table scan.";
			tbl.description += " Avoid using this setting if possible.";

			webPage.AddContent(tbl.ToXHtml());
			webPage.SaveInFolder(path);
		}
	}
	catch(exception& e)
	{
		cout << "EXCEPTION Analyzer_Index_Documentation: " << e.what() << endl;
	}
}
