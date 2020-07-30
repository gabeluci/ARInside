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
#include "DocGroupDetails.h"
#include "../output/ImageTag.h"
#include "../output/URLLink.h"

CDocGroupDetails::CDocGroupDetails(CARGroup &arGroup)
: group(arGroup)
{
}

CDocGroupDetails::~CDocGroupDetails(void)
{
}

void CDocGroupDetails::Documentation()
{
	CPageParams file(PAGE_DETAILS, &group);
	this->rootLevel = file->GetRootLevel();

	try
	{
		CWebPage webPage(file->GetFileName(), this->group.GetName(), this->rootLevel, this->pInside->appConfig);

		//ContentHead informations
		stringstream contHeadStrm;
		contHeadStrm << CWebUtil::LinkToGroupIndex(this->rootLevel) << MenuSeparator
		             << ImageTag(group, rootLevel) << CWebUtil::ObjName(this->group.GetName())
		             << " (Id: " << group.GetGroupId() << ")" << endl;
		webPage.AddContentHead(contHeadStrm.str());

		//Group details
		CTable tbl("groupDetails", "TblObjectList");
		tbl.AddColumn(30, "Description");
		tbl.AddColumn(70, "Value");

		CTableRow tblRow("");
		tblRow.AddCellList(CTableCell("Group Name"), CTableCell(this->group.GetName()));
		tbl.AddRow(tblRow);

		tblRow.AddCellList(CTableCell("Long Group Name"), CTableCell(this->group.GetLongName()));
		tbl.AddRow(tblRow);

		tblRow.AddCellList(CTableCell("Group Type"), CTableCell(CAREnum::GroupType(this->group.GetType())));
		tbl.AddRow(tblRow);

		tblRow.AddCellList(CTableCell("Group Category"), CTableCell(CAREnum::GroupCategory(this->group.GetCategory())));
		tbl.AddRow(tblRow);

		if (this->group.GetCategory() == AR_GROUP_CATEGORY_COMPUTED) {
			tblRow.AddCellList(CTableCell("Computed Group Definition"), CTableCell(this->group.GetComputedQualification()));
			tbl.AddRow(tblRow);
		}

		tblRow.AddCellList(CTableCell("Permissions"), this->GroupPermissions());
		tbl.AddRow(tblRow);

		tblRow.AddCellList(CTableCell("Role Mapping"), this->RoleReferences());
		tbl.AddRow(tblRow);

		webPage.AddContent(tbl.ToXHtml());
		tbl.Clear();

		//Histoy
		webPage.AddContent(this->pInside->ServerObjectHistory(&this->group, this->rootLevel));

		webPage.SaveInFolder(file->GetPath());
	}
	catch(exception& e)
	{
		cout << "EXCEPTION CDocGroupDetails_Documentation of '" << group.GetName() << "': " << e.what() << endl;
	}
}

string CDocGroupDetails::RoleReferences()
{
	CTable tbl("roleList", "TblNoSort");
	tbl.AddColumn(30, "Type");
	tbl.AddColumn(70, "Role");

	unsigned int roleCount = this->pInside->roleList.GetCount();
	for ( unsigned int roleIndex = 0; roleIndex < roleCount; ++roleIndex )
	{	
		CARRole role(roleIndex);

		const CARRole::GroupList& groupsProd = role.GetGroupsProd();
		CARRole::GroupList::const_iterator curIt = groupsProd.begin();
		CARRole::GroupList::const_iterator endIt = groupsProd.end();

		for (; curIt != endIt; ++curIt)
		{
			if(*curIt == this->group.GetGroupId())
			{
				CTableRow row("");
				row.AddCellList(CTableCell("Production"), CTableCell( URLLink(role, this->rootLevel)));
				tbl.AddRow(row);
			}
		}

		const CARRole::GroupList& groupsTest = role.GetGroupsTest();
		curIt = groupsTest.begin();
		endIt = groupsTest.end();

		for (; curIt != endIt; ++curIt)
		{
			if(*curIt == this->group.GetGroupId())
			{
				CTableRow row("");
				row.AddCellList(CTableCell("Test"), CTableCell( URLLink(role, this->rootLevel)));
				tbl.AddRow(row);
			}
		}
	}

	return tbl.ToXHtml();
}

