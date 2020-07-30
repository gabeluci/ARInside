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
#include "DocSchemaDetails.h"
#include "DocFieldDetails.h"
#include "../output/CsvPage.h"
#include "../output/ImageTag.h"
#include "../output/TabControl.h"
#include "../output/URLLink.h"
#include "../output/WorkflowReferenceTable.h"
#include "../core/ARDayStructHelper.h"
#include "../core/ARHandle.h"
#include "../core/OpenWindowReportData.h"
#include "../core/OpenWindowSampleData.h"
#include "../util/Context.h"
#include "DocOverlayHelper.h"
#include "DocMain.h"

#include "rapidjson/document.h"
#include "rapidjson/genericwritestream.h"
#include "rapidjson/writer.h"

using namespace rapidjson;

CDocSchemaDetails::CDocSchemaDetails(unsigned int schemaInsideId, int rootLevel)
: schema(schemaInsideId)
{
	this->uniqueAlList.clear();
	this->uniqueEscalList.clear();
	this->uniqueFilterList.clear();
	this->overlayType = 0;
}

CDocSchemaDetails::~CDocSchemaDetails(void)
{
}

void CDocSchemaDetails::Documentation()
{
	try
	{
		CPageParams file(PAGE_DETAILS, &this->schema);
		rootLevel = file->GetRootLevel();
		string path = file->GetPath();

		FileSystemUtil fsUtil(this->pInside->appConfig);
		if(fsUtil.CreateSubDirectory(path)>=0)
		{
			//stringstream pgStrm;	
			CWebPage webPage(file->GetFileName(), this->schema.GetName(), rootLevel, this->pInside->appConfig);
			CDocOverlayHelper overlayHelper(schema, rootLevel);
			
			const ARCompoundSchema& compSchema = this->schema.GetCompound();
			overlayType = schema.GetOverlayType();

			//ContentHead informations
			stringstream contHeadStrm;
			contHeadStrm << CWebUtil::LinkToSchemaIndex(rootLevel, false) << endl;
			contHeadStrm << MenuSeparator << this->pInside->LinkToSchemaTypeList(schema.GetInternalSchemaType(), rootLevel) << endl;
			contHeadStrm << MenuSeparator << ImageTag(schema, rootLevel) << CWebUtil::ObjName(this->schema.GetName());
			contHeadStrm << CAREnum::GetOverlayTypeString(overlayType);

			if(!this->schema.GetAppRefName().empty())
				contHeadStrm << MenuSeparator << " Application " << this->pInside->LinkToContainer(this->schema.GetAppRefName(), rootLevel);

			webPage.AddContentHead(contHeadStrm.str(), overlayHelper.PlaceOverlayLink());
			webPage.AddContent(overlayHelper.PlaceOverlaidNotice());

			// add the javascript we need for this page to display correctly
			webPage.GetReferenceManager()
				.AddScriptReference("img/object_list.js")
				.AddScriptReference("img/schema_page.js")
				.AddScriptReference("img/jquery.timers.js")
				.AddScriptReference("img/jquery.address.min.js");

			// now the content
			CTabControl tabControl;

			// Add general schema informations to the page
			tabControl.AddTab("General", ShowGeneralInfo());

			// Add list of all fields to the page
			tabControl.AddTab("Fields", (IsJoinViewOrVendorForm() ? this->AllFieldsSpecial() : this->AllFields()) );

			// Add list of all views to the page
			tabControl.AddTab("Views", this->ShowVuiList());

			// Add a section which lists workflow thats reading data from this form
			tabControl.AddTab("Workflow", WorkflowDoc());

			// Add table with all references to the page
			tabControl.AddTab("References", GenerateReferencesTable(compSchema));

			webPage.AddContent(tabControl.ToXHtml());
			webPage.SaveInFolder(path);
		}
	}
	catch(exception& e)
	{
		cout << "EXCEPTION schema details documentation of '"<< this->schema.GetName() << "': " << e.what() << endl;
	}
}

//Create a page with all fields of this form
string CDocSchemaDetails::AllFields()
{		
	CTable tbl("fieldListAll", "TblObjectList");
	tbl.AddColumn(40, "Field Name");
	tbl.AddColumn(10, "Field ID");	
	tbl.AddColumn(10, "Datatype");
	tbl.AddColumn(10, "In Views");
	tbl.AddColumn(10, "Modified");
	tbl.AddColumn(20, "By");

	try
	{
		CARFieldList* fields = schema.GetFields();
		unsigned int fieldCount = fields->GetCount();
		for (unsigned int fieldIndex = 0; fieldIndex < fieldCount; ++fieldIndex)
		{
			CARField field(schema.GetInsideId(), 0, fieldIndex);

			CTableRow row("");

			CTableCell cellName(URLLink(field, rootLevel), "");
			CTableCell cellFieldId(field.GetFieldId(), "");
			CTableCell cellDataType(CAREnum::DataType(field.GetDataType()), "");

			stringstream strmTmp;
			if(field.GetDisplayInstances().numItems == 0 && field.GetFieldId() != 15)				
				strmTmp << "<span class=\"fieldInNoView\">" << field.GetDisplayInstances().numItems << "</span>" << endl;
			else
				strmTmp << field.GetDisplayInstances().numItems;			
			CTableCell cellNumViews(strmTmp.str(), "");			

			CTableCell cellTimestamp(CUtil::DateTimeToHTMLString(field.GetTimestamp()), "");
			CTableCell cellLastChanged(this->pInside->LinkToUser(field.GetLastChanged(), rootLevel), "");

			row.AddCell(cellName);
			row.AddCell(cellFieldId);
			row.AddCell(cellDataType);
			row.AddCell(cellNumViews);
			row.AddCell(cellTimestamp);
			row.AddCell(cellLastChanged);

			tbl.AddRow(row);
		}

		tbl.description = GenerateFieldTableDescription(tbl);

		AllFieldsCsv();
	}
	catch(exception& e)
	{
		cout << "EXCEPTION schema all fields of '"<< this->schema.GetName() << "': " << e.what() << endl;
	}

	return tbl.ToXHtml();	
}

void CDocSchemaDetails::AllFieldsCsv()
{		
	CTable tbl("fieldListAll", "TblObjectList");
	tbl.AddColumn(40, "Field Name");
	tbl.AddColumn(10, "Field ID");	
	tbl.AddColumn(10, "Datatype");
	tbl.AddColumn(10, "In Views");
	tbl.AddColumn(10, "Modified");
	tbl.AddColumn(20, "By");

	try
	{
		CARFieldList* fields = schema.GetFields();
		unsigned int fieldCount = fields->GetCount();
		for (unsigned int fieldIndex = 0; fieldIndex < fieldCount; ++fieldIndex)
		{
			CARField field(schema.GetInsideId(), 0, fieldIndex);

			CTableRow row("");
			CTableCell cellName(field.GetName(), "");
			CTableCell cellFieldId(field.GetFieldId(), "");
			CTableCell cellDataType(CAREnum::DataType(field.GetDataType()), "");			
			CTableCell cellNumViews(field.GetDisplayInstances().numItems, "");	
			CTableCell cellTimestamp(CUtil::DateTimeToString(field.GetTimestamp()), "");
			CTableCell cellLastChanged(field.GetLastChanged(), "");

			row.AddCell(cellName);		
			row.AddCell(cellFieldId);
			row.AddCell(cellDataType);
			row.AddCell(cellNumViews);
			row.AddCell(cellTimestamp);
			row.AddCell(cellLastChanged);

			tbl.AddRow(row);
		}

		//Save field information to ccs
		CPageParams file(PAGE_SCHEMA_FIELDS_CSV, &this->schema);
		CCsvPage csvPage(file->GetFileName(), this->pInside->appConfig);
		csvPage.SaveInFolder(file->GetPath(), tbl.ToCsv());
	}
	catch(exception& e)
	{
		cout << "EXCEPTION schema all fields csv of '" << this->schema.GetName() << "': " << e.what() << endl;
	}
}

