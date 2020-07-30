//Copyright (C) 2014 John Luthgers | jls17@gmx.net
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
#include "../ARApi.h"
#include "ARParseField.h"

const char FIELD_PART_DELIMITER = '.';

CARParseField::CARParseField(const std::string &fieldIdString)
: fieldString(fieldIdString)
{
	ARZeroMemory(&field);
	Parse();
}

void CARParseField::Parse()
{
	if (fieldString.empty())
		return;

	unsigned int readPos = 0;

	int fieldId = 0;
	ReadResult result = ReadInteger(readPos, fieldId);

	if (result == FINISHED)
	{
		SetupField(fieldId);
		return;
	}
	else if (result == NEXT)
	{
		int secondId = 0;
		result = ReadInteger(readPos, secondId);

		if (result == FINISHED)
		{
			if (secondId >= AR_CURRENCY_PART_FIELD && secondId <= AR_CURRENCY_PART_DATE)
			{
				SetupCurrencyField(fieldId, secondId);
				return;
			}

			result = FAILED;
			return;
		}
		else if (result == NEXT)
		{
			int thirdId = 0;
			result = ReadInteger(readPos, thirdId);

			if (result == FAILED && fieldString.length() - readPos >= AR_MAX_CURRENCY_CODE_SIZE)
			{
				ARCurrencyCodeType cCode;
				strncpy(cCode, fieldString.c_str() + readPos, AR_MAX_CURRENCY_CODE_SIZE);
				cCode[AR_MAX_CURRENCY_CODE_SIZE] = 0;
				readPos += AR_MAX_CURRENCY_CODE_SIZE;

				if (fieldString.length() == readPos)
				{
					SetupCurrencyField(fieldId, secondId, cCode);
					return;
				}
			}
			else if (result == FINISHED)
			{
				if (fieldId == 15) { SetupStatusHistory(fieldId, thirdId, secondId); }
			}
		}
	}
}

CARParseField::ReadResult CARParseField::ReadInteger(unsigned int &curPos, int &outInt)
{
	const int FIELD_BUFFER_SIZE = 16;

	ReadResult result = FINISHED;
	unsigned int readCount = 0;
	char field[FIELD_BUFFER_SIZE];
	unsigned int pos;

	for (pos = curPos; pos < fieldString.length(); pos++)
	{
		if (readCount >= FIELD_BUFFER_SIZE)
		{
			return FAILED;
		}

		char currChar = fieldString.at(pos);
		
		// - is only allowed at the beginning
		if (currChar == '-' && pos > curPos)  
			return FAILED;

		if (isValidChar(currChar))
		{
			field[readCount++] = currChar;
		}
		else if (readCount > 0 && currChar == FIELD_PART_DELIMITER)
		{
			pos++;
			result = NEXT;
			break;
		}
		else
		{
			return FAILED;
		}
	}

	if (readCount > 0)
	{
		field[readCount] = 0;
		outInt = atoi(field);

		curPos = pos;
		return result;
	}
	return FAILED;
}

bool CARParseField::isValidChar(char c)
{
	return (c >= '0' && c <= '9' || c == '-');
}

const ARParseField& CARParseField::getField()
{
	return field;
}

void CARParseField::SetupField(int fieldId)
{
	field.tag = AR_FIELD;
	field.u.fieldId = fieldId;
}

void CARParseField::SetupStatusHistory(int fieldId, int usrOrTime, int enumId)
{
	if (fieldId != 15 || !IsValidStatHistorySubType(usrOrTime))
		return;
	field.tag = AR_STAT_HISTORY;
	field.u.statHistory.userOrTime = usrOrTime;
	field.u.statHistory.enumVal = enumId;
}

bool CARParseField::IsValidStatHistorySubType(int usrOrTime)
{
	switch (usrOrTime)
	{
	case AR_STAT_HISTORY_USER:
	case AR_STAT_HISTORY_TIME:
		return true;
	};
	return false;
}

void CARParseField::SetupCurrencyField(int fieldId, int currencyPart, char* currencyCode)
{
	if (!IsValidCurrencyPart(currencyPart))
		return;

	field.tag = AR_CURRENCY_FLD;
	field.u.currencyField = new ARCurrencyPartStruct;
	field.u.currencyField->fieldId = fieldId;
	field.u.currencyField->partTag = currencyPart;

	if (currencyCode == NULL)
	{
		ARZeroMemory(&field.u.currencyField->currencyCode);
	}
	else
	{
		strncpy(field.u.currencyField->currencyCode, currencyCode, AR_MAX_CURRENCY_CODE_SIZE + 1);
	}
}

bool CARParseField::IsValidCurrencyPart(int currencyPart)
{
	switch (currencyPart)
	{
	case AR_CURRENCY_PART_FIELD:
	case AR_CURRENCY_PART_VALUE:
	case AR_CURRENCY_PART_TYPE:
	case AR_CURRENCY_PART_DATE:
	case AR_CURRENCY_PART_FUNCTIONAL:
		return true;
	}
	return false;
}
