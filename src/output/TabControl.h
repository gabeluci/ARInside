//Copyright (C) 2012 John Luthgers | jls17
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

namespace OUTPUT
{
	class CTabControl
	{
	public:
		CTabControl(void);
		~CTabControl(void);

		void AddTab(const std::string &name, const std::string &content);
		std::string ToXHtml();

	private:
		class Tab
		{
		public:
			Tab() {}
			Tab(const std::string &name, const std::string content, const std::string &id) : name(name), content(content), htmlId(id) {}
		public:
			string name;
			string content;
			string htmlId;
		};

		typedef vector<Tab> TabList;
		TabList m_Tabs;

	private:
		std::string GetNextTabId();

		void RenderTabList(ostream &strm);
		void RenderTabContent(ostream &strm);
		void RenderTabInit(ostream &strm);
	};
};
