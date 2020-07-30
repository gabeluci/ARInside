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
#include "../AppConfig.h"
#include "../AppException.h"
#include "webpage/HtmlReferenceList.h"

namespace OUTPUT
{

	class CWebPage
	{
	public:
		CWebPage(const string &fileName, const string &title, int dirLevel, const AppConfig &appConfig);
		~CWebPage(void);

		void AddContent(const string &content);	
		void AddContentHead(const string &description) { AddContentHead(description, ""); }
		void AddContentHead(const string &description, const string &rightInfo);
		void SetNavigation(const string &nav);

		int SaveInFolder(const string &path);

		WebPage::HtmlReferenceList& GetReferenceManager();

	private:
		vector<string> bodyContent;
		string navContent;
		string fileName;
		string title;
		int rootLevel;

		const AppConfig &appConfig;
		WebPage::HtmlReferenceList *htmlReferences;
		
		void WriteContent(ostream &strm);

		void PageHeader(ostream &strm);
		void ContentOpen(ostream &strm);
		void ContentClose(ostream &strm);
		void DynamicHeaderText(ostream &strm);
		void DynamicFooterText(ostream &strm);
		string CurrentDateTime();

		void SetupDefaultReferences(WebPage::HtmlReferenceList &inst);

		void AddScriptReference(ostream &strm, const std::string &scriptPath);
		void AddStyleSheetReference(std::ostream &strm, const std::string &cssPath);
	};
}
