//Copyright (C) 2014 John Luthgers | jls17
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
//    along with ARInside.  If not, see <http://www.gnu.org/licenses/>.

#include "stdafx.h"
#include "../core/ARServerObject.h"
#include "ImageTag.h"
#include "RootPath.h"
#include "URLLink.h"
#include "WebUtil.h"

namespace OUTPUT
{
	// constructors
	URLLink::URLLink(const std::string &caption, const CPageParams &linkToPage, const OUTPUT::ImageTag &image, int rootLevel, bool validate, LinkTargetMode target)
	{
		Init(caption, linkToPage, image, rootLevel, validate, target);
	}
	URLLink::URLLink(const std::string &caption, const CPageParams &linkToPage, const OUTPUT::ImageTag &image, int rootLevel, LinkTargetMode target)
	{
		Init(caption, linkToPage, image, rootLevel, true, target);
	}
	URLLink::URLLink(const std::string &caption, const CPageParams &linkToPage, const OUTPUT::ImageTag::ImageEnum imageId, int rootLevel)
	{
		ImageTag image(imageId, rootLevel);
		Init(caption, linkToPage, image, rootLevel, true, TARGET_MODE_SELF);
	}
	URLLink::URLLink(const std::string &caption, const CPageParams &linkToPage, int rootLevel)
	{
		ImageTag image(ImageTag::NoImage, 0);
		Init(caption, linkToPage, image, rootLevel, true, TARGET_MODE_SELF);
	}
	URLLink::URLLink(const std::string &caption, unsigned int page, OUTPUT::ImageTag::ImageEnum imageId, int rootLevel)
	{
		CPageParams linkToPage(page);
		ImageTag image(imageId, rootLevel);
		Init(caption, linkToPage, image, rootLevel, true, TARGET_MODE_SELF);
	}
	URLLink::URLLink(const std::string &caption, unsigned int page, int rootLevel)
	{
		CPageParams linkToPage(page);
		ImageTag image(ImageTag::NoImage, 0);
		Init(caption, linkToPage, image, rootLevel, true, TARGET_MODE_SELF);
	}
	URLLink::URLLink(const CARServerObject &workflowObject, int rootLevel, bool showImage)
	{
		InitObj(workflowObject.GetName(), workflowObject, rootLevel, showImage);
	}
	URLLink::URLLink(const std::string &caption, const CARServerObject &workflowObject, int rootLevel, bool showImage)
	{
		InitObj((caption.empty() ? workflowObject.GetName() : caption), workflowObject, rootLevel, showImage);
	}

	// Central class initialization
	void URLLink::Init(const std::string &caption, const CPageParams &linkToPage, const OUTPUT::ImageTag &image, int rootLevel, bool validate, OUTPUT::URLLink::LinkTargetMode target)
	{
		stringstream strmTmp;

		strmTmp << image;
		
		if (!linkToPage.Valid())
			AddCaption(strmTmp, caption, validate);
		else
		{
			strmTmp << "<a href=\"" << RootPath(rootLevel) << linkToPage->GetFullFileName() << "\"";
			if (target > TARGET_MODE_SELF)
			{
				strmTmp << " target=\"";
				switch (target)
				{
					case TARGET_MODE_PARENT: strmTmp << "_parent"; break;
					case TARGET_MODE_TOP: strmTmp << "_top"; break;
					case TARGET_MODE_BLANK: strmTmp << "_blank"; break;
				}
				strmTmp << "\"";
			}
			strmTmp << ">"; 
			AddCaption(strmTmp, caption, validate);
			strmTmp << "</a>";
		}

		link = strmTmp.str();
	}

	void URLLink::InitObj(const std::string &caption, const CARServerObject &workflowObject, int rootLevel, bool showImage)
	{
		CPageParams linkToPage(PAGE_DETAILS, &workflowObject);
		Init(caption, linkToPage, (showImage ? ImageTag(workflowObject, rootLevel) : ImageTag(ImageTag::NoImage, 0)), rootLevel, true, URLLink::TARGET_MODE_SELF);
	}

	void URLLink::InitDirect(const std::string &linkHTML)
	{
		link = linkHTML;
	}

	void URLLink::AddCaption(std::ostream &strm, const std::string &caption, bool validate)
	{
		strm << (validate ? CWebUtil::Validate(caption) : caption);
	}

	ostream& URLLink::ToStream(std::ostream &strm) const
	{
		strm << link;
		return strm;
	}

	ostream& operator <<(ostream &strm, const URLLink &link)
	{
		return link.ToStream(strm);
	}

	URLLink::operator std::string() const
	{
		stringstream strm;
		ToStream(strm);
		return strm.str();
	}

	CheckedURLLink::CheckedURLLink(const CARServerObject &workflowObject, const std::string &alternateHTML, int rootLevel, bool showImage)
	{
		if (workflowObject.Exists())
		{
			InitObj(workflowObject.GetName(), workflowObject, rootLevel, showImage);
		}
		else
		{
			InitDirect(alternateHTML);
		}
	}

	DirectURLLink::DirectURLLink(OUTPUT::DirectURLLink::DirectLinkEnum directLinkType, int rootLevel)
	{
		switch (directLinkType)
		{
		case CreateTop: InitDirect("<a id=\"top\"></a>"); break;
		case LinkToTop: InitLinkEnum("Top", ImageTag::Up, "#top", rootLevel); break;
		default: InitDirect("");
		}
	}
	DirectURLLink::DirectURLLink(OUTPUT::DirectURLLink::DirectLinkEnum directLinkType, const std::string &caption, int rootLevel)
	{
		switch (directLinkType)
		{
		case JavascriptVoid: InitLinkEnum(caption, ImageTag::NoImage, "javascript:void(0)", rootLevel); break;
		default: InitDirect("");
		}
	}

	void DirectURLLink::InitLinkEnum(const std::string &caption, const OUTPUT::ImageTag::ImageEnum imageId, const std::string &href, int rootLevel)
	{
		stringstream strm;
		if (imageId != ImageTag::NoImage)
		{
			ImageTag image(imageId, rootLevel);
			strm << image;
		}
		strm << "<a href=\"" << href << "\">";
		AddCaption(strm, caption, true);
		strm << "</a>";

		InitDirect(strm.str());
	}

	ostream& operator <<(ostream &strm, const OUTPUT::DirectURLLink::DirectLinkEnum link)
	{
		DirectURLLink linkInst(link, 0);
		return linkInst.ToStream(strm);
	}

	ostream& operator <<(ostream &strm, const OUTPUT::DirectURLLink &link)
	{
		return link.ToStream(strm);
	}

}; // end namespace OUTPUT

