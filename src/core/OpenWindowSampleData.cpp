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
#include "OpenWindowSampleData.h"
#include "../util/Context.h"

bool OpenWindowSampleData::ParseSampleData()
{
	// ok, this is a very ugly design of the ARS api. The sample data of
	// the action is stored within the object properties of the active-
	// link. that wouldnt be that bad if we just need to read the data
	// from there, but the data is something like an API structure and
	// there is no ARDecode*** function. So we need to implement our
	// own decode routine.

	const ARPropList &propList = context.getActLink().GetPropList();

	// first, decide which property we are looking for
	unsigned int PropID = (context.getIfElse() == IES_IF ? AR_OPROP_WINDOW_OPEN_IF_SAMPLE_SERVER_SCHEMA : AR_OPROP_WINDOW_OPEN_ELSE_SAMPLE_SERVER_SCHEMA);

	// now find the index of the object property
	int propIndex = -1;
	for (unsigned int k=0; k < propList.numItems; ++k)
	{
		if (propList.props[k].prop == PropID)
		{
			propIndex = k;
			break;
		}
	}

	if (propIndex > -1 && propList.props[propIndex].value.dataType == AR_DATA_TYPE_CHAR)
	{
		// the property is found and has correct data type
		return ParseSampleList(propList.props[propIndex].value.u.charVal);
	}
	return false;
}

bool OpenWindowSampleData::ParseSampleList(char *encodedList)
{
	if (encodedList == NULL) return false;

	// retrieve lists item count
	int listCount = atoi(encodedList);

	// find the \ after the list item count
	const char* currentPos = strchr(encodedList, '\\');
	if (currentPos == NULL) return false;

	if (listCount > 0 && *currentPos != 0)
	{
		++currentPos; // skip the "\"
		
		// now we need to check each entry of the list against the action-index we're lookup for
		for (int listIndex = 0; listIndex < listCount; ++listIndex)
		{
			int propActionIndex = atoi(currentPos);
			currentPos = strchr(currentPos, '\\');
			if (currentPos == NULL) return false;
			++currentPos; // skip the "\"

			if (propActionIndex == context.getActionIndex() && *currentPos != 0)
			{
				// match! found the action we were looking for!
				const char* strStart = currentPos;
				currentPos = strchr(currentPos, '\\');
				if (currentPos == NULL) return false;

				server_Start = strStart;
				server_End = currentPos;

				++currentPos; // skip last "\"
				strStart = currentPos;
				while (*currentPos != '\\' && *currentPos != 0) ++currentPos; // we can't use strchr here, because we're looking to two possible chars

				schema_Start = strStart;
				schema_End = currentPos;
				return true;	// we are done
			}

			// skip next two data entries now
			for (int tmpDataCount = 0; tmpDataCount < 2; ++tmpDataCount)
			{
				currentPos = strchr(currentPos, '\\');
				if (currentPos == NULL) return false;
				++currentPos; // skip last "\"
			}
			if (currentPos == NULL) return false;
		}
	}
	return false;
}

void OpenWindowSampleData::CheckAlreadyParsed()
{
	if (!parsed)
		valid = ParseSampleData();
}

string OpenWindowSampleData::getServer()
{
	CheckAlreadyParsed();
	if (!valid) return "";

	return string(server_Start, server_End);
}

string OpenWindowSampleData::getSchema()
{
	CheckAlreadyParsed();
	if (!valid) return "";

	return string(schema_Start, schema_End);
}