string CDocGroupDetails::GroupPermissions()
{
	CTable tbl("permissionList", "TblNoSort");
	tbl.AddColumn(100, "Permission Details");

	stringstream strmTmp;
	strmTmp.str("");

	//Form Access
	int nResult = 0;
	this->FormsDoc(nResult, "Form Permission");
	if(nResult == 0)
		strmTmp.str("No Form Access");
	else
		strmTmp << URLLink("Form Access", CPageParams(PAGE_GROUP_SCHEMA_LIST, &group), rootLevel) << " (" << nResult << ")<br/>";

	CTableRow row("");		
	row.AddCell(CTableCell(strmTmp.str()));
	tbl.AddRow(row);


	//Field Permission
	strmTmp.str("");
	this->FieldPermissionDoc(nResult, "Field Permission");
	if(nResult == 0)
		strmTmp.str("No Field Permission");
	else
		strmTmp << URLLink("Field Permission", CPageParams(PAGE_GROUP_FIELD_LIST, &group), rootLevel) << " (" << nResult << ")<br/>";

	row.ClearCells();
	row.AddCell(CTableCell(strmTmp.str()));
	tbl.AddRow(row);


	//Active Link Permissions
	strmTmp.str("");
	this->AlPermissionDoc(nResult, "Active Link Permission");
	if(nResult == 0)
		strmTmp.str("No Active Link Permission");
	else
		strmTmp << URLLink("Active Link Permission", CPageParams(PAGE_GROUP_ACTIVELINK_LIST, &group), rootLevel) << " (" << nResult << ")<br/>";

	row.ClearCells();
	row.AddCell(CTableCell(strmTmp.str()));
	tbl.AddRow(row);


	//Users in group
	strmTmp.str("");
	this->UserDoc(nResult, "Group Members");
	if(nResult == 0)
		strmTmp.str("No Group Members");
	else
		strmTmp << URLLink("Group Members", CPageParams(PAGE_GROUP_USER_LIST, &group), rootLevel) << " (" << nResult << ")<br/>";

	row.ClearCells();
	row.AddCell(CTableCell(strmTmp.str()));
	tbl.AddRow(row);


	//Packing List Permissions
	strmTmp.str("");
	this->ContainerPermissionDoc(nResult, "Packing List Permission", ARCON_PACK);
	if(nResult == 0)
		strmTmp.str("No Packing List Permission");
	else
		strmTmp << URLLink("Packing List Permission", CPageParams(PAGE_GROUP_CONTAINER_LIST, ARCON_PACK, &group), rootLevel) << " (" << nResult << ")<br/>";

	row.ClearCells();
	row.AddCell(CTableCell(strmTmp.str()));
	tbl.AddRow(row);


	//ActiveLink Guide
	strmTmp.str("");
	this->ContainerPermissionDoc(nResult, "Active Link Guide Permission", ARCON_GUIDE);
	if(nResult == 0)
		strmTmp.str("No Active Link Guide Permission");
	else
		strmTmp << URLLink("Active Link Guide Permission", CPageParams(PAGE_GROUP_CONTAINER_LIST, ARCON_GUIDE, &group), rootLevel) << " (" << nResult << ")<br/>";

	row.ClearCells();
	row.AddCell(CTableCell(strmTmp.str()));
	tbl.AddRow(row);


	//Webservice Permissions
	strmTmp.str("");
	this->ContainerPermissionDoc(nResult, "Webservice Permission", ARCON_WEBSERVICE);
	if(nResult == 0)
		strmTmp.str("No Webservice Permission");
	else
		strmTmp << URLLink("Webservice Permission", CPageParams(PAGE_GROUP_CONTAINER_LIST, ARCON_WEBSERVICE, &group), rootLevel) << " (" << nResult << ")<br/>";

	row.ClearCells();
	row.AddCell(CTableCell(strmTmp.str()));
	tbl.AddRow(row);	

	return tbl.ToXHtml();
}

