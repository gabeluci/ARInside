//Copyright (C) 2014 John Luthgers | jls17
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

#include "../ARInside.h"

class Context
{
public:
	Context(CARServerObject &obj, IfElseState ifOrElseAction, int actionIndexPos, int currentWfSchemaId, int theRootLevel)
		: object(obj)
	{
		ifElse = ifOrElseAction;
		actionIndex = actionIndexPos;
		currentSchemaId = currentWfSchemaId;
		rootLevel = theRootLevel;
	}

public:
	CARInside& getInside() const { return *CARInside::GetInstance(); }
	CARServerObject& getCurrentObject() const { return object; }
	int getRootLevel() const { return rootLevel; }
	IfElseState getIfElse() const { return ifElse; }
	int getActionIndex() const { return actionIndex; }
	int getCurrentSchemaId() const { return currentSchemaId; }

	CARActiveLink& getActLink() const { assert(object.GetServerObjectTypeXML() == AR_STRUCT_ITEM_XML_ACTIVE_LINK); return static_cast<CARActiveLink&>(object); }

protected:
	CARServerObject &object;
	IfElseState ifElse;
	int actionIndex;
	int rootLevel;
	int currentSchemaId;
};

class SettableContext : public Context
{
public:
	SettableContext(CARServerObject &obj, IfElseState ifOrElseAction, int actionIndexPos, int currentWfSchemaId, int theRootLevel)
		: Context(obj, ifOrElseAction, actionIndexPos, currentWfSchemaId, theRootLevel) {}
	SettableContext(Context &ctx)
		: Context(ctx) {}


};

class LookupFormContext : public Context
{
public:
	LookupFormContext(Context &context, const std::string schemaName)
		: Context(context), lookupSchemaName(schemaName)
	{
		lookupSchemaId = this->getInside().SchemaGetInsideId(lookupSchemaName);
	}
	LookupFormContext(Context &context, int schemaId);

	string getLookupSchemaName();
	int getLookupSchemaId() { return lookupSchemaId; }
protected:
	std::string lookupSchemaName;
	int lookupSchemaId;
};

class MappingContext : public Context
{
public:
	// create a new MappingContext and copies the data from the specified context
	MappingContext(const Context &currentContext, int secondaryWfSchemaId)
		: Context(currentContext), secondarySchemaId(secondaryWfSchemaId) {}
	MappingContext(const Context &currentContext)
		: Context(currentContext), secondarySchemaId(-1) {}

	int getSecondarySchemaId() { return secondarySchemaId; }

	void setPrimarySchemaId(int value) { currentSchemaId = value; }
	void setSecondarySchemaId(int value) { secondarySchemaId = value; }

protected:
	int secondarySchemaId;
};
