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

#include "ARApi.h"
#include "core/ARActiveLink.h"
#include "core/ARFilter.h"
#include "core/AREscalation.h"
#include "core/ARCharMenu.h"
#include "core/ARContainer.h"
#include "core/ARSchema.h"
#include "core/ARField.h"
#include "core/ARVui.h"
#include "core/AREnum.h"
#include "core/ARServerInfo.h"
#include "core/ARGlobalField.h"
#include "core/ARUser.h"
#include "core/ARGroup.h"
#include "core/ARRole.h"
#include "core/ARImage.h"
#include "output/WebPage.h"
#include "output/IFileStructure.h"
#include "util/BlackListItem.h"
#include "FileSystemUtil.h"
#include "AppConfig.h"
#include "util/RefItem.h"
#include "util/AppTimer.h"
#include "lists/ARSchemaList.h"
#include "lists/ARActiveLinkList.h"
#include "lists/ARFilterList.h"
#include "lists/AREscalationList.h"
#include "lists/ARContainerList.h"
#include "lists/ARMenuList.h"
#include "lists/ARImageList.h"
#include "lists/BlackList.h"
#include "lists/ARUserList.h"
#include "lists/ARGroupList.h"
#include "lists/ARRoleList.h"
#include "lists/ARServerInfoList.h"

extern const string AppVersion;

// forward declarations
class Context;
class LookupFormContext;

class CARInside
{
public:
	CARInside(AppConfig &appConfig);
public:
	~CARInside(void);

	ARControlStruct		arControl;
	AppConfig			appConfig;

	int					arXmlVersion;
	string				arServerVersion;
	int					vMajor;
	int					vMinor;
	int					vRevision;

	inline static CARInside* GetInstance() { return CARInside::pInsideInstance; }
	
	int Init(string user, string pw, string server, int port, int rpc);
	void DoWork(int nMode);
	int Terminate(void);

	bool FileExists(string fName);
	void LoadServerObjects(int nMode);
	void LoadFromServer(void);
	void LoadFromFile(void);
	void SetupOverlaySupport();

	bool InBlacklist(int refType, const string &objName) { 	return blackList.Contains(refType, objName.c_str()); }
	void Prepare(void);		
	void ExtractResources(void);
	void Documentation(void);


	string srvHostName;
	string srvFullHostName;
	int overlayMode;
	CARSchemaList schemaList;
	CARFilterList filterList;
	CAREscalationList escalationList;
	CARActiveLinkList alList;
	CARContainerList containerList;
	CARMenuList menuList;
	CARUserList userList;
	CARGroupList groupList;
	CARRoleList roleList;
	CARServerInfoList serverInfoList;

	list<CARGlobalField> globalFieldList;
	CBlackList blackList;
	map<string, vector<CRefItem> > missingMenuReferences;
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_750
	CARImageList	imageList;
#endif

	string LinkToServerInfo(const std::string &srvName, int rootLevel);
	string LinkToServerInfo(Context &context, const std::string &srvName);

	int SchemaGetInsideId(string searchObjName);

	string LinkToVui(int schemaInsideId, int vuiInsideId, int fromRootLevel);
	string LinkToField(const string& schemaName, int fieldInsideId, int fromRootLevel);	
	string LinkToField(int schemaInsideId, int fieldInsideId, const string& linkText, int fromRootLevel);
	string LinkToField(int schemaInsideId, int fieldInsideId, int fromRootLevel);
	string LinkToField(Context &context, int fieldInsideId);
	string LinkToField(LookupFormContext &context, int fuieldInsideId);
	string LinkToMenuField(int schemaInsideId, int fieldInsideId, int fromRootLevel);

	string LinkToContainer(string containerName, int rootLevel);
	string LinkToContainer(const CRefItem& refItem, int rootLevel);
	string LinkToAl(const string& alName, int rootLevel);
	string LinkToAl(int alInsideId, int rootLevel);
	string LinkToFilter(string filterName, int rootLevel);	
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_750
	string LinkToImage(unsigned int imageIndex, int rootLevel);
	string LinkToImage(const string &imageName, int rootLevel);
#endif
	string LinkToSchema(const string& schemaName, int fromRootLevel);
	string LinkToSchema(int insideId, int fromRootLevel);
	string LinkToSchema(int schemaInsideId, const string &nameToUseIfSchemaNotExists, int rootLevel);
	string LinkToSchemaIndex(string indexName, int schemaInsideId, int fromRootLevel);	
	string LinkToEscalation(const string& escalationName, int fromRootLevel);
	string LinkToEscalation(const CRefItem& refItem, int fromRootLevel);
	string LinkToUser(string loginName, int rootLevel);	
	string LinkToSchemaTypeList(int schemaType, int rootLevel);	
	string LinkToGroup(const string& appRefName, int permissionId, int rootLevel);
	string GetFieldEnumValue(int schemaInsideId, int fieldInsideId, int enumPosition);

	void AddFieldReference(int schemaId, int fieldId, const CRefItem& ref);
	void AddMenuReference(const string& menuName, const CRefItem& ref);

	string TextFindFields(const string &inText, const string &fieldSeparator, int schemaInsideId, int rootLevel, bool findKeywords, const CRefItem *refItem);
	string TextFindFields(Context &context, const string &inText, bool findKeywords, const CRefItem *refItem);
	string XMLFindFields(string inText, int schemaInsideId, int rootLevel, const CRefItem *refItem);

	bool FieldreferenceExists(int schemaInsideId, int fieldInsideId, const CRefItem &refItem);

	string ServerObjectHistory(CARServerObject *obj, int rootLevel, bool noTableDescription = false);
	string DataObjectHistory(CARDataObject *obj, int rootLevel);
	bool ValidateGroup(const string& appRefName, int permissionId);
	int CompareServerVersion(int major, int minor = -1, int revision = -1);

	float nDurationLoad;
	float nDurationDocumentation;
private:
	static CARInside*	pInsideInstance;
private:	
	int LoadActiveLinks(void);
	int LoadFilters(void);
	int LoadEscalations(void);
	int LoadCharMenus(void);
	int LoadContainer(void);
	int LoadForms(void);
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_750
	int LoadImages(void);
#endif

	void ParseVersionString(string version);
	void ParseVersionString(int xmlVersion);

	bool WriteHTAccess();
};
