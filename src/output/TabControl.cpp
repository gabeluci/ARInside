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

#include "stdafx.h"
#include "TabControl.h"

namespace OUTPUT
{
	CTabControl::CTabControl(void)
	{
	}

	CTabControl::~CTabControl(void)
	{
	}

	void CTabControl::AddTab(const std::string &name, const std::string &content)
	{
		m_Tabs.push_back(Tab(name, content, GetNextTabId()));
	}

	string CTabControl::GetNextTabId()
	{
		stringstream id;
		id << "tab-" << (m_Tabs.size() + 1);
		return id.str();
	}

	string CTabControl::ToXHtml()
	{
		stringstream strm;

		RenderTabInit(strm);
		strm << "<div id=\"MainObjectTabCtrl\">" << endl;
		RenderTabList(strm);
		RenderTabContent(strm);
		strm << "</div>" << endl;

		return strm.str();
	}

	void CTabControl::RenderTabList(ostream &strm)
	{
		TabList::iterator curIt = m_Tabs.begin();
		TabList::iterator endIt = m_Tabs.end();

		strm << "<ul>" << endl;
		for (; curIt != endIt; ++curIt)
		{
			strm << "<li><a href=\"#" << curIt->htmlId << "\">" << curIt->name << "</a></li>" << endl;
		}
		strm << "</ul>" << endl;
	}

	void CTabControl::RenderTabContent(ostream &strm)
	{
		TabList::iterator curIt = m_Tabs.begin();
		TabList::iterator endIt = m_Tabs.end();

		for (; curIt != endIt; ++curIt)
		{
			strm << "<div id=\"" << curIt->htmlId << "\">" << endl;
			strm << curIt->content << endl;
			strm << "</div>" << endl;
		}
	}

	void CTabControl::RenderTabInit(ostream &strm)
	{
		//strm << "<script src=\"" << CWebUtil::RootPath(rootLevel) << "schema_page.js" << "\" type=\"text/javascript\"></script>";
		//strm << "<script>$(function() {	$(\"#MainObjectTabCtrl\").tabs(); $(\"#MainObjectTabCtrl div\").addClass(\"inner-tab\"); });"
		//	"$('document').ready(function() { $.address.change(function(event){ $(\"#MainObjectTabCtrl\").tabs( \"select\" , window.location.hash )"
		//	"}); $(\"#MainObjectTabCtrl\").bind(\"tabsselect\", function(event, ui) { window.location.hash = ui.tab.hash; });});"
		//	"</script>" << endl;
	}
};