void CDocGroupDetails::UserDoc(int &nResult, string title)
{
	CPageParams file(PAGE_GROUP_USER_LIST, &group);

	try
	{
		rootLevel = file->GetRootLevel();
		nResult = 0;

		CWebPage webPage(file->GetFileName(), title + " " +this->group.GetName(), rootLevel, this->pInside->appConfig);	

		//ContentHead informations
		stringstream contHeadStrm;
		contHeadStrm << CWebUtil::LinkToGroupIndex(rootLevel)
		             << MenuSeparator << URLLink(group, rootLevel)
		             << MenuSeparator << CWebUtil::ObjName(title) << endl;
		webPage.AddContentHead(contHeadStrm.str());
		contHeadStrm.str("");

		//Add a table with all users
		CTable tbl("userList", "TblObjectList");
		tbl.AddColumn(60, "Login Name");
		tbl.AddColumn(20, "Modified");
		tbl.AddColumn(20, "By");

		unsigned int userCount = this->pInside->userList.GetCount();
		for (unsigned int userId = 0; userId < userCount; ++userId)
		{	
			CARUser user(userId);

			const CARUser::GroupList& grpList = user.GetGroups();
			CARUser::GroupList::const_iterator findIt = std::find(grpList.begin(), grpList.end(), this->group.GetGroupId());

			if (findIt != grpList.end())
			{
				CTableRow row("");
				row.AddCell(CTableCell(URLLink(user.GetName(), CPageParams(PAGE_DETAILS, &user), rootLevel)));
				row.AddCell(CTableCell(CUtil::DateTimeToHTMLString(user.GetTimestamp())));
				row.AddCell(CTableCell(this->pInside->LinkToUser(user.GetLastChanged(), rootLevel)));
				tbl.AddRow(row);

				nResult++;
			}
		}

		webPage.AddContent(tbl.ToXHtml());

		webPage.SaveInFolder(file->GetPath());
	}
	catch(exception& e)
	{
		cout << "EXCEPTION CDocGroupDetails_FormsDoc of '" << this->group.GetName() << "': " << e.what() << endl;
	}
}

