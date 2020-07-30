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
#include "ARInside.h"

#include "core/ChangeHistoryEntry.h"
#include "core/ARHandle.h"
#include "core/ARStatusList.h"

#include "doc/DocMain.h"
#include "doc/DocUserDetails.h"
#include "doc/DocGroupDetails.h"
#include "doc/DocSchemaDetails.h"
#include "doc/DocAlDetails.h"
#include "doc/DocFilterDetails.h"
#include "doc/DocEscalationDetails.h"
#include "doc/DocCharMenuDetails.h"
#include "doc/DocFieldDetails.h"
#include "doc/DocVuiDetails.h"
#include "doc/DocWebserviceDetails.h"
#include "doc/DocPacklistDetails.h"
#include "doc/DocApplicationDetails.h"
#include "doc/DocAlGuideDetails.h"
#include "doc/DocFilterGuideDetails.h"
#include "doc/DocContainerHelper.h"
#include "doc/DocAnalyzer.h"
#include "doc/DocValidator.h"
#include "doc/DocRoleDetails.h"
#include "doc/DocSummaryInfo.h"
#include "doc/DocImageDetails.h"
#include "doc/DocImageOverview.h"
#include "doc/DocCustomWorkflow.h"
#include "doc/DocTextReferences.h"

#include "output/ObjNotFound.h"
#include "output/ImageTag.h"
#include "output/Table.h"
#include "output/WebUtil.h"
#include "output/NavigationPage.h"

#include "output/IFileStructure.h"
#include "output/FileNaming.h"
#include "output/URLLink.h"

#include "scan/ScanMain.h"

#include "util/ResourceFileLocatorAndExtractor.h"
#include "util/Context.h"

/////////
// the following file is generated via a pre-build step using "svnrev_template.h" as template. 
// The $WCREV$ keyword of the template is replaced with the revision number.
#include "svnrev.h"

/////////
// version information block
#define VERSION "3.1.2"
#if defined(_DEBUG)
#define VERSION_STR VERSION "." SVN_REV_STR " Debug"
#elif defined(_ARINSIDE_BETA)
#define VERSION_STR VERSION "." SVN_REV_STR " Beta"
#else
#define VERSION_STR VERSION "." SVN_REV_STR
#endif
const string AppVersion = VERSION_STR;
/////////


using namespace OUTPUT;

// some kind of singleton pattern to keep compatibility
CARInside* CARInside::pInsideInstance = NULL;

CARInside::CARInside(AppConfig &appConfig)
{
	this->appConfig = appConfig;
	this->globalFieldList.clear();
	this->overlayMode = 1; // TODO: this is the default value for ars764. check for later versions

	this->nDurationLoad = 0;
	this->nDurationDocumentation = 0;

	this->vMajor = 0;
	this->vMinor = 0;
	this->vRevision = 0;
	this->arXmlVersion = 0;

	if (appConfig.oldNaming)
		SetFileNamingStrategy(new FileNaming::DefaultFileNamingStrategy());
	else
		SetFileNamingStrategy(new FileNaming::ObjectNameFileNamingStrategy());

	if (CARInside::pInsideInstance == NULL) 
		CARInside::pInsideInstance = this;

	ARZeroMemory(&emptyPropList); // init struct; see lists/ARListHelpers.h
}

CARInside::~CARInside(void)
{
	DestroyFileNamingStrategy();
}

int CARInside::Init(string user, string pw, string server, int port, int rpc)
{
	cout << endl << "Connecting to server " << server;
	if (port > 0) { cout << ":" << port; }
	cout << " ..." << endl;

	ARStatusList status;

	ARZeroMemory(&arControl);
	ARZeroMemory(&status);

	if(this->appConfig.bUseUtf8)
		strcpy(arControl.localeInfo.charSet, "UTF-8");

	strncpy(arControl.user, user.c_str(), AR_MAX_NAME_SIZE);
	arControl.user[AR_MAX_NAME_SIZE]='\0';
	strncpy(arControl.password, pw.c_str(), AR_MAX_PASSWORD_SIZE);
	arControl.password[AR_MAX_PASSWORD_SIZE]='\0';
	strncpy(arControl.server, server.c_str(), AR_MAX_SERVER_SIZE);
	arControl.server[AR_MAX_SERVER_SIZE]='\0';

	int nResult = ARInitialization(&this->arControl,&status);
	if (nResult != AR_RETURN_OK)
	{
		cout << "Initilization of ARAPI returned: " << nResult << " (" << CAREnum::ActiveLinkMessageType(nResult) << ")" << endl;
		cout << BuildMessageAndFreeStatus(status);
		return nResult;
	}

	if(server == "" && nResult == AR_RETURN_OK) // Filemode
	{
		return AR_RETURN_OK;
	}

	if ( nResult == AR_RETURN_OK)
	{
		if(port>0)
		{
			nResult = ARSetServerPort(&this->arControl, this->arControl.server, port, rpc, &status);
			if (nResult != AR_RETURN_OK)
			{
				throw(AppException(BuildMessageAndFreeStatus(status), "undefined", "ARSystem"));
			}
		}

		if(this->appConfig.apiTimeout > 120) // at least 120 seconds api timeout
		{
			ARValueStruct val; 
			for (unsigned int valId = AR_SESS_TIMEOUT_NORMAL; valId <= AR_SESS_TIMEOUT_XLONG; ++valId)
			{
				ARZeroMemory(&val);
				nResult = ARGetSessionConfiguration(&this->arControl, valId, &val, &status);

				// validate result
				if (nResult != AR_RETURN_OK) continue;	// ok, if this fails, dont bother .. next one
				if (val.dataType != AR_DATA_TYPE_INTEGER) continue;
				if (val.u.intVal > this->appConfig.apiTimeout) continue;

				// setup value
				val.dataType = AR_DATA_TYPE_INTEGER;
				val.u.intVal = this->appConfig.apiTimeout;

				// now configure session
				nResult = ARSetSessionConfiguration(&this->arControl, valId, &val, &status);
				if (nResult != AR_RETURN_OK)
				{
					cout << "Setting session timeout failed: " << BuildMessageAndFreeStatus(status);
				}
			}
		}

		if(nResult == AR_RETURN_OK)
		{
			ARBoolean isAdmin, isSubadmin, hasCustomize;
			nResult = ARVerifyUser(&this->arControl, &isAdmin, &isSubadmin, &hasCustomize, &status);
			
			if (nResult != AR_RETURN_OK)
			{
				throw(AppException(BuildMessageAndFreeStatus(status), "undefined", "ARSystem"));
			}
			FreeARStatusList(&status, false);

			serverInfoList.LoadAndGetValue(AR_SERVER_INFO_HOSTNAME, StoreTo(this->srvHostName));
			serverInfoList.LoadAndGetValue(AR_SERVER_INFO_FULL_HOSTNAME, StoreTo(this->srvFullHostName));
			serverInfoList.LoadAndGetValue(AR_SERVER_INFO_VERSION, StoreTo(this->arServerVersion));

			ParseVersionString(this->arServerVersion);

#if AR_CURRENT_API_VERSION >= AR_API_VERSION_764
			if (CompareServerVersion(7,6,4) >= 0)
				serverInfoList.LoadAndGetValue(AR_SERVER_INFO_OVERLAY_MODE, StoreTo(this->overlayMode));
#endif
			cout << "User '" << this->arControl.user <<"' connected to server " << srvFullHostName << endl;

			// the most ARGetMultiple... calls aren't supported below ARServer 6.3 so it's better to 
			// switch to slow object loadinig automatically
			if (CompareServerVersion(6,3) < 0)
				appConfig.slowObjectLoading = true;

			blackList.LoadFromServer(appConfig.blackList);
		}
	}

	FreeARStatusList(&status, false);
	return nResult;
}

