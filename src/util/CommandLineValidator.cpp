#include "stdafx.h"
#include "CommandLineValidator.h"
#include "../AppConfig.h"

using namespace TCLAP;

extern const string AppVersion;

CommandLineValidator::CommandLineValidator(int argc, char* argv[])
: cmd("ARInside -- http://arinside.org\n"
    "Copyright (C) 2014 Stefan Nerlich, LJ Longwing, John Luthgers\n"
		"This program comes with ABSOLUTELY NO WARRANTY, is free software, and you are welcome to "
		"redistribute it under certain conditions; see COPYING file for more details.", 
		' ', AppVersion),
	iniArg       ("i", "ini", "Application settings filename", true, "settings.ini", "string"),
	serverArg    ("s","server","ARSystem server",false,"","string"),
	loginArg     ("l", "login", "Login name", false, "", "string"),
	pwdArg       ("p", "pwd", "Password", false, "", "string"),
	tcpArg       ("t", "tcp", "Tcp port", false, 0, "int"),
	rpcArg       ("r", "rcp", "Rcp port", false, 0, "int"),
	outputFolder ("o", "output", "Output folder", false, "", "string"),
	slowArg      ("", "slow", "Uses slow object loading", false),
	verboseArg   ("v","verbose","Verbose Output",false)
#if ARINSIDE_TEST_SUPPORT
	,testModeArg ("","test", "", false)
#endif
{
	argumentCount = argc;
	argumentArray = argv;
	exitCode = 1;

	SetupCommandLine();
}

CommandLineValidator::~CommandLineValidator(void)
{
}

void CommandLineValidator::SetupCommandLine()
{
#if ARINSIDE_TEST_SUPPORT
	cmd.add(testModeArg);
#endif
	// add it in reverse order. the "--help" output lists the arguments from the last to the first added.
	cmd.add(verboseArg);
	cmd.add(slowArg);
	cmd.add(rpcArg);
	cmd.add(tcpArg);
	cmd.add(pwdArg);
	cmd.add(loginArg);
	cmd.add(outputFolder);
	cmd.add(serverArg);
	cmd.add(iniArg);
}

bool CommandLineValidator::Validate()
{
	try 
	{
		cmd.parse(argumentCount, argumentArray);
		
		// !! in case, turn on the global verbose mode now !!
		AppConfig::verboseMode = verboseArg.getValue();
	}
	catch (ArgException &e)
	{ 
		cerr << "error: " << e.error() << " for arg " << e.argId() << endl;
		return false;
	}
	catch(exception &e)
	{
		cerr << endl << "Unhandled execption in CommandLineValidator::Validate: " << e.what() << endl;
		return false;
	}
	exitCode = 0;
	return true;
}

int CommandLineValidator::GetExitCode() const
{
	return exitCode;
}

TCLAP::CmdLineInterface& CommandLineValidator::GetCmdLine()
{
	return cmd;
}

bool CommandLineValidator::isServerSet() const
{
	return serverArg.isSet();
}

bool CommandLineValidator::isOutputFolderSet() const
{
	return outputFolder.isSet();
}

bool CommandLineValidator::isUsernameSet() const
{
	return loginArg.isSet();
}

bool CommandLineValidator::isPasswordSet() const
{
	return pwdArg.isSet();
}

bool CommandLineValidator::isTcpPortSet() const
{
	return tcpArg.isSet();
}

bool CommandLineValidator::isRpcPortSet() const
{
	return rpcArg.isSet();
}

string CommandLineValidator::GetIniFilename()
{
	return iniArg.getValue();
}

string CommandLineValidator::GetServer()
{
	return serverArg.getValue();
}

string CommandLineValidator::GetOutputFolder()
{
	return outputFolder.getValue();
}

string CommandLineValidator::GetUsername()
{
	return loginArg.getValue();
}

string CommandLineValidator::GetPassword()
{
	return pwdArg.getValue();
}

int CommandLineValidator::GetTcpPort()
{
	return tcpArg.getValue();
}

int CommandLineValidator::GetRpcPort()
{
	return rpcArg.getValue();
}

bool CommandLineValidator::GetSlowObjectLoading()
{
	return slowArg.getValue();
}

#if ARINSIDE_TEST_SUPPORT
bool CommandLineValidator::GetTestMode()
{
	return testModeArg.getValue();
}
#endif
