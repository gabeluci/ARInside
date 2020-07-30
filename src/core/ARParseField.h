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

#pragma once

typedef struct ARParseField
{
 unsigned int       tag;  /* AR_FIELD, AR_STAT_HISTORY, etc */
 union
 {
    size_t                noval_;
    ARInternalId          fieldId;
    ARStatHistoryValue    statHistory;
    ARCurrencyPartStruct *currencyField;
 } u;
} ARParseField;

class CARParseField
{
public:
	CARParseField(const std::string &fieldIdString);
	const ARParseField& getField();

private:
	std::string fieldString;
	ARParseField field;

	enum ReadResult
	{
		FINISHED,
		NEXT,
		FAILED,
	};

private:
	void Parse();
	ReadResult ReadInteger(unsigned int &curPos, int &outInt);
	static bool isValidChar(char c);
	static bool IsValidStatHistorySubType(int usrOrTime);
	static bool IsValidCurrencyPart(int currencyPart);

	void SetupField(int fieldId);
	void SetupStatusHistory(int fieldId, int usrOrTime, int enumId);
	void SetupCurrencyField(int fieldId, int currencyPart, char* currencyCode = NULL);
};