int CARInside::Terminate(void)
{
	ARStatusList status;
	ARZeroMemory(&status);

	ARTermination(&this->arControl, &status);
	
	FreeARStatusList(&status, false);
	return 0;
}

bool CARInside::FileExists(string fName)
{
	bool result = FileSystemUtil::FileExistsAndReadable(fName);
	if (result)
		cout << fName << " exists" << endl;
	return result;
}


void CARInside::Prepare(void)
{	
	CDocMain *docMain = new CDocMain();

	if( docMain->Index() == 1)
	{
		InitFileNamingStrategy();
#ifdef ARINSIDE_ENABLE_ZLIB_SUPPORT
		if (appConfig.bGZCompression)
			WriteHTAccess();
#endif
	}

	delete docMain;
}

bool CARInside::FieldreferenceExists(int schemaInsideId, int fieldInsideId, const CRefItem &refItem)
{
	CARField fld(schemaInsideId, fieldInsideId);
	if (!fld.Exists()) return false;

	return fld.ReferenceExists(refItem);
}

void CARInside::LoadServerObjects(int nMode)
{
	CAppTimer mTimer;
	mTimer.StartTimer();

	if(nMode==1)
	{
		this->LoadFromFile();
	}
	else
	{
		this->LoadFromServer();
	}
	mTimer.EndTimer();
	this->nDurationLoad = mTimer.GetDuration();
}

void CARInside::LoadFromFile(void)
{
	try
	{
		cout << endl << "Loading objects from file '" << appConfig.objListXML << "'" << endl;

		ARStatusList status;
		ARZeroMemory(&status);

		ARXMLInputDoc xmlInputDoc;
		xmlInputDoc.docType = AR_XML_DOC_FILE_NAME;
		xmlInputDoc.u.fileName = (char*)appConfig.objListXML.c_str();

		ARXMLParsedStream parsedStream;
		ARStructItemList parsedObjects;
		unsigned int xmlDocVersion = 0;

		if(ARParseXMLDocument(&this->arControl, 
			&xmlInputDoc,
			NULL,
			&parsedStream,
			&parsedObjects,
			NULL,
			&status) == AR_RETURN_OK)
		{			
			cout << parsedObjects.numItems << " items loaded." << endl;

			unsigned int schemaCount = 0;
			unsigned int imagesCount = 0;
			unsigned int activelinkCount = 0;
			unsigned int filterCount = 0;
			unsigned int escalationCount = 0;
			unsigned int containerCount = 0;
			unsigned int menuCount = 0;

			for (unsigned int i=0; i < parsedObjects.numItems; ++i)
			{
				switch (parsedObjects.structItemList[i].type)
				{
				case AR_STRUCT_ITEM_XML_SCHEMA:
					++schemaCount;
					break;
				case AR_STRUCT_ITEM_XML_ACTIVE_LINK:
					++activelinkCount;
					break;
				case AR_STRUCT_ITEM_XML_FILTER:
					++filterCount;
					break;
				case AR_STRUCT_ITEM_XML_ESCALATION:
					++escalationCount;
					break;
				case AR_STRUCT_ITEM_XML_CONTAINER:
					++containerCount;
					break;
				case AR_STRUCT_ITEM_XML_CHAR_MENU:
					++menuCount;
					break;
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_750
				case AR_STRUCT_ITEM_XML_IMAGE:
					++imagesCount; 
					break;
#endif
				}
			}

			if (schemaCount > 0) schemaList.Reserve(schemaCount);
			if (activelinkCount > 0) alList.Reserve(activelinkCount);
			if (filterCount > 0) filterList.Reserve(filterCount);
			if (escalationCount > 0) escalationList.Reserve(escalationCount);
			if (containerCount > 0) containerList.Reserve(containerCount);
			if (menuCount > 0) menuList.Reserve(menuCount);
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_750
			if (imagesCount > 0) imageList.Reserve(imagesCount);
#endif

			for(unsigned int i=0; i< parsedObjects.numItems; i++)
			{
				switch(parsedObjects.structItemList[i].type)
				{						
				case AR_STRUCT_ITEM_XML_FILTER:
					{
						LOG << "Loading Filter: " << parsedObjects.structItemList[i].name; 

						int objInsideId = filterList.AddFilterFromXML(parsedStream, parsedObjects.structItemList[i].name, &xmlDocVersion);

						if (objInsideId > -1)
						{
							ParseVersionString(xmlDocVersion);
							LOG << " (InsideID: " << objInsideId << ") [OK]" << endl;
						}
					}
					break;
				case AR_STRUCT_ITEM_XML_SCHEMA:
					{
						LOG << "Loading Form: " << parsedObjects.structItemList[i].name;

						int objInsideId = schemaList.AddSchemaFromXML(parsedStream, parsedObjects.structItemList[i].name, &xmlDocVersion);

						if (objInsideId > -1)
						{
							ParseVersionString(xmlDocVersion);
							LOG << " (InsideID: " << objInsideId << ") [OK]" << endl;
						}
					}
					break;					
				case AR_STRUCT_ITEM_XML_ACTIVE_LINK:
					{
						LOG << "Loading ActiveLink: " << parsedObjects.structItemList[i].name; 

						int objInsideId = alList.AddActiveLinkFromXML(parsedStream, parsedObjects.structItemList[i].name, &xmlDocVersion);

						if (objInsideId > -1)
						{
							ParseVersionString(xmlDocVersion);
							LOG << " (InsideID: " << objInsideId << ") [OK]" << endl;
						}
					}
					break;
				case AR_STRUCT_ITEM_XML_CHAR_MENU:
					{
						LOG << "Loading CharMenu: " << parsedObjects.structItemList[i].name; 

						int objInsideId = menuList.AddMenuFromXML(parsedStream, parsedObjects.structItemList[i].name, &xmlDocVersion);

						if (objInsideId > -1)
						{
							ParseVersionString(xmlDocVersion);
							LOG << " (InsideID: " << objInsideId << ") [OK]" << endl;
						}
					}
					break;
				case AR_STRUCT_ITEM_XML_ESCALATION:
					{
						LOG << "Loading Escalation: " << parsedObjects.structItemList[i].name; 

						int objInsideId = escalationList.AddEscalationFromXML(parsedStream, parsedObjects.structItemList[i].name, &xmlDocVersion);

						if (objInsideId > -1)
						{
							ParseVersionString(xmlDocVersion);
							LOG << " (InsideID: " << objInsideId << ") [OK]" << endl;
						}
					}
					break;
				case AR_STRUCT_ITEM_XML_CONTAINER:
					{
						LOG << "Loading Container: " << parsedObjects.structItemList[i].name; 

						int objInsideId = containerList.AddContainerFromXML(parsedStream, parsedObjects.structItemList[i].name, &xmlDocVersion);

						if (objInsideId > -1)
						{
							ParseVersionString(xmlDocVersion);
							LOG << " (InsideID: " << objInsideId << ") [OK]" << endl;
						}
					}
					break;
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_750
				case AR_STRUCT_ITEM_XML_IMAGE:
					{
						LOG << "Loading Image: " << parsedObjects.structItemList[i].name;
						
						int imageInsideId = imageList.AddImageFromXML(parsedStream, parsedObjects.structItemList[i].name);
						
						// dont know why bmc has decided to remove the arDocVersion parameter from the
						// ARGetImageFromXML api call. Now in case the xml-file contains only images we 
						// dont have a version at all. So we set it to version 7.5 by default. if other
						// objects are present they will overwrite this version if it is a 7.5+ version.
						ParseVersionString(AR_XML_VERSION_750);

						if (imageInsideId > -1)
						{
							LOG << " (InsideID: " << imageInsideId << ") [OK]" << endl;
						}
					}
					break;
#endif
#if _DEBUG
				default:
					cout << "Unused object type: [" << parsedObjects.structItemList[i].type << "] " << parsedObjects.structItemList[i].name << endl;
					break;
#endif
				}	
			}		
			
			schemaList.Sort();
			alList.Sort();
			filterList.Sort();
			escalationList.Sort();
			containerList.Sort();
			menuList.Sort();
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_750
			imageList.Sort();
#endif
		}
		else
		{
			cout << "An error occured parsing the xml document '" << appConfig.objListXML << "'" << endl;
			cout << BuildMessageAndFreeStatus(status);
		}
		if (!arServerVersion.empty())
			cout << "server version: " << arServerVersion << endl;

		FreeARXMLParsedStream(&parsedStream, false);
		FreeARStatusList(&status, false);
	} 
	catch (...)
	{ 
		cerr << "EXCEPTION loading server objects from xml file." << endl; 
	}
}

