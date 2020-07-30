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

#include "stdafx.h"
#include "ARValue.h"

CARValue::CARValue()
{	

}

CARValue::~CARValue(void)
{
}

string CARValue::ValueToString(const ARValueStruct &value)
{
	switch(value.dataType)
	{
	case AR_DATA_TYPE_NULL:
		{
			return "NULL";
		}
		break;
	case AR_DATA_TYPE_KEYWORD:
		{
			return CAREnum::Keyword(value.u.keyNum);
		}
		break;
	case AR_DATA_TYPE_INTEGER:
		{
			stringstream strm;
			strm.str("");

			strm << value.u.intVal;
			return strm.str();
		}
		break;
	case AR_DATA_TYPE_REAL:
		{
			stringstream strm;
			strm.str("");

			strm <<value.u.realVal;
			return strm.str();
		}
		break;
	case AR_DATA_TYPE_CHAR:
	case AR_DATA_TYPE_VIEW:	// older versions used this data type (e.g. to assign URL-string to view-field)
		{
			if(value.u.charVal != NULL)
			{
				return value.u.charVal;	
			}
			else
				return "";
		}
		break;
	case AR_DATA_TYPE_DIARY:
		{
			if(value.u.diaryVal != NULL)
			{
				stringstream strm;
				strm.str("");
				strm << value.u.diaryVal;

				return strm.str();
			}
			else
				return "";
		}
		break;	
	case AR_DATA_TYPE_ENUM:
		{
			stringstream strm;
			strm.str("");
			strm << value.u.enumVal;
			return strm.str();
		}
		break;
	case AR_DATA_TYPE_TIME:
		{
			stringstream strm;
			strm.str("");
			strm << CUtil::DateTimeToHTMLString(value.u.timeVal);
			return strm.str();
		}
		break;
	case AR_DATA_TYPE_BITMASK:
		{
			return "BitMask";
		}
		break;
	case AR_DATA_TYPE_BYTES:
		{
			return "Bytelist";
		}
		break;
	case AR_DATA_TYPE_DECIMAL:
		{
			if(value.u.decimalVal != NULL)
			{
				stringstream strm;
				strm.str("");
				strm << value.u.decimalVal;

				return strm.str();
			}
			else
				return "0.0";
		}
		break;
	case AR_DATA_TYPE_ATTACH:
		{		
			if(value.u.attachVal != NULL
				&& value.u.attachVal->name != NULL)
			{
				return value.u.attachVal->name;	
			}
		}
		break;
	case AR_DATA_TYPE_CURRENCY:
		{
			if(value.u.currencyVal != NULL)
			{	
				stringstream strm;
				strm.str("");

				strm << "Code: ";
				if(value.u.currencyVal->currencyCode != NULL)
				{
					strm << value.u.currencyVal->currencyCode;
				}

				if(value.u.currencyVal->value != NULL)
				{
					strm << " Value: " << value.u.currencyVal->value;
				}

				return strm.str();
			}
		}
		break;
	case AR_DATA_TYPE_DATE:
		{
			stringstream strm;
			strm.str("");
			strm << CUtil::DateToString(value.u.dateVal);

			return strm.str();
		}
		break;
	case AR_DATA_TYPE_ULONG:
		{
			stringstream strm;
			strm.str("");
			strm << value.u.ulongVal;

			return strm.str();
		}
		break;
	case AR_DATA_TYPE_TIME_OF_DAY:
		{
			stringstream strm;
			strm.str("");
			strm << CUtil::TimeOfDayToString(value.u.timeOfDayVal);

			return strm.str();
		}
		break;
	}

	return "";
}

int CARValue::ValueToInt(const ARValueStruct &value, bool* isIntegerValue)
{

	switch (value.dataType)
	{
	case AR_DATA_TYPE_KEYWORD:
	case AR_DATA_TYPE_INTEGER:
	case AR_DATA_TYPE_ENUM:
	case AR_DATA_TYPE_ULONG:
		if (isIntegerValue != NULL)
			*isIntegerValue = true;
		return value.u.intVal;
	}

	if (isIntegerValue != NULL) 
		*isIntegerValue = false;
	return 0;
}
