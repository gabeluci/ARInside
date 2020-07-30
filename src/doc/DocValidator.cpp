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
#include "DocValidator.h"
#include "../output/ObjNotFound.h"
#include "../output/URLLink.h"
#include "../output/WorkflowReferenceTable.h"

// helper functions ///////////////////////////////////////////////////////////
bool InList(vector<int>& list, int fieldId)
{
	try
	{
		vector<int>::iterator curIt = list.begin();
		vector<int>::iterator endIt = list.end();
		for (; curIt != endIt; ++curIt)
		{
			if (*curIt == fieldId) return true;
		}
	}
	catch(exception& e)
	{
		cout << "EXCEPTION Validation_InList: " << e.what() << endl;
	}

	return false;
}


void BuildUniqueFieldList(vector<int>& list, const CARSchemaList::MissingReferenceList* references)
{
	try
	{
		list.clear();

		CARSchemaList::MissingReferenceList::const_iterator curIt = references->begin();
		CARSchemaList::MissingReferenceList::const_iterator endIt = references->end();

		for(; curIt != endIt; ++curIt)
		{
			if(!InList(list, curIt->first))
			{
				list.push_back(curIt->first);
			}
		}
		std::sort(list.begin(), list.end());
	}
	catch(exception& e)
	{
		cout << "EXCEPTION Validation_BuildUniqueFieldList: " << e.what() << endl;
	}
}

// DocValidator implementation ////////////////////////////////////////////////
CDocValidator::CDocValidator()
{
}

CDocValidator::~CDocValidator(void)
{
}


void CDocValidator::Main()
{
	CPageParams file(PAGE_VALIDATOR_MAIN);

	try
	{
		int rootLevel = file->GetRootLevel();
		string path = file->GetPath();

		FileSystemUtil fsUtil(this->pInside->appConfig);
		if(fsUtil.CreateSubDirectory(path)>=0)
		{
			CWebPage webPage(file->GetFileName(), "Validator", rootLevel, this->pInside->appConfig);

			//ContentHead informations
			stringstream contHeadStrm;
			contHeadStrm << "Server object validation:" << endl;
			webPage.AddContentHead(contHeadStrm.str());

			//Field reference check
			webPage.AddContent("Missing Objects referenced by Workflow:<br/>");
			cout << "Field reference validation" << endl;
			webPage.AddContent(URLLink("Fields", PAGE_VALIDATOR_MISSING_FIELDS, ImageTag::Document, rootLevel));
			this->FieldReferenceValidator();
			webPage.AddContent("<br/>");

			//Menu reference check
			cout << "Menu reference validation" << endl;
			webPage.AddContent(URLLink("Menus", PAGE_VALIDATOR_MISSING_MENUS, ImageTag::Document, rootLevel));
			this->MenuReferenceValidator();

			//Group permission check
			webPage.AddContent("<br/><br/>List of server objects with no specified access groups:<br/>");

			cout << "Form access group validation" << endl;
			webPage.AddContent(URLLink("Forms", PAGE_VALIDATOR_FORM_GROUPS, ImageTag::Document, rootLevel));
			this->FormGroupValidator();

			cout << "Field access group validation" << endl;
			webPage.AddContent("<br/>");
			webPage.AddContent(URLLink("Fields", PAGE_VALIDATOR_FIELD_GROUPS, ImageTag::Document, rootLevel));
			this->FieldGroupValidator();

			cout << "Active Link access group validation" << endl;
			webPage.AddContent("<br/>");
			webPage.AddContent(URLLink("Active Links", PAGE_VALIDATOR_ACTIVELINKS_GROUPS, ImageTag::Document, rootLevel));
			this->AlGroupValidator();

			cout << "Container access group validation" << endl;
			webPage.AddContent("<br/>");
			webPage.AddContent(URLLink("Container", PAGE_VALIDATOR_CONTAINER_GROUPS, ImageTag::Document, rootLevel));
			this->ContainerGroupValidator();

			webPage.SaveInFolder(path);
		}
	}
	catch(exception& e)
	{
		cout << "EXCEPTION Group_Validation: " << e.what() << endl;
	}
}