void CARInside::LoadFromServer(void)
{
	cout << endl << "Loading objects from server '" << appConfig.serverName << "'" << endl;
	cout << "server version: " << arServerVersion << endl;

	if (appConfig.slowObjectLoading)
	{
		cout << "NOTE: Fast object loading disabled!" << endl;
	}

	//LoadServerInfoList	
	if(appConfig.bLoadServerInfoList)
	{
		cout << "Start loading Server Information:" << endl;
		serverInfoList.Load();
		cout << serverInfoList.GetCount() << " server settings loaded" << endl;
	}
	else
		cout << endl << "Loading Server Informations [SKIPPED]" << endl;

	//LoadUserList
	if(appConfig.bLoadUserList)
	{
		cout << endl << "Start loading Users:" << endl;		
		userList.LoadFromServer();
		cout << userList.GetCount() << " Users loaded" << endl;
	}
	else
		cout << endl << "Loading Users [SKIPPED]" << endl;


	//LoadGroupList
	if(appConfig.bLoadGroupList)
	{
		cout << endl << "Start loading Groups:" << endl;		
		groupList.LoadFromServer();
		cout << groupList.GetCount() << " Groups loaded" << endl;
	}
	else
		cout << endl << "Loading Groups [SKIPPED]" << endl;

	//LoadRoleList
	if(appConfig.bLoadRoleList)
	{
		cout << endl << "Start loading Roles:" << endl;		
		roleList.LoadFromServer();
		cout << (unsigned int)roleList.GetCount() << " Roles loaded" << endl;
	}
	else
		cout << endl << "Loading Roles [SKIPPED]" << endl;

	SetupOverlaySupport();

	//ActiveLinks		
	cout << endl << "Start loading Active Links:" << endl;
	int nResult = LoadActiveLinks();
	cout << nResult << " Active Links loaded" << endl;


	//Filters	
	cout << endl << "Start loading Filters:" << endl;
	nResult = LoadFilters();
	cout << nResult << " Filters loaded" << endl;

	//Container	
	cout << endl << "Start loading Containers:" << endl;
	nResult = LoadContainer();
	cout << nResult << " Containers loaded" << endl;

	//Escalations	
	cout << endl << "Start loading Escalations:" << endl;
	nResult = LoadEscalations();
	cout << nResult << " Escalations loaded" << endl;

	//CharMenus	
	cout << endl << "Start loading Menus:" << endl;
	nResult = LoadCharMenus();
	cout << nResult << " Menus loaded" << endl;

	//Images
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_750
	if (CompareServerVersion(7,5) >= 0)
	{
		cout << endl << "Start loading Images:" << endl;
		nResult = LoadImages();
		cout << nResult << " Images loaded" << endl;
	}
#endif

	//Load schemas
	cout << endl << "Start loading Forms:" << endl;
	nResult = LoadForms();
	cout << nResult << " Forms loaded" << endl << endl;
}

int CARInside::LoadForms()
{
	try
	{
		schemaList.LoadFromServer();
		schemaList.Sort();
	}
	catch(exception& e)
	{
		cout << "EXCEPTION loading Forms: " << e.what() << endl;
	}

	return schemaList.GetCount();
}

int CARInside::LoadContainer(void)
{
	try
	{
		containerList.LoadFromServer();
		containerList.Sort();		
	}
	catch(exception& e)
	{
		cout << "EXCEPTION loading Container: " << e.what() << endl;
	}

	return containerList.GetCount();
}

int CARInside::LoadCharMenus(void)
{
	try
	{
		menuList.LoadFromServer();
		menuList.Sort();
	}
	catch(exception& e)
	{
		cout << "EXCEPTION loading Menus: " << e.what() << endl;
	}

	return menuList.GetCount();
}