void CDocSchemaDetails::AllFieldsJson(std::ostream &out)
{
	try
	{
		Document document;
		Document::AllocatorType &alloc = document.GetAllocator();
		document.SetArray();

		CARFieldList* fields = schema.GetFields();
		unsigned int fieldCount = fields->GetCount();
		bool isSpecialForm = IsJoinViewOrVendorForm();

		for (unsigned int fieldIndex = 0; fieldIndex < fieldCount; ++fieldIndex)
		{
			CARField field(schema.GetInsideId(), 0, fieldIndex);
			CPageParams fieldLink(PAGE_DETAILS, &field);

			Value item;
			item.SetArray();

			string strName = field.GetName();
			string strDate = CUtil::DateTimeToString(field.GetTimestamp());
			string strLink = CWebUtil::DocName(fieldLink->GetFileName());

			Value name(strName.c_str(), static_cast<SizeType>(strName.size()), alloc);
			Value modified(strDate.c_str(), static_cast<SizeType>(strDate.size()), alloc);
			Value link(strLink.c_str(), static_cast<SizeType>(strLink.size()), alloc);

			item.PushBack(static_cast<int>(field.GetFieldId()), alloc);
			item.PushBack(name, alloc);
			item.PushBack(field.GetDataType(), alloc);
			item.PushBack(field.GetDisplayInstances().numItems, alloc);
			item.PushBack(modified, alloc);
			item.PushBack(field.GetLastChanged(), alloc);
			item.PushBack(link, alloc);
			
			// for special forms, we need some more details for the real-field column
			if (isSpecialForm)
			{
				switch (field.GetMapping().fieldType)
				{
				case AR_FIELD_JOIN:
					{
						if(field.GetFieldId() == 1) // RequestID 1 in Joinform = ReqId1 | ReqId2
						{
							const ARCompoundSchema& compSchema = this->schema.GetCompound();
							CARSchema schemaLeft(compSchema.u.join.memberA);
							CARSchema schemaRight(compSchema.u.join.memberB);

							CARField fldLeft(schemaLeft.GetInsideId(), 1);
							CARField fldRight(schemaRight.GetInsideId(), 1);

							CPageParams schemaLeftLink(PAGE_DETAILS, &schemaLeft);
							CPageParams schemaRightLink(PAGE_DETAILS, &schemaRight);
							CPageParams fldLeftLink(PAGE_DETAILS, &fldLeft);
							CPageParams fldRightLink(PAGE_DETAILS, &fldRight);

							string leftFieldName;
							string leftFieldLink;
							if (fldLeft.Exists())
							{
								leftFieldName = fldLeft.GetName();
								leftFieldLink = CWebUtil::GetRelativeURL(rootLevel, fldLeftLink);
							}
							else
							{
								leftFieldName = "1";
							}

							string leftSchemaName = compSchema.u.join.memberA;
							string leftSchemaLink;
							if (schemaLeft.Exists())
								leftSchemaLink = CWebUtil::GetRelativeURL(rootLevel, schemaLeftLink);
							
							string rightFieldName;
							string rightFieldLink;
							if (fldRight.Exists())
							{
								rightFieldName = fldRight.GetName();
								rightFieldLink = CWebUtil::GetRelativeURL(rootLevel, fldRightLink);
							}
							else
							{
								rightFieldName = "1";
							}
							string rightSchemaName = compSchema.u.join.memberB;
							string rightSchemaLink;
							if (schemaRight.Exists())
								rightSchemaLink = CWebUtil::GetRelativeURL(rootLevel, schemaRightLink);

							Value leftNameVal(leftFieldName.c_str(), static_cast<SizeType>(leftFieldName.size()), alloc);
							Value leftLinkVal(leftFieldLink.c_str(), static_cast<SizeType>(leftFieldLink.size()), alloc);

							Value rightNameVal(rightFieldName.c_str(), static_cast<SizeType>(rightFieldName.size()), alloc);
							Value rightLinkVal(rightFieldLink.c_str(), static_cast<SizeType>(rightFieldLink.size()), alloc);

							item.PushBack(leftNameVal, alloc);
							item.PushBack(leftLinkVal, alloc);

							item.PushBack(rightNameVal, alloc);
							item.PushBack(rightLinkVal, alloc);
						}
						else
						{
							if(field.GetMapping().u.join.realId > 0)
							{
								const ARCompoundSchema& compSchema = this->schema.GetCompound();

								string baseSchemaName = (field.GetMapping().u.join.schemaIndex == 0 ? compSchema.u.join.memberA : compSchema.u.join.memberB);
								
								CARSchema baseSchema(baseSchemaName);
								CPageParams baseSchemaPage(PAGE_DETAILS, &baseSchema);

								CARField baseField(baseSchema.GetInsideId(), field.GetMapping().u.join.realId);
								CPageParams baseFieldPage(PAGE_DETAILS, &baseField);

								string baseFieldName;
								string baseFieldLink;

								// now check if the field exists in the join-member! Otherwise we can't determine the field name and URL!
								if (baseField.Exists())
								{
									baseFieldName = baseField.GetName();
									baseFieldLink = CWebUtil::GetRelativeURL(rootLevel, baseFieldPage);
								}
								else
								{
									// if this field doesn't exist in the join member, show the fieldid instead!
									stringstream baseFieldIdStrm;
									baseFieldIdStrm << field.GetMapping().u.join.realId;
									baseFieldName = baseFieldIdStrm.str();
								}
								
								string baseSchemaLink; 
								if (baseSchema.Exists())
									baseSchemaLink = CWebUtil::GetRelativeURL(rootLevel, baseSchemaPage);
								
								Value baseFileNameVal(baseFieldName.c_str(), static_cast<SizeType>(baseFieldName.size()), alloc);
								Value baseFileLinkVal(baseFieldLink.c_str(), static_cast<SizeType>(baseFieldLink.size()), alloc);

								item.PushBack(baseFileNameVal, alloc);
								item.PushBack(baseFileLinkVal, alloc);
								// write the schema-index (left- or right join-member) so we could link to the correct form
								item.PushBack(field.GetMapping().u.join.schemaIndex, alloc);
							}
						}
					}
					break;
				case AR_FIELD_VIEW:
					{
						string val = field.GetMapping().u.view.fieldName;
						Value itemVal(val.c_str(), static_cast<SizeType>(val.size()), alloc);
						item.PushBack(itemVal, alloc);
					}
					break;
				case AR_FIELD_VENDOR:
					{
						string val = field.GetMapping().u.vendor.fieldName;
						Value itemVal(val.c_str(), static_cast<SizeType>(val.size()), alloc);
						item.PushBack(itemVal, alloc);
					}
					break;
				}

			}

			document.PushBack(item, alloc);
		}

		GenericWriteStream output(out);
		Writer<GenericWriteStream> writer(output);

		out << endl << "<script type=\"text/javascript\">" << endl;
		out << "var schemaFieldList = "; document.Accept(writer); out << ";";
		if (isSpecialForm)
		{
			string type;
			switch (this->schema.GetCompound().schemaType)
			{
			case AR_SCHEMA_VIEW:
				type = "view";
				break;
			case AR_SCHEMA_VENDOR:
				type = "vendor";
				break;
			case AR_SCHEMA_JOIN:
				type = "join";
				break;
			}
			if (!type.empty())
			{
				out << "schemaFieldManager.setRenderer(\"" << type << "\");";
			}
		}
		out << endl;
		out << "</script>" << endl;
	}
	catch(exception& e)
	{
		cout << "EXCEPTION schema all fields json of '" << this->schema.GetName() << "': " << e.what() << endl;
	}
}

//Create a page with all fields of a joinform
string CDocSchemaDetails::AllFieldsSpecial()
{		
	CTable tbl("fieldListAll", "TblObjectList");
	tbl.AddColumn(20, "Field Name");
	tbl.AddColumn(5, "Field ID");
	tbl.AddColumn(5, "Datatype");
	tbl.AddColumn(30, "Real Field");
	tbl.AddColumn(10, "In Views");
	tbl.AddColumn(10, "Modified");
	tbl.AddColumn(20, "By");

	try
	{
		CARFieldList* fields = schema.GetFields();
		unsigned int fieldCount = fields->GetCount();
		for (unsigned int fieldIndex = 0; fieldIndex < fieldCount; ++fieldIndex)
		{
			CARField field(schema.GetInsideId(), 0, fieldIndex);

			CTableRow row("");
			CTableCell cellName(URLLink(field, rootLevel), "");
			CTableCell cellFieldId(field.GetFieldId(), "");

			stringstream strmTmp;
			if(field.GetDisplayInstances().numItems == 0 && field.GetFieldId() != 15)				
				strmTmp << "<span class=\"fieldInNoView\">" << field.GetDisplayInstances().numItems << "</span" << endl;
			else
				strmTmp << field.GetDisplayInstances().numItems;			
			
			CTableCell cellNumViews(strmTmp.str(), "");	
			CTableCell cellDataType(CAREnum::DataType(field.GetDataType()), "");

			strmTmp.str("");			
			switch (field.GetMapping().fieldType)
			{
			case AR_FIELD_JOIN:
				{
					if(field.GetFieldId() == 1) // RequestID 1 in Joinform = ReqId1 | ReqId2
					{
						const ARCompoundSchema& compSchema = this->schema.GetCompound();
						strmTmp << this->pInside->LinkToField(compSchema.u.join.memberA, 1, rootLevel) << "&nbsp;" << MenuSeparator << "&nbsp;" << this->pInside->LinkToSchema(compSchema.u.join.memberA, rootLevel);
						strmTmp << "<br/>" << endl;
						strmTmp << this->pInside->LinkToField(compSchema.u.join.memberB, 1, rootLevel) << "&nbsp;" << MenuSeparator << "&nbsp;" << this->pInside->LinkToSchema(compSchema.u.join.memberB, rootLevel);
					}
					else
					{
						if(field.GetMapping().u.join.realId > 0)
						{
							string tmpBaseSchema = this->schema.GetCompound().u.join.memberA;
							if(field.GetMapping().u.join.schemaIndex > 0)
								tmpBaseSchema = this->schema.GetCompound().u.join.memberB;

							strmTmp << this->pInside->LinkToField(tmpBaseSchema, field.GetMapping().u.join.realId, rootLevel) << "&nbsp;" << MenuSeparator << "&nbsp;" << this->pInside->LinkToSchema(tmpBaseSchema, rootLevel);
						}
						else
							strmTmp << "&nbsp;";
					}
				}
				break;
			case AR_FIELD_VIEW:
				strmTmp << field.GetMapping().u.view.fieldName;
				break;
			case AR_FIELD_VENDOR:
				strmTmp << field.GetMapping().u.vendor.fieldName;
				break;
			}

			CTableCell cellFieldRealId(strmTmp.str(), "");
			CTableCell cellTimestamp(CUtil::DateTimeToHTMLString(field.GetTimestamp()), "");
			CTableCell cellLastChanged(this->pInside->LinkToUser(field.GetLastChanged(), rootLevel), "");

			row.AddCell(cellName);
			row.AddCell(cellFieldId);
			row.AddCell(cellDataType);
			row.AddCell(cellFieldRealId);
			row.AddCell(cellNumViews);
			row.AddCell(cellTimestamp);
			row.AddCell(cellLastChanged);

			tbl.AddRow(row);
		}

		tbl.description = GenerateFieldTableDescription(tbl);

		AllFieldsSpecialCsv();
	}
	catch(exception& e)
	{
		cout << "EXCEPTION schema all fields join of '"<< this->schema.GetName() << "': " << e.what() << endl;
	}

	return tbl.ToXHtml();	
}

void CDocSchemaDetails::AllFieldsSpecialCsv()
{		
	CTable tbl("fieldListAll", "TblObjectList");
	tbl.AddColumn(20, "Field Name");
	tbl.AddColumn(5, "Field ID");
	tbl.AddColumn(5, "Datatype");
	tbl.AddColumn(30, "Real Field");
	tbl.AddColumn(10, "In Views");
	tbl.AddColumn(10, "Modified");
	tbl.AddColumn(20, "By");

	try
	{
		CARFieldList* fields = schema.GetFields();
		unsigned int fieldCount = fields->GetCount();
		for (unsigned int fieldIndex = 0; fieldIndex < fieldCount; ++fieldIndex)
		{
			CARField field(schema.GetInsideId(), 0, fieldIndex);

			CTableRow row("");
			CTableCell cellName(field.GetName(), "");
			CTableCell cellFieldId(field.GetFieldId(), "");
			CTableCell cellNumViews(field.GetDisplayInstances().numItems, "");
			CTableCell cellDataType(CAREnum::DataType(field.GetDataType()), "");

			stringstream strmTmp;
			switch (field.GetMapping().fieldType)
			{
			case AR_FIELD_JOIN:
				{
					if(field.GetFieldId() == 1) // RequestID 1 in Joinform = ReqId1 | ReqId2
					{
						strmTmp << 1;
					}
					else
					{
						if(field.GetMapping().u.join.realId > 0)
						{
							strmTmp << field.GetMapping().u.join.realId;
						}
					}
				}
				break;
			case AR_FIELD_VIEW:
				{
					strmTmp << field.GetMapping().u.view.fieldName;
				}
				break;
			case AR_FIELD_VENDOR:
				{
					strmTmp << field.GetMapping().u.vendor.fieldName;
				}
				break;			
			}

			CTableCell cellFieldRealId(strmTmp.str());
			CTableCell cellTimestamp(CUtil::DateTimeToString(field.GetTimestamp()), "");
			CTableCell cellLastChanged(field.GetLastChanged(), "");

			row.AddCell(cellName);
			row.AddCell(cellFieldId);
			row.AddCell(cellDataType);
			row.AddCell(cellFieldRealId);
			row.AddCell(cellNumViews);
			row.AddCell(cellTimestamp);
			row.AddCell(cellLastChanged);

			tbl.AddRow(row);
		}

		//Save field information to csv
		CPageParams file(PAGE_SCHEMA_FIELDS_CSV, &this->schema);
		CCsvPage csvPage(file->GetFileName(), this->pInside->appConfig);
		csvPage.SaveInFolder(file->GetPath(), tbl.ToCsv());
	}
	catch(exception& e)
	{
		cout << "EXCEPTION schema all fields join csv of '" << this->schema.GetName() << "': " << e.what() << endl;
	}
}

string CDocSchemaDetails::GenerateFieldTableDescription(CTable &tbl)
{
	stringstream outputStrm;
	AllFieldsJson(outputStrm);
	outputStrm << "<div><span class='clearable'><input type=\"text\" class='data_field' id=\"fieldNameFilter\" placeholder=\"search by name or id\"/></span><button id=\"execFieldFilter\">Filter</button></div>" << endl;
	outputStrm << ImageTag(ImageTag::Document, rootLevel) << "<span id='fieldListFilterResultCount'></span>" << tbl.NumRows() << " fields (" << URLLink("data", CPageParams(PAGE_SCHEMA_FIELDS_CSV, &this->schema), rootLevel) << ")" << endl;
	outputStrm << "<div id=\"result\"></div>";
	return outputStrm.str();
}

