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
#include "RootPath.h"
#include "URLLink.h"
#include "WebPage.h"
#include "WebUtil.h"
#include "../ARInside.h"
#include "../gzstream.h"
#include "webpage/HtmlReferenceListImpl.h"

using namespace OUTPUT;
using namespace OUTPUT::WebPage;

// newline template to avoid lots of flush calls in file output stream
// taken from http://kuhllib.com/2012/01/14/stop-excessive-use-of-stdendl/
template <typename cT, typename Traits>
std::basic_ostream<cT, Traits>& newline(std::basic_ostream<cT, Traits>& out) 
{ 
	return out << out.widen('\n'); 
}

extern int nFilesCreated;

// TODO: replace fileName parameter with CPageParams obj and use IFileStructure internal to get fileName, folder and dirLevel
CWebPage::CWebPage(const string &fileName, const string &title, int dirLevel, const AppConfig &appConfig)
: appConfig(appConfig)
{
	this->fileName = fileName;	
	this->title = title;
	this->rootLevel = dirLevel;
	this->htmlReferences = NULL;
}

CWebPage::~CWebPage(void)
{
	if (htmlReferences != NULL)
		delete htmlReferences;
}

void CWebPage::SetNavigation(const string &nav)
{
	navContent = nav;
}

void CWebPage::AddContent(const string &content)
{
	this->bodyContent.push_back(content);
}

void CWebPage::AddContentHead(const string &description, const string &rightInfo)
{
	AddContent("<div id='locLeft'>");
	AddContent(description);
	AddContent("</div><div id='locRight'>");
	AddContent(( !rightInfo.empty() ? rightInfo : "&nbsp;"));
	AddContent("</div>");
}

void CWebPage::PageHeader(ostream &strm)
{
	strm << "<?xml version=\"1.0\" ?>" << newline;
	strm << "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">" << newline;
	strm << "<html xmlns=\"http://www.w3.org/1999/xhtml\" xml:lang=\"en\" lang=\"en\">" << newline;
	strm << "<!-- saved from url=(0025)http://arinside.org/ -->" << newline;
	strm << "<head>" << newline;
	strm << "<title>" << title << "</title>" << newline;
	strm << "<meta http-equiv=\"content-language\" content=\"EN\" />" << newline;
	strm << "<meta http-equiv=\"content-type\" content=\"text/html; charset=ISO-8859-1\" />" << newline;
	strm << "<meta http-equiv=\"expires\" content=\"-1\" />" << newline;
	strm << "<meta name=\"author\" content=\"ARInside\" />" << newline;
	strm << "<script type='text/javascript'>var rootLevel=" << rootLevel << ";</script>" << newline;
	strm << GetReferenceManager() << newline;
	strm << "</head>" << newline;
}

void CWebPage::DynamicHeaderText(ostream &strm)
{
	strm << "<table>" << newline;
	strm << "<tr>" << newline;
	strm << "<td>" << URLLink("Main", PAGE_MAINHOME, ImageTag::Server, rootLevel) << "</td>" << newline;
	strm << "<td>" << " (Server: " << URLLink(appConfig.serverName, PAGE_SERVER_INFO, rootLevel) << "</td>" << newline;
	strm << "<td>" << "@" << "</td>" << newline;
	strm << "<td>" << "<a href=\"" << appConfig.companyUrl << "\" target=\"_blank\">" << appConfig.companyName << "</a>" << ")" << "</td>" << newline;
	strm << "</tr>" << newline;
	strm << "</table>" << newline;	
}

string CWebPage::CurrentDateTime()
{
	return CUtil::CurrentDateTimeToHTMLString();
}

void CWebPage::DynamicFooterText(ostream &strm)
{
	strm << "<table><tr>" << newline;
	strm << "<td>" << URLLink("Main", PAGE_MAINHOME, ImageTag::Next, rootLevel)<< "</td>" << newline;
	strm << "<td>&nbsp;</td>" << newline;
	strm << "<td>" << DirectURLLink(DirectURLLink::LinkToTop, rootLevel) << "</td>" << newline;
	strm << "<td>&nbsp;</td>" << newline;
#if ARINSIDE_TEST_SUPPORT
	if (appConfig.testMode)
		strm << "<td>&nbsp;</td>";
	else
#endif
		strm << "<td>(Page created " << CurrentDateTime() << " by <a href=\"http://arinside.org\" target=\"_blank\">ARInside v" << AppVersion <<"</a>)</td>";
	strm << "</tr></table>" << newline;
}