void CDocGroupDetails::FormsDoc(int &nResult, string title)
{
	CPageParams file(PAGE_GROUP_SCHEMA_LIST, &group);

	try
	{
		rootLevel = file->GetRootLevel();
		nResult = 0;

		CWebPage webPage(file->GetFileName(), title + " " +this->group.GetName(), rootLevel, this->pInside->appConfig);	

		//ContentHead informations
		stringstream contHeadStrm;
		contHeadStrm << CWebUtil::LinkToGroupIndex(rootLevel);
		contHeadStrm << MenuSeparator << URLLink(group, rootLevel);
		contHeadStrm << MenuSeparator << CWebUtil::ObjName(title) << endl;
		webPage.AddContentHead(contHeadStrm.str());
		contHeadStrm.str("");

		//Create table with forms the group can access
		CTable schemaTbl("schemaList", "TblObjectList");
		schemaTbl.description = "Form Permission";
		schemaTbl.AddColumn(5, "Visible");
		schemaTbl.AddColumn(35, "Form Name");
		schemaTbl.AddColumn(5, "Fields");
		schemaTbl.AddColumn(5, "Views");
		schemaTbl.AddColumn(10, "Type");
		schemaTbl.AddColumn(20, "Modified");
		schemaTbl.AddColumn(20, "By");

		//Create table with forms for group subadmin permission
		CTable subadminTbl("schemaListSubadmin", "TblObjectList");
		subadminTbl.description = "Form Subadministrator Permission";
		subadminTbl.AddColumn(35, "Form Name");
		subadminTbl.AddColumn(5, "Fields");
		subadminTbl.AddColumn(5, "Views");
		subadminTbl.AddColumn(10, "Type");
		subadminTbl.AddColumn(20, "Modified");
		subadminTbl.AddColumn(20, "By");

		unsigned int schemaCount = this->pInside->schemaList.GetCount();
		for ( unsigned int schemaIndex = 0; schemaIndex < schemaCount; ++schemaIndex )
		{	
			CARSchema schema(schemaIndex);

			// skip this object in case it's overlaid (hidden)
			if (pInside->appConfig.bOverlaySupport && !IsVisibleObject(schema))
				continue;

			const ARPermissionList& groupList = schema.GetPermissions();

			for(unsigned int nGrp = 0; nGrp < groupList.numItems; nGrp++)
			{
				if (this->group.GetGroupId() == groupList.permissionList[nGrp].groupId)
				{
					ImageTag visibility((groupList.permissionList[nGrp].permissions == AR_PERMISSIONS_VISIBLE ? ImageTag::Visible : ImageTag::Hidden), rootLevel);

					CTableRow row("");
					row.AddCell(CTableCell(visibility));
					row.AddCell(CTableCell(URLLink(schema, rootLevel)));						
					row.AddCell(CTableCell(schema.GetFields()->GetCount()));
					row.AddCell(CTableCell(schema.GetVUIs()->GetCount()));
					row.AddCell(CTableCell(CAREnum::SchemaType(schema.GetCompound().schemaType)));
					row.AddCell(CTableCell(CUtil::DateTimeToHTMLString(schema.GetTimestamp())));
					row.AddCell(CTableCell(this->pInside->LinkToUser(schema.GetLastChanged(), rootLevel)));
					schemaTbl.AddRow(row);
					nResult++;
				}
			}

			const ARInternalIdList& admingrpList = schema.GetSubadmins();

			for(unsigned int nGrp = 0; nGrp < admingrpList.numItems; nGrp++)
			{
				if(this->group.GetGroupId() == admingrpList.internalIdList[nGrp])
				{
					CTableRow row("");
					row.AddCell(CTableCell(URLLink(schema, rootLevel)));						
					row.AddCell(CTableCell(schema.GetFields()->GetCount()));
					row.AddCell(CTableCell(schema.GetVUIs()->GetCount()));
					row.AddCell(CTableCell(CAREnum::SchemaType(schema.GetCompound().schemaType)));
					row.AddCell(CTableCell(CUtil::DateTimeToHTMLString(schema.GetTimestamp())));
					row.AddCell(CTableCell(this->pInside->LinkToUser(schema.GetLastChanged(), rootLevel)));
					subadminTbl.AddRow(row);
					nResult++;
				}
			}
		}


		webPage.AddContent(schemaTbl.ToXHtml());

		webPage.AddContent(subadminTbl.ToXHtml());

		webPage.SaveInFolder(file->GetPath());
	}
	catch(exception& e)
	{
		cout << "EXCEPTION CDocGroupDetails_FormsDoc of '" << this->group.GetName() << "': " << e.what() << endl;
	}
}

void CDocGroupDetails::AlPermissionDoc(int &nResult, string title)
{
	CPageParams file(PAGE_GROUP_ACTIVELINK_LIST, &group);

	try
	{
		rootLevel = file->GetRootLevel();
		nResult = 0;

		CWebPage webPage(file->GetFileName(), title + " " +this->group.GetName(), rootLevel, this->pInside->appConfig);	

		//ContentHead informations
		stringstream contHeadStrm;
		contHeadStrm << CWebUtil::LinkToGroupIndex(rootLevel);
		contHeadStrm << MenuSeparator << URLLink(group, rootLevel);
		contHeadStrm << MenuSeparator << CWebUtil::ObjName(title) << endl;
		webPage.AddContentHead(contHeadStrm.str());
		contHeadStrm.str("");

		//Create table with ALs the role can access
		CAlTable *alTable = new CAlTable(*this->pInside);

		unsigned int alCount = pInside->alList.GetCount();
		for (unsigned int alIndex = 0; alIndex < alCount; ++alIndex)
		{	
			CARActiveLink al(alIndex);

			// skip this object in case it's overlaid (hidden)
			if (pInside->appConfig.bOverlaySupport && !IsVisibleObject(al))
				continue;

			for(unsigned int nGrp = 0; nGrp < al.GetGroupList().numItems; nGrp++)
			{
				if(this->group.GetGroupId() == al.GetGroupList().internalIdList[nGrp])
				{
					alTable->AddRow(alIndex, this->rootLevel);
					nResult++;
				}
			}
		}


		webPage.AddContent(alTable->Print());
		delete alTable;

		webPage.SaveInFolder(file->GetPath());
	}
	catch(exception& e)
	{
		cout << "EXCEPTION CDocGroupDetails_ActiveLinkDoc of '" << this->group.GetName() << "': " << e.what() << endl;
	}
}

