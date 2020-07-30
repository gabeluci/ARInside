//Copyright (C) 2010 John Luthgers | jls17
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
#pragma once

// forward declaration
class CARServerObject;
class CARDataObject;

class IFileStructure
{
public:

	/// returns the root level of the directory returned by GetPath
	virtual unsigned int GetRootLevel() const = 0;

	/// returns path of an active link detail page. It shouldnt end with a "/"
	virtual string GetPath() const = 0;

	/// returns only the file name of an active link detail page with the extension
	virtual string GetFileName() const = 0;
	
	/// returns path, file name and extension of a page
	virtual string GetFullFileName() const = 0;

	/// call this method when the object instance is no longer needed 
	virtual void Release() { delete this; }
};

////////////////////////////////////////////////////////////////////
// CPageParams
class CPageParams
{
	// This object holds the data to identify a specific page. It is needed as parameter 
	// to IFileNamingFactory::GetFileNameOf to create a page specific implementation of 
	// IFileStructure.
	// At the same time this is a helper-class arround the creation of IFileStructure
	// objects. During the instancation of the CPageParams-object a IFileStructure 
	// implementation is created as well. If a page could be found the Valid() function
	// returns true and thus the -> operator could be used to access the IFileStructure
	// derived object.
public:
	CPageParams(unsigned int page);
	CPageParams(unsigned int page, unsigned int uParam1);
	CPageParams(unsigned int page, unsigned int uParam1, unsigned int uParam2);
	CPageParams(unsigned int page, const CARServerObject* obj1);
	CPageParams(unsigned int page, unsigned int uParam1, const CARServerObject* obj1);
	CPageParams(const CPageParams& val, unsigned int page); // copy constructor with overridable page
	~CPageParams();

public:
	bool Valid() const;
	const IFileStructure* operator->() const;

	unsigned int page;
	unsigned int uint1;
	unsigned int uint2;
	const CARServerObject* obj1;

private:
	IFileStructure* file;
	void InitFile();
};

////////////////////////////////////////////////////////////////////
// Pages and their usage                                          //

// === PAGE_OVERVIEW ===
// CPageParams: uint1 = objType -- overview page for object type (except VUIs & CONTAINERS) --- objType = AR_STRUCT_ITEM_XML_*
// CPageParams: uint1 = objType, uint2 = cntType -- overview page for containers. --- objType = AR_STRUCT_ITEM_XML_CONTAINER, cntType = ARCON_*
// CPageParams: dataObjType = dataObj -- overview page for data objects -- see DATA_TYPE_* constants
// CPageParams: uint1 = AR_STRUCT_ITEM_XML_VUI, obj1 = schemaObj -- overview page for VUIs of specified schema -- obj1 = CARSchema*
const unsigned int PAGE_OVERVIEW = '*';

// === PAGE_OVERVIEW_LETTER & OTHER ===
// CPageParams: uint1 = objType -- overview page for specific letter and object type (except CONTAINERS) --- objType = AR_STRUCT_ITEM_XML_*
// CPageParams: uint1 = objType, uint2 = cntType -- overview page for containers. --- objType = AR_STRUCT_ITEM_XML_CONTAINER, cntType = ARCON_*
const unsigned int PAGE_OVERVIEW_LETTER_A = 'a';
const unsigned int PAGE_OVERVIEW_LETTER_Z = 'z';
const unsigned int PAGE_OVERVIEW_LETTER_0 = '0';
const unsigned int PAGE_OVERVIEW_LETTER_9 = '9';
const unsigned int PAGE_OVERVIEW_OTHER = '#';

const unsigned int PAGE_MAINHOME = 0;

// === PAGE_DETAILS ===
// CPageParams: obj1 = arServerObject -- detail page for object --- objType = AR_STRUCT_ITEM_XML_*
// CPageParams: data1 = dataObj --- dataObj (Group/User/Role)
const unsigned int PAGE_DETAILS = 1;


// === PAGE_ACTION_OVERVIEW ===
// CPageParams: uint1 = objType -- object specific action overview page (ALs, FLTs, ESCs) --- objType = AR_STRUCT_ITEM_XML_*
const unsigned int PAGE_ACTION_OVERVIEW = 2;