bool CDocSchemaDetails::InAlList(string objName)
{
	list<string>::iterator listIter;		
	for ( listIter = this->uniqueAlList.begin(); listIter != this->uniqueAlList.end(); listIter++ )
	{
		string *listItemName = &(*listIter);
		if(strcmp(objName.c_str(), listItemName->c_str())==0)
		{
			return true;
		}
	}
	return false;
}

bool CDocSchemaDetails::InFilterList(string objName)
{
	list<string>::iterator listIter;		
	for ( listIter = this->uniqueFilterList.begin(); listIter != this->uniqueFilterList.end(); listIter++ )
	{
		string *listItemName = &(*listIter);
		if(strcmp(objName.c_str(), listItemName->c_str())==0)
		{
			return true;
		}
	}
	return false;
}

bool CDocSchemaDetails::InEscalList(string objName)
{
	list<string>::iterator listIter;		
	for ( listIter = this->uniqueEscalList.begin(); listIter != this->uniqueEscalList.end(); listIter++ )
	{
		string *listItemName = &(*listIter);
		if(strcmp(objName.c_str(), listItemName->c_str())==0)
		{
			return true;
		}
	}
	return false;
}

bool CDocSchemaDetails::IsSchemaInWFConnectStruct(const ARWorkflowConnectStruct& wfCS)
{
	if (wfCS.type == AR_WORKFLOW_CONN_SCHEMA_LIST && wfCS.u.schemaList != NULL)
	{
		for (unsigned int connectIndex = 0; connectIndex < wfCS.u.schemaList->numItems; ++connectIndex)
		{
			if (schema.GetName() == wfCS.u.schemaList->nameList[connectIndex])
			{
				return true;
			}
		}
	}
	return false;
}

void AddJsonRow(Document &doc, CARActiveLink &al, int rootLevel)
{
	CPageParams alDetailPage(PAGE_DETAILS, &al);
	Document::AllocatorType &alloc = doc.GetAllocator();
	Value item;
	item.SetArray();

	string strModDate, strActlinkName, strLink;
	strModDate = CUtil::DateTimeToString(al.GetTimestamp());
	strActlinkName = al.GetName();
	strLink = CWebUtil::GetRelativeURL(rootLevel, alDetailPage);

	Value modDate, alName, alLink;
	modDate.SetString(strModDate.c_str(), static_cast<SizeType>(strModDate.length()), alloc);
	alName.SetString(strActlinkName.c_str(), static_cast<SizeType>(strActlinkName.length()), alloc);
	alLink.SetString(strLink.c_str(), static_cast<SizeType>(strLink.length()), alloc);

	item.PushBack((al.GetServerObjectTypeXML()-AR_STRUCT_XML_OFFSET), alloc);
	item.PushBack(alName, alloc);
	item.PushBack((al.GetEnabled() ? true : false), alloc);
	item.PushBack(al.GetOrder(), alloc);
	item.PushBack(al.GetExecuteMask(), alloc);
	item.PushBack(al.GetIfActions().numItems, alloc);
	item.PushBack(al.GetElseActions().numItems, alloc);
	item.PushBack(modDate, alloc);
	item.PushBack(al.GetLastChanged(), alloc);
	item.PushBack(alLink, alloc);
	
	doc.PushBack(item, alloc);
}

void AddJsonRow(Document &doc, CARFilter &flt, int rootLevel)
{
	CPageParams fltDetailPage(PAGE_DETAILS, &flt);
	Document::AllocatorType &alloc = doc.GetAllocator();
	Value item;
	item.SetArray();

	string strModDate, strName, strLink;
	strModDate = CUtil::DateTimeToString(flt.GetTimestamp());
	strName = flt.GetName();
	strLink = CWebUtil::GetRelativeURL(rootLevel, fltDetailPage);

	Value modDate, objName, objLink;
	modDate.SetString(strModDate.c_str(), static_cast<SizeType>(strModDate.length()), alloc);
	objName.SetString(strName.c_str(), static_cast<SizeType>(strName.length()), alloc);
	objLink.SetString(strLink.c_str(), static_cast<SizeType>(strLink.length()), alloc);

	item.PushBack((flt.GetServerObjectTypeXML()-AR_STRUCT_XML_OFFSET), alloc);
	item.PushBack(objName, alloc);
	item.PushBack((flt.GetEnabled() ? true : false), alloc);
	item.PushBack(flt.GetOrder(), alloc);
	item.PushBack(flt.GetOperation(), alloc);
	item.PushBack(flt.GetIfActions().numItems, alloc);
	item.PushBack(flt.GetElseActions().numItems, alloc);
	item.PushBack(modDate, alloc);
	item.PushBack(flt.GetLastChanged(), alloc);
	item.PushBack(objLink, alloc);
	
	doc.PushBack(item, alloc);
}

void AddJsonRow(Document &doc, CAREscalation &esc, int rootLevel)
{
	CPageParams escDetailPage(PAGE_DETAILS, &esc);
	Document::AllocatorType &alloc = doc.GetAllocator();
	Value item;
	item.SetArray();

	string strModDate, strName, strLink;
	strModDate = CUtil::DateTimeToString(esc.GetTimestamp());
	strName = esc.GetName();
	strLink = CWebUtil::GetRelativeURL(rootLevel, escDetailPage);

	Value modDate, objName, objLink;
	modDate.SetString(strModDate.c_str(), static_cast<SizeType>(strModDate.length()), alloc);
	objName.SetString(strName.c_str(), static_cast<SizeType>(strName.length()), alloc);
	objLink.SetString(strLink.c_str(), static_cast<SizeType>(strLink.length()), alloc);

	item.PushBack((esc.GetServerObjectTypeXML()-AR_STRUCT_XML_OFFSET), alloc);
	item.PushBack(objName, alloc);
	item.PushBack((esc.GetEnabled() ? true : false), alloc);
	item.PushBack("", alloc);
	item.PushBack(esc.GetTimeStruct().escalationTmType, alloc);
	item.PushBack(esc.GetIfActions().numItems, alloc);
	item.PushBack(esc.GetElseActions().numItems, alloc);
	item.PushBack(modDate, alloc);
	item.PushBack(esc.GetLastChanged(), alloc);
	item.PushBack(objLink, alloc);
	
	doc.PushBack(item, alloc);
}

void AddJsonRow(Document &doc, CARContainer &cnt, int rootLevel)
{
	CPageParams cntDetailPage(PAGE_DETAILS, &cnt);
	Document::AllocatorType &alloc = doc.GetAllocator();
	Value item;
	item.SetArray();

	string strModDate, strName, strLink;
	strModDate = CUtil::DateTimeToString(cnt.GetTimestamp());
	strName = cnt.GetName();
	strLink = CWebUtil::GetRelativeURL(rootLevel, cntDetailPage);

	Value modDate, objName, objLink;
	modDate.SetString(strModDate.c_str(), static_cast<SizeType>(strModDate.length()), alloc);
	objName.SetString(strName.c_str(), static_cast<SizeType>(strName.length()), alloc);
	objLink.SetString(strLink.c_str(), static_cast<SizeType>(strLink.length()), alloc);

	item.PushBack((cnt.GetServerObjectTypeXML()-AR_STRUCT_XML_OFFSET), alloc);
	item.PushBack(objName, alloc);
	item.PushBack(cnt.GetType(), alloc);
	item.PushBack("", alloc);
	item.PushBack("", alloc);
	item.PushBack("", alloc);
	item.PushBack("", alloc);
	item.PushBack(modDate, alloc);
	item.PushBack(cnt.GetLastChanged(), alloc);
	item.PushBack(objLink, alloc);
	
	doc.PushBack(item, alloc);
}

string CDocSchemaDetails::WorkflowDoc()
{
	try
	{
		//CPageParams file(PAGE_SCHEMA_WORKFLOW, &this->schema);

		Document document;
		document.SetArray();

		//Field references
		CTable tblRef("referenceList", "TblObjectList");
		tblRef.AddColumn(35, "Server object");
		tblRef.AddColumn(05, "Enabled");
		tblRef.AddColumn(05, "Order");
		tblRef.AddColumn(15, "Execute On");
		tblRef.AddColumn(05, "If");
		tblRef.AddColumn(05, "Else");
		tblRef.AddColumn(15, "Changed");
		tblRef.AddColumn(15, "By");

		const CARSchemaList::ObjectRefList& alList = this->schema.GetActiveLinks();
		const CARSchemaList::ObjectRefList& fltList = this->schema.GetFilters();
		const CARSchemaList::ObjectRefList& escList = this->schema.GetEscalations();
		const CARSchemaList::ObjectRefList& algList = this->schema.GetActLinkGuides();
		const CARSchemaList::ObjectRefList& flgList = this->schema.GetFilterGuides();
		const CARSchemaList::ObjectRefList& wbsList = this->schema.GetWebservices();

		// Add all active links
		CARSchemaList::ObjectRefList::const_iterator curIt = alList.begin();
		CARSchemaList::ObjectRefList::const_iterator endIt = alList.end();
		for (; curIt != endIt; ++curIt)
		{
			CARActiveLink al(*curIt);
			AddJsonRow(document, al, rootLevel);
		}

		// Add all filters
		curIt = fltList.begin();
		endIt = fltList.end();
		for (; curIt != endIt; ++curIt)
		{
			CARFilter flt(*curIt);
			AddJsonRow(document, flt, rootLevel);
		}

		// Add all escalations
		curIt = escList.begin();
		endIt = escList.end();
		for (; curIt != endIt; ++curIt)
		{
			CAREscalation esc(*curIt);
			AddJsonRow(document, esc, rootLevel);
		}

		// add all active link guides
		curIt = algList.begin();
		endIt = algList.end();
		for (; curIt != endIt; ++curIt)
		{
			CARContainer alg(*curIt);
			AddJsonRow(document, alg, rootLevel);
		}

		// add all filter guides
		curIt = flgList.begin();
		endIt = flgList.end();
		for (; curIt != endIt; ++curIt)
		{
			CARContainer flg(*curIt);
			AddJsonRow(document, flg, rootLevel);
		}

		// add all webservices
		curIt = wbsList.begin();
		endIt = wbsList.end();
		for (; curIt != endIt; ++curIt)
		{
			CARContainer ws(*curIt);
			AddJsonRow(document, ws, rootLevel);
		}

		// generate json output struct
		stringstream strm;
		GenericWriteStream genericStream(strm);
		Writer<GenericWriteStream> genericWriter(genericStream);

		strm << "<script type=\"text/javascript\">" << "var schemaWFLInit = false;" << endl;
		strm << "var referenceList = "; document.Accept(genericWriter); strm << ";" << endl
		     << "var rootLevel = " << rootLevel << endl
		     << "</script>" << endl
				 << CDocMain::CreateSchemaReferenceFilterControl() << endl
		     << tblRef;
		return strm.str();
	}
	catch(exception& e)
	{
		cout << "EXCEPTION schema workflow doc of '" << this->schema.GetName() << "': " << e.what() << endl;
		return "";
	}
}

