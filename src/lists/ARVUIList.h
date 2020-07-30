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
//    along with ARInside.  If not, see <http://www.gnu.org/licenses/>.#pragma once
#pragma once
#include "../ARApi.h"
#include "../util/Uncopyable.h"
#include "ARListHelpers.h"
#include <assert.h>

///////////////////////////////////////////////////////////////////////////////
// CARFieldList - interface definition
class CARVUIList : Uncopyable
{
public:
	// no special constructor here ... but a virtual destructor to make sure the correct one is called
	virtual ~CARVUIList(void) { };

	// no loading here ... abstract class!

	// list functions
	virtual unsigned int GetCount() = 0;
	virtual int Find(unsigned int vuiId) = 0;
	virtual void Sort() = 0;

	virtual ARInternalId VUIGetId(unsigned int index) = 0;
	virtual const ARNameType& VUIGetName(unsigned int index) const = 0;
	virtual const ARLocaleType& VUIGetLocale(unsigned int index) const = 0;
	virtual int VUIGetType(unsigned int index) = 0;
	virtual const ARPropList& VUIGetDisplayProps(unsigned int index) const = 0;
	virtual const char* VUIGetHelptext(unsigned int index) const = 0;
	virtual const ARTimestamp& VUIGetTimestamp(unsigned int index) const = 0;
	virtual const ARAccessNameType& VUIGetOwner(unsigned int index) const = 0;
	virtual const ARAccessNameType& VUIGetModifiedBy(unsigned int index) const = 0;
	virtual const char* VUIGetChangeDiary(unsigned int index) const = 0;
	virtual const ARPropList& VUIGetPropList(unsigned int index) const = 0;
};

///////////////////////////////////////////////////////////////////////////////
// CARVUIListXML - vui list support for XML files
class CARVUIListXML : public CARVUIList
{
public:
	CARVUIListXML() { ARZeroMemory(&vuiList); }
	virtual ~CARVUIListXML(void) { }

	// loading...
	void FinishLoading();

	// list functions
	virtual unsigned int GetCount() { return vuiList.numItems; }
	virtual int Find(unsigned int vuiId);
	virtual void Sort();

	// data access
	virtual ARInternalId VUIGetId(unsigned int index) { return vuiList.vuiList[sortedList[index]].vuiId; }
	virtual const ARNameType& VUIGetName(unsigned int index) const { return vuiList.vuiList[sortedList[index]].vuiName; }
	virtual const ARLocaleType& VUIGetLocale(unsigned int index) const { return vuiList.vuiList[sortedList[index]].locale; }
	virtual int VUIGetType(unsigned int index) { return vuiList.vuiList[sortedList[index]].vuiType; }
	virtual const ARPropList& VUIGetDisplayProps(unsigned int index) const { return vuiList.vuiList[sortedList[index]].props; }
	virtual const char* VUIGetHelptext(unsigned int index) const { return vuiList.vuiList[sortedList[index]].helpText; }
	virtual const ARTimestamp& VUIGetTimestamp(unsigned int index) const { return vuiList.vuiList[sortedList[index]].timestamp; }
	virtual const ARAccessNameType& VUIGetOwner(unsigned int index) const { return vuiList.vuiList[sortedList[index]].owner; }
	virtual const ARAccessNameType& VUIGetModifiedBy(unsigned int index) const { return vuiList.vuiList[sortedList[index]].lastChanged; }
	virtual const char* VUIGetChangeDiary(unsigned int index) const { return vuiList.vuiList[sortedList[index]].changeDiary; }
	virtual const ARPropList& VUIGetPropList(unsigned int index) const;

	friend class CARSchemaList;
private:
	ARVuiInfoList vuiList;
	vector<unsigned int> sortedList;  // sorted by vui name
};

///////////////////////////////////////////////////////////////////////////////
// CARVUIListServer - vui list support for direct server access
class CARVUIListServer : public CARVUIList
{
public:
	CARVUIListServer(unsigned int schemaInsideId);
	virtual ~CARVUIListServer(void);

	// loading ...
	bool LoadFromServer();

	// list functions
	virtual unsigned int GetCount() { return names.numItems; }
	virtual int Find(unsigned int vuiId);
	virtual void Sort();

	// data access
	virtual ARInternalId VUIGetId(unsigned int index) { return ids.internalIdList[sortedList[index]]; }
	virtual const ARNameType& VUIGetName(unsigned int index) const { return names.nameList[sortedList[index]]; }
	virtual const ARLocaleType& VUIGetLocale(unsigned int index) const { return locales.localeList[sortedList[index]]; }
	virtual int VUIGetType(unsigned int index) { return types.intList[sortedList[index]]; }
	virtual const ARPropList& VUIGetDisplayProps(unsigned int index) const { return dispProps.propsList[sortedList[index]]; }
	virtual const char* VUIGetHelptext(unsigned int index) const { return helpTexts.stringList[sortedList[index]]; }
	virtual const ARTimestamp& VUIGetTimestamp(unsigned int index) const { return changedTimes.timestampList[sortedList[index]]; }
	virtual const ARAccessNameType& VUIGetOwner(unsigned int index) const { return owners.nameList[sortedList[index]]; }
	virtual const ARAccessNameType& VUIGetModifiedBy(unsigned int index) const { return changedUsers.nameList[sortedList[index]]; }
	virtual const char* VUIGetChangeDiary(unsigned int index) const { return changeDiary.stringList[sortedList[index]]; }
	virtual const ARPropList& VUIGetPropList(unsigned int index) const;

private:
	void Reserve(unsigned int amount);
	void SetNumItems(unsigned int amount);
	void BuildIndex();

private:
	unsigned int schemaId;
	
	ARInternalIdList ids;
	ARNameList names;
	ARLocaleList locales;
	ARUnsignedIntList types;
	ARPropListList dispProps;
	ARTextStringList helpTexts;
	ARTimestampList changedTimes;
	ARAccessNameList owners;
	ARAccessNameList changedUsers;
	ARTextStringList changeDiary;
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_763
	ARPropListList objProps;
#endif

	vector<unsigned int> sortedList;
};
