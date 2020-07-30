#include "ARInsideTest.h"
#include "AppConfigReader.h"
#include "AppConfig.h"
#include "AppException.h"
#include "ConfigFile.h"

class TestAppConfigReader : public AppConfigReader
{
public:
	TestAppConfigReader(const std::string &filename) 
		: AppConfigReader(filename) 
	{ 
		fileExists = true; 
	}

	void setExist(bool value) { fileExists = value; }
	void setContent(const std::string &value) { cfgContent = value; }

private:
	bool fileExists;
	std::string cfgContent;

	virtual bool ConfigFileExistsAndIsReadable() { return fileExists; }

	virtual ConfigFile* CreateConfigFileObject() 
	{ 
		ConfigFile* cfgObj = new ConfigFile();
		istringstream strm; 
		strm.str(cfgContent);
		strm >> (*cfgObj);
		return cfgObj; 
	}
};

class AppConfigReaderTest : public ::testing::Test 
{
protected:
	AppConfigReaderTest() : cfgReader("mytest.file") { }
	TestAppConfigReader cfgReader;
	AppConfig myConfig;
};


TEST_F(AppConfigReaderTest, DISABLED_InvalidConfigurationFile)
{
	ASSERT_THROW(cfgReader.LoadTo(myConfig), AppException);
}

TEST_F(AppConfigReaderTest, CheckDefaults)
{
	cfgReader.setContent("ServerName = ");
	cfgReader.LoadTo(myConfig);

	ASSERT_EQ("", myConfig.serverName);
	ASSERT_EQ("", myConfig.userName);
	ASSERT_EQ("", myConfig.password);
	ASSERT_EQ(0, myConfig.tcpPort);
	ASSERT_EQ(0, myConfig.rpcPort);

	ASSERT_EQ("", myConfig.targetFolder);
	ASSERT_EQ(false, myConfig.fileMode);
	ASSERT_EQ("", myConfig.objListXML);
	ASSERT_EQ(false, myConfig.bUseUtf8);
	ASSERT_EQ("", myConfig.blackList);
	ASSERT_EQ(true, myConfig.bLoadServerInfoList);
	ASSERT_EQ(false, myConfig.bCompactFolder);
	ASSERT_EQ(false, myConfig.bGZCompression);
	ASSERT_EQ(false, myConfig.bDeleteExistingFiles);
	ASSERT_EQ(false, myConfig.oldNaming);
	ASSERT_EQ("TRUE", myConfig.overlayMode);

	ASSERT_EQ(true, myConfig.bLoadUserList);
	ASSERT_EQ("User", myConfig.userForm);
	ASSERT_EQ("1=1", myConfig.userQuery);

	ASSERT_EQ(true, myConfig.bLoadGroupList);
	ASSERT_EQ("Group", myConfig.groupForm);
	ASSERT_EQ("1=1", myConfig.groupQuery);

	ASSERT_EQ(true, myConfig.bLoadRoleList);
	ASSERT_EQ("Roles", myConfig.roleForm);
	ASSERT_EQ("1=1", myConfig.roleQuery);

	ASSERT_EQ("", myConfig.companyName);
	ASSERT_EQ("", myConfig.companyUrl);

	ASSERT_EQ("", myConfig.runNotes);
}

TEST_F(AppConfigReaderTest, DISABLED_MissingConfigFile)
{
	cfgReader.setExist(false);
	ASSERT_THROW(cfgReader.LoadTo(myConfig), AppException);
}

TEST_F(AppConfigReaderTest, CheckMappingForServerSettings)
{
	stringstream settings;
	settings << "ServerName = localhost" << endl;
	settings << "Username = Demo" << endl;
	settings << "Password = password" << endl;
	settings << "TCPPort = 4321" << endl;
	settings << "RPCPort = 390680" << endl;
	cfgReader.setContent(settings.str());
	cfgReader.LoadTo(myConfig);

	ASSERT_EQ("localhost", myConfig.serverName);
	ASSERT_EQ("Demo", myConfig.userName);
	ASSERT_EQ("password", myConfig.password);
	ASSERT_EQ(4321, myConfig.tcpPort);
	ASSERT_EQ(390680, myConfig.rpcPort);
}