void CWebPage::ContentOpen(ostream &strm)
{
	strm << "<body>" << newline;
	strm << DirectURLLink::CreateTop << newline;
	strm << "<table class=\"TblMain\">" << newline;
	strm << "<tr><td class=\"TdMainHeader\" colspan=\"3\">" << newline;
	DynamicHeaderText(strm);
	strm << "</td></tr><tr><td class=\"TdMainMenu\">" << newline;
	if (!navContent.empty())
	{
		strm << "<div id=\"form_navigation\" class=\"form_navigation\">" << newline;
		strm << navContent << newline;
		strm << "</div>" << newline;
	}
	strm << "<iframe id=\"IFrameMenu\" src=\"" << RootPath(rootLevel) << "template/navigation." << CWebUtil::WebPageSuffix() << "\" name=\"Navigation\" frameborder=\"0\">" << newline;
	strm << "<p>IFrame not supported by this browser.</p></iframe></td><td class=\"TdMainContent\">" << newline;
}

void CWebPage::ContentClose(ostream &strm)
{
	strm << "</td>" << newline;
	strm << "<td></td>" << newline;	// TODO: this column isn't used at all. Remove it completely from the table.

	strm << "</tr><tr><td class=\"TdMainButtom\" colspan=\"3\">" << newline;
	DynamicFooterText(strm);
	strm << newline << "</td></tr></table></body></html>" << newline;
}



void CWebPage::WriteContent(ostream &strm)
{	
	PageHeader(strm);
	ContentOpen(strm);
	
	vector<string>::iterator curIt = bodyContent.begin();
	vector<string>::iterator endIt = bodyContent.end();
	for (; curIt != endIt; ++curIt)	strm << *curIt;

	ContentClose(strm);
}


int CWebPage::SaveInFolder(const string &path)
{
	int result = 0;

	stringstream strm;
	if(!path.empty())
		strm << this->appConfig.targetFolder << "/" << path << "/" << CWebUtil::DocName(this->fileName);
	else
		strm << this->appConfig.targetFolder << "/" << CWebUtil::DocName(this->fileName);

	try
	{
		string fileName = strm.str();
		LOG << "Save file '" << fileName;

		ostream *outStream;
#ifdef ARINSIDE_ENABLE_ZLIB_SUPPORT
		if (CARInside::GetInstance()->appConfig.bGZCompression)
			outStream = new ogzstream(fileName.c_str(), ios::out);
		else
#endif
			outStream = new ofstream(fileName.c_str(), ios::out);

		ostream &fout = *outStream;

		WriteContent(fout);

		fout.flush();
		delete outStream;

		LOG << "' [OK]" << endl;

		nFilesCreated++;
		result = 1;
	}
	catch(exception& e)
	{		
		stringstream erStrm;
		erStrm << "Error saving file '" << strm.str() << "' to disk. Error: " << e.what();
		throw(AppException(erStrm.str(), "undefined", "FileIo"));
	}

	return result;
}

void CWebPage::AddScriptReference(std::ostream &strm, const std::string &scriptPath)
{
	strm << "<script src=\"" << RootPath(rootLevel) << scriptPath << "\" type=\"text/javascript\"></script>" << newline;
}

void CWebPage::AddStyleSheetReference(std::ostream &strm, const std::string &cssPath)
{
	strm << "<link rel=\"stylesheet\" type=\"text/css\" href=\"" << RootPath(rootLevel) << cssPath << "\" />" << newline;
}

HtmlReferenceList& CWebPage::GetReferenceManager()
{
	if (htmlReferences == NULL)
	{
		htmlReferences = new HtmlReferenceListImpl(rootLevel);
		SetupDefaultReferences(*htmlReferences);
	}
	return *htmlReferences;
}

void CWebPage::SetupDefaultReferences(WebPage::HtmlReferenceList &inst)
{
	inst.AddStyleSheetReference("img/style.css");
	inst.AddStyleSheetReference("img/jquery-ui-custom.css");
	inst.AddScriptReference("img/sortscript.js");
	inst.AddScriptReference("img/tabscript.js");
	inst.AddScriptReference("img/jquery.js");
	inst.AddScriptReference("img/jquery-ui.js");
	inst.AddScriptReference("img/arshelper.js");
}
