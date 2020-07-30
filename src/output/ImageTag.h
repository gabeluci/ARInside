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

#pragma once

class CARServerObject;

namespace OUTPUT
{
	class ImageTag 
	{
	public:
		enum ImageEnum
		{
			NoImage = 0,
			Schema = 1,
			SchemaRegular = 1,
			SchemaJoin,
			SchemaView,
			SchemaDialog,
			SchemaVendor,
			Server,
			Document,
			Folder,
			ActiveLink,
			Filter,
			Escalation,
			Menu,
			ActiveLinkGuide,
			FilterGuide,
			Application,
			PackingList,
			Webservice,
			Image,
			User,
			Group,
			Role,
			Hidden,
			Visible,
			Edit,
			Next,
			SortAsc,
			SortDesc,
			Up,
			Down,
		};

		// constructors
		ImageTag(const CARServerObject &obj, int rootLevel);
		ImageTag(ImageEnum image, int rootLevel);

		std::ostream& ToStream(std::ostream &strm) const;

		operator string() const;
	private:
		int rootLevel;
		ImageEnum imageId;
		unsigned int imageOverlayType;
	};

	std::ostream& operator<<(std::ostream& strm, OUTPUT::ImageTag::ImageEnum image);
	std::ostream& operator<<(std::ostream& strm, const OUTPUT::ImageTag &image);
};
