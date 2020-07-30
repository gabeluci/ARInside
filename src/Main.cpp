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

#include "Main.h"
#include "AppConfigReader.h"
#include "AppException.h"
#include "ARInside.h"
#include "ConfigFile.h"
#include "FileSystemUtil.h"
#include "tclap/CmdLine.h"
#include "util/CommandLineValidator.h"

using namespace TCLAP;

// this variable counts all generated files and as such is defined globally and referenced in other files
// TODO: remote this global dependency
int nFilesCreated;

int CMain::Run(int argc, char* argv[])
{
	mTimer.StartTimer();
	int result = AR_RETURN_ERROR;

	OutputARInsideBanner();

	try
	{
		CommandLineValidator cmdLineValidator(argc, argv);
		if (!cmdLineValidator.Validate())
			return cmdLineValidator.GetExitCode();

		string settingsIni = cmdLineValidator.GetIniFilename();

		cout << endl << "Load application configuration settings: '" << settingsIni << "' " << endl;
		AppConfigReader reader(settingsIni);
		AppConfig appConfig;
		reader.LoadTo(appConfig);

		// validate throws exceptions if configuration isnt valid
		appConfig.Validate(cmdLineValidator);
		
		// store executable for later directory detection
		appConfig.argv_0 = argv[0];

		if (AppConfig::verboseMode)
			appConfig.Dump();
		
		//Delete existing files
		if(appConfig.bDeleteExistingFiles)
		{
			DoDeleteExistingFiles(appConfig.targetFolder);
		}

		//Create the target directory specified in the configuration files
		//TODO: CreateAppDirectory returns false if the directory already exists .. this should be changed so
		//      we can check if there is something going wrong and stop the process!!
		FileSystemUtil fsUtil(appConfig);		
		fsUtil.CreateAppDirectory();

		if(fsUtil.ValidateTargetDir(appConfig.targetFolder) == 0)
		{
			nFilesCreated = 0;

			if(appConfig.bCompactFolder) // Compact folder
			{
				FileSystemUtil::CompactFolder(appConfig.targetFolder);
			}

			if(!appConfig.fileMode)	//ServerMode
			{
				result = StartServerMode(appConfig);
			}
			else //FileMode
			{
				result = StartFileMode(appConfig);
			}
		}
		else
		{
			// TODO: ValidateTargetDir returns 0 on success. On error there is no information about the error
			// at all .. only "whoops, cant create directory" .. hell yes, and now? where is my glass sphere...
			cout << "Failed to create target directory: " << appConfig.targetFolder << endl;
			result = AR_RETURN_ERROR;
		}

		if(result == AR_RETURN_OK)
		{
			mTimer.EndTimer();
			float nTotalDuration = mTimer.GetDuration();

			cout << endl << nFilesCreated << " files created in " << nTotalDuration << " seconds." << endl;
			cout << "Documentation successfully saved. The application will now exit." << endl;
			result =  AR_RETURN_OK;
		}
		else
		{
			cout << "Application terminated." << endl;
		}

	}
	catch(AppException &e)
	{
		cout << endl << "AppException: " << e.typeDescription() << " -- " << e.error() << endl;	
	}
	catch (ArgException &e)
	{ 
		cerr << "error: " << e.error() << " for arg " << e.argId() << endl;
		return AR_RETURN_ERROR;
	}
	catch (ExitException &ee) 
	{
		exit(ee.getExitStatus());
	}
	catch(exception &e)
	{
		cout << endl << "Unhandled execption in _main: " << e.what() << endl;
	}

	return result;
}

const char* CMain::GetPlatformString() const
{
	char* platform;
	if (sizeof(platform) == 4)
		return "32bit";
	if (sizeof(platform) == 8)
		return "64bit";
	return "";
}

void CMain::OutputARInsideBanner()
{
	cout << "ARInside Version " << AppVersion << " " << GetPlatformString() << endl << endl;
}

int CMain::StartServerMode(AppConfig &appConfig)
{
	int result = AR_RETURN_ERROR;
	CARInside arInside(appConfig);
	if(arInside.Init(appConfig.userName, appConfig.password, appConfig.serverName, appConfig.tcpPort, appConfig.rpcPort) == AR_RETURN_OK)
	{
		arInside.DoWork(0);
		result = AR_RETURN_OK;
	}
	arInside.Terminate();
	return result;
}

int CMain::StartFileMode(AppConfig &appConfig)
{
	int result = AR_RETURN_ERROR;
	CARInside arInside(appConfig);

	if(!appConfig.objListXML.empty())
	{		
		if(arInside.FileExists(appConfig.objListXML) == true)
		{
			if(arInside.Init("", "", "", 0, 0) == AR_RETURN_OK)
			{
				arInside.DoWork(1);
				result = AR_RETURN_OK;
			}
		}
		else
		{
			cout << "Could not find file '" << appConfig.objListXML << "'" << endl;
			result = AR_RETURN_ERROR;
		}
	}
	else
	{
		cout << "No 'ObjListXML' file specified in the application configuration file!" << endl;
		result = AR_RETURN_ERROR;
	}

	arInside.Terminate();
	return result;
}

void CMain::DoDeleteExistingFiles(string path)
{
	cout << "Deleting existing files" << endl;
	if (!FileSystemUtil::DeleteDirectory(path.c_str()))
		cout << "Deletion failed!" << endl;			
}