void CDocValidator::ContainerGroupValidator()
{
	CPageParams file(PAGE_VALIDATOR_CONTAINER_GROUPS);

	try
	{		
		int rootLevel = file->GetRootLevel();
		string path = file->GetPath();

		FileSystemUtil fsUtil(this->pInside->appConfig);
		if(fsUtil.CreateSubDirectory(path)>=0)
		{
			CWebPage webPage(file->GetFileName(), "Container access group validation", rootLevel, this->pInside->appConfig);

			//ContentHead informations
			stringstream contHeadStrm;
			contHeadStrm << URLLink("Validation", PAGE_VALIDATOR_MAIN, rootLevel) << MenuSeparator;
			contHeadStrm << "Container with no or unknown group permission:" << endl;
			webPage.AddContentHead(contHeadStrm.str());

			//Check forms	
			CTable tblObj("ContainerNoPermission", "TblObjectList");
			tblObj.AddColumn(10, "Type");
			tblObj.AddColumn(90, "Container");

			unsigned int cntCount = this->pInside->containerList.GetCount();
			for ( unsigned int cntIndex = 0; cntIndex < cntCount; ++cntIndex )
			{			
				CARContainer cont(cntIndex);

				// skip this object in case it's overlaid (hidden)
				if (pInside->appConfig.bOverlaySupport && !IsVisibleObject(cont))
					continue;

				unsigned int type = cont.GetType();
				if(type == ARCON_WEBSERVICE || type == ARCON_GUIDE || type == ARCON_APP)
				{
					if(cont.GetPermissions().numItems == 0)		//Check if the container has no access group
					{
						//Container has no access group
						CTableRow row("");	
						row.AddCell(CAREnum::ContainerType(type));
						row.AddCell(pInside->LinkToContainer(cont.GetName(), rootLevel));
						tblObj.AddRow(row);
					}
				}
			}

			webPage.AddContent(tblObj.ToXHtml());

			webPage.SaveInFolder(path);
		}
	}
	catch(exception& e)
	{
		cout << "EXCEPTION Container_Group_Validation: " << e.what() << endl;
	}
}

void CDocValidator::AlGroupValidator()
{
	CPageParams file(PAGE_VALIDATOR_ACTIVELINKS_GROUPS);

	try
	{
		int rootLevel = file->GetRootLevel();
		string path = file->GetPath();

		FileSystemUtil fsUtil(this->pInside->appConfig);
		if(fsUtil.CreateSubDirectory(path)>=0)
		{
			CWebPage webPage(file->GetFileName(), "Active Link access group validation", rootLevel, this->pInside->appConfig);

			//ContentHead informations
			stringstream contHeadStrm;
			contHeadStrm << URLLink("Validation", PAGE_VALIDATOR_MAIN, rootLevel) << MenuSeparator;
			contHeadStrm << "Active Links with no or unknown group permission:" << endl;
			webPage.AddContentHead(contHeadStrm.str());

			//Check forms	
			CTable tblObj("AlNoPermission", "TblObjectList");
			tblObj.AddColumn(100, "Active Link");

			unsigned int alCount = pInside->alList.GetCount();
			for (unsigned int alIndex = 0; alIndex < alCount; ++alIndex)
			{			
				CARActiveLink al(alIndex);

				// skip this object in case it's overlaid (hidden)
				if (pInside->appConfig.bOverlaySupport && !IsVisibleObject(al))
					continue;

				if(al.GetGroupList().numItems == 0)		//Check if the al has no access group
				{
					//Form has no access group
					CTableRow row("");		
					row.AddCell(pInside->LinkToAl(alIndex, rootLevel));
					tblObj.AddRow(row);
				}
			}

			webPage.AddContent(tblObj.ToXHtml());

			webPage.SaveInFolder(path);
		}
	}
	catch(exception& e)
	{
		cout << "EXCEPTION ActiveLink_Group_Validation: " << e.what() << endl;
	}
}