int CARInside::LoadEscalations(void)
{
	try
	{
		escalationList.LoadFromServer();
		escalationList.Sort();
	}
	catch(exception& e)
	{
		cout << "EXCEPTION loading Escalations: " << e.what() << endl;
	}

	return escalationList.GetCount();
}

int CARInside::LoadFilters(void)
{
	try
	{
		filterList.LoadFromServer();
		filterList.Sort();
	}
	catch(exception& e)
	{
		cout << "EXCEPTION loading Filters: " << e.what() << endl;
	}

	return filterList.GetCount();
}

int CARInside::LoadActiveLinks(void)
{
	try
	{
		alList.LoadFromServer();
		alList.Sort();
	}
	catch(exception& e)
	{
		cout << "EXCEPTION loading ActiveLinks: " << e.what() << endl;
	}
	return alList.GetCount();
}

void CARInside::Documentation(void)
{	
	CAppTimer mTimer;
	mTimer.StartTimer();

	string strValue = objectNameFirstCharLetters; // "abcdefghijklmnopqrstuvwxyz0123456789#";
	CDocMain *docMain = new CDocMain();

	//Server information
	docMain->ServerInfoList();

	CDocSummaryInfo indexSummary(*this, "");	// this is the object for the summary start page (it's written at the end of this function)

	//ContainerList
	indexSummary.alguideCount = docMain->ContainerList(ARCON_GUIDE, "ContainerList (ActiveLinkGuide)");
	indexSummary.applicationCount = docMain->ContainerList(ARCON_APP, "ContainerList (Application)");
	indexSummary.packlistCount = docMain->ContainerList(ARCON_PACK, "ContainerList (PackingList)");
	indexSummary.fltguideCount = docMain->ContainerList(ARCON_FILTER_GUIDE, "ContainerList (FilterGuide)");
	indexSummary.webserviceCount = docMain->ContainerList(ARCON_WEBSERVICE, "ContainerList (Webservice)");

	//Application Details
	int nTmpCnt = 1;

	//Create documentation here to fill objects applicationName reference information	
	cout << "Starting Container Documentation" << endl;

	unsigned int cntCount = this->containerList.GetCount();
	for ( unsigned int cntIndex = 0; cntIndex < cntCount; ++cntIndex )
	{
		CARContainer cont(cntIndex);

		switch(cont.GetType())
		{
		case ARCON_APP:
			{
				LOG << "Application [" << (cntIndex + 1) << "-" << cntCount << "] '" << cont.GetName() << "': ";
				CDocApplicationDetails appDetails(cont);
				appDetails.Documentation();
			}
			break;
		default:
			{
				// TODO: is this output really correct? All other container types are documented and LOGged within the next loop!
				LOG << "Container [" << (cntIndex + 1) << "-" << cntCount << "] '" << cont.GetName() << "' [OK]" << endl;
			}
			break;
		}

		nTmpCnt++;
	}

	unsigned int tmpCount = this->containerList.GetCount();
	for ( unsigned int cntIndex = 0; cntIndex < tmpCount; ++cntIndex )
	{
		CARContainer cont(cntIndex);
		switch(cont.GetType())
		{
		case ARCON_WEBSERVICE:
			{
				LOG << "Webservice [" << (cntIndex + 1) << "-" << tmpCount << "] '" << cont.GetName() << "': ";
				CDocWebserviceDetails wsDetails(cont);
				wsDetails.Documentation();
			}
			break;
		case ARCON_GUIDE:
			{
				LOG << "ActiveLinkGuide [" << (cntIndex + 1) << "-" << tmpCount << "] '" << cont.GetName() << "': ";
				CDocAlGuideDetails guideDetails(cont);
				guideDetails.Documentation();
			}
			break;
		case ARCON_FILTER_GUIDE:
			{
				LOG << "FilterGuide [" << (cntIndex + 1) << "-" << tmpCount << "] '" << cont.GetName() << "': ";
				CDocFilterGuideDetails fltGuideDetails(cont);
				fltGuideDetails.Documentation();
			}
			break;
		case ARCON_PACK:
			{
				LOG << "PackingList [" << (cntIndex + 1) << "-" << tmpCount << "] '" << cont.GetName() << "': ";
				CDocPacklistDetails packDetails(cont);
				packDetails.Documentation();
			}
			break;
		case ARCON_APP:
			{
				LOG << "Application [" << (cntIndex + 1) << "-" << tmpCount << "] '" << cont.GetName() << "' [OK]" << endl;
			}
			break;
		}

		nTmpCnt++;
	}


	//ActiveLink List
	indexSummary.activelinkCount = docMain->ActiveLinkList();
	docMain->ActiveLinkActionList();

	//ActiveLink Details
	tmpCount = alList.GetCount();
	cout << "Starting ActiveLink Documentation" << endl;
	for (unsigned int actlinkIndex = 0; actlinkIndex < tmpCount; ++actlinkIndex)
	{	
		LOG << "ActiveLink [" << actlinkIndex << "-" << tmpCount << "] '" << alList.ActiveLinkGetName(actlinkIndex) << "': ";
		CDocAlDetails alDetails(actlinkIndex);
		alDetails.Documentation();
	}


	//Filter List
	indexSummary.filterCount = docMain->FilterList();
	docMain->FilterActionList();
	docMain->FilterErrorHandlers();

	//Filter Details
	tmpCount = filterList.GetCount();
	cout << "Starting Filter Documentation" << endl;
	for (unsigned int filterIndex = 0; filterIndex < tmpCount; ++filterIndex)
	{
		LOG << "Filter [" << filterIndex << "-" << tmpCount << "] '" << filterList.FilterGetName(filterIndex) << "': ";
		CDocFilterDetails filterDetails(filterIndex);
		filterDetails.Documentation();
	}


	//Escalation List
	indexSummary.escalationCount = docMain->EscalationList();
	docMain->EscalationActionList();

	//Escalation Details
	tmpCount = escalationList.GetCount();
	cout << "Starting Escalation Documentation" << endl;
	for (unsigned int escalIndex = 0; escalIndex < tmpCount; ++escalIndex)
	{
		LOG << "Escalation [" << escalIndex << "-" << tmpCount << "] '" << escalationList.EscalationGetName(escalIndex) << "': ";
		CDocEscalationDetails escalDetails(escalIndex);
		escalDetails.Documentation();
	}


	//CharMenus
	indexSummary.menuCount = docMain->CharMenuList();

	// Char Menu Details
	tmpCount = menuList.GetCount();
	cout << "Starting Menu Documentation" << endl;
	for (unsigned int menuIndex = 0; menuIndex < tmpCount; ++menuIndex)
	{
		LOG << "Menu [" << menuIndex << "-" << tmpCount << "] '" << menuList.MenuGetName(menuIndex) << "': ";
		CDocCharMenuDetails menuDetails(menuIndex);
		menuDetails.Documentation();
	}


	//Schema List
	indexSummary.schemaCount = docMain->SchemaList();

	//Schema and field Details
	nTmpCnt=1;
	unsigned int schemaCount = schemaList.GetCount();
	cout << "Starting Schema Documentation" << endl;
	for (unsigned int schemaIndex = 0; schemaIndex < schemaCount; ++schemaIndex)
	{
		int rootLevel = 2;
		CARSchema schema(schemaIndex);

		LOG << "Schema [" << (schemaIndex + 1) << "-" << schemaCount << "] '" << schema.GetName() << "': ";
		CDocSchemaDetails *schemaDetails = new CDocSchemaDetails(schemaIndex, rootLevel);
		schemaDetails->Documentation();
		delete schemaDetails;


		//VuiDetails
		LOG << "VuiDetails Schema '" << schema.GetName() << "'" << endl;
		unsigned int objCount = schema.GetVUIs()->GetCount();
		for (unsigned int vuiIndex = 0; vuiIndex < objCount; ++vuiIndex)
		{
			CARVui vui(schema.GetInsideId(), 0, vuiIndex);

			LOG << "SchemaView '" << vui.GetName() << "' [" << (vuiIndex + 1) << "-" << objCount << "]: ";
			CDocVuiDetails *vuiDetails = new CDocVuiDetails(schema.GetInsideId(), vui, rootLevel);
			vuiDetails->Documentation();
			delete vuiDetails;
		}

		//FieldDetails
		LOG << "FieldDetails Schema '" << schema.GetName() << "'" << endl;		
		objCount = schema.GetFields()->GetCount();
		for (unsigned int fieldIndex = 0; fieldIndex < objCount; ++fieldIndex)
		{	
			CARField field(schema.GetInsideId(), 0, fieldIndex);

			LOG << "[" << (fieldIndex + 1) << "-" << objCount << "]: ";
			CDocFieldDetails *fieldDetails = new CDocFieldDetails(schema.GetInsideId(), field, rootLevel);
			fieldDetails->Documentation();
			delete fieldDetails;
		}

		nTmpCnt++;
	}

#if AR_CURRENT_API_VERSION >= AR_API_VERSION_750

	// Image
	{
		CDocImageOverview imageOverview;
		indexSummary.imageCount = imageOverview.Build();
	}

	// Image Details
	tmpCount = imageList.GetCount();
	cout << "Starting Image Documentation" << endl;
	for (unsigned int imgIndex = 0; imgIndex < tmpCount; ++imgIndex)
	{
		LOG << "Image [" << imgIndex << "-" << tmpCount << "] '" << imageList.ImageGetName(imgIndex) << "': ";

		CDocImageDetails imgDetails(imgIndex);
		imgDetails.Documentation();
	}
#endif

	//GlobalFieldList
	docMain->GlobalFieldList();	

	//MessageList
	docMain->MessageList();	

	//NotificationList
	docMain->NotificationList();

	//Analyzer
	CDocAnalyzer *analyzer = new CDocAnalyzer();
	analyzer->Documentation();
	delete analyzer;

	//Validation
	CDocValidator *validator = new CDocValidator();
	validator->Main();
	delete validator;

	{
		CDocCustomWorkflow customWF;
		customWF.Documentation();
	}


	//Group List
	docMain->GroupList();

	//Group Details
	cout << "Starting Group Documentation" << endl;

	tmpCount = groupList.GetCount();
	for (unsigned int groupIndex = 0; groupIndex < tmpCount; ++groupIndex)
	{
		CARGroup grp(groupIndex);

		LOG << "Group [" << (groupIndex + 1) << "-" << tmpCount << "] '" << grp.GetName() << "': ";
		CDocGroupDetails grpDetails(grp);
		grpDetails.Documentation();
	}


	//Role List
	docMain->RoleList();

	//Role Details
	cout << "Starting Role Documentation" << endl;

	tmpCount = roleList.GetCount();
	for (unsigned int roleIndex = 0; roleIndex < tmpCount; ++roleIndex)
	{
		CARRole role(roleIndex);

		LOG << "Role [" << (roleIndex + 1) << "-" << tmpCount << "] '" << role.GetName() << "': ";
		CDocRoleDetails roleDetails(role);
		roleDetails.Documentation();
	}


	// user count per first char
	vector<int> usrObjCount; usrObjCount.resize(38);

	//Userlists
	docMain->UserList("*", usrObjCount);
	for (unsigned int i = 0; i < strValue.size(); ++i)
	{		
		docMain->UserList(std::string(1, strValue.at(i)), usrObjCount);
	}	

	//User Details
	cout << "Starting User Documentation" << endl;

	tmpCount = userList.GetCount();
	for (unsigned int userIndex = 0; userIndex < tmpCount; ++userIndex)
	{
		CARUser user(userIndex);

		LOG << "User [" << (userIndex + 1) << "-" << tmpCount << "] '" << user.GetName() << "': ";
		
		CDocUserDetails userDetails(user);
		userDetails.Documentation();
	}

	mTimer.EndTimer();
	this->nDurationDocumentation = mTimer.GetDuration();

	indexSummary.Documentation();

	delete docMain;
}

