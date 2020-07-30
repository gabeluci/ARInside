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

using namespace std;

/****
 * the following macro should be used instead of cout to show the output only 
 * in verbose mode. to make the macro available in a code file just make sure
 * you have included "ARInside.h".
 */ 
#define LOG if(AppConfig::verboseMode) cout

// forward declarations
class CommandLineValidator;

class AppConfig
{
public:
	AppConfig(void);
	~AppConfig(void);

	// global settings
	static bool verboseMode;

	// ARSystem data
	string userForm;
	string groupForm;
	string roleForm;
	string userQuery;
	string groupQuery;
	string roleQuery;
	int maxRetrieve;
	string overlayMode;
	bool slowObjectLoading;

	// Output and Layout configuration
	string companyName;
	string companyUrl;
	string targetFolder;
	bool fileMode;
	string objListXML;
	bool oldNaming;
	bool testMode;

	// BlackList
	string blackList;

	//Restrict ObjectLibrary
	bool bLoadServerInfoList;
	bool bLoadUserList;
	bool bLoadGroupList;
	bool bLoadRoleList;
	bool bUseUtf8;
	bool bCompactFolder;
	bool bGZCompression;
	bool bDeleteExistingFiles;
	bool bOverlaySupport;

	string serverName;
	string userName;
	string password;
	int tcpPort;
	int rpcPort;
	int apiTimeout;

	string runNotes;
	string argv_0;

public:
	void Validate(CommandLineValidator& cmdLine);
	void Dump();
private:
	void OverrideSettingsByCommandLine(CommandLineValidator& cmdLine);
};