//list of groups with access rights
void CDocSchemaDetails::ShowPermissionProperties(std::ostream &strm, CARProplistHelper *propIndex)
{
	try
	{
		//CPageParams file(PAGE_SCHEMA_PERMISSIONS, &this->schema);

		CTable tbl("permissionList", "TblObjectList");
		tbl.AddColumn(60, "Group Name");
		tbl.AddColumn(20, "Group Id");
		tbl.AddColumn(20, "Permission");

		const ARPermissionList& perms = this->schema.GetPermissions();
		for(unsigned int i = 0; i < perms.numItems; ++i)
		{
			if(this->pInside->ValidateGroup(this->schema.GetAppRefName(), perms.permissionList[i].groupId))
			{
				CTableRow row("");
				stringstream perm;

				if(perms.permissionList[i].permissions == AR_PERMISSIONS_HIDDEN)
					perm << ImageTag(ImageTag::Hidden, rootLevel);
				else
					perm << ImageTag(ImageTag::Visible, rootLevel);

				perm << CAREnum::ObjectPermission(perms.permissionList[i].permissions);

				row.AddCell(CTableCell(this->pInside->LinkToGroup(this->schema.GetAppRefName(), perms.permissionList[i].groupId, rootLevel)));
				row.AddCell(CTableCell(perms.permissionList[i].groupId));
				row.AddCell(perm.str());
				tbl.AddRow(row);
			}
		}

		//CPageParams file(PAGE_SCHEMA_SUBADMINS, &this->schema); //////////////////////////////////
		CTable tblSubAdm("subadminPerms", "TblObjectList");
		tblSubAdm.AddColumn(90, "Group Name");
		tblSubAdm.AddColumn(10, "Group Id");

		const ARInternalIdList& subAdmins = schema.GetSubadmins();
		for(unsigned int i = 0; i < subAdmins.numItems; ++i)
		{
			CTableRow row("");
			row.AddCell(this->pInside->LinkToGroup(this->schema.GetAppRefName(), subAdmins.internalIdList[i], rootLevel));
			row.AddCell(subAdmins.internalIdList[i]);
			tblSubAdm.AddRow(row);
		}

		//Show all fields with all group permissions
		CTable tblFieldPerm("fieldPerms", "TblObjectList");

		tblFieldPerm.AddColumn(40, "Field Name");
		tblFieldPerm.AddColumn(10, "Field ID");	
		tblFieldPerm.AddColumn(10, "Datatype");		
		tblFieldPerm.AddColumn(40, "Permissions");


		CARFieldList* fields = schema.GetFields();
		unsigned int fieldCount = fields->GetCount();
		for (unsigned int fieldIndex = 0; fieldIndex < fieldCount; ++fieldIndex)
		{
			CARField field(schema.GetInsideId(), 0, fieldIndex);

			//Field Permissions
			stringstream strmFieldPermissions;
			strmFieldPermissions.str("");

			const ARPermissionList& fldPerms = field.GetPermissions();
			if(fldPerms.numItems > 0)
			{
				CTable tblFieldPermissionDetails("PermissionFieldList", "TblHidden");
				tblFieldPermissionDetails.AddColumn(50, "Group Name");
				tblFieldPermissionDetails.AddColumn(50, "Permission");
				tblFieldPermissionDetails.DisableHeader();

				for(unsigned int i = 0; i < fldPerms.numItems; ++i)
				{
					stringstream perm;
					
					if(fldPerms.permissionList[i].permissions == AR_PERMISSIONS_CHANGE)
						perm << ImageTag(ImageTag::Edit, rootLevel);
					else
						perm << ImageTag(ImageTag::Visible, rootLevel);

					perm << CAREnum::FieldPermission(fldPerms.permissionList[i].permissions);

					CTableRow row("");
					row.AddCell(this->pInside->LinkToGroup(schema.GetAppRefName(), fldPerms.permissionList[i].groupId, rootLevel));
					row.AddCell(perm.str());
					tblFieldPermissionDetails.AddRow(row);
				}

				strmFieldPermissions << tblFieldPermissionDetails;
			}
			else
			{
				strmFieldPermissions << EmptyValue << endl;
			}


			CTableRow row("");			
			row.AddCell(CTableCell(URLLink(field, rootLevel)));
			row.AddCell(CTableCell(field.GetFieldId()));
			row.AddCell(CTableCell(CAREnum::DataType(field.GetDataType())));
			row.AddCell(CTableCell(strmFieldPermissions.str()));
			tblFieldPerm.AddRow(row);
		}

		strm << "<h2>" << ImageTag(ImageTag::Document, rootLevel) << "Permissions" << "</h2>";
		strm << "<div id='schemaPermissions'>" 
		         << "<h2>" << "Group Permissions" << "</h2>" << "<div>" << tbl << "</div>"
             << "<h2>" << "Subadministrator Permissions" << "</h2>" << "<div>" << tblSubAdm << "</div>"
             << "<h2>" << "Field Permissions" << "</h2>" << "<div>" << tblFieldPerm << "</div>"
		     << "</div>";
	}
	catch(exception& e)
	{
		cout << "EXCEPTION schema permission doc of '" << this->schema.GetName() << "': " << e.what() << endl;
	}
}

//Create a page that shows a list of all indexes
void CDocSchemaDetails::ShowIndexProperties(std::ostream &strm, CARProplistHelper *propIndex)
{
	try
	{
		//CPageParams file(PAGE_SCHEMA_INDEXES, &this->schema);

		strm << "<h2>" << ImageTag(ImageTag::Document, rootLevel) << "Indexes" << "</h2>";
		strm << "<div>";

		const ARIndexList& indexList = this->schema.GetIndexList();
		for(unsigned int nIndex=0; nIndex < indexList.numItems; ++nIndex)
		{		
			CTable tbl("indexTbl", "TblObjectList");
			tbl.AddColumn(0, "Field Name");
			tbl.AddColumn(0, "Field ID");
			tbl.AddColumn(0, "Datatype");
			tbl.AddColumn(0, "Modified");
			tbl.AddColumn(0, "By");

			stringstream tblDesc;
			if(indexList.indexList[nIndex].unique)
				tblDesc << "Unique Index :" << CWebUtil::ObjName(indexList.indexList[nIndex].indexName);
			else
				tblDesc << "Index: " << CWebUtil::ObjName(indexList.indexList[nIndex].indexName);

			tbl.description = tblDesc.str();

			for(unsigned int nField=0; nField < indexList.indexList[nIndex].numFields; ++nField)
			{
				CARField field(schema.GetInsideId(), indexList.indexList[nIndex].fieldIds[nField]);

				if (field.Exists())
				{
					CTableRow row("");
					row.AddCell( CTableCell(URLLink(field, rootLevel)));
					row.AddCell( CTableCell(field.GetFieldId()));
					row.AddCell( CTableCell(CAREnum::DataType(field.GetDataType())));
					row.AddCell( CTableCell(CUtil::DateTimeToHTMLString(field.GetDataType())));
					row.AddCell( CTableCell(this->pInside->LinkToUser(field.GetLastChanged(), rootLevel)));
					tbl.AddRow(row);

					//Add a reference
					CRefItem refItem(this->schema, 0, nIndex, REFM_SCHEMA_INDEX);
					pInside->AddFieldReference(schema.GetInsideId(), field.GetInsideId(), refItem);
				}
			}

			strm << tbl;
		}

		strm << "</div>";
	}
	catch(exception& e)
	{
		cout << "EXCEPTION creating schema index doc of '" << this->schema.GetName() << "': " << e.what() << endl;
	}
}

//Create a page that shows the form resultlist
void CDocSchemaDetails::ShowResultListProperties(std::ostream &strm, CARProplistHelper *propIndex)
{
	try
	{
		CTable tbl("fieldListIndex", "TblObjectList");
		tbl.AddColumn(25, "Field Name");
		tbl.AddColumn(10, "Field Id");
		tbl.AddColumn(10, "Datatype");
		tbl.AddColumn(5, "Width");
		tbl.AddColumn(10, "Separator");
		tbl.AddColumn(20, "Modified");
		tbl.AddColumn(20, "By");

		const AREntryListFieldList& resultFields = schema.GetResultFields();
		for(unsigned int i = 0; i < resultFields.numItems; ++i)
		{
			CARField field(schema.GetInsideId(), resultFields.fieldsList[i].fieldId);

			if (field.Exists())
			{
				CTableRow row("");
				row.AddCell( CTableCell(URLLink(field, rootLevel)));
				row.AddCell( CTableCell(field.GetFieldId()));
				row.AddCell( CTableCell(CAREnum::DataType(field.GetDataType())));
				row.AddCell( CTableCell(resultFields.fieldsList[i].columnWidth));
				row.AddCell( CTableCell(resultFields.fieldsList[i].separator));
				row.AddCell( CTableCell(CUtil::DateTimeToHTMLString(field.GetTimestamp())));
				row.AddCell( CTableCell(this->pInside->LinkToUser(field.GetLastChanged(), rootLevel)));
				tbl.AddRow(row);

				//Add a reference
				CRefItem refItem(this->schema, REFM_SCHEMA_RESULTLIST);
				pInside->AddFieldReference(schema.GetInsideId(), field.GetInsideId(), refItem);
			}
		}

		strm << "<h2>" << ImageTag(ImageTag::Document, rootLevel) << "Result List Fields" << "</h2>";
		strm << "<div>" << tbl << "</div>";
	}
	catch(exception& e)
	{
		cout << "EXCEPTION creating schema resultlist doc of '" << this->schema.GetName() << "': " << e.what() << endl;
	}
}

//Create a page that shows the page sortslist
void CDocSchemaDetails::ShowSortListProperties(std::ostream &strm, CARProplistHelper *propIndex)
{
	try
	{
		//CPageParams file(PAGE_SCHEMA_SORTLIST, &this->schema);

		CTable tbl("fieldListIndex", "TblObjectList");
		tbl.AddColumn(10, "Sort Order");
		tbl.AddColumn(30, "Field Name");
		tbl.AddColumn(10, "Field Id");
		tbl.AddColumn(10, "Datatype");
		tbl.AddColumn(20, "Modified");
		tbl.AddColumn(20, "By");


		const ARSortList& sorting = schema.GetSortList();
		for(unsigned int i = 0; i < sorting.numItems; ++i)
		{
			CARField field(schema.GetInsideId(), sorting.sortList[i].fieldId);

			if (field.Exists())
			{
				CTableRow row("");

				string sortImage;
				if(sorting.sortList[i].sortOrder == AR_SORT_DESCENDING)
					sortImage = ImageTag(ImageTag::SortDesc, rootLevel);
				else
					sortImage = ImageTag(ImageTag::SortAsc, rootLevel);

				row.AddCell( CTableCell(sortImage));
				row.AddCell( CTableCell(URLLink(field, rootLevel)));
				row.AddCell( CTableCell(field.GetFieldId()));
				row.AddCell( CTableCell(CAREnum::DataType(field.GetDataType())));				
				row.AddCell( CTableCell(CUtil::DateTimeToHTMLString(field.GetTimestamp())));
				row.AddCell( CTableCell(this->pInside->LinkToUser(field.GetLastChanged(), rootLevel)));

				tbl.AddRow(row);

				//Add a reference
				CRefItem refItem(this->schema, REFM_SCHEMA_SORTLIST);
				pInside->AddFieldReference(schema.GetInsideId(), field.GetInsideId(), refItem);
			}
		}

		strm << "<h2>" << ImageTag(ImageTag::Document, rootLevel) << "Sort" << "</h2>";
		strm << "<div>" << tbl << "</div>";
	}
	catch(exception& e)
	{
		cout << "EXCEPTION creating schema sortlist doc of '" << this->schema.GetName() << "': " << e.what() << endl;
	}
}