string CARInside::GetFieldEnumValue(int schemaInsideId, int fieldInsideId, int enumPosition)
{
	CARField field(schemaInsideId, fieldInsideId);
	if (field.Exists())
	{
		if(field.GetDataType() == AR_DATA_TYPE_ENUM)
		{
			const ARFieldLimitStruct& limits = field.GetLimits();
			switch(limits.u.enumLimits.listStyle)
			{
			case AR_ENUM_STYLE_REGULAR:
				if (static_cast<unsigned int>(enumPosition) < limits.u.enumLimits.u.regularList.numItems)
					return limits.u.enumLimits.u.regularList.nameList[enumPosition];
				break;
			case AR_ENUM_STYLE_CUSTOM:
				for (unsigned int i=0; i < limits.u.enumLimits.u.customList.numItems; i++) { 
					if (limits.u.enumLimits.u.customList.enumItemList[i].itemNumber == enumPosition) 
						return limits.u.enumLimits.u.customList.enumItemList[i].itemName; 
				} 
				break;
			case AR_ENUM_STYLE_QUERY:
				return "QUERY";
			}						
		}
	}
	return "";
}

string CARInside::LinkToVui(int schemaInsideId, int vuiInsideId, int fromRootLevel)
{
	CARVui vui(schemaInsideId, vuiInsideId);
	if (vui.Exists())
	{
		return URLLink(vui, fromRootLevel);
	}
	return "";
}