void CDocGroupDetails::ContainerPermissionDoc(int &nResult, string title, int containerType)
{
	CPageParams file(PAGE_GROUP_CONTAINER_LIST, containerType, &group);

	try
	{
		rootLevel = file->GetRootLevel();
		nResult = 0;

		CWebPage webPage(file->GetFileName(), title + " " +this->group.GetName(), rootLevel, this->pInside->appConfig);	

		//ContentHead informations
		stringstream contHeadStrm;
		contHeadStrm << CWebUtil::LinkToGroupIndex(rootLevel);
		contHeadStrm << MenuSeparator << URLLink(group, rootLevel);
		contHeadStrm << MenuSeparator << CWebUtil::ObjName(title) << endl;
		webPage.AddContentHead(contHeadStrm.str());
		contHeadStrm.str("");

		//Create table with forms the role can access
		CContainerTable *contTbl = new CContainerTable(*this->pInside);
		CContainerTable *subadminTbl = (containerType == ARCON_PACK ? new CContainerTable(*this->pInside) : NULL);

		contTbl->SetDescription("Container Permission");

		unsigned int cntCount = this->pInside->containerList.GetCount();
		for ( unsigned int cntIndex = 0; cntIndex < cntCount; ++cntIndex )
		{	
			CARContainer cont(cntIndex);

			// skip this object in case it's overlaid (hidden)
			if (pInside->appConfig.bOverlaySupport && !IsVisibleObject(cont))
				continue;

			if(cont.GetType() == containerType)
			{
				const ARPermissionList& groupList = cont.GetPermissions();
				for(unsigned int nGrp = 0; nGrp < groupList.numItems; nGrp++)
				{
					if(this->group.GetGroupId() == groupList.permissionList[nGrp].groupId)
					{
						contTbl->AddRow(cont, this->rootLevel);
						nResult++;
					}
				}
			}

			if(containerType == ARCON_PACK)
			{
				//Create table with forms for role subadmin permission
				subadminTbl->SetDescription("Subadministrator Permission");
				
				const ARInternalIdList& admingrpList = cont.GetSubadmins();
				for(unsigned int nGrp = 0; nGrp < admingrpList.numItems; nGrp++)
				{
					if(this->group.GetGroupId() == admingrpList.internalIdList[nGrp])
					{
						subadminTbl->AddRow(cont, this->rootLevel);
						nResult++;
					}
				}

			}
		}


		webPage.AddContent(contTbl->Print());
		delete contTbl;

		if (subadminTbl != NULL)
		{
			webPage.AddContent(subadminTbl->Print());
			delete subadminTbl;
		}

		webPage.SaveInFolder(file->GetPath());
	}
	catch(exception& e)
	{
		cout << "EXCEPTION CDocGroupDetails_FormsDoc of '" << this->group.GetName() << "': " << e.what() << endl;
	}
}

int CDocGroupDetails::NumAllowedFields(CARSchema& schema)
{
	int nResult = 0;
	try
	{
		unsigned int fieldCount = schema.GetFields()->GetCount();
		for( unsigned int fieldIndex = 0; fieldIndex < fieldCount; ++fieldIndex )
		{
			CARField field(schema.GetInsideId(), 0, fieldIndex);
			const ARPermissionList& permissions = field.GetPermissions();
			for(unsigned int i = 0; i< permissions.numItems; i++)
			{
				if(permissions.permissionList[i].groupId == this->group.GetGroupId())
				{
					nResult++;
				}
			}
		}
	}
	catch(exception& e)
	{
		cout << "EXCEPTION CDocGroupDetails_NumAllowedFields of '" << this->group.GetName() << "': " << e.what() << endl;
	}
	return nResult;
}