//Create a page with a list of all views
string CDocSchemaDetails::ShowVuiList()
{	
	try
	{
		//CPageParams file(PAGE_OVERVIEW, AR_STRUCT_ITEM_XML_VUI, &this->schema);

		CTable tbl("vuiList", "TblObjectList");
		tbl.AddColumn(30, "Vui Name");
		tbl.AddColumn(20, "Label");
		tbl.AddColumn(10, "Web Alias");
		tbl.AddColumn(10, "Type");
		tbl.AddColumn(15, "Modified");
		tbl.AddColumn(15, "By");

		unsigned int vuiCount = schema.GetVUIs()->GetCount();
		for (unsigned int vuiIndex = 0; vuiIndex < vuiCount; ++vuiIndex)
		{
			CARVui vui(schema.GetInsideId(), 0, vuiIndex);

			CTableRow row("");			
			row.AddCell( CTableCell(URLLink(vui, rootLevel)));
			row.AddCell( CTableCell(vui.Label()));
			row.AddCell( CTableCell(vui.webAlias()));
			row.AddCell( CTableCell(CAREnum::VuiType(vui.GetType())));
			row.AddCell( CTableCell(CUtil::DateTimeToHTMLString(vui.GetTimestamp())));
			row.AddCell( CTableCell(this->pInside->LinkToUser(vui.GetLastChanged(), rootLevel)));
			tbl.AddRow(row);
		}

		stringstream strm;
		strm << tbl;
		return strm.str();
	}
	catch(exception& e)
	{
		cout << "EXCEPTION creating schema vuilist doc of '" << this->schema.GetName() << "': " << e.what() << endl;
		return "";
	}
}

string CDocSchemaDetails::TypeDetails()
{
	stringstream strm;
	strm.str("");

	try
	{
		const ARCompoundSchema& compSchema = schema.GetCompound();
		switch(compSchema.schemaType)
		{
		case AR_SCHEMA_JOIN:
			{
				strm << "(" << "<span id='join-left'>" << this->pInside->LinkToSchema(compSchema.u.join.memberA, rootLevel) << "</span>" << " <-> " << "<span id='join-right'>" << this->pInside->LinkToSchema(compSchema.u.join.memberB, rootLevel) << "</span>" << ")" << "<br/>";

				if(compSchema.u.join.joinQual.operation != AR_COND_OP_NONE)
				{
					stringstream strmQuery;
					CARSchema memberA(compSchema.u.join.memberA);
					CARSchema memberB(compSchema.u.join.memberB);
					CRefItem refItem(this->schema, REFM_SCHEMA_JOIN_QUALIFICATION);

					CARQualification arQual(*this->pInside, refItem, memberA.GetInsideId(), memberB.GetInsideId(), rootLevel);
					arQual.CheckQuery(&compSchema.u.join.joinQual, strmQuery);

					strm << "Qualification: " << strmQuery.str();
				}
			}
			break;
		case AR_SCHEMA_VIEW:
			{
				strm << "<span class='additionalInfo'>" << "(" << "Table&nbsp;Name: " << compSchema.u.view.tableName << " &nbsp;&nbsp;&nbsp; "
				     << "Key&nbsp;Field: " << compSchema.u.view.keyField << ")" << "</span>";
			}
			break;			
		case AR_SCHEMA_VENDOR:
			{
				strm << "<span class='additionalInfo'>" << "(" << "Plugin:&nbsp;" << compSchema.u.vendor.vendorName << " &nbsp;&nbsp;&nbsp; ";
				strm << "Table: " << compSchema.u.vendor.tableName << ")" << "</span>";
			}
			break;
		default:
			{
				strm << EmptyValue;
			}
			break;
		}
	}
	catch(exception& e)
	{
		cout << "EXCEPTION enumerating regular schema type information of '" << this->schema.GetName() << "': " << e.what() << endl;
	}
	return strm.str();
}

string CDocSchemaDetails::ContainerReferences()
{
	stringstream strm;
	strm.str("");
	try
	{
		CContainerTable *contTable = new CContainerTable(*this->pInside);

		//// Add Packing Lists ////
		const CARSchemaList::ObjectRefList& pkl = schema.GetPackingLists();
		CARSchemaList::ObjectRefList::const_iterator curIt = pkl.begin();
		CARSchemaList::ObjectRefList::const_iterator endIt = pkl.end();

		for (; curIt != endIt; ++curIt)
		{
			CARContainer cont(*curIt);
			contTable->AddRow(cont, rootLevel);
		}

		//// create output ////
		if(contTable->NumRows() > 0)
			strm << *contTable;
		else
			strm << EmptyValue;

		delete contTable;
	}
	catch(exception& e)
	{
		cout << "EXCEPTION enumerating container references in schema '" << this->schema.GetName() << "': " << e.what() << endl;
	}

	return strm.str();
}

string CDocSchemaDetails::JoinFormReferences()
{
	stringstream strm;
	strm.str("");
	try
	{
		const ARNameType& schemaName = this->schema.GetARName();
		unsigned int schemaCount = this->pInside->schemaList.GetCount();
		for (unsigned int schemaIndex = 0; schemaIndex < schemaCount; ++schemaIndex)
		{
			CARSchema schema(schemaIndex);

			if (pInside->appConfig.bOverlaySupport && !IsVisibleObject(schema))
				continue;

			const ARCompoundSchema& compSchema = schema.GetCompound();

			if(compSchema.schemaType == AR_SCHEMA_JOIN)
			{
				if(strcmp(schemaName, compSchema.u.join.memberA) == 0)
				{
					strm << "Primary Form in: " << URLLink(schema, rootLevel) << "<br/>" << endl;
				}

				if(strcmp(schemaName, compSchema.u.join.memberB)==0)					
				{
					strm << "Secondary Form in: " << URLLink(schema, rootLevel) << "<br/>" << endl;
				}
			}
		}

		if(strm.str().size() == 0)
			strm << EmptyValue;
	}
	catch(exception& e)
	{
		cout << "EXCEPTION enumerating join form references of '" << this->schema.GetName() << "': " << e.what() << endl;
	}

	return strm.str();
}


string CDocSchemaDetails::TableFieldReferences()
{
	stringstream strm;
	strm.str("");
	try
	{
		// TODO: there is a function that checks for field references between table-field and column-field
		// before the documentation starts. Move this function over to this scanning routing and store
		// "table field to form" references in a list within the CARSchemaList
		// ===> move scaning over to CARInside::CustomFieldReferences
		bool bFound = false;

		unsigned int schemaCount = pInside->schemaList.GetCount();
		for (unsigned int schemaIndex = 0; schemaIndex < schemaCount; ++schemaIndex)
		{			
			CARSchema searchSchema(schemaIndex);
			
			if (pInside->appConfig.bOverlaySupport && !IsVisibleObject(searchSchema))
				continue;

			unsigned int fieldCount = searchSchema.GetFields()->GetCount();
			for (unsigned int fieldIndex = 0; fieldIndex < fieldCount; ++fieldIndex)
			{
				CARField field(schemaIndex, 0, fieldIndex);
				
				if(field.GetDataType() == AR_DATA_TYPE_TABLE && field.GetLimits().dataType == AR_DATA_TYPE_TABLE)
				{
					const ARTableLimitsStruct &limit = field.GetLimits().u.tableLimits;					
					const char *tableSchema = limit.schema;

					if (limit.schema[0] == '$')
						tableSchema = limit.sampleSchema;

					if(schema.GetName().compare(tableSchema) == 0)
					{
						strm << "Table: " << URLLink(field, rootLevel);
						strm << " in form: " << URLLink(searchSchema, rootLevel) << "<br/>" << endl;

						bFound = true;
					}
				}
			}
		}

		if(!bFound)
			strm << EmptyValue;
	}
	catch(exception& e)
	{
		cout << "EXCEPTION enumerating table references in schema '" << this->schema.GetName() << "': " << e.what() << endl;
	}

	return strm.str();
}

string CDocSchemaDetails::SearchMenuReferences()
{
	stringstream strm;
	strm.str("");
	try
	{
		CMenuTable *menuTable = new CMenuTable(*this->pInside);

		const CARSchema::ReferenceList &refList = schema.GetReferences();
		CARSchema::ReferenceList::const_iterator curIt = refList.begin();
		CARSchema::ReferenceList::const_iterator endIt = refList.end();

		for (; curIt != endIt; ++curIt)
		{
			if (curIt->GetMessageId() == REFM_CHARMENU_FORM && curIt->GetObjectType() == AR_STRUCT_ITEM_XML_CHAR_MENU)
			{
				CARHandle<CARCharMenu> hMenu(*curIt);
				menuTable->AddRow(*hMenu, rootLevel);
			}
		}

		if(menuTable->NumRows() > 0)
			strm << *menuTable;
		else
			strm << EmptyValue;

		delete menuTable;
	}
	catch(exception& e)
	{
		cout << "EXCEPTION enumerating search menu references in schema '" << this->schema.GetName() << "': " << e.what() << endl;
	}

	return strm.str();
}

string CDocSchemaDetails::AlWindowOpenReferences()
{
	stringstream strm;
	strm.str("");
	try
	{
		CAlTable *alTable = new CAlTable(*this->pInside);

		const CARSchema::ReferenceList &references = schema.GetReferences();
		CARSchema::ReferenceList::const_iterator curIt = references.begin();
		CARSchema::ReferenceList::const_iterator endIt = references.end();

		for (; curIt != endIt; ++curIt)
		{
			if (curIt->GetMessageId() != REFM_OPENWINDOW_FORM && curIt->GetObjectType() != AR_STRUCT_ITEM_XML_ACTIVE_LINK)
				continue;

			CARActiveLink al(curIt->GetObjectId());

			if (!al.Exists())
				continue;

			if (pInside->appConfig.bOverlaySupport && !IsVisibleObject(al))
				continue;

			alTable->AddRow(curIt->GetObjectId(), rootLevel);
		}

		if(alTable->NumRows() > 0)
			strm << *alTable;
		else
			strm << EmptyValue;

		delete alTable;
	}
	catch(exception& e)
	{
		cout << "EXCEPTION enumerating window open references in schema '" << this->schema.GetName() << "': " << e.what() << endl;
	}

	return strm.str();
}

string CDocSchemaDetails::ShowProperties()
{
	stringstream strm;
	strm.str("");
	int schemaType = this->schema.GetCompound().schemaType;
	
	try
	{
		const ARPropList& propList = this->schema.GetPropList();
		CARProplistHelper propIdx(&propList);

		strm << "<div id='schemaProperties'>";

		// doc basic properties
		ShowBasicProperties(strm, &propIdx);
		ShowEntryPointProperties(strm, &propIdx);

		if (schemaType != AR_SCHEMA_DIALOG)
		{
			ShowResultListProperties(strm, &propIdx);
			ShowSortListProperties(strm, &propIdx);
			ShowArchiveProperties(strm);

			if (pInside->CompareServerVersion(7,0) >= 0) 
			{
				ShowAuditProperties(strm);
			}
			
			if (schemaType != AR_SCHEMA_VENDOR && schemaType != AR_SCHEMA_VIEW)
				ShowIndexProperties(strm, &propIdx);

			ShowFTSMTSProperties(strm, &propIdx);
		}

		ShowPermissionProperties(strm, &propIdx);

		propIdx.UnusedPropertiesToHTML(strm, rootLevel);

		ShowChangeHistory(strm, &propIdx);

		strm << "</div>";
	}
	catch(exception& e)
	{
		cerr << "EXCEPTION enumerating properties: " << e.what() << endl;
	}
	return strm.str();
}