TEST_F(AppConfigReaderTest, CheckMappingForApplicationSettings)
{
	stringstream settings;
	settings << "TargetFolder         = DefaultOutputFolder" << endl;
	settings << "FileMode             = TRUE" << endl;
	settings << "ObjListXML           = FilterList.xml" << endl;
	settings << "UTF-8                = TRUE" << endl;
	settings << "BlackList            = MyBlacklist" << endl;
	settings << "LoadServerInfoList   = FALSE" << endl;
	settings << "CompactFolder        = TRUE" << endl;
	settings << "GZCompression        = TRUE" << endl;
	settings << "DeleteExistingFiles  = TRUE" << endl;
	settings << "OldNaming            = TRUE" << endl;
	settings << "OverlayMode          = FALSE" << endl;
	cfgReader.setContent(settings.str());
	cfgReader.LoadTo(myConfig);

	ASSERT_EQ("DefaultOutputFolder", myConfig.targetFolder);
	ASSERT_EQ(true, myConfig.fileMode);
	ASSERT_EQ("FilterList.xml", myConfig.objListXML);
	ASSERT_EQ(false, myConfig.bUseUtf8);
	ASSERT_EQ("MyBlacklist", myConfig.blackList);
	ASSERT_EQ(false, myConfig.bLoadServerInfoList);
	ASSERT_EQ(true, myConfig.bCompactFolder);
	ASSERT_EQ(true, myConfig.bGZCompression);
	ASSERT_EQ(true, myConfig.bDeleteExistingFiles);
	ASSERT_EQ(true, myConfig.oldNaming);
	ASSERT_EQ("FALSE", myConfig.overlayMode);
};

TEST_F(AppConfigReaderTest, CheckMappingForDataRetrievalSettings)
{
	stringstream settings;
	settings << "LoadUserList         = FALSE" << endl;
	settings << "UserForm             = MyUserJoin" << endl;
	settings << "UserQuery            = '1'!=$NULL$" << endl;
	settings << "LoadGroupList        = FALSE" << endl;
	settings << "GroupForm            = MyGroupJoin" << endl;
	settings << "GroupQuery           = '1'!=$NULL$" << endl;
	settings << "LoadRoleList         = FALSE" << endl;
	settings << "RoleForm             = MyRolesJoin" << endl;
	settings << "RoleQuery            = '1'!=$NULL$" << endl;
	settings << "MaxRetrieve          = 0" << endl;
	cfgReader.setContent(settings.str());
	cfgReader.LoadTo(myConfig);

	ASSERT_EQ(false, myConfig.bLoadUserList);
	ASSERT_EQ("MyUserJoin", myConfig.userForm);
	ASSERT_EQ("'1'!=$NULL$", myConfig.userQuery);
	ASSERT_EQ(false, myConfig.bLoadGroupList);
	ASSERT_EQ("MyGroupJoin", myConfig.groupForm);
	ASSERT_EQ("'1'!=$NULL$", myConfig.groupQuery);
	ASSERT_EQ(false, myConfig.bLoadRoleList);
	ASSERT_EQ("MyRolesJoin", myConfig.roleForm);
	ASSERT_EQ("'1'!=$NULL$", myConfig.roleQuery);
}

TEST_F(AppConfigReaderTest, CheckMappingForOtherSettings)
{
	stringstream settings;
	settings << "CompanyName          = yourcompanyname" << endl;
	settings << "CompanyUrl           = http://companyurl.com" << endl;
	settings << "# Notes that will display on the main page" << endl;
	settings << "RunNotes             = test notes" << endl;
	cfgReader.setContent(settings.str());
	cfgReader.LoadTo(myConfig);

	ASSERT_EQ("yourcompanyname", myConfig.companyName);
	ASSERT_EQ("http://companyurl.com", myConfig.companyUrl);
	ASSERT_EQ("test notes", myConfig.runNotes);
}
