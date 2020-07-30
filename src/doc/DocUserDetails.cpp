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
#include "DocUserDetails.h"
#include "../output/ImageTag.h"

CDocUserDetails::CDocUserDetails(CARUser &arUser)
{
	this->pUser = &arUser;
}

CDocUserDetails::~CDocUserDetails(void)
{
}

void CDocUserDetails::Documentation()
{
	CPageParams file(PAGE_DETAILS, pUser);
	this->rootLevel = file->GetRootLevel();

	try
	{
		CWebPage webPage(file->GetFileName(), this->pUser->GetName(), this->rootLevel, this->pInside->appConfig);

		//ContentHead informations
		stringstream contHeadStrm;
		contHeadStrm << CWebUtil::LinkToUserIndex(this->rootLevel) << MenuSeparator
		             << ImageTag(*pUser, rootLevel) << CWebUtil::ObjName(this->pUser->GetName());
		webPage.AddContentHead(contHeadStrm.str());

		//User details
		CTable tbl("userDetails", "TblObjectList");
		tbl.AddColumn(30, "Description");
		tbl.AddColumn(70, "Value");

		CTableRow tblRow("");
		tblRow.AddCellList(CTableCell("Full Name"), CTableCell(this->pUser->GetFullName()));
		tbl.AddRow(tblRow);

		tblRow.AddCellList(CTableCell("Email"), CTableCell(this->pUser->GetEmail()));
		tbl.AddRow(tblRow);

		tblRow.AddCellList(CTableCell("License Type"), CTableCell(CAREnum::UserGetFTLicType(this->pUser->GetLicenseType())));
		tbl.AddRow(tblRow);

		tblRow.AddCellList(CTableCell("Full Text License Type"), CTableCell(CAREnum::UserGetFTLicType(this->pUser->GetFTLicenseType())));
		tbl.AddRow(tblRow);

		tblRow.AddCellList(CTableCell("Default Notify Mechanism"), CTableCell(CAREnum::UserGetDefNotify(this->pUser->GetDefaultNotify())));
		tbl.AddRow(tblRow);

		//Groups
		CTable tblGrplist("userGroups", "TblObjectList");
		tblGrplist.AddColumn(10, "Group ID");
		tblGrplist.AddColumn(90, "Group Name");

		const CARUser::GroupList& groups = this->pUser->GetGroups();
		for(unsigned int i=0; i < groups.size(); ++i)
		{
			CTableRow rowGrp("cssStdRow");	
			rowGrp.AddCell(CTableCell(groups[i]));
			rowGrp.AddCell(CTableCell(this->pInside->LinkToGroup("", groups[i], this->rootLevel)));
			tblGrplist.AddRow(rowGrp);			
		}

		tblRow.AddCellList(CTableCell("Group List"), CTableCell(tblGrplist.ToXHtml()));
		tbl.AddRow(tblRow);

		//Add the complete table to the page
		webPage.AddContent(tbl.ToXHtml());
		tbl.Clear();

		//Histoy
		webPage.AddContent(this->pInside->ServerObjectHistory(this->pUser, this->rootLevel));

		webPage.SaveInFolder(file->GetPath());
	}
	catch(exception& e)
	{
		cout << "EXCEPTION user details documentation: " << e.what() << endl;
	}
}