void CDocSchemaDetails::ShowBasicProperties(std::ostream& strm, CARProplistHelper* propIndex)
{
	ARValueStruct* propVal;

	try
	{
		stringstream tmpStrm;
		CTable tbl("basicProps", "TblNoBorder");
		tbl.AddColumn(20, "Description");
		tbl.AddColumn(80, "Value");
		tbl.DisableHeader();

		// entry id block size
		ARLong32 nextIDBlockSize = -1;

		propVal = propIndex->GetAndUseValue(AR_OPROP_NEXT_ID_BLOCK_SIZE);
		if (propVal != NULL)
			if (propVal->dataType == AR_DATA_TYPE_INTEGER)
				nextIDBlockSize = propVal->u.intVal;

		tmpStrm.str("");
		tmpStrm << (nextIDBlockSize>0?"Enabled":"Disabled") << "<br/>";
		if (nextIDBlockSize>0)
			tmpStrm << "Size: " << nextIDBlockSize;

		CTableRow rowBS("");
		rowBS.AddCell("Next Request ID Block");
		rowBS.AddCell(tmpStrm.str());
		tbl.AddRow(rowBS);

#if AR_CURRENT_API_VERSION >= AR_API_VERSION_710
		// cache properties
		ARLong32 cacheDisplayProps = -1;

		propVal = propIndex->GetAndUseValue(AR_OPROP_CACHE_DISP_PROP);
		if (propVal != NULL) 
			if (propVal->dataType == AR_DATA_TYPE_INTEGER)
				cacheDisplayProps = propVal->u.intVal;

		tmpStrm.str("");
		tmpStrm << "Override Server Settings: " << (cacheDisplayProps>=0?"Enabled":"Disabled");
		if (cacheDisplayProps>=0)
		{
			tmpStrm << "<br/>";
			tmpStrm << CWebUtil::ChkBoxInput("disableVUICaching",(cacheDisplayProps & AR_CACHE_DPROP_VUI) > 0) << "Disable VUI Display Property Caching<br/>" ;
			tmpStrm << CWebUtil::ChkBoxInput("disableFieldCaching",(cacheDisplayProps & AR_CACHE_DPROP_FIELD) > 0) << "Disable Field Display Property Caching" ;
		}

		CTableRow rowOC("");
		rowOC.AddCell("Display Property Caching");
		rowOC.AddCell(tmpStrm.str());
		tbl.AddRow(rowOC);

		/////////////////////////////////////////////////////////////////////////////////////

		ARLong32 disableStatusHistory = 0;
		propVal = propIndex->GetAndUseValue(AR_OPROP_CORE_FIELDS_OPTION_MASK);
		if (propVal != NULL)
			if (propVal->dataType == AR_DATA_TYPE_INTEGER)
				disableStatusHistory = propVal->u.intVal;

		CTableRow disSH("");
		disSH.AddCell("Disable Status History");
		disSH.AddCell((disableStatusHistory & AR_CORE_FIELDS_OPTION_DISABLE_STATUS_HISTORY ? "Yes" : "No"));
		tbl.AddRow(disSH);

#if AR_CURRENT_API_VERSION >= AR_API_VERSION_763
		ARLong32 allowDelete = 0;
		propVal = propIndex->GetAndUseValue(AR_OPROP_FORM_ALLOW_DELETE);
		if (propVal != NULL)
			if (propVal->dataType == AR_DATA_TYPE_INTEGER)
				allowDelete = propVal->u.intVal;

		CTableRow row("");
		row.AddCell("Allow Delete");
		row.AddCell((allowDelete == 1 ? "Yes" : "No"));
		tbl.AddRow(row);

		/////////////////////////////////////////////////////////////////////////////////////

		ARLong32 allowDrillDownWebReports = 0;
		propVal = propIndex->GetAndUseValue(AR_OPROP_FORM_ALLOW_DELETE);
		if (propVal != NULL)
			if (propVal->dataType == AR_DATA_TYPE_INTEGER)
				allowDrillDownWebReports = propVal->u.intVal;

		row.ClearCells();
		row.AddCell("Allow Drill Down in Web Reports");
		row.AddCell((allowDrillDownWebReports == 1 ? "Yes" : "No"));
		tbl.AddRow(row);

		/////////////////////////////////////////////////////////////////////////////////////

		ARLong32 value = 0;
		propVal = propIndex->GetAndUseValue(AR_OPROP_LOCALIZE_FORM_VIEWS);
		if (propVal != NULL && propVal->dataType == AR_DATA_TYPE_INTEGER)
		{
			value = propVal->u.intVal;
		}
		else
			value = AR_LOCALIZE_FORM_VIEWS_ALL;	// default, if property isn't present

		const char* strState = "Disabled";
		if (value == AR_LOCALIZE_FORM_VIEWS_ALL) strState = "All";
		if (value == AR_LOCALIZE_FORM_VIEWS_ALIASES) strState = "Only for selection field aliases";

		row.ClearCells();
		row.AddCell(CAREnum::FieldPropertiesLabel(AR_OPROP_LOCALIZE_FORM_VIEWS));
		row.AddCell(strState);
		tbl.AddRow(row);

		/////////////////////////////////////////////////////////////////////////////////////

		value = 0;
		propVal = propIndex->GetAndUseValue(AR_OPROP_LOCALIZE_FORM_DATA);
		if (propVal != NULL && propVal->dataType == AR_DATA_TYPE_INTEGER)
		{
			value = propVal->u.intVal;
		}
		else
			value = AR_LOCALIZE_FORM_DATA_ALL; // default, if property isn't present

		row.ClearCells();
		row.AddCell(CAREnum::FieldPropertiesLabel(AR_OPROP_LOCALIZE_FORM_DATA));
		row.AddCell((value == 1 ? "Yes" : "No"));
		tbl.AddRow(row);

#if AR_CURRENT_API_VERSION >= AR_API_VERSION_800
		
		const char* strValue = "";
		propVal = propIndex->GetAndUseValue(AR_OPROP_FORM_TAG_NAME);
		if (propVal != NULL && propVal->dataType == AR_DATA_TYPE_CHAR)
		{
			strValue = propVal->u.charVal;
		}

		row.ClearCells();
		row.AddCell(CAREnum::FieldPropertiesLabel(AR_OPROP_FORM_TAG_NAME));
		row.AddCell(strValue);
		tbl.AddRow(row);

#endif //AR_CURRENT_API_VERSION >= AR_API_VERSION_800
#endif //AR_CURRENT_API_VERSION >= AR_API_VERSION_763
#endif //AR_CURRENT_API_VERSION >= AR_API_VERSION_710

		// now write the table
		strm << "<h2>" << ImageTag(ImageTag::Document, rootLevel) << "Basic" << "</h2>";
		strm << "<div>" << tbl << "</div>";
	}
	catch(exception& e)
	{
		cout << "EXCEPTION enumerating basic properties: " << e.what() << endl;
	}
}

void CDocSchemaDetails::ShowEntryPointProperties(std::ostream &strm, CARProplistHelper *propIndex)
{
	ARValueStruct* propVal;

	try
	{
		stringstream tmpStrm;
		CTable tbl("entryPoints", "TblNoBorder");
		tbl.AddColumn(20, "Description");
		tbl.AddColumn(80, "Value");
		tbl.DisableHeader();

		// entry points
		ARLong32 entryPointNewOrder = -1;
		ARLong32 entryPointSearchOrder = -1;

		propVal = propIndex->GetAndUseValue(AR_SMOPROP_ENTRYPOINT_DEFAULT_NEW_ORDER);
		if (propVal != NULL) 
			if (propVal->dataType == AR_DATA_TYPE_INTEGER)
				entryPointNewOrder = propVal->u.intVal;

		propVal = propIndex->GetAndUseValue(AR_SMOPROP_ENTRYPOINT_DEFAULT_SEARCH_ORDER);
		if (propVal != NULL) 
			if (propVal->dataType == AR_DATA_TYPE_INTEGER)
				entryPointSearchOrder = propVal->u.intVal;


		tmpStrm << CWebUtil::ChkBoxInput("" ,(entryPointNewOrder >= 0)) << "Enable Entry Point" << "<br/>";
		tmpStrm << "Application List Display Order: "; if (entryPointNewOrder >=0) tmpStrm << entryPointNewOrder; tmpStrm << "<br/>" << "<br/>";

		CTableRow row;
		row.AddCell("New Mode");
		row.AddCell(tmpStrm.str());
		tbl.AddRow(row);
		
		tmpStrm.str("");
		tmpStrm << CWebUtil::ChkBoxInput("", (entryPointSearchOrder >= 0)) << "Enable Entry Point" << "<br/>";
		tmpStrm << "Application List Display Order: "; if (entryPointSearchOrder >= 0) tmpStrm << entryPointSearchOrder; tmpStrm << endl;

		row.ClearCells();
		row.AddCell("Search Mode");
		row.AddCell(tmpStrm.str());
		tbl.AddRow(row);
		
		// now write the table
		strm << "<h2>" << ImageTag(ImageTag::Document, rootLevel) << "EntryPoints" << "</h2>";
		strm << "<div>" << tbl << "</div>";
	}
	catch(exception& e)
	{
		cout << "EXCEPTION enumerating basic properties: " << e.what() << endl;
	}
}

void CDocSchemaDetails::ShowAuditProperties(std::ostream& strm)
{
	try
	{
		const ARAuditInfoStruct& audit = this->schema.GetAuditInfo();
		CTable tbl("displayPropList", "TblObjectList");
		tbl.AddColumn(20, "Description");
		tbl.AddColumn(80, "Values");

		CTableRow row("");
		row.AddCell("Audit Style");
		row.AddCell(CAREnum::AuditStyle(audit.style));
		tbl.AddRow(row);

		row.ClearCells();
		row.AddCell("Audit Enabled");
		row.AddCell((audit.enable==0?"No":"Yes"));
		tbl.AddRow(row);

#if AR_CURRENT_API_VERSION > 13 // Version 7.5 and higher
		row.ClearCells();
		row.AddCell("Audit Only Changed Fields");
		row.AddCell(CAREnum::AuditChangedFields(audit.auditMask));
		tbl.AddRow(row);
#endif

		row.ClearCells();
		switch (audit.style)
		{
			case AR_AUDIT_NONE:
				{
					if (audit.formName[0] != 0)
					{
						row.AddCell("Audited From Form");
						row.AddCell(this->pInside->LinkToSchema(audit.formName,rootLevel));
						tbl.AddRow(row);
					}
				}
				break;
			case AR_AUDIT_COPY:
				{
					row.AddCell("Audit Form");
					row.AddCell(this->pInside->LinkToSchema(audit.formName,rootLevel));
					tbl.AddRow(row);
				}
				break;
			case AR_AUDIT_LOG:
				{
					row.AddCell("Audit Log Form");
					row.AddCell(this->pInside->LinkToSchema(audit.formName,rootLevel));
					tbl.AddRow(row);
				}
				break;
			case AR_AUDIT_LOG_SHADOW:
				{
					row.AddCell("Audited From Forms");
					row.AddCell(AuditTargetReferences());
					tbl.AddRow(row);
				}
				break;
		}

		// audit qualification
		stringstream qualStrm; qualStrm.str("");
		int pFormId = schema.GetInsideId();

		if (audit.query.operation != AR_COND_OP_NONE)
		{
			CRefItem refItem(this->schema, REFM_SCHEMA_AUDIT_QUALIFICATION);
			CARQualification arQual(*this->pInside, refItem, pFormId, rootLevel);
			arQual.CheckQuery(&audit.query, qualStrm);
		}
		else
		{
			qualStrm << EmptyRunIf << endl;
		}

		row.ClearCells();
		row.AddCell("Qualification");
		row.AddCell(qualStrm.str());
		tbl.AddRow(row);

		strm << "<h2>" << ImageTag(ImageTag::Document, rootLevel) << "Audit Settings" << "</h2>";
		strm << "<div>" << tbl << "</div>";
	}
	catch (...)
	{
		cerr << "EXCEPTION audit properties" << endl;
	}
}

