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
#include "HtmlReferenceList.h"

namespace OUTPUT { namespace WebPage {

	class HtmlReferenceListImpl :	public OUTPUT::WebPage::HtmlReferenceList
	{
	public:
		HtmlReferenceListImpl(int rootLevel);
		virtual ~HtmlReferenceListImpl(void);

		virtual HtmlReferenceList& AddScriptReference(const std::string &scriptPath);
		virtual HtmlReferenceList& AddStyleSheetReference(const std::string &cssPath);

	protected:
		virtual void ToStream(std::ostream &output) const;
		void WriteCSSReference(std::ostream &output, const std::string &cssPath) const;
		void WriteJSReference(std::ostream &output, const std::string &scriptPath) const;

	private:
		int rootLevel;
		vector<string> jsReferences;
		vector<string> cssReferences;
	};

}}; // end of namespace OUTPUT::WebPage