void CDocValidator::FieldGroupValidatorDetails(CARSchema &schema)
{
	CPageParams file(PAGE_VALIDATOR_FIELD_GROUP_DETAILS, &schema);

	try
	{
		int rootLevel = file->GetRootLevel();
		string path = file->GetPath();

		FileSystemUtil fsUtil(this->pInside->appConfig);
		if(fsUtil.CreateSubDirectory(path)>=0)
		{
			CWebPage webPage(file->GetFileName(), "Field access group validation", rootLevel, this->pInside->appConfig);

			//ContentHead informations
			stringstream contHeadStrm;
			contHeadStrm << URLLink("Validation", PAGE_VALIDATOR_MAIN, rootLevel) << MenuSeparator;
			contHeadStrm << "Fields with no or unknown group permission:" << endl;
			webPage.AddContentHead(contHeadStrm.str());

			CTable tblObj("FieldsNoPermission", "TblObjectList");
			tblObj.AddColumn(100, "Field Name");

			unsigned int fieldCount = schema.GetFields()->GetCount();
			for( unsigned int fieldIndex = 0; fieldIndex < fieldCount; ++fieldIndex)
			{
				CARField field(schema.GetInsideId(), 0, fieldIndex);

				if(field.GetPermissions().numItems == 0)      //First check if the field has any access group
				{
					//field has no access group
					CTableRow row("");		
					row.AddCell(pInside->LinkToField(schema.GetInsideId(), field.GetInsideId(), rootLevel));
					tblObj.AddRow(row);					
				}
			}

			tblObj.description = pInside->LinkToSchema(schema.GetInsideId(), rootLevel);
			webPage.AddContent(tblObj.ToXHtml());

			webPage.SaveInFolder(path);
		}
	}
	catch(exception& e)
	{
		cout << "EXCEPTION Field_Group_Validation_Details: " << e.what() << endl;
	}
}

void CDocValidator::FieldGroupValidator()
{
	CPageParams file(PAGE_VALIDATOR_FIELD_GROUPS);

	try
	{
		int rootLevel = file->GetRootLevel();
		string path = file->GetPath();

		FileSystemUtil fsUtil(this->pInside->appConfig);
		if(fsUtil.CreateSubDirectory(path)>=0)
		{
			CWebPage webPage(file->GetFileName(), "Field access group validation", rootLevel, this->pInside->appConfig);

			//ContentHead informations
			stringstream contHeadStrm;
			contHeadStrm << URLLink("Validation", PAGE_VALIDATOR_MAIN, rootLevel) << MenuSeparator;
			contHeadStrm << "Fields with no or unknown group permission:" << endl;
			webPage.AddContentHead(contHeadStrm.str());

			//Check fields
			CTable tblObj("FieldsNoPermission", "TblObjectList");
			tblObj.AddColumn(10, "Num. Fields");
			tblObj.AddColumn(90, "Form Name");

			// TODO: maybe move the following code to FieldGroupValidatorDetails, because the code is already there, but not the counting!
			unsigned int schemaCount = this->pInside->schemaList.GetCount();
			for ( unsigned int schemaIndex = 0; schemaIndex < schemaCount; ++schemaIndex )
			{			
				CARSchema schema(schemaIndex);

				// skip this object in case it's overlaid (hidden)
				if (pInside->appConfig.bOverlaySupport && !IsVisibleObject(schema))
					continue;

				int nEmptyFields = 0;
				unsigned int fieldCount = schema.GetFields()->GetCount();
				for (unsigned int fieldIndex = 0; fieldIndex < fieldCount; ++fieldIndex)
				{
					CARField field(schemaIndex, 0, fieldIndex);

					if(field.GetPermissions().numItems == 0)      //First check if the field has any access group
					{
						nEmptyFields++;
					}
				}

				if(nEmptyFields > 0)
				{
					CTableRow row("");		
					row.AddCell(nEmptyFields);
					row.AddCell(URLLink(schema.GetName(), CPageParams(PAGE_VALIDATOR_FIELD_GROUP_DETAILS, &schema), rootLevel));
					tblObj.AddRow(row);			

					FieldGroupValidatorDetails(schema/*, fName*/);
				}
			}

			webPage.AddContent(tblObj.ToXHtml());
			webPage.SaveInFolder(path);
		}
	}
	catch(exception& e)
	{
		cout << "EXCEPTION Field_Group_Validation: " << e.what() << endl;
	}
}

