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
#include "AppConfig.h"
#include "FileSystemUtil.h"
#include "tclap/CmdLine.h"
#include "util/CommandLineValidator.h"
#include "output/WebUtil.h"

using namespace TCLAP;
using namespace OUTPUT;

bool AppConfig::verboseMode = false;

AppConfig::AppConfig(void)
{
	// ARSystem data
	userForm = "";
	groupForm = "";
	roleForm = "";
	userQuery = "";
	groupQuery = "";
	roleQuery = "";
	maxRetrieve = 0;
	overlayMode = "";
	slowObjectLoading = false;

	// Output and Layout configuration
	companyName = "";
	companyUrl = "";
	targetFolder = "";
	fileMode	= false;
	objListXML	= "";
	oldNaming = false;
	testMode = false;

	// BlackList
	blackList = "";

	//Restrict ObjectLibrary
	bLoadServerInfoList = true;
	bLoadUserList = true;
	bLoadGroupList = true;
	bLoadRoleList = true;
	bUseUtf8 = false;
	bOverlaySupport;

	serverName = "";
	userName = "";
	password = "";
	tcpPort = 0;
	rpcPort = 0;
	apiTimeout = 0;
	bCompactFolder = false;
	bDeleteExistingFiles = false;
	bGZCompression = false;

	//Notes to be displayed on home page
	runNotes = "";
	argv_0 = "";
}

AppConfig::~AppConfig(void)
{
}

void AppConfig::Validate(CommandLineValidator& cmdLine)
{
	OverrideSettingsByCommandLine(cmdLine);

	// special checks for server mode
	if (!fileMode) 
	{
		string missingArgs;
		unsigned int missingCount = 0;

		if (!fileMode && serverName.empty())
		{
			missingCount++;
			missingArgs = "server / ServerName";
		}
		if (userName.empty())
		{
			missingCount++;
			if (!missingArgs.empty()) missingArgs += ", ";
			missingArgs += "login / Username";
		}

		if (!missingArgs.empty())
		{
			string msg;
			StdOutput _output;
			msg = "Required argument(s) missing: " + missingArgs;
			
			cout << endl;
			CmdLineParseException parseErr(msg);
			_output.failure(cmdLine.GetCmdLine(), parseErr);
		}
	}

	// validate the path of the target folder
	if (targetFolder.empty())
	{
		cout << "[ERR] Target folder setting is missing or not setup correctly!" << endl;
		throw ExitException(1);
	}

	// Just in case someone has set "DeleteExistingFiles" on and specified the root of the file system.
	// For security reasons we disallow the root directory.
	string fullOutputPath = FileSystemUtil::GetRealPathName(targetFolder);
	if (CUtil::StrEndsWith(fullOutputPath, ":\\") || CUtil::StrEndsWith(fullOutputPath, ":/") || fullOutputPath == "/")
	{
		cout << "[ERR] The target directory points to the root of the device. This is not allowed!" << endl;
		throw ExitException(1);
	}

	// now configure the environment
#ifdef ARINSIDE_ENABLE_ZLIB_SUPPORT
	if (bGZCompression)
		CWebUtil::webpageFileExtension = CWebUtil::HtmlGZPageSuffix();
	else
#endif
		CWebUtil::webpageFileExtension = CWebUtil::HtmlPageSuffix();

	// later we can support configuring specific layer documentation
	if (overlayMode != "FALSE" && overlayMode != "TRUE")
	{
		overlayMode = "TRUE";
	}

	// should overlay support be disabled completely?
	if (overlayMode == "FALSE")
		bOverlaySupport = false;
	else
		bOverlaySupport = true;

}

void AppConfig::OverrideSettingsByCommandLine(CommandLineValidator& cmdLine)
{
	// override settings with values specified by the command line 
	if (cmdLine.isServerSet())
		serverName = cmdLine.GetServer();

	if (cmdLine.isOutputFolderSet())
		targetFolder = cmdLine.GetOutputFolder();

	if (cmdLine.isUsernameSet())
		userName = cmdLine.GetUsername();

	if (cmdLine.isPasswordSet())
		password = cmdLine.GetPassword();

	if (cmdLine.isTcpPortSet())
		tcpPort = cmdLine.GetTcpPort();

	if (cmdLine.isRpcPortSet())
		rpcPort = cmdLine.GetRpcPort();

	// the following settings are set by command line only 
	slowObjectLoading = cmdLine.GetSlowObjectLoading();

#if ARINSIDE_TEST_SUPPORT
	testMode = cmdLine.GetTestMode();
#endif
}

void AppConfig::Dump()
{
	cout << "UserForm: " << userForm << endl;		
	cout << "UserQuery: " << userQuery << endl;
	cout << "GroupForm: " << groupForm << endl;
	cout << "GroupQuery: " << groupQuery << endl;
	cout << "RoleForm: " << roleForm << endl;
	cout << "RoleQuery: " << roleQuery << endl;
	cout << "MaxRetrieve: " << maxRetrieve << endl;
	cout << "CompanyName: " << companyName << endl;
	cout << "CompanyUrl: " << companyUrl << endl;
	cout << "TargetFolder: " << targetFolder << endl;
	cout << "FileMode: " << fileMode << endl;
	cout << "ObjListXML: " << objListXML << endl;
	cout << "OldNaming: " << oldNaming << endl;
	cout << "BlackList: " << blackList << endl;
	cout << "LoadServerInfoList: " << bLoadServerInfoList << endl;
	cout << "LoadUserList: " << bLoadUserList << endl;
	cout << "LoadGroupList: " << bLoadGroupList << endl;
	cout << "LoadRoleList: " << bLoadRoleList << endl;
	cout << "Utf-8: " << bUseUtf8 << endl;
	cout << "CompactFolder: " << bCompactFolder << endl;
	cout << "GZCompression: " << bGZCompression << endl;
	cout << "DeleteExistingFiles: " << bDeleteExistingFiles << endl;
	cout << "OverlayMode: " << overlayMode << endl;
	cout << "RunNotes: " << runNotes << endl;
	cout << "APITimeout: " << apiTimeout << endl;
	cout << endl;
}

