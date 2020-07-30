//Copyright (C) 2009 John Luthgers | jls17
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
#include "ImageTag.h"
#include "NavigationPage.h"
#include "URLLink.h"
#include "WebUtil.h"
#include "../AppException.h"
#include "../ARInside.h"
#include "../gzstream.h"

using namespace OUTPUT;

void CNavigationPage::Write()
{
	// TODO: maybe add this page to IFileStructure?? or is a static file enough in this scenario??

	stringstream strmName;
	strmName << this->conf.targetFolder << "/" << CWebUtil::DocName(this->fileName);
	CARInside *pInside = CARInside::GetInstance();
	ImageTag docImage(ImageTag::Document, rootLevel);

	try
	{
		LOG << "Save file '" << strmName.str();

		ostream *outStream;
#ifdef ARINSIDE_ENABLE_ZLIB_SUPPORT
		if (pInside->appConfig.bGZCompression)
			outStream = new ogzstream(strmName.str().c_str(), ios::out);
		else 
#endif
			outStream = new ofstream(strmName.str().c_str(), ios::out);

		ostream &fout = *outStream;

		// header
		Header(fout);

		// content
		fout << "<li>";
			fout << URLLink("Forms", CPageParams(PAGE_OVERVIEW, AR_STRUCT_ITEM_XML_SCHEMA), ImageTag(ImageTag::Schema, rootLevel), rootLevel, URLLink::TARGET_MODE_PARENT);
		fout << "</li>";

		fout << "<li>";
			fout << URLLink("Active Links", CPageParams(PAGE_OVERVIEW, AR_STRUCT_ITEM_XML_ACTIVE_LINK), ImageTag(ImageTag::ActiveLink, rootLevel), rootLevel, URLLink::TARGET_MODE_PARENT);			
			fout << "<ul><li>" << URLLink("By Action", CPageParams(PAGE_ACTION_OVERVIEW, AR_STRUCT_ITEM_XML_ACTIVE_LINK), docImage, rootLevel, URLLink::TARGET_MODE_PARENT) << "</li></ul>";
		fout << "</li>";

		fout << "<li>";
			fout << URLLink("Filters", CPageParams(PAGE_OVERVIEW, AR_STRUCT_ITEM_XML_FILTER), ImageTag(ImageTag::Filter, rootLevel), rootLevel, URLLink::TARGET_MODE_PARENT);
			fout << "<ul>";
				fout << "<li>" << URLLink("By Action", CPageParams(PAGE_ACTION_OVERVIEW, AR_STRUCT_ITEM_XML_FILTER), docImage, rootLevel, URLLink::TARGET_MODE_PARENT) << "</li>";
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_710
				if (pInside->CompareServerVersion(7,1) >= 0)
				{
					fout << "<li>" << URLLink("Error Handler", CPageParams(PAGE_FILTER_ERRORHANDLERS), docImage, rootLevel, URLLink::TARGET_MODE_PARENT) << "</li>";
				}
#endif
			fout << "</ul>";
		fout << "</li>";

		fout << "<li>";
			fout << URLLink("Escalations", CPageParams(PAGE_OVERVIEW, AR_STRUCT_ITEM_XML_ESCALATION), ImageTag(ImageTag::Escalation, rootLevel), rootLevel, URLLink::TARGET_MODE_PARENT);
			fout << "<ul><li>" << URLLink("By Action", CPageParams(PAGE_ACTION_OVERVIEW, AR_STRUCT_ITEM_XML_ESCALATION), docImage, rootLevel, URLLink::TARGET_MODE_PARENT) << "</li></ul>";
		fout << "</li>";

		fout << "<li>" << URLLink("Menus"             , CPageParams(PAGE_OVERVIEW, AR_STRUCT_ITEM_XML_CHAR_MENU)                    , ImageTag(ImageTag::Menu, rootLevel)           , rootLevel, URLLink::TARGET_MODE_PARENT) << "</li>";
		fout << "<li>" << URLLink("Active Link Guides", CPageParams(PAGE_OVERVIEW, AR_STRUCT_ITEM_XML_CONTAINER, ARCON_GUIDE)       , ImageTag(ImageTag::ActiveLinkGuide, rootLevel), rootLevel, URLLink::TARGET_MODE_PARENT) << "</li>";
		fout << "<li>" << URLLink("Filter Guides"     , CPageParams(PAGE_OVERVIEW, AR_STRUCT_ITEM_XML_CONTAINER, ARCON_FILTER_GUIDE), ImageTag(ImageTag::FilterGuide, rootLevel)    , rootLevel, URLLink::TARGET_MODE_PARENT) << "</li>";
		fout << "<li>" << URLLink("Applications"      , CPageParams(PAGE_OVERVIEW, AR_STRUCT_ITEM_XML_CONTAINER, ARCON_APP)         , ImageTag(ImageTag::Application, rootLevel)    , rootLevel, URLLink::TARGET_MODE_PARENT) << "</li>";
		fout << "<li>" << URLLink("Packing Lists"     , CPageParams(PAGE_OVERVIEW, AR_STRUCT_ITEM_XML_CONTAINER, ARCON_PACK)        , ImageTag(ImageTag::PackingList, rootLevel)    , rootLevel, URLLink::TARGET_MODE_PARENT) << "</li>";
		fout << "<li>" << URLLink("Webservices"       , CPageParams(PAGE_OVERVIEW, AR_STRUCT_ITEM_XML_CONTAINER, ARCON_WEBSERVICE)  , ImageTag(ImageTag::Webservice, rootLevel)     , rootLevel, URLLink::TARGET_MODE_PARENT) << "</li>";
		fout << "<li>" << URLLink("Groups"            , CPageParams(PAGE_OVERVIEW, AR_STRUCT_ITEM_XML_GROUP)                        , ImageTag(ImageTag::Group, rootLevel)          , rootLevel, URLLink::TARGET_MODE_PARENT) << "</li>";
		fout << "<li>" << URLLink("Roles"             , CPageParams(PAGE_OVERVIEW, AR_STRUCT_ITEM_XML_ROLE)                         , ImageTag(ImageTag::Role, rootLevel)           , rootLevel, URLLink::TARGET_MODE_PARENT) << "</li>";
		fout << "<li>" << URLLink("Users"             , CPageParams(PAGE_OVERVIEW, AR_STRUCT_ITEM_XML_USER)                         , ImageTag(ImageTag::User, rootLevel)           , rootLevel, URLLink::TARGET_MODE_PARENT) << "</li>";

#if AR_CURRENT_API_VERSION >= AR_API_VERSION_750
		if (pInside->CompareServerVersion(7,5) >= 0)
		{
			fout << "<li>" << URLLink("Images", CPageParams(PAGE_OVERVIEW, AR_STRUCT_ITEM_XML_IMAGE), ImageTag(ImageTag::Image, rootLevel), rootLevel, URLLink::TARGET_MODE_PARENT) << "</li>";
		}
#endif

		fout << "<li>"; 
		  fout << ImageTag(ImageTag::Folder, rootLevel) << "Information:";
			fout << "<ul>";
			  fout << "<li>" << URLLink("Messages"          , CPageParams(PAGE_MESSAGES)      , docImage, rootLevel, URLLink::TARGET_MODE_PARENT) << "</li>";
				fout << "<li>" << URLLink("Notifications"     , CPageParams(PAGE_NOTIFICATIONS) , docImage, rootLevel, URLLink::TARGET_MODE_PARENT) << "</li>";
				fout << "<li>" << URLLink("Global&nbsp;Fields", CPageParams(PAGE_GLOBALFIELS)   , docImage, rootLevel, false, URLLink::TARGET_MODE_PARENT) << "</li>";
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_764
				if (pInside->CompareServerVersion(7,6,4) >= 0 || (pInside->appConfig.fileMode == true && pInside->CompareServerVersion(7,5) >= 0))
					fout << "<li>" << URLLink("Customizations"    , CPageParams(PAGE_CUSTOMWORKFLOW), docImage, rootLevel, URLLink::TARGET_MODE_PARENT) << "</li>";
#endif
				fout << "<li>" << URLLink("Validator"         , CPageParams(PAGE_VALIDATOR_MAIN), docImage, rootLevel, URLLink::TARGET_MODE_PARENT) << "</li>";
				fout << "<li>" << URLLink("Analyzer"          , CPageParams(PAGE_ANALYZER_MAIN) , docImage, rootLevel, URLLink::TARGET_MODE_PARENT) << "</li>";
			fout << "</ul>";
		fout << "</li>";

		// footer
		Footer(fout);

		outStream->flush();
		delete outStream;

		LOG << "' [OK]" << endl;
	}
	catch(exception& e)
	{		
		stringstream erStrm;
		erStrm << "Error saving file '" << strmName.str() << "' to disk. Error: " << e.what();
		throw(AppException(erStrm.str(), "undefined", "FileIo"));
	}
}

void CNavigationPage::Header(ostream &strm)
{
	strm << "<?xml version=\"1.0\" encoding=\"ISO-8859-1\" ?> " << endl;

	// TODO: dont know if the encoding would be the best choice .. 
	// one day the whole program should use unicode support
	strm << 
"<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \
\"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">\
<html xmlns=\"http://www.w3.org/1999/xhtml\" xml:lang=\"en\" lang=\"en\">\
<!-- saved from url=(0025)http://arinside.org/ -->\
<head>\
	<title>Navigation</title>\
		<meta name=\"description\" content=\"ARSystem Documentation\" />\
		<meta name=\"author\" content=\"Demo\" />\
		<meta http-equiv=\"CONTENT-LANGUAGE\" content=\"EN\" />\
		<meta name=\"ROBOTS\" content=\"INDEX, FOLLOW\" />\
		<meta http-equiv=\"content-type\" content=\"text/html; charset=ISO-8859-1\" />\
		<link rel=\"stylesheet\" type=\"text/css\" href=\"../img/style.css\" />\
	</head>\
	<body><ul>";
}

void CNavigationPage::Footer(ostream &strm)
{
	strm << "</ul></body></html>";
}
