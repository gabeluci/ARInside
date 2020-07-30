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
#include "Context.h"

LookupFormContext::LookupFormContext(Context &context, int schemaId)
: Context(context)
{
	CARSchema schema(schemaId);
	lookupSchemaId = schema.GetInsideId();
}

string LookupFormContext::getLookupSchemaName()
{
	if (!lookupSchemaName.empty())
		return lookupSchemaName;

	CARSchema schema(lookupSchemaId);
	if (schema.Exists())
		return schema.GetName();

	return "";
}