void CDocValidator::FormGroupValidator()
{
	CPageParams file(PAGE_VALIDATOR_FORM_GROUPS);

	try
	{		
		int rootLevel = file->GetRootLevel();
		string path = file->GetPath();

		FileSystemUtil fsUtil(this->pInside->appConfig);
		if(fsUtil.CreateSubDirectory(path)>=0)
		{
			CWebPage webPage(file->GetFileName(), "Form access group validation", rootLevel, this->pInside->appConfig);

			//ContentHead informations
			stringstream contHeadStrm;
			contHeadStrm << URLLink("Validation", PAGE_VALIDATOR_MAIN, rootLevel) << MenuSeparator;
			contHeadStrm << "Forms with no or unknown group permission:" << endl;
			webPage.AddContentHead(contHeadStrm.str());

			//Check forms	
			CTable tblForms("FormNoPermission", "TblObjectList");
			tblForms.AddColumn(100, "Form Name");

			unsigned int schemaCount = this->pInside->schemaList.GetCount();
			for (unsigned int schemaIndex = 0; schemaIndex < schemaCount; ++schemaIndex)
			{			
				CARSchema schema(schemaIndex);

				// skip this object in case it's overlaid (hidden)
				if (pInside->appConfig.bOverlaySupport && !IsVisibleObject(schema))
					continue;

				if(schema.GetPermissions().numItems == 0)      //Check if the form has no access group
				{
					//Form has no access group
					CTableRow row("");		
					row.AddCell(pInside->LinkToSchema(schema.GetName(), rootLevel));
					tblForms.AddRow(row);
				}
			}

			webPage.AddContent(tblForms.ToXHtml());

			webPage.SaveInFolder(path);
		}
	}
	catch(exception& e)
	{
		cout << "EXCEPTION Form_Group_Validation: " << e.what() << endl;
	}
}

void CDocValidator::FieldReferenceValidator()
{
	CPageParams file(PAGE_VALIDATOR_MISSING_FIELDS);

	try
	{
		int rootLevel = file->GetRootLevel();
		string path = file->GetPath();

		FileSystemUtil fsUtil(this->pInside->appConfig);
		if(fsUtil.CreateSubDirectory(path)>=0)
		{
			CWebPage webPage(file->GetFileName(), "Field validator", rootLevel, this->pInside->appConfig);

			//ContentHead informations
			stringstream contHeadStrm;
			contHeadStrm << URLLink("Validation", PAGE_VALIDATOR_MAIN, rootLevel) << MenuSeparator;
			contHeadStrm << "List of missing fields that are referenced in ARSystem workflow:" << endl;
			webPage.AddContentHead(contHeadStrm.str());

			//Outer table
			bool emptyTable = true;
			CTable tbl("fieldListAll", "TblObjectList");
			tbl.AddColumn(10, "Missing Field");
			tbl.AddColumn(30, "Form");		
			tbl.AddColumn(60, "Workflow Items");

			// TODO: check if there is workflow, that creates missing field references to overlaid forms. That's not necessary.
			unsigned int schemaCount = pInside->schemaList.GetCount();
			for (unsigned int schemaIndex = 0; schemaIndex < schemaCount; ++schemaIndex)
			{
				CARSchema schema(schemaIndex);
				
				// skip this object in case it's overlaid (hidden)
				if (pInside->appConfig.bOverlaySupport && !IsVisibleObject(schema))
					continue;

				const CARSchema::MissingReferenceList* missingList = schema.GetMissingReferences();
				if (missingList == NULL) continue;
				if (missingList->size() == 0) continue;
				emptyTable = false;

				// create a unique field list
				vector<int> missingFields;
				BuildUniqueFieldList(missingFields, missingList);

				vector<int>::iterator missFldCurIt = missingFields.begin();
				vector<int>::iterator missFldEndIt = missingFields.end();

				for (; missFldCurIt != missFldEndIt; ++missFldCurIt)
				{
					CARSchema::MissingReferenceList::const_iterator curIt = missingList->begin();
					CARSchema::MissingReferenceList::const_iterator endIt = missingList->end();

					// inner field references table
					CTable tblRef("referenceList", "TblObjectList");
					tblRef.AddColumn(10, "Type");
					tblRef.AddColumn(45, "Server object");
					tblRef.AddColumn(5, "Enabled");
					tblRef.AddColumn(40, "Description");

					for (; curIt < endIt; ++curIt)
					{
						if (curIt->first == *missFldCurIt)
						{
							CTableRow row("cssStdRow");		
							row.AddCell(CTableCell(CAREnum::XmlStructItem(curIt->second.GetObjectType())));
							row.AddCell(CTableCell(WorkflowReferenceTable::LinkToObjByRefItem(curIt->second, rootLevel)));

							bool supportsEnabled;
							unsigned int enabled = curIt->second.GetObjectEnabled(supportsEnabled);

							string tmpEnabled = "";
							string tmpCssEnabled = "";

							if (supportsEnabled)
							{
								tmpEnabled = CAREnum::ObjectEnable(enabled);
								if (!enabled) { tmpCssEnabled = "objStatusDisabled"; }
							}

							row.AddCell(CTableCell(tmpEnabled, tmpCssEnabled));
							row.AddCell(CTableCell(curIt->second.GetDescription(rootLevel)));
							tblRef.AddRow(row);		
						}
					}

					CTableRow row("");				
					row.AddCell(CTableCell(*missFldCurIt));
					row.AddCell(CTableCell(this->pInside->LinkToSchema(schema.GetInsideId(), rootLevel)));
					row.AddCell(CTableCell(tblRef.ToXHtml()));	
					tbl.AddRow(row);					
				}
			}

			if (!emptyTable)
			{
				webPage.AddContent(tbl.ToXHtml());
			}
			else
			{
				webPage.AddContent("Integrity check found no missing fields in workflow.");
			}
			webPage.SaveInFolder(path);
		}
	}
	catch(exception& e)
	{
		cout << "EXCEPTION Field_Reference_Validation: " << e.what() << endl;
	}
}

