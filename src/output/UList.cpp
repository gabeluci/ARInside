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
#include "UList.h"
#include "ImageTag.h"

using namespace OUTPUT;

CUList::CUList(int rootLevel, string cssClass)
{
	this->cssClass = cssClass;
	this->rootLevel = rootLevel;
}

CUList::~CUList(void)
{
	this->listItem.clear();
}

void CUList::AddItem(const CUListItem &li)
{
	this->listItem.insert(this->listItem.end(), li);
}

string CUList::ToXHtml(string title, bool bItemImage)
{
	stringstream strm;

	if(title.size() > 0)
		strm << title << endl;


	strm << "<ul>" << endl;
	list<CUListItem>::iterator iter;
	CUListItem *listItem;	

	for ( iter = this->listItem.begin(); iter != this->listItem.end(); ++iter )
	{	
		listItem = &(*iter);

		string liImage = "";

		if(bItemImage)
			liImage = ImageTag(ImageTag::Document, rootLevel);

		strm << "<li>" << liImage << listItem->itemText << "</li>" << endl;
	}
	strm << "</ul>" << endl;
	return strm.str();
}