string CARInside::LinkToField(const string& schemaName, int fieldInsideId, int fromRootLevel)
{	
	CARSchema schema(schemaName);
	return LinkToField(schema.GetInsideId(), fieldInsideId, fromRootLevel);
}

string CARInside::LinkToField(Context &context, int fieldInsideId)
{
	return LinkToField(context.getCurrentSchemaId(), fieldInsideId, context.getRootLevel());
}

string CARInside::LinkToField(LookupFormContext &lookupContext, int fieldInsideId)
{
	return LinkToField(lookupContext.getLookupSchemaId(), fieldInsideId, lookupContext.getRootLevel());
}

string CARInside::LinkToField(int schemaInsideId, int fieldInsideId, const string& linkText, int fromRootLevel)
{	
	CARField field(schemaInsideId, fieldInsideId);
	if (field.Exists())
	{
		return URLLink(linkText, field, fromRootLevel);
	}

	//Field has not been found
	stringstream tmp;

	if(fieldInsideId > 0 && schemaInsideId > -1) //OpenWindow uses 0 what is no valid field
	{
		ObjNotFound notFound(tmp);
		notFound << fieldInsideId;
		notFound.End();
	}
	else
	{
		tmp << fieldInsideId;
	}

	return tmp.str();
}

string CARInside::LinkToField(int schemaInsideId, int fieldInsideId, int fromRootLevel)
{
	return LinkToField(schemaInsideId, fieldInsideId, "", fromRootLevel);
}

// TODO: maybe change callers to LinkToField and remove this function completely
string CARInside::LinkToMenuField(int schemaInsideId, int fieldInsideId, int fromRootLevel)
{
	return LinkToField(schemaInsideId, fieldInsideId, fromRootLevel);
}

string CARInside::LinkToSchemaTypeList(int schemaType, int rootLevel)
{
	unsigned int page = PAGE_OVERVIEW;

	switch (schemaType)
	{
		case AR_SCHEMA_REGULAR: page = PAGE_SCHEMA_REGULAR; break;
		case AR_SCHEMA_JOIN: page = PAGE_SCHEMA_JOIN; break;
		case AR_SCHEMA_VIEW: page = PAGE_SCHEMA_VIEW; break;
		case AR_SCHEMA_DIALOG: page = PAGE_SCHEMA_DIALOG; break;
		case AR_SCHEMA_VENDOR: page = PAGE_SCHEMA_VENDOR; break;
		case AR_SCHEMA_AUDIT: page = PAGE_SCHEMA_AUDIT; break;
		case AR_SCHEMA_ARCHIVE: page = PAGE_SCHEMA_ARCHIVE; break;
	}

	return URLLink(CAREnum::SchemaType(schemaType), page, rootLevel);
}

// TODO: add a function with parameter CARSchema instead of schemaInsideId to pass in the object directly
string CARInside::LinkToSchemaIndex(string indexName, int schemaInsideId, int fromRootLevel)
{
	CARSchema schema(schemaInsideId);
	CPageParams file(PAGE_SCHEMA_INDEXES, &schema);
	return URLLink(indexName, file, fromRootLevel);
}

string CARInside::LinkToSchema(int insideId, int fromRootLevel)
{
	return LinkToSchema(insideId, EmptyValue, fromRootLevel);
}

string CARInside::LinkToSchema(const string& schemaName, int fromRootLevel)
{
	CARSchema schema(schemaName);
	if(schema.Exists())
	{
		return URLLink(schema, fromRootLevel);
	}
	return schemaName;
}

string CARInside::LinkToSchema(int schemaInsideId, const string &nameToUseIfSchemaNotExists, int fromRootLevel)
{
	CARSchema schema(schemaInsideId);
	if (schema.Exists())
	{
		return URLLink(schema, fromRootLevel);
	}
	return nameToUseIfSchemaNotExists;
}

int CARInside::SchemaGetInsideId(string searchObjName)
{
	CARSchema schema(searchObjName);
	if (schema.Exists())
	{
		return schema.GetInsideId();
	}
	return -1;
}

string CARInside::LinkToUser(string loginName, int rootLevel)
{
	CARUser user(loginName);

	if (user.Exists())
		return URLLink(loginName, CPageParams(PAGE_DETAILS, &user), rootLevel);

	return loginName;
}

bool CARInside::ValidateGroup(const string& appRefName, int permissionId)
{
	if(permissionId >= 0)
	{
		return true;
	}
	else
	{
		CARRole role(permissionId, appRefName);

		if (role.Exists())
		{
			return true;
		}
	}

	return false;
}

string CARInside::LinkToGroup(const string& appRefName, int permissionId, int rootLevel)
{	
	if(permissionId >= 0)
	{
		CARGroup group(-1, permissionId);
		if (group.Exists())
		{
			return URLLink(group, rootLevel);
		}		
	}
	else
	{
		if(!appRefName.empty())
		{
			CARRole role(permissionId, appRefName);

			if(role.Exists())
			{
				return URLLink(role, rootLevel);
			}
		}
	}

	stringstream strmTmp;
	strmTmp << permissionId;
	return strmTmp.str();
}

string CARInside::LinkToAl(const string& alName, int fromRootLevel)
{
	CARActiveLink al(alName);
	if (!al.Exists())
		return alName;

	return URLLink(al, fromRootLevel);
}

string CARInside::LinkToAl(int alInsideId, int rootLevel)
{
	CARActiveLink al(alInsideId);

	if (al.Exists())
		return URLLink(al, rootLevel);

	return EmptyValue;
}

string CARInside::LinkToFilter(string filterName, int fromRootLevel)
{
	if (filterName.empty()) return filterName;

	int fltInsideId = filterList.Find(filterName.c_str());
	if (fltInsideId > -1)
	{
		CARFilter flt(fltInsideId);
		return URLLink(flt, fromRootLevel);
	}
	return filterName;
}

string CARInside::LinkToEscalation(const string& escalationName, int fromRootLevel)
{
	CAREscalation escal(escalationName);
	if (escal.Exists())
	{
		return URLLink(escal, fromRootLevel);
	}
	return escalationName;
}

string CARInside::LinkToEscalation(const CRefItem& refItem, int fromRootLevel)
{
	CAREscalation escal(refItem.GetObjectId());
	if (escal.Exists())
	{
		return URLLink(escal, fromRootLevel);
	}
	return EmptyValue;
}

string CARInside::LinkToContainer(string containerName, int fromRootLevel)
{
	CARContainer cnt(containerName);
	if (cnt.Exists())
	{
		return URLLink(cnt, fromRootLevel);
	}
	return containerName;
}

string CARInside::LinkToContainer(const CRefItem& refItem, int rootLevel)
{
	CARContainer cnt(refItem.GetObjectId());
	if (cnt.Exists())
	{
		return URLLink(cnt, rootLevel);
	}
	return EmptyValue;
}