void CDocSchemaDetails::ShowArchiveProperties(std::ostream& strm)
{
	try
	{
		const ARArchiveInfoStruct& archive = this->schema.GetArchiveInfo();
		bool archiveToForm = (archive.archiveType & AR_ARCHIVE_FORM)>0;
		bool deleteSource = (archive.archiveType & AR_ARCHIVE_DELETE)>0;
		bool archiveToFile = (archive.archiveType & (AR_ARCHIVE_FILE_ARX | AR_ARCHIVE_FILE_XML))>0;
		unsigned int fileFormat = (archive.archiveType & (AR_ARCHIVE_FILE_ARX | AR_ARCHIVE_FILE_XML)) << 2;
		bool noAttachments = (archive.archiveType & AR_ARCHIVE_NO_ATTACHMENTS)>0;
		bool noDiary = (archive.archiveType & AR_ARCHIVE_NO_DIARY)>0;

		CTable tbl("displayPropList", "TblObjectList");
		tbl.AddColumn(20, "Description");
		tbl.AddColumn(80, "Values");

		// archive type
		stringstream typeStrm; typeStrm.str("");
		if (!archiveToForm && !archiveToFile)
		{
			typeStrm << "None";
		}
		else if (archiveToForm || deleteSource)
		{
			if (archiveToForm) typeStrm << "Copy to Archive";
			if (deleteSource && archiveToForm) typeStrm << " and ";
			if (deleteSource) typeStrm << "Delete From Source";
		}

		CTableRow row("");
		row.AddCell("Archive Type");
		row.AddCell(typeStrm.str());
		tbl.AddRow(row);

		row.ClearCells();
		row.AddCell("Archive State");
		row.AddCell((archive.enable==0?"Disabled":"Enabled"));
		tbl.AddRow(row);

		row.ClearCells();
		if (archiveToFile)
		{
			// archive to file is not supported by admin/developer tool; but maybe some day...
			row.AddCell("Archive to File");
			row.AddCell(archive.u.dirPath);
			tbl.AddRow(row);
		}
		else if (archiveToForm)
		{
			stringstream tmpStrm; tmpStrm.str("");
			tmpStrm << this->pInside->LinkToSchema(archive.u.formName,rootLevel) << "<br/>" << endl;
			tmpStrm << CWebUtil::ChkBoxInput("noAttachments",noAttachments) << "No Attachments&nbsp;&nbsp;";
			tmpStrm << CWebUtil::ChkBoxInput("noDiary",noDiary) << "No Diary" << endl;

			row.AddCell("Archive to Form");
			row.AddCell(tmpStrm.str());
			tbl.AddRow(row);
		}

		if (archive.archiveFrom[0] != 0)
		{
			row.ClearCells();
			row.AddCell("Archive From Form");
			row.AddCell(this->pInside->LinkToSchema(archive.archiveFrom, rootLevel));
			tbl.AddRow(row);
		}

		stringstream qualStrm; qualStrm.str("");
		int pFormId = this->schema.GetInsideId(); //this->pInside->SchemaGetInsideId(this->schema.GetARName());

		if (archive.query.operation != AR_COND_OP_NONE)
		{
			CRefItem refItem(this->schema, REFM_SCHEMA_ARCHIVE_QUALIFICATION);
			CARQualification arQual(*this->pInside, refItem, pFormId, rootLevel);
			arQual.CheckQuery(&archive.query, qualStrm);
		}
		else
		{
			qualStrm << EmptyRunIf << endl;
		}

		row.ClearCells();
		row.AddCell("Times");
		row.AddCell(CARDayStructHelper::DayStructToHTMLString(archive.archiveTime));
		tbl.AddRow(row);

		row.ClearCells();
		row.AddCell("Qualification");
		row.AddCell(qualStrm.str());
		tbl.AddRow(row);

		strm << "<h2>" << ImageTag(ImageTag::Document, rootLevel) << "Archive Settings" << "</h2>";
		strm << "<div>" << tbl << "</div>";
	}
	catch (...)
	{
		cerr << "EXCEPTION archive properties" << endl;
	}
}

void CDocSchemaDetails::WorkflowReferences(std::ostream &strm)
{
	try
	{
		CTable tabSet("setFieldReferences", "TblObjectList");
		tabSet.AddColumn(50, "Object Name");
		tabSet.AddColumn(10, "Enabled");
		tabSet.AddColumn(20, "Execute On");
		tabSet.AddColumn(20, "Description");

		CTable tabPush("pushReferences", "TblObjectList");
		tabPush.AddColumn(50, "Object Name");
		tabPush.AddColumn(10, "Enabled");
		tabPush.AddColumn(20, "Execute On");
		tabPush.AddColumn(20, "Description");

		CTable delAction("deleteReferences", "TblObjectList");
		delAction.AddColumn(50, "Object Name");
		delAction.AddColumn(10, "Enabled");
		delAction.AddColumn(20, "Execute On");
		delAction.AddColumn(20, "Description");

		CTable tabService("serviceReferences", "TblObjectList");
		tabService.AddColumn(50, "Object Name");
		tabService.AddColumn(10, "Enabled");
		tabService.AddColumn(20, "Execute On");
		tabService.AddColumn(20, "Description");


		const CARSchema::ReferenceList &refList = schema.GetReferences();
		CARSchema::ReferenceList::const_iterator curIt = refList.begin();
		CARSchema::ReferenceList::const_iterator endIt = refList.end();

		for (; curIt != endIt; ++curIt)
		{
			int messageId = curIt->GetMessageId();
			if (messageId == REFM_SETFIELDS_FORM)
			{
				bool hasEnabledFlag;
				string tmpEnabled = "";
				string tmpCssEnabled = "";

				unsigned int enabled = curIt->GetObjectEnabled(hasEnabledFlag);

				if (hasEnabledFlag)
				{
					tmpEnabled = CAREnum::ObjectEnable(enabled);
					if (!enabled) { tmpCssEnabled = "objStatusDisabled"; }
				}

				CTableRow row;
				row.AddCell(WorkflowReferenceTable::LinkToObjByRefItem(*curIt, rootLevel));
				row.AddCell(CTableCell(tmpEnabled, tmpCssEnabled)); // Enabled?
				row.AddCell(curIt->GetObjectExecuteOn()); // Exceute On
				row.AddCell(curIt->GetDescription(rootLevel));
				tabSet.AddRow(row);
			}
			if (messageId == REFM_SERVICE_CALL)
			{
				bool hasEnabledFlag;
				string tmpEnabled = "";
				string tmpCssEnabled = "";

				unsigned int enabled = curIt->GetObjectEnabled(hasEnabledFlag);

				if (hasEnabledFlag)
				{
					tmpEnabled = CAREnum::ObjectEnable(enabled);
					if (!enabled) { tmpCssEnabled = "objStatusDisabled"; }
				}

				CTableRow row;
				row.AddCell(WorkflowReferenceTable::LinkToObjByRefItem(*curIt, rootLevel));
				row.AddCell(CTableCell(tmpEnabled, tmpCssEnabled)); // Enabled?
				row.AddCell(curIt->GetObjectExecuteOn()); // Exceute On
				row.AddCell(curIt->GetDescription(rootLevel));
				tabService.AddRow(row);
			}
			if (messageId == REFM_PUSHFIELD_TARGET)
			{
				bool hasEnabledFlag;
				string tmpEnabled = "";
				string tmpCssEnabled = "";

				unsigned int enabled = curIt->GetObjectEnabled(hasEnabledFlag);

				if (hasEnabledFlag)
				{
					tmpEnabled = CAREnum::ObjectEnable(enabled);
					if (!enabled) { tmpCssEnabled = "objStatusDisabled"; }
				}

				CTableRow row;
				row.AddCell(WorkflowReferenceTable::LinkToObjByRefItem(*curIt, rootLevel));
				row.AddCell(CTableCell(tmpEnabled, tmpCssEnabled)); // Enabled?
				row.AddCell(curIt->GetObjectExecuteOn()); // Exceute On
				row.AddCell(curIt->GetDescription(rootLevel));
				tabPush.AddRow(row);
			}
			if (messageId == REFM_DELETE_ENTRY_ACTION)
			{
				bool hasEnabledFlag;
				string tmpEnabled = "";
				string tmpCssEnabled = "";

				unsigned int enabled = curIt->GetObjectEnabled(hasEnabledFlag);

				if (hasEnabledFlag)
				{
					tmpEnabled = CAREnum::ObjectEnable(enabled);
					if (!enabled) { tmpCssEnabled = "objStatusDisabled"; }
				}

				CTableRow row;
				row.AddCell(WorkflowReferenceTable::LinkToObjByRefItem(*curIt, rootLevel));
				row.AddCell(CTableCell(tmpEnabled, tmpCssEnabled)); // Enabled?
				row.AddCell(curIt->GetObjectExecuteOn()); // Exceute On
				row.AddCell(curIt->GetDescription(rootLevel));
				delAction.AddRow(row);
			}
		}

		strm << ImageTag(ImageTag::Document, rootLevel) << "Workflow reading data from this form" << endl;
		tabSet.ToXHtml(strm);

		strm << ImageTag(ImageTag::Document, rootLevel) << "Workflow writing data to this form" << endl;
		tabPush.ToXHtml(strm);

		strm << ImageTag(ImageTag::Document, rootLevel) << "Workflow deleting data on this form" << endl;
		delAction.ToXHtml(strm);

		strm << ImageTag(ImageTag::Document, rootLevel) << "Workflow executing services on this form" << endl;
		tabService.ToXHtml(strm);
	}
	catch(exception& e)
	{
		cout << "EXCEPTION enumerating filter push fields references in schema '" << this->schema.GetName() << "': " << e.what() << endl;
	}
}

string CDocSchemaDetails::GenerateReferencesTable(const ARCompoundSchema &compSchema)
{
	stringstream strmTmp;
	WorkflowReferences(strmTmp);

	//Schema Properties
	CTable tblObjProp("objProperties", "TblObjectList");
	tblObjProp.AddColumn(0, "Property");
	tblObjProp.AddColumn(0, "Value");

	//Schema type informations
	CTableRow row("cssStdRow");	
	CTableCell cellProp("");				
	CTableCell cellPropValue("");    

	//Container References
	row.ClearCells();
	cellProp.content = "Container References";
	cellPropValue.content = this->ContainerReferences();
	row.AddCell(cellProp);
	row.AddCell(cellPropValue);
	tblObjProp.AddRow(row);			

	//TableField References
	row.ClearCells();
	cellProp.content = "Table Fields datasource form";
	cellPropValue.content = this->TableFieldReferences();
	row.AddCell(cellProp);
	row.AddCell(cellPropValue);
	tblObjProp.AddRow(row);	

	//AL window open references
	row.ClearCells();
	cellProp.content = "Active Link \"Open Window Action\"";
	cellPropValue.content = this->AlWindowOpenReferences();
	row.AddCell(cellProp);
	row.AddCell(cellPropValue);
	tblObjProp.AddRow(row);

	//Join References
	row.ClearCells();
	cellProp.content = "Join Form References";
	cellPropValue.content = this->JoinFormReferences();
	row.AddCell(cellProp);
	row.AddCell(cellPropValue);
	tblObjProp.AddRow(row);

	//Menu References
	row.ClearCells();
	cellProp.content = "Search Menu References";
	cellPropValue.content = this->SearchMenuReferences();
	row.AddCell(cellProp);
	row.AddCell(cellPropValue);
	tblObjProp.AddRow(row);

	strmTmp << tblObjProp;
	return strmTmp.str();
}

