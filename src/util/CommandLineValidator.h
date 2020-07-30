#pragma once

#include <tclap/CmdLine.h>

class CommandLineValidator
{
public:
	CommandLineValidator(int argc, char* argv[]);
	~CommandLineValidator(void);

public:
	bool Validate();

	int GetExitCode() const;
	TCLAP::CmdLineInterface& GetCmdLine();

	bool isServerSet() const;
	bool isOutputFolderSet() const;
	bool isUsernameSet() const;
	bool isPasswordSet() const;
	bool isTcpPortSet() const;
	bool isRpcPortSet() const;

	std::string GetIniFilename();
	std::string GetServer();
	std::string GetOutputFolder();
	std::string GetUsername();
	std::string GetPassword();
	int GetTcpPort();
	int GetRpcPort();
	bool GetSlowObjectLoading();
#if ARINSIDE_TEST_SUPPORT
	bool GetTestMode();
#endif

private:
	int argumentCount;
	char** argumentArray;
	unsigned int exitCode;

private:
	TCLAP::CmdLine cmd;
	TCLAP::ValueArg<std::string> iniArg;
	TCLAP::ValueArg<std::string> serverArg;
	TCLAP::ValueArg<std::string> loginArg;
	TCLAP::ValueArg<std::string> pwdArg;
	TCLAP::ValueArg<int>         tcpArg;
	TCLAP::ValueArg<int>         rpcArg;
	TCLAP::ValueArg<std::string> outputFolder;
	TCLAP::SwitchArg             slowArg;
	TCLAP::SwitchArg             verboseArg;
#if ARINSIDE_TEST_SUPPORT
	TCLAP::SwitchArg             testModeArg;
#endif

private:
	void SetupCommandLine();
};