string CARInside::LinkToServerInfo(const std::string &srvName, int rootLevel)
{		
	string result;

	if(srvName.empty())
	{
		return URLLink(appConfig.serverName, PAGE_SERVER_INFO, rootLevel);
	}
	else if(srvName.compare(AR_CURRENT_SERVER_TAG)==0 || srvName.compare(AR_CURRENT_SCREEN_TAG)==0)
	{
		return URLLink(appConfig.serverName, PAGE_SERVER_INFO, rootLevel);
	}
	else
	{
		return URLLink(srvName, PAGE_SERVER_INFO, rootLevel);
	}

	return result;
}

string CARInside::LinkToServerInfo(Context &context, const std::string &srvName)
{
	return LinkToServerInfo(srvName, context.getRootLevel());
}

void CARInside::AddFieldReference(int schemaId, int fieldId, const CRefItem& ref)
{
	if (ref.GetMessageId() == -1) return; // if no message id is specified, dont create a reference

	CARHandle<> hObj(ref);
	if (appConfig.bOverlaySupport && hObj.Exists() && !IsVisibleObject(*hObj))
		return;

	CARSchema schema(schemaId);
	CARField fld(schemaId, fieldId);

	if (fld.Exists())
	{
		if (!fld.ReferenceExists(ref))
			fld.AddReference(ref);
	}
	else if (schema.Exists())
	{
		schema.AddMissingFieldReference(fieldId, ref);
	}
	// TODO: create a list of missing schemas
	//else
	//{
	//	LOG << "Missing Schema!" << endl;
	//}
}

void CARInside::AddMenuReference(const string& menuName, const CRefItem &ref)
{
	if (menuName == "$NULL$") return;

	CARCharMenu menu(menuName);

	if (menu.Exists())
	{
		// if the menu was found add the referece to it
		if (!menu.ReferenceExists(ref))
			menu.AddReference(ref);
	}
	else
	{
		// if the menu is missing, add the name to the missing menus map and append the reference to it
		if (missingMenuReferences.find(menuName) != missingMenuReferences.end())
		{
			missingMenuReferences.insert(pair<string, vector<CRefItem> >(menuName, vector<CRefItem>()));
		}

		CARCharMenu::ReferenceList::iterator curIt = missingMenuReferences[menuName].begin();
		CARCharMenu::ReferenceList::iterator endIt = missingMenuReferences[menuName].end();

		for (; curIt != endIt; ++curIt)
		{
			if (*curIt == ref)
				return;
		}

		missingMenuReferences[menuName].push_back(ref);
	}
}

string CARInside::TextFindFields(const string &inText, const string &fieldSeparator, int schemaInsideId, int rootLevel, bool findKeywords, const CRefItem *refItem)
{	
	CDocTextReferences textRefs(inText, fieldSeparator, schemaInsideId, rootLevel, findKeywords, refItem);
	return textRefs.TextFindFields();
}

string CARInside::TextFindFields(Context &context, const std::string &inText, bool findKeywords, const CRefItem *refItem)
{
	return TextFindFields(inText, "$", context.getCurrentSchemaId(), context.getRootLevel(), findKeywords, refItem);
}

string CARInside::XMLFindFields(string inText, int schemaInsideId, int rootLevel, const CRefItem *refItem)
{	
	try
	{
		if(inText.empty())
			return "";

		CARSchema schema(schemaInsideId);
		if (!schema.Exists())
			return inText;

		unsigned int fieldCount = schema.GetFields()->GetCount();
		for(unsigned int fieldIndex = 0; fieldIndex < fieldCount; ++fieldIndex)
		{
			CARField field(schemaInsideId, 0, fieldIndex);

			stringstream strmTmp;
			strmTmp << "arFieldId=&quot;" << field.GetFieldId() << "&quot;";			

			stringstream fieldLink;
			fieldLink << "arFieldId=&quot;" << URLLink(field, rootLevel) << "&quot;";					

			unsigned int nLengthOrg = (unsigned int)inText.length();

			string fField = strmTmp.str();
			inText = CUtil::StrReplace(fField, fieldLink.str(), inText);

			//if the string is longer because we have added a link (long string) we add a field reference
			if(inText.length() > nLengthOrg) 
			{
				AddFieldReference(schema.GetInsideId(), field.GetInsideId(), *refItem);
			}
		}
	}
	catch(exception& e)
	{
		cout << "EXCEPTION in XMLFindField: " << e.what() << endl;
	}

	return inText;
}

string CARInside::ServerObjectHistory(CARServerObject *obj, int rootLevel, bool noTableDescription)
{		
	stringstream strm;
	strm.str("");

	try
	{
		stringstream historyLog;
		if(obj->GetChangeDiary() != NULL)
		{				
			ARDiaryList diaryList; ARZeroMemory(&diaryList);
			ARStatusList status; ARZeroMemory(&status);
			if(ARDecodeDiary(&this->arControl, const_cast<char*>(obj->GetChangeDiary()), &diaryList, &status)==AR_RETURN_OK)
			{
				if(diaryList.numItems > 0)
				{
					for(unsigned int j=0; j<diaryList.numItems; j++)
					{
						historyLog << CUtil::DateTimeToHTMLString(diaryList.diaryList[j].timeVal) << " " << this->LinkToUser(diaryList.diaryList[j].user, rootLevel) << "<br/>" << endl;
						historyLog << diaryList.diaryList[j].value << "<br/><br/>" << endl;
					}
				}
				else
				{
					historyLog << EmptyValue << endl;
				}
			}
			FreeARDiaryList(&diaryList, false);
			FreeARStatusList(&status, false);
		}

		CTable tbl("history", "TblObjectHistory");
		tbl.AddColumn(20, "Description");
		tbl.AddColumn(80, "Value");

		if (!noTableDescription)
		{
			tbl.description = ImageTag(ImageTag::Document, rootLevel);
			tbl.description+= "Change History";
		}

		//Owner
		CTableRow tblRow("");
		tblRow.AddCellList(CTableCell("Owner"), CTableCell(this->LinkToUser(obj->GetOwner(), rootLevel)));
		tbl.AddRow(tblRow);

		//Last changed		
		stringstream strmLastChanged;
		strmLastChanged.str("");
		strmLastChanged << CUtil::DateTimeToHTMLString(obj->GetTimestamp()) << " " << this->LinkToUser(obj->GetLastChanged(), rootLevel) << endl;

		tblRow.AddCellList(CTableCell("Last changed"), CTableCell(strmLastChanged.str()));
		tbl.AddRow(tblRow);


		//History
		tblRow.AddCellList(CTableCell("History Log"), CTableCell(historyLog.str()));
		tbl.AddRow(tblRow);

		//Helptext
		string tmpHelptext;
		if(obj->GetHelpText() != NULL)
		{
			tmpHelptext = CUtil::StrReplace("\n", "<br/>", obj->GetHelpText());
		}
		else
		{
		  tmpHelptext = EmptyValue;
		}

		tblRow.AddCellList(CTableCell("Helptext"), CTableCell(tmpHelptext));
		tbl.AddRow(tblRow);

		strm << tbl;
	}
	catch(exception& e)
	{
		cout << "EXCEPTION writing server object history: " << e.what() << endl;
	}	

	return strm.str();
}

