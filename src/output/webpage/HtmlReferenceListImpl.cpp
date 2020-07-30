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
#include "HtmlReferenceListImpl.h"
#include "../RootPath.h"
#include "../WebUtil.h"

using namespace OUTPUT;
using namespace OUTPUT::WebPage;

HtmlReferenceListImpl::HtmlReferenceListImpl(int rootLevel)
: rootLevel(rootLevel)
{
}

HtmlReferenceListImpl::~HtmlReferenceListImpl(void)
{
}

HtmlReferenceList& HtmlReferenceListImpl::AddScriptReference(const std::string &scriptPath)
{
	jsReferences.push_back(scriptPath);
	return *this;
}

HtmlReferenceList& HtmlReferenceListImpl::AddStyleSheetReference(const std::string &cssPath)
{
	cssReferences.push_back(cssPath);
	return *this;
}

void HtmlReferenceListImpl::ToStream(std::ostream &output) const
{
	vector<string>::const_iterator curIt = cssReferences.begin();
	vector<string>::const_iterator endIt = cssReferences.end();
	for (; curIt != endIt; ++curIt)
	{
		WriteCSSReference(output, *curIt);
	}

	curIt = jsReferences.begin();
	endIt = jsReferences.end();
	for (; curIt != endIt; ++curIt)
	{
		WriteJSReference(output, *curIt);
	}
}

void HtmlReferenceListImpl::WriteCSSReference(std::ostream &output, const std::string &cssPath) const
{
	output << "<link rel=\"stylesheet\" type=\"text/css\" href=\"" << RootPath(rootLevel) << cssPath << "\" />" << endl;
}

void HtmlReferenceListImpl::WriteJSReference(std::ostream &output, const std::string &scriptPath) const
{
	output << "<script src=\"" << RootPath(rootLevel) << scriptPath << "\" type=\"text/javascript\"></script>" << endl;
}