void CDocGroupDetails::FieldPermissionDoc(int &nResult, string title)
{
	CPageParams file(PAGE_GROUP_FIELD_LIST, &group);

	try
	{
		rootLevel = file->GetRootLevel();
		nResult = 0;
		CWebPage webPage(file->GetFileName(), title + " " +this->group.GetName(), rootLevel, this->pInside->appConfig);

		//ContentHead informations
		stringstream contHeadStrm;
		contHeadStrm << CWebUtil::LinkToGroupIndex(rootLevel);
		contHeadStrm << MenuSeparator << URLLink(group, rootLevel);
		contHeadStrm << MenuSeparator << CWebUtil::ObjName("Field Permissions") << endl;
		webPage.AddContentHead(contHeadStrm.str());
		contHeadStrm.str("");

		unsigned int schemaCount = this->pInside->schemaList.GetCount();
		for ( unsigned int schemaIndex = 0; schemaIndex < schemaCount; ++schemaIndex )
		{			
			CARSchema schema(schemaIndex);

			// skip this object in case it's overlaid (hidden)
			if (pInside->appConfig.bOverlaySupport && !IsVisibleObject(schema))
				continue;

			if(NumAllowedFields(schema) > 0)
			{
				const ARPermissionList& groupList = schema.GetPermissions();

				//Check if the current group has access to the form
				bool bVisiblePermission = false;		
				bool bInsert = false;

				for(unsigned int nGrp = 0; nGrp < groupList.numItems; nGrp++)
				{
					if(this->group.GetGroupId() == groupList.permissionList[nGrp].groupId)
					{
						if (groupList.permissionList[nGrp].permissions == AR_PERMISSIONS_VISIBLE)
						{
							bVisiblePermission = true;
						}
						bInsert = true;
						break;
					}
				}	

				stringstream strmFormDesc;
				strmFormDesc.str("");
				if(bInsert)
				{
					ImageTag image((bVisiblePermission ? ImageTag::Visible : ImageTag::Hidden), rootLevel);
					strmFormDesc << image << URLLink(schema, rootLevel) << endl;
				}
				else
				{
					strmFormDesc << URLLink(schema, rootLevel) << endl;
				}

				//Create a table for every form
				CTable schemaTbl("fieldListAll"+schema.GetInsideId(), "TblObjectList");
				schemaTbl.description = strmFormDesc.str();
				schemaTbl.AddColumn(80, "Field");
				schemaTbl.AddColumn(10, "Permission");
				schemaTbl.AddColumn(10, "Description");

				unsigned int fieldCount = schema.GetFields()->GetCount();
				for( unsigned int fieldIndex = 0; fieldIndex < fieldCount; ++fieldIndex)
				{
					CARField field(schemaIndex, 0, fieldIndex);
					const ARPermissionList& permissions = field.GetPermissions();
					for(unsigned int i = 0; i < permissions.numItems; i++)
					{
						if(permissions.permissionList[i].groupId == this->group.GetGroupId())
						{
							//We found a field that this group is allowed to access
							ImageTag image((permissions.permissionList[i].permissions == AR_PERMISSIONS_CHANGE ? ImageTag::Edit : ImageTag::Visible), rootLevel);

							CTableRow row("");			
							row.AddCell(CTableCell(URLLink(field, rootLevel)));
							row.AddCell(CTableCell(image));
							row.AddCell(CTableCell(CAREnum::FieldPermission(permissions.permissionList[i].permissions)));
							schemaTbl.AddRow(row);

							nResult++;
						}
					}
				}

				webPage.AddContent(schemaTbl.ToXHtml());
			}
		}

		webPage.SaveInFolder(file->GetPath());
	}
	catch(exception& e)
	{
		cout << "EXCEPTION CDocGroupDetails_FieldsDoc of '" << this->group.GetName() << "': " << e.what() << endl;
	}
}