void CDocValidator::MenuReferenceValidator()
{
	CPageParams file(PAGE_VALIDATOR_MISSING_MENUS);

	try
	{
		int rootLevel = file->GetRootLevel();
		string path = file->GetPath();

		FileSystemUtil fsUtil(this->pInside->appConfig);
		if(fsUtil.CreateSubDirectory(path)>=0)
		{
			CWebPage webPage(file->GetFileName(), "Menu validator", rootLevel, this->pInside->appConfig);

			//ContentHead informations
			stringstream contHeadStrm;
			contHeadStrm << URLLink("Validation", PAGE_VALIDATOR_MAIN, rootLevel) << MenuSeparator;
			contHeadStrm << "List of missing menus that are referenced in ARSystem workflow:" << endl;
			webPage.AddContentHead(contHeadStrm.str());

			if (pInside->missingMenuReferences.size() > 0)
			{
				CTable tbl("missingMenus", "TblObjectList");
				tbl.AddColumn(30, "Menu Name");
				tbl.AddColumn(10, "Object Type");
				tbl.AddColumn(30, "Server object");
				tbl.AddColumn(30, "Details");

				map<string, CARCharMenu::ReferenceList>::iterator curIt = pInside->missingMenuReferences.begin();
				map<string, CARCharMenu::ReferenceList>::iterator endIt = pInside->missingMenuReferences.end();

				for ( ; curIt != endIt; ++curIt)
				{

					CARCharMenu::ReferenceList::iterator curRefIt = curIt->second.begin();
					CARCharMenu::ReferenceList::iterator endRefIt = curIt->second.end();

					for (; curRefIt != endRefIt; ++curRefIt)
					{
						CTableRow row("cssStdRow");

						int arsObjectType = curRefIt->GetObjectType();

						row.AddCell(curIt->first);
						row.AddCell(CAREnum::XmlStructItem(arsObjectType));
						row.AddCell(WorkflowReferenceTable::LinkToObjByRefItem(*curRefIt, rootLevel));

						stringstream strm;
						strm << curRefIt->GetDescription(rootLevel);

						if (arsObjectType == AR_STRUCT_ITEM_XML_ACTIVE_LINK)
						{
							unsigned int enabled = curRefIt->GetObjectEnabled();
							if (!enabled)
							{
								// use the same formatting like used for missing objects
								strm << " (";
								ObjNotFound notFound(strm);
								notFound << CAREnum::ObjectEnable(enabled);
								notFound.End();
								strm << ")";
							}
						}

						row.AddCell(strm.str());
						
						tbl.AddRow(row);
					}
				}
				webPage.AddContent(tbl.ToXHtml());
				tbl.ClearRows();
			}
			else
			{
				webPage.AddContent("Integrity check found no missing menus in workflow.");
			}

			webPage.SaveInFolder(path);
		}
	}
	catch (...)
	{
		cout << "EXCEPTION in MenuReferenceValidator" << endl;
	}
}