void CARInside::DoWork(int nMode)
{	
	// first step is to create directory structure
	Prepare();

	// now extract resources (images, css, js and so on)
	ExtractResources();

	// now load the object either from server or from file
	LoadServerObjects(nMode);

	// now create navigation page based on supported server features
	{ CNavigationPage navPage(appConfig); navPage.Write(); }

	// build needed reference tables
	CScanMain::BuildReferences();

	// write documentation
	Documentation();
}

void CARInside::ParseVersionString(string version)
{
	char ver[40];
	int part = 0;

	vMajor = 0;
	vMinor = 0;
	vRevision = 0;

	unsigned int verPos=0;
	unsigned int verStart=0;
	for (; verPos < version.size(); ++verPos)
	{
		char c = version.at(verPos);
		if (c >= '0' && c <= '9' ) 
		{
			ver[verPos] = c;
			continue;
		}
		if (verPos > verStart)
		{
			ver[verPos] = 0;
			int num = atoi(&ver[verStart]);
			switch (part)
			{
			case 0:
				vMajor = num;
				break;
			case 1:
				vMinor = num;
				break;
			case 2:
				vRevision = num;
				break;
			}
			++part;
			verStart = verPos + 1;
		}
		if (c != '.') break;
	}
	ver[verPos] = 0;
}

void CARInside::ParseVersionString(int xmlVersion)
{
	if (xmlVersion <= arXmlVersion) return;

	if (xmlVersion >= AR_XML_VERSION_750)
	{
		arServerVersion = "7.5.00";
		vMajor = 7; vMinor = 5; vRevision = 0;
	}
	else if (xmlVersion >= AR_XML_VERSION_710)
	{
		arServerVersion = "7.1.00";
		vMajor = 7; vMinor = 1; vRevision = 0;
	}
	else if (xmlVersion >= AR_XML_VERSION_700)
	{
		arServerVersion = "7.0.00";
		vMajor = 7; vMinor = 0; vRevision = 0;
	}
	else if (xmlVersion >= AR_XML_VERSION_600)
	{
		// 6.0 and 6.3 use the same export version number. To show keywords
		// and other things (in case of a 6.3 export file) correctly, the
		// version is set to 6.3
		arServerVersion = "6.03.00";
		vMajor = 6; vMinor = 3; vRevision = 0;
	}
	else if (xmlVersion >= AR_XML_VERSION_510)
	{
		arServerVersion = "5.1.00";
		vMajor = 5; vMinor = 1; vRevision = 0;
	}
	else if (xmlVersion >= AR_XML_VERSION_500)
	{
		arServerVersion = "5.0.00";
		vMajor = 5; vMinor = 0; vRevision = 0;
	}
	else if (xmlVersion >= AR_XML_VERSION_450)
	{
		arServerVersion = "4.5.00";
		vMajor = 4; vMinor = 5; vRevision = 0;
	}
}

int CARInside::CompareServerVersion(int major, int minor, int revision)
{
	if (vMajor == major)
	{
		if (minor > -1)
		{
			if (vMinor == minor)
			{
				if (revision > -1)
				{
					if (vRevision == revision) return 0;
					if (vRevision < revision) return -1;
					if (vRevision > revision) return 1;
				}
				return 0;
			}
			if (vMinor < minor) return -1;
			if (vMinor > minor) return 1;
		}
		return 0;
	}
	if (vMajor < major) return -1;
	/*if (vMajor > major)*/ return 1;
}

#if AR_CURRENT_API_VERSION >= AR_API_VERSION_750
int CARInside::LoadImages()
{
	imageList.LoadFromServer();
	imageList.Sort();
	return imageList.GetCount();
}

string CARInside::LinkToImage(unsigned int imageIndex, int rootLevel)
{
	CARImage image(imageIndex);
	if (image.Exists())
	{
		return URLLink(image, rootLevel);
	}
	return EmptyValue;
}

string CARInside::LinkToImage(const string &imageName, int rootLevel)
{
	int imageIndex = imageList.FindImage(imageName.c_str());
	if (imageIndex < 0)
	{
		stringstream strm;
		ObjNotFound notFound(strm);
		notFound << imageName;
		notFound.End();
		return strm.str();
	}
	else
	{
		return LinkToImage(imageIndex, rootLevel);
	}
}
#endif // AR_CURRENT_API_VERSION >= AR_API_VERSION_750

bool CARInside::WriteHTAccess()
{
	stringstream strm;
	strm << this->appConfig.targetFolder << "/" << ".htaccess";

	if (FileExists(strm.str()))
		return true;		// if file is already there, it should be configured correctly

	try
	{
		string fileName = strm.str();
		LOG << "Save file '" << fileName;

		ofstream fout(fileName.c_str(), ios::out);
		fout << "RemoveType .gz" << endl << "AddEncoding gzip .gz";
		fout.close();
	}
	catch (exception &e)
	{
		stringstream erStrm;
		erStrm << "Error saving file '" << strm.str() << "' to disk. Error: " << e.what();
		throw(AppException(erStrm.str(), "undefined", "FileIo"));
	}
	return true;
}

void CARInside::SetupOverlaySupport()
{
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_764
	if (CompareServerVersion(7,6,4) >= 0 && appConfig.bOverlaySupport)
	{
		ARStatusList status; ARZeroMemory(&status);
		ARValueStruct value;
		value.dataType = AR_DATA_TYPE_CHAR;
		value.u.charVal = (char*)AR_OVERLAY_CLIENT_MODE_FULL;
		if (ARSetSessionConfiguration(&arControl, AR_SESS_CONTROL_PROP_API_OVERLAYGROUP, &value, &status) != AR_RETURN_OK)
			cerr << "SetSessionConfiguration failed: " << BuildMessageAndFreeStatus(status);
	}
#endif
}

void CARInside::ExtractResources()
{
	try
	{
		ResourceFileLocatorAndExtractor resExtractor("arires.tgz");
		resExtractor.ExtractTo(appConfig.targetFolder);
	}
	catch (std::exception &ex)
	{
		cerr << "Error while extracting resources: " << ex.what() << endl;
	}
}
