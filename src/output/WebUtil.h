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

#pragma once

#include "IFileStructure.h"

class CRefItem;

namespace OUTPUT
{
	enum LinkTargetMode {
		TARGET_MODE_SELF = 0,
		TARGET_MODE_PARENT = 1,
		TARGET_MODE_TOP = 2,
		TARGET_MODE_BLANK = 3,
	};

	class CWebUtil
	{
	public:
		CWebUtil(void);
		~CWebUtil(void);

		static string Validate(const string& text);
		//static string Replace(string text);

		static string Link(const string& caption, const string& linkTo, const string &imgName, int rootLevel);
		static string Link(const string& caption, const string& linkTo, const string &imgName, int rootLevel, bool validate);
		static string Link(const string& caption, const CPageParams &linkToPage, const string& imgName, int rootLevel);
		static string Link(const string& caption, const CPageParams &linkToPage, const string& imgName, int rootLevel, bool validate);
		static string Link(const string& caption, const CPageParams &linkToPage, const string& imgName, int rootLevel, LinkTargetMode target);
		static string Link(const string& caption, const CPageParams &linkToPage, const string& imgName, int rootLevel, bool validate, LinkTargetMode target);

		static string HtmlPageSuffix();
		static string HtmlGZPageSuffix();
		static string WebPageSuffix();
		static string CsvPageSuffix();
		static string ImageTag(const string& imgName, int overlayType, int rootLevel);
		static string ImageTag(const string& imgName, int rootLevel);
		static string DocName(const string& fName);
		static string CsvDocName(const string& fName);
		static string ObjName(const string& objName);
		static string ChkBoxInput(string nameAndValue, bool checked);

		static string LinkToActiveLinkIndex(int rootLevel);
		static string LinkToActiveLinkIndex(int objectCount, int rootLevel);
		static string LinkToActiveLinkGuideIndex(int rootLevel);
		static string LinkToActiveLinkGuideIndex(int objectCount, int rootLevel);
		static string LinkToApplicationIndex(int rootLevel);
		static string LinkToApplicationIndex(int objectCount, int rootLevel);
		static string LinkToEscalationIndex(int rootLevel);
		static string LinkToEscalationIndex(int objectCount, int rootLevel);
		static string LinkToFilterIndex(int rootLevel);
		static string LinkToFilterIndex(int objectCount, int rootLevel);
		static string LinkToFilterGuideIndex(int rootLevel);
		static string LinkToFilterGuideIndex(int objectCount, int rootLevel);
		static string LinkToGroupIndex(int rootLevel);
		static string LinkToGroupIndex(int objectCount, int rootLevel);
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_750
		static string LinkToImageIndex(int rootLevel);
		static string LinkToImageIndex(int objectCount, int rootLevel);
#endif
		static string LinkToMenu(string menuName, int rootLevel);
		static string LinkToMenu(const CRefItem& refItem, int rootLevel);
		static string LinkToMenuIndex(int rootLevel);
		static string LinkToMenuIndex(int objectCount, int rootLevel);
		static string LinkToPackingListIndex(int rootLevel);
		static string LinkToPackingListIndex(int objectCount, int rootLevel);
		static string LinkToRoleIndex(int rootLevel);
		static string LinkToRoleIndex(int objectCount, int rootLevel);
		static string LinkToSchemaIndex(int rootLevel, bool showImage = true);
		static string LinkToSchemaIndex(int objectCount, int rootLevel, bool showImage = true);
		static string LinkToUserIndex(int rootLevel);
		static string LinkToUserIndex(int objectCount, int rootLevel);
		static string LinkToWebServiceIndex(int rootLevel);
		static string LinkToWebServiceIndex(int objectCount, int rootLevel);	
		static string LinkToContainer(int objectCount, int rootLevel, int containerType);

		static string LinkToHelper(string name, int objectCount, const CPageParams& page, const string &image, int rootLevel);
		static string GetRelativeURL(int rootLevel, const CPageParams& page);

		static string webpageFileExtension;
	};
}