bool CDocSchemaDetails::IsJoinViewOrVendorForm()
{
	switch(this->schema.GetCompound().schemaType)
	{
	case AR_SCHEMA_JOIN:
	case AR_SCHEMA_VIEW:
	case AR_SCHEMA_VENDOR:
		return true;
	default:	
		return false;
	}
}

string CDocSchemaDetails::ShowGeneralInfo()
{
	const ARCompoundSchema &compSchema = this->schema.GetCompound();
	stringstream strm;

	CTable tbl("general", "TblNoBorder");
	tbl.AddColumn(20, "");
	tbl.AddColumn(80, "");
	tbl.DisableHeader();

	CTableRow row;
	row.AddCell("Name");
	row.AddCell(this->schema.GetName());
	tbl.AddRow(row);	
	row.ClearCells();

	// generate the schema type row (and with additional details for special form types like join, view and vendor)
	row.AddCell("Type");
	row.AddCell(GetSchemaType());
	tbl.AddRow(row);
	row.ClearCells();
	strm.str("");

	// search for the default vui
	CARVui defaultVUI(this->schema.GetInsideId(), this->schema.GetDefaultVUI());

	row.AddCell("Default View");
	row.AddCell(CheckedURLLink(defaultVUI, schema.GetDefaultVUI(), rootLevel));
	tbl.AddRow(row);
	row.ClearCells();

	strm << tbl.ToXHtml();
	tbl.ClearRows();

	if (pInside->CompareServerVersion(7,1) >= 0)
	{
		stringstream numberConverter;
		if (schema.GetDbTableId() > 0)
			numberConverter << schema.GetDbTableId();

		row.AddCell("DB Table ID");
		row.AddCell(numberConverter.str());
		tbl.AddRow(row);
		row.ClearCells();

		if (compSchema.schemaType != AR_SCHEMA_DIALOG && compSchema.schemaType != AR_SCHEMA_VENDOR)
		{
			row.AddCell("DB Table View");
			row.AddCell(schema.GetDbViewName());
			tbl.AddRow(row);
			row.ClearCells();

			row.AddCell("DB Table SH Views");
			row.AddCell(schema.GetDbShViewName());
			tbl.AddRow(row);
			row.ClearCells();
		}

		strm << tbl.ToXHtml();
	}

	strm << "<hr/>" << endl;

	strm << ShowProperties();

	strm << "<hr/>" << endl;

	return strm.str();
}

void CDocSchemaDetails::ShowFTSMTSProperties(std::ostream& strm, CARProplistHelper *propIndex)
{
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_763
	if (pInside->CompareServerVersion(7,6,3) < 0)
		return;

	ARValueStruct* propVal;
	int iValue;

	try
	{
		stringstream tmpStrm;
		CTable tbl("ftsProps", "TblNoBorder");
		tbl.AddColumn(20, "Description");
		tbl.AddColumn(80, "Value");
		tbl.DisableHeader();

		///////////////////////////////////////////////////////////////////////////////////////

		CTableRow	row("");
		iValue = 0;
		propVal = propIndex->GetAndUseValue(AR_OPROP_MFS_OPTION_MASK);
		if (propVal != NULL && propVal->dataType == AR_DATA_TYPE_INTEGER)
			iValue = propVal->u.intVal;
		
		row.AddCell("Exclude from multi-form search");
		row.AddCell((iValue & AR_MULTI_FORM_SEARCH_OPTION_EXCLUDE ? "Yes" : "No"));		
		tbl.AddRow(row);

		///////////////////////////////////////////////////////////////////////////////////////

		row.ClearCells();
		char* strValue = NULL;
		vector<int> weightedRelevancyFields; weightedRelevancyFields.resize(4);

		propVal = propIndex->GetAndUseValue(AR_OPROP_MFS_WEIGHTED_RELEVANCY_FIELDS);
		if (propVal != NULL && propVal->dataType == AR_DATA_TYPE_CHAR)
			strValue = propVal->u.charVal;


		if (strValue != NULL && strValue[0] != 0)
		{
			int numFields = atoi(strValue);
			char* newPos = strchr(strValue, ';');
			if (newPos)
			{
				strValue = newPos + 1;
				for (int fieldPos = 0; fieldPos < numFields; fieldPos++)
				{
					int fieldTag = atoi(strValue);
					
					newPos = strchr(strValue, ';');
					if (newPos)
					{
						strValue = newPos + 1;
						int fieldId = atoi(strValue);
						
						if (fieldTag > 0 && fieldTag <= AR_MFS_WEIGHTED_RELEVANCY_KEYWORDS_FIELD_TAG)
						{
							weightedRelevancyFields[fieldTag-1] = fieldId;
						}
					}
				}
			}
		}

		CTable weightedRelFields("WRFields", "TblNoBorder");
		weightedRelFields.AddColumn(0, "");
		weightedRelFields.AddColumn(80, "");
		weightedRelFields.DisableHeader();

		for (unsigned int wrfPos = 0; wrfPos < AR_MFS_WEIGHTED_RELEVANCY_KEYWORDS_FIELD_TAG; wrfPos++)
		{
			int fieldId = weightedRelevancyFields[wrfPos];

			CTableRow wrfRow("");
			wrfRow.AddCell(CAREnum::WeightedRelevancyFieldType(wrfPos+1));
			wrfRow.AddCell((fieldId > 0 ? pInside->LinkToField(this->schema.GetInsideId(), fieldId, rootLevel) : ""));
			weightedRelFields.AddRow(wrfRow);

			if (fieldId > 0 && (!pInside->appConfig.bOverlaySupport || IsVisibleObject(schema)))
			{
				CRefItem ref(schema, REFM_SCHEMA_FTS_WEIGHTED_RELEVANCY_FIELD);
				pInside->AddFieldReference(schema.GetInsideId(), fieldId, ref);
			}
		}

		row.AddCell("Weighted relevancy fields");
		row.AddCell(weightedRelFields.ToXHtml());
		tbl.AddRow(row);

		///////////////////////////////////////////////////////////////////////////////////////

		row.ClearCells();
		ARDayStruct timeValue;
		unsigned int intervalValue = 0;

		ARZeroMemory(&timeValue);

		propVal = propIndex->GetAndUseValue(AR_OPROP_FT_SCAN_TIME_MONTH_MASK);
		if (propVal != NULL && propVal->dataType == AR_DATA_TYPE_INTEGER)
			timeValue.monthday = propVal->u.intVal;

		propVal = propIndex->GetAndUseValue(AR_OPROP_FT_SCAN_TIME_WEEKDAY_MASK);
		if (propVal != NULL && propVal->dataType == AR_DATA_TYPE_INTEGER)
			timeValue.weekday = propVal->u.intVal;

		propVal = propIndex->GetAndUseValue(AR_OPROP_FT_SCAN_TIME_HOUR_MASK);
		if (propVal != NULL && propVal->dataType == AR_DATA_TYPE_INTEGER)
			timeValue.hourmask = propVal->u.intVal;
		
		propVal = propIndex->GetAndUseValue(AR_OPROP_FT_SCAN_TIME_MINUTE);
		if (propVal != NULL && propVal->dataType == AR_DATA_TYPE_INTEGER)
			timeValue.minute = propVal->u.intVal;

		propVal = propIndex->GetAndUseValue(AR_OPROP_FT_SCAN_TIME_INTERVAL);
		if (propVal != NULL && (propVal->dataType == AR_DATA_TYPE_INTEGER || propVal->dataType == AR_DATA_TYPE_ULONG))
			intervalValue = propVal->u.ulongVal;
		
		row.AddCell("FT-indexed field updates");
		if (timeValue.monthday != 0 || timeValue.weekday != 0 || timeValue.hourmask != 0 || timeValue.minute != 0)
		{
			row.AddCell(CARDayStructHelper::DayStructToHTMLString(timeValue));
		}
		else if (intervalValue != 0)
		{
			unsigned int days, hours, minutes, seconds;
			CARDayStructHelper::SplitInterval(intervalValue, days, hours, minutes, seconds);

			tmpStrm.str("");
			tmpStrm << days << " Days " << hours << " Hours " << minutes << " Minutes";
			row.AddCell(tmpStrm.str());
		}
		else
		{
			row.AddCell("No Time specified");
		}
		tbl.AddRow(row);

		///////////////////////////////////////////////////////////////////////////////////////

		strm << "<h2>" << ImageTag(ImageTag::Document, rootLevel) << "Full Text Search" << "</h2>";
		strm << "<div>" << tbl << "</div>";
	}
	catch (exception &e)
	{
		cerr << "EXCEPTION in ShowFTSMTSProperties: " << e.what() << endl;
	}
#endif
}

void CDocSchemaDetails::ShowChangeHistory(std::ostream &strm, CARProplistHelper *propIndex)
{
	strm << "<h2>" << ImageTag(ImageTag::Document, rootLevel) << "Change History &amp; Helptext" << "</h2>"
	     << "<div>" << this->pInside->ServerObjectHistory(&this->schema, rootLevel, true) << "</div>" << endl;
}

string CDocSchemaDetails::GetSchemaType()
{
	const ARCompoundSchema &compSchema = schema.GetCompound();
	unsigned int schemaType = schema.GetInternalSchemaType();
	stringstream strm;

	if (schemaType == AR_SCHEMA_JOIN)
	{
		strm << CAREnum::JoinType(compSchema.u.join.option) << "-";
	}
	strm << CAREnum::SchemaType(schemaType);

	if(schemaType == AR_SCHEMA_JOIN
		|| schemaType == AR_SCHEMA_VIEW
		|| schemaType == AR_SCHEMA_VENDOR)
	{
		strm << " " << this->TypeDetails();
	}

	return strm.str();
}

string CDocSchemaDetails::AuditTargetReferences()
{
	vector<int> schemas;

	const CARSchema::ReferenceList &references = schema.GetReferences();
	CARSchema::ReferenceList::const_iterator curIt = references.begin();
	CARSchema::ReferenceList::const_iterator endIt = references.end();

	for (; curIt != endIt; ++curIt)
	{
		if (curIt->GetMessageId() == REFM_SCHEMA_AUDIT_SOURCE && curIt->GetObjectType() == AR_STRUCT_ITEM_XML_SCHEMA)
			schemas.push_back(curIt->GetObjectId());
	}

	if (schemas.size() > 0)
	{
		stringstream strm;
		
		size_t count = schemas.size();

		for (size_t index = 0; index < count; ++index)
		{
			if (index > 0) { strm << "<br/>"; }
			strm << pInside->LinkToSchema(schemas[index], rootLevel);
		}
		return strm.str();
	}
	return "";
}