// === PAGE_ACTION_OBJLIST ===
// CPageParams: uint1 = objType, uint2 = actionType -- action page for ALs, FLTs & ESCs. --- objType = AR_STRUCT_ITEM_XML_*
const unsigned int PAGE_ACTION_OBJLIST = 3;

// === PAGE_SCHEMA_PERMISSIONS ===
// CPageParams: obj1 = schemaObj --- schemaObj = CARSchema
const unsigned int PAGE_SCHEMA_PERMISSIONS = 1000;

// === PAGE_SCHEMA_WORKFLOW ===
// CPageParams: obj1 = schemaObj --- schemaObj = CARSchema
const unsigned int PAGE_SCHEMA_WORKFLOW = 1001;

// === PAGE_SCHEMA_INDEXES ===
// CPageParams: obj1 = schemaObj --- schemaObj = CARSchema
const unsigned int PAGE_SCHEMA_INDEXES = 1002;

// === PAGE_SCHEMA_SORTLIST ===
// CPageParams: obj1 = schemaObj --- schemaObj = CARSchema
const unsigned int PAGE_SCHEMA_SORTLIST = 1003;

// === PAGE_SCHEMA_RESULTLIST ===
// CPageParams: obj1 = schemaObj --- schemaObj = CARSchema
const unsigned int PAGE_SCHEMA_RESULTLIST = 1004;

// === PAGE_SCHEMA_VUIS ===
// CPageParams: obj1 = schemaObj --- schemaObj = CARSchema
//const unsigned int PAGE_SCHEMA_VUIS = 1005; TOREMOVE: ==> use PAGE_OVERVIEW with AR_STRUCT_ITEM_XML_VUI instead

// === PAGE_SCHEMA_SUBADMINS ===
// CPageParams: obj1 = schemaObj --- schemaObj = CARSchema
const unsigned int PAGE_SCHEMA_SUBADMINS = 1006;

// === PAGE_SCHEMA_ACTIVELINKS ===
// CPageParams: obj1 = schemaObj --- schemaObj = CARSchema
const unsigned int PAGE_SCHEMA_ACTIVELINKS = 1007;

// === PAGE_SCHEMA_FILTERS ===
// CPageParams: obj1 = schemaObj --- schemaObj = CARSchema
const unsigned int PAGE_SCHEMA_FILTERS = 1008;

// === PAGE_SCHEMA_ESCALATIONS ===
// CPageParams: obj1 = schemaObj --- schemaObj = CARSchema
const unsigned int PAGE_SCHEMA_ESCALATIONS = 1009;

// === PAGE_SCHEMA_REGULAR ===
// CPageParams: none
const unsigned int PAGE_SCHEMA_REGULAR = 1010;

// === PAGE_SCHEMA_JOIN ===
// CPageParams: none
const unsigned int PAGE_SCHEMA_JOIN = 1011;

// === PAGE_SCHEMA_VIEW ===
// CPageParams: none
const unsigned int PAGE_SCHEMA_VIEW = 1012;

// === PAGE_SCHEMA_DIALOG ===
// CPageParams: none
const unsigned int PAGE_SCHEMA_DIALOG = 1013;

// === PAGE_SCHEMA_VENDOR ===
// CPageParams: none
const unsigned int PAGE_SCHEMA_VENDOR = 1014;

// === PAGE_SCHEMA_FIELDS_CSV ===
// CPageParams: obj1 = schemaObj (CARSchema)
const unsigned int PAGE_SCHEMA_FIELDS_CSV = 1015;

// === PAGE_SCHEMA_VUIFIELDS_CSV ===
// CPageParams: obj1 = vuiObj (CARVui*)
const unsigned int PAGE_SCHEMA_VUIFIELDS_CSV = 1016;

// === PAGE_SCHEMA_AUDIT ===
// CPageParams: none
const unsigned int PAGE_SCHEMA_AUDIT = 1017;

