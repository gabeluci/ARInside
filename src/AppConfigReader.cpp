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
#include "AppConfigReader.h"
#include "AppException.h"
#include "ConfigFile.h"
#include "FileSystemUtil.h"

AppConfigReader::AppConfigReader(const std::string &filename)
: configFile(filename)
{
	settingsFoundCount = 0;
}

AppConfigReader::~AppConfigReader(void)
{
}

void AppConfigReader::LoadTo(AppConfig &appConfig)
{
	// reset settings-found count incase the LoadTo function is called multiple times
	settingsFoundCount = 0;

	if (!ConfigFileExistsAndIsReadable())
		ThrowNotFoundException();

	auto_ptr<ConfigFile> cfg(CreateConfigFileObject());

	if (cfg.get() == NULL)
		throw AppException("internal error, couldn't create ConfigFile object!", "CFG_OBJ_CREATE_FAILED", "configuration");

	MapConfigFileToAppConfig(*cfg, appConfig);

	if (settingsFoundCount == 0)
		ThrowInvalidConfigFileException();
}

bool AppConfigReader::ConfigFileExistsAndIsReadable()
{
	return FileSystemUtil::FileExistsAndReadable(configFile);
}

ConfigFile* AppConfigReader::CreateConfigFileObject()
{
	return new ConfigFile(configFile);
}

void AppConfigReader::MapConfigFileToAppConfig(ConfigFile &config, AppConfig& cfg)
{
	IncFound(config.readInto<string>(cfg.userForm, "UserForm", "User"));
	IncFound(config.readInto<string>(cfg.userQuery, "UserQuery", "1=1"));
	IncFound(config.readInto<string>(cfg.groupForm, "GroupForm", "Group"));
	IncFound(config.readInto<string>(cfg.groupQuery, "GroupQuery", "1=1"));
	IncFound(config.readInto<string>(cfg.roleForm, "RoleForm", "Roles"));
	IncFound(config.readInto<string>(cfg.roleQuery, "RoleQuery", "1=1"));
	IncFound(config.readInto<int>(cfg.maxRetrieve, "MaxRetrieve", 0));
	IncFound(config.readInto<string>(cfg.companyName, "CompanyName", ""));
	IncFound(config.readInto<string>(cfg.companyUrl, "CompanyUrl", ""));
	IncFound(config.readInto<string>(cfg.targetFolder, "TargetFolder", ""));
	IncFound(config.readInto<bool>(cfg.fileMode, "FileMode", false));
	IncFound(config.readInto<string>(cfg.objListXML, "ObjListXML", ""));
	IncFound(config.readInto<bool>(cfg.oldNaming, "OldNaming", false));
	IncFound(config.readInto<string>(cfg.blackList, "BlackList", ""));
	IncFound(config.readInto<bool>(cfg.bLoadServerInfoList, "LoadServerInfoList", true));
	IncFound(config.readInto<bool>(cfg.bLoadUserList, "LoadUserList", true));
	IncFound(config.readInto<bool>(cfg.bLoadGroupList, "LoadGroupList", true));
	IncFound(config.readInto<bool>(cfg.bLoadRoleList, "LoadRoleList", true));
	IncFound(config.readInto<bool>(cfg.bUseUtf8, "Utf-8", false));
	IncFound(config.readInto<bool>(cfg.bCompactFolder, "CompactFolder", false));
	IncFound(config.readInto<bool>(cfg.bGZCompression, "GZCompression", false));
	IncFound(config.readInto<bool>(cfg.bDeleteExistingFiles, "DeleteExistingFiles", false));
	IncFound(config.readInto<string>(cfg.runNotes, "RunNotes", ""));
	IncFound(config.readInto<string>(cfg.serverName, "ServerName", ""));
	IncFound(config.readInto<int>(cfg.tcpPort, "TCPPort", 0));
	IncFound(config.readInto<int>(cfg.rpcPort, "RPCPort", 0));
	IncFound(config.readInto<string>(cfg.userName, "Username", ""));
	IncFound(config.readInto<string>(cfg.password, "Password", ""));
	IncFound(config.readInto<int>(cfg.apiTimeout, "APITimeout", 0));
	IncFound(config.readInto<string>(cfg.overlayMode, "OverlayMode", "TRUE"));
}

void AppConfigReader::IncFound(bool wasFound)
{
	if (wasFound) settingsFoundCount++;
}

void AppConfigReader::ThrowNotFoundException()
{
	stringstream strm;
	strm << "File '" << configFile << "' not found.";
	throw(AppException(strm.str(), "CONFIG_FILE_MISSING", "configuration"));
}

void AppConfigReader::ThrowInvalidConfigFileException()
{
	stringstream strm;
	strm << "File '" << configFile << "' doesn't look like a valid configuration file!";
	throw(AppException(strm.str(), "CONFIG_FILE_INVALID", "configuration"));
}
