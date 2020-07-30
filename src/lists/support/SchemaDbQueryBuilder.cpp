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

#include "stdafx.h"
#include "SchemaDbQueryBuilder.h"

SchemaDbQueryBuilder::SchemaDbQueryBuilder()
: maxRetrieve(0), lastReceivedSchemaId(0)
{
}

SchemaDbQueryBuilder::~SchemaDbQueryBuilder(void)
{
}

void SchemaDbQueryBuilder::SetLastReceivedSchemaId(int schemaId)
{
	this->lastReceivedSchemaId = schemaId;
}

void SchemaDbQueryBuilder::SetMaxRetrieve(unsigned int maxRetrieve)
{
	this->maxRetrieve = maxRetrieve;
}

const char* SchemaDbQueryBuilder::GetNextQuery()
{
	stringstream strm;

	AppendStatement(strm);
	AppendWhereCondition(strm);
	AppendOrdering(strm);	

	query = strm.str();
	return query.c_str();
}

unsigned int SchemaDbQueryBuilder::ExpectedColumnCount()
{
	return 4;
}

void SchemaDbQueryBuilder::AppendStatement(std::ostream &strm)
{
	strm << "select schemaId, name, viewName, shViewName from arschema";
}

void SchemaDbQueryBuilder::AppendOrdering(std::ostream &strm)
{
	strm << " order by schemaId asc";
}

void SchemaDbQueryBuilder::AppendWhereCondition(std::ostream &strm)
{
	if (this->maxRetrieve > 0)
	{
		BuildWhereCondition(strm);
	}
}

void SchemaDbQueryBuilder::BuildWhereCondition(std::ostream &strm)
{
	strm << " where schemaId > " << lastReceivedSchemaId;
}

bool SchemaDbQueryBuilder::TryReadSchemaId(ARValueList &row, unsigned int &schemaId)
{
	if (row.valueList[0].dataType == AR_DATA_TYPE_INTEGER)
	{
		schemaId = row.valueList[0].u.ulongVal;
		return true;
	}
	return false;
}

bool SchemaDbQueryBuilder::TryReadSchemaView(ARValueList &row, ARNameType &schemaView)
{
	if (row.valueList[2].dataType == AR_DATA_TYPE_CHAR)
	{
		strncpy(schemaView, row.valueList[2].u.charVal, AR_MAX_NAME_SIZE);
		schemaView[AR_MAX_NAME_SIZE] = 0;
		return true;
	}
	return false;
}

bool SchemaDbQueryBuilder::TryReadSchemaShView(ARValueList &row, ARNameType &shSchemaView)
{
	if (row.valueList[3].dataType == AR_DATA_TYPE_CHAR)
	{
		strncpy(shSchemaView, row.valueList[3].u.charVal, AR_MAX_NAME_SIZE);
		shSchemaView[AR_MAX_NAME_SIZE] = 0;
		return true;
	}
	return false;
}