// === PAGE_SCHEMA_ARCHIVE ===
// CPageParams: none
const unsigned int PAGE_SCHEMA_ARCHIVE = 1018;

// === PAGE_GROUP_SCHEMA_LIST ===
// CPageParams: data1 = groupObj
const unsigned int PAGE_GROUP_SCHEMA_LIST = 1101;

// === PAGE_GROUP_FIELD_LIST ===
// CPageParams: data1 = groupObj
const unsigned int PAGE_GROUP_FIELD_LIST = 1102;

// === PAGE_GROUP_ACTIVELINK_LIST ===
// CPageParams: data1 = groupObj
const unsigned int PAGE_GROUP_ACTIVELINK_LIST = 1103;

// === PAGE_GROUP_USER_LIST ===
// CPageParams: data1 = groupObj
const unsigned int PAGE_GROUP_USER_LIST = 1104;

// === PAGE_GROUP_PACKLIST_LIST ===
// CPageParams: uint1 = sub-type --- data1 = groupObj
const unsigned int PAGE_GROUP_CONTAINER_LIST = 1105;

const unsigned int PAGE_ROLE_SCHEMA_LIST = 1201;          // CPageParams: obj1 = roleObj
const unsigned int PAGE_ROLE_FIELD_LIST = 1202;           // CPageParams: obj1 = roleObj
const unsigned int PAGE_ROLE_ACTIVELINK_LIST = 1203;      // CPageParams: obj1 = roleObj
const unsigned int PAGE_ROLE_CONTAINER_LIST = 1204;       // CPageParams: uParam1 = subType, obj1 = roleObj

// === PAGE_IMAGE_DATA ===
// a file holding the real image of this ARImage-Object
// CPageParams: obj1 = imageObj
const unsigned int PAGE_IMAGE_DATA = 1301;

const unsigned int PAGE_FILTER_ERRORHANDLERS = 1999;      // CPageParams: none
const unsigned int PAGE_MESSAGES = 2000;                  // CPageParams: none
const unsigned int PAGE_GLOBALFIELS = 2001;               // CPageParams: none
const unsigned int PAGE_SERVER_INFO = 2002;               // CPageParams: none
const unsigned int PAGE_NOTIFICATIONS = 2003;             // CPageParams: none

const unsigned int PAGE_VALIDATOR_MAIN = 2100;
const unsigned int PAGE_VALIDATOR_MISSING_FIELDS = 2101;
const unsigned int PAGE_VALIDATOR_MISSING_MENUS = 2102;
const unsigned int PAGE_VALIDATOR_FORM_GROUPS = 2103;
const unsigned int PAGE_VALIDATOR_FIELD_GROUPS = 2104;
const unsigned int PAGE_VALIDATOR_FIELD_GROUP_DETAILS = 2105;
const unsigned int PAGE_VALIDATOR_ACTIVELINKS_GROUPS = 2106;
const unsigned int PAGE_VALIDATOR_CONTAINER_GROUPS = 2107;

const unsigned int PAGE_ANALYZER_MAIN = 2200; // CPageParams: none
const unsigned int PAGE_ANALYZER_QBE_CHECK = 2201; // CPageParams: none

const unsigned int PAGE_CUSTOMWORKFLOW = 2300;            // CPageParams: none


///////////////////////////////////////////////////////////////////////////////
// the strategy interface
class IFileNamingFactory
{
public:
	/// this method is called during program initialization and should create the
	/// necessary structure of the output directory 
	virtual void InitStructure() = 0;
	
	/// returns a file naming object based on the specified params object. The page
	/// parameter is required and all other parameters are page-dependend.
	virtual IFileStructure* GetFileNameOf(CPageParams &params) = 0;
};

// use this function to select a strategy
void SetFileNamingStrategy(IFileNamingFactory* strat);

// This function initialized the strategy, mainly the folder structure. The
// appConfig variable of CARInside must be loaded before this function is
// called.
void InitFileNamingStrategy();

// This deletes the allocated memory of the strategy.
void DestroyFileNamingStrategy();


///////////////////////////////////////////////////////////////////////////////
// Templates & Macros 
