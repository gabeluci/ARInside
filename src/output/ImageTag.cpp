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
#include "ImageTag.h"
#include "../core/ARContainer.h"
#include "../core/ARSchema.h"
#include "../core/ARServerObject.h"
#include "../output/RootPath.h"

namespace OUTPUT
{
	struct ImageDimensions
	{
		unsigned short x;
		unsigned short y;
	};

	// the following function maps the imageId to a file name
	// make sure new images are added here
	const char* GetImageName(int imageId)
	{
		switch (imageId)
		{
		case ImageTag::NoImage: return "";
		case ImageTag::Schema: return "schema.gif";
		case ImageTag::SchemaJoin: return "schema_join.gif";
		case ImageTag::SchemaView: return "schema_view.gif";
		case ImageTag::SchemaDialog: return "schema_display.gif";
		case ImageTag::SchemaVendor: return "schema_vendor.gif";
		case ImageTag::Server: return "server.gif";
		case ImageTag::Document: return "doc.gif";
		case ImageTag::Folder: return "folder.gif";
		case ImageTag::ActiveLink: return "active_link.gif";
		case ImageTag::Filter: return "filter.gif";
		case ImageTag::Escalation: return "escalation.gif";
		case ImageTag::Menu: return "menu.gif";
		case ImageTag::ActiveLinkGuide: return "al_guide.gif";
		case ImageTag::FilterGuide: return "filter_guide.gif";
		case ImageTag::Application: return "application.gif";
		case ImageTag::PackingList: return "packing_list.gif";
		case ImageTag::Webservice: return "webservice.gif";
		case ImageTag::Image: return "image.gif";
		case ImageTag::User: return "user.gif";
		case ImageTag::Group: return "group.gif";
		case ImageTag::Role: return "role.gif";
		case ImageTag::Hidden: return "hidden.gif";
		case ImageTag::Visible: return "visible.gif";
		case ImageTag::Edit: return "edit.gif";
		case ImageTag::Next: return "next.gif";
		case ImageTag::SortAsc: return "sort_asc.gif";
		case ImageTag::SortDesc: return "sort_desc.gif";
		case ImageTag::Up: return "up.gif";
		case ImageTag::Down: return "down.gif";
		}
		// always throw an assert here, in case a undefined image is used!
		assert(false);
		return "";
	}

	ImageDimensions DefaultImageDimensions = { 16, 16 };
	ImageDimensions DocumentImageDimensions = { 15, 10 };
	ImageDimensions FolderImageDimensions = { 16, 13 };
	ImageDimensions PermissionDimensions =  { 18, 18 };
	ImageDimensions NextImageDimensions = { 10, 10 };
	ImageDimensions UpDownDimensions = { 14, 10 };

	// the following provides the image dimensions (width and height)
	// for a particular imageId. If new images don't use the default
	// width and height of 16x16, make sure the correct dimension is
	// returned here.
	ImageDimensions GetImageDimensions(ImageTag::ImageEnum image)
	{
		switch (image)
		{
		case ImageTag::Document: return DocumentImageDimensions;
		case ImageTag::Folder: return FolderImageDimensions;
		case ImageTag::Hidden:
		case ImageTag::Visible:
		case ImageTag::Edit: return PermissionDimensions;
		case ImageTag::Next: return NextImageDimensions;
		case ImageTag::Up: 
		case ImageTag::Down: return UpDownDimensions;
		}
		return DefaultImageDimensions;
	}

	// #### some helpers for construction
	ImageTag::ImageEnum GetContainerImage(unsigned int containerType)
	{
		switch (containerType)
		{
		case ARCON_GUIDE: return ImageTag::ActiveLinkGuide;
		case ARCON_APP: return ImageTag::Application;
		case ARCON_PACK: return ImageTag::PackingList;
		case ARCON_FILTER_GUIDE: return ImageTag::FilterGuide;
		case ARCON_WEBSERVICE: return ImageTag::Webservice;
		default: return ImageTag::Document;
		}
	}

	ImageTag::ImageEnum GetSchemaImage(unsigned int schemaType)
	{
		switch (schemaType)
		{
		case AR_SCHEMA_REGULAR: return ImageTag::SchemaRegular;
		case AR_SCHEMA_JOIN: return ImageTag::SchemaJoin;
		case AR_SCHEMA_VIEW: return ImageTag::SchemaView;
		case AR_SCHEMA_DIALOG: return ImageTag::SchemaDialog;
		case AR_SCHEMA_VENDOR: return ImageTag::SchemaVendor;
		default: return ImageTag::Schema;
		}
	}

