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
#include "ARServerObject.h"

class CAREscalation :
	public CARServerObject
{
public:
	CAREscalation();
	CAREscalation(int insideId);
	CAREscalation(const string& name);
	~CAREscalation(void);

	bool Exists() const;

	// implement functions inherited from CARObject
	string GetName();
	string GetName() const;
	string GetNameFirstChar();
	bool NameStandardFirstChar();

	// implement functions inherited from CARServerObject
	const char* GetHelpText() const;
	ARTimestamp GetTimestamp() const;
	const ARAccessNameType& GetOwner() const;
	const ARAccessNameType& GetLastChanged() const;
	const char* GetChangeDiary() const;

	// other filter data access functions
	const AREscalationTmStruct& GetTimeStruct() const;
	const ARWorkflowConnectStruct& GetSchemaList() const;
	unsigned int GetEnabled();
	const ARQualifierStruct& GetRunIf() const;
	const ARFilterActionList& GetIfActions() const;
	const ARFilterActionList& GetElseActions() const;
	const ARPropList& GetPropList() const;

	const string& GetAppRefName() const;
	void SetAppRefName(const string& appName);

	// some helpers
	string GetTimeCriteria();
	string GetExecuteOn();
	unsigned int GetPool(CARProplistHelper* propList = NULL) const;
	string GetPoolStr(CARProplistHelper* propList = NULL) const;

	// class type support
	int GetServerObjectTypeXML() const { return AR_STRUCT_ITEM_XML_ESCALATION; }
	bool IsClonable() const;
	CARServerObject* Clone() const;
};