	ImageTag::ImageEnum MapXmlStructItemToImage(const CARServerObject &serverObj)
	{
		switch (serverObj.GetServerObjectTypeXML())
		{
		case AR_STRUCT_ITEM_XML_SCHEMA:
			{
				const CARSchema &schema = static_cast<const CARSchema&>(serverObj);
				return GetSchemaImage(schema.GetCompound().schemaType);
			}
			break;
		case AR_STRUCT_ITEM_XML_ACTIVE_LINK: return ImageTag::ActiveLink;
		case AR_STRUCT_ITEM_XML_FILTER: return ImageTag::Filter;
		case AR_STRUCT_ITEM_XML_ESCALATION: return ImageTag::Escalation;
		case AR_STRUCT_ITEM_XML_CHAR_MENU: return ImageTag::Menu;
		case AR_STRUCT_ITEM_XML_CONTAINER:
			{
				const CARContainer &cnt = static_cast<const CARContainer&>(serverObj);
				return GetContainerImage(cnt.GetType());
			}
			break;
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_750
		case AR_STRUCT_ITEM_XML_IMAGE: return ImageTag::Image;
#endif
		case AR_STRUCT_ITEM_XML_USER: return ImageTag::User;
		case AR_STRUCT_ITEM_XML_GROUP: return ImageTag::Group;
		case AR_STRUCT_ITEM_XML_ROLE: return ImageTag::Role;
		default: return ImageTag::NoImage;
		}
	}

	unsigned int MapOverlayTypeToInternal(unsigned int overlayType)
	{
		switch (overlayType)
		{
		case AR_OVERLAY_OBJECT: return AR_OVERLAY_OBJECT;
		case AR_CUSTOM_OBJECT: return AR_CUSTOM_OBJECT;
		}
		return AR_ORIGINAL_OBJECT;
	}

	const char* MapOverlayTypeToImageName(unsigned int overlayType)
	{
		switch (overlayType)
		{
		case AR_OVERLAY_OBJECT: return "overlay.gif";
		case AR_CUSTOM_OBJECT: return "custom.gif";
		}
		return "";
	}

	// ################################################################
	// ## ImageTag class definition
	ImageTag::ImageTag(const CARServerObject &obj, int currentRootLevel)
	{
		rootLevel = currentRootLevel;
		imageId = MapXmlStructItemToImage(obj);
		imageOverlayType = MapOverlayTypeToInternal(obj.GetOverlayType());
	}

	ImageTag::ImageTag(OUTPUT::ImageTag::ImageEnum image, int currentRootLevel)
	{
		rootLevel = currentRootLevel;
		imageId = image;
		imageOverlayType = AR_ORIGINAL_OBJECT;
	}

	ostream& ImageTag::ToStream(std::ostream &strm) const
	{
		if (imageId != NoImage)
		{
			const char* imageSrc = GetImageName(imageId);
			const char* imageAlt = imageSrc;
			const char* imageBg  = NULL;

			ImageDimensions imageDim = GetImageDimensions(imageId);

			if (imageOverlayType > AR_ORIGINAL_OBJECT)
			{
				imageBg = imageSrc;
				imageSrc = MapOverlayTypeToImageName(imageOverlayType);
			}

			strm << "<img ";
			strm << "src=\"" << RootPath(rootLevel) << "img/" << imageSrc << "\" ";
			if (imageBg != NULL)
			{
				strm << "style=\"background:url(" << RootPath(rootLevel) << "img/" << imageBg << ")\" ";
			}
			strm << "width=\"" << imageDim.x << "\" height=\"" << imageDim.y << "\" alt=\"" << imageAlt << "\" />";
		}
		return strm;
	}

	ostream& operator <<(ostream &strm, OUTPUT::ImageTag::ImageEnum image)
	{
		ImageTag img(image, 0);
		return img.ToStream(strm);
	}

	ostream& operator <<(ostream &strm, const OUTPUT::ImageTag &image)
	{
		return image.ToStream(strm);
	}

	ImageTag::operator std::string() const
	{
		stringstream strm;
		ToStream(strm);
		return strm.str();
	}
}; // end namespace OUTPUT
