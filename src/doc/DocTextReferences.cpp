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
#include "DocTextReferences.h"
#include "DocBasicField.h"
#include "DocCurrencyField.h"
#include "DocStatusHistoryField.h"
#include "../core/ARParseField.h"
#include "../output/ObjNotFound.h"
#include "../output/URLLink.h"
#include "../ARInside.h"

CDocTextReferences::CDocTextReferences(const string& inText, const string &fieldSeparator, int schemaInsideId, int rootLevel, bool findKeywords, const CRefItem *refItem)
: inText(inText), fieldSeparator(fieldSeparator)
{
	pInside = CARInside::GetInstance();

	this->schemaInsideId = schemaInsideId;
	this->rootLevel = rootLevel;
	this->findKeywords = findKeywords;
	this->refItem = refItem;
}

string CDocTextReferences::TextFindFields()
{
	try
	{
		if(inText.size() == 0)
			return "";

		if (!isInvalidSchemaId())
			return inText;

		replaceAllSpecials();
		replaceAllFields();
	}
	catch(exception& e)
	{
		cout << "EXCEPTION in TextFindField: " << e.what() << endl;
	}

	return inText;
}

void CDocTextReferences::replaceAllSpecials()
{
	stringstream strmTmp;

	// check for special run-process commands
	bool specialFound = false;
	string::size_type cmdStartPos = inText.find("Application-");
	if (cmdStartPos != string::npos)
	{
		string::size_type nextSearchPos = cmdStartPos + 12; // add length("Application-")
		specialFound = true;

		if (inText.compare(nextSearchPos, 17, "Copy-Field-Value ") == 0)
		{
			strmTmp << processTwoFields("Application-Copy-Field-Value");
		}
		else if (inText.compare(nextSearchPos, 13, "Delete-Entry ") == 0)
		{
			CRefItem newRefItem(*refItem, REFM_DELETE_ENTRY_ACTION);
			strmTmp << processForm("Application-Delete-Entry", (refItem == NULL ? refItem : &newRefItem));
		}
		else if (inText.compare(nextSearchPos, 12, "Format-Qual ") == 0)
		{
			strmTmp << processForm("Application-Format-Qual");
		}
		else if (inText.compare(nextSearchPos, 19, "Format-Qual-Filter ") == 0)
		{
			strmTmp << processForm("Application-Format-Qual-Filter");
		}
		else if (inText.compare(nextSearchPos, 15, "Format-Qual-ID ") == 0)
		{
			strmTmp << processForm("Application-Format-Qual-ID");
		}
		else if (inText.compare(nextSearchPos, 14, "Format-Qual-L ") == 0)
		{
			strmTmp << processForm("Application-Format-Qual-L");
		}
		else if (inText.compare(nextSearchPos, 18, "Get-Approval-Join ") == 0)
		{
			strmTmp << processForm("Application-Get-Approval-Join");
		}
		else if (inText.compare(nextSearchPos, 19, "Get-Approval-Join2 ") == 0)
		{
			strmTmp << processForm("Application-Get-Approval-Join2");
		}
		else if (inText.compare(nextSearchPos, 16, "Get-DetSig-Join ") == 0)
		{
			strmTmp << processForm("Application-Get-DetSig-Join");
		}
		else if (inText.compare(nextSearchPos, 17, "Get-DetSig-Join2 ") == 0)
		{
			strmTmp << processForm("Application-Get-DetSig-Join2");
		}
		else if (inText.compare(nextSearchPos, 15, "Get-Form-Alias ") == 0)
		{
			strmTmp << processForm("Application-Get-Form-Alias");
		}
		else if (inText.compare(nextSearchPos, 17, "Get-Locale-VuiID ") == 0)
		{
			strmTmp << processForm("Application-Get-Locale-VuiID");
		}
		else if (inText.compare(nextSearchPos, 25, "Get-Next-Recurrence-Time ") == 0)
		{
			strmTmp << processForm("Application-Get-Next-Recurrence-Time");
		}
		else if (inText.compare(nextSearchPos, 17, "Map-Ids-To-Names ") == 0)
		{
			strmTmp << processForm("Application-Map-Ids-To-Names");
		}
		else if (inText.compare(nextSearchPos, 19, "Map-Ids-To-Names-L ") == 0)
		{
			strmTmp << processForm("Application-Map-Ids-To-Names-L");
		}
		else if (inText.compare(nextSearchPos, 17, "Map-Names-To-Ids ") == 0)
		{
			strmTmp << processForm("Application-Map-Names-To-Ids");
		}
		else if (inText.compare(nextSearchPos, 19, "Map-Names-To-Ids-L ") == 0)
		{
			strmTmp << processForm("Application-Map-Names-To-Ids-L");
		}
		else if (inText.compare(nextSearchPos, 11, "Parse-Qual ") == 0)
		{
			strmTmp << processForm("Application-Parse-Qual");
		}
		else if (inText.compare(nextSearchPos, 18, "Parse-Qual-Filter ") == 0)
		{
			strmTmp << processForm("Application-Parse-Qual-Filter");
		}
		else if (inText.compare(nextSearchPos, 13, "Parse-Qual-L ") == 0)
		{
			strmTmp << processForm("Application-Parse-Qual-L");
		}
		else if (inText.compare(nextSearchPos, 20, "Parse-Qual-SField-L ") == 0)
		{
			strmTmp << processForm("Application-Parse-Qual-SField-L");
		}
		else if (inText.compare(nextSearchPos, 17, "Parse-Val-SField ") == 0)
		{
			strmTmp << processForm("Application-Parse-Val-SField");
		}
		else if (inText.compare(nextSearchPos, 19, "Query-Delete-Entry ") == 0)
		{
			CRefItem newRefItem(*refItem, REFM_DELETE_ENTRY_ACTION);
			strmTmp << processForm("Application-Query-Delete-Entry", (refItem == NULL ? NULL : &newRefItem));
		}
		else
		{
			specialFound = false;
		}
	}
	
	cmdStartPos = inText.find("PERFORM-ACTION-");
	if (cmdStartPos != string::npos)
	{
		string::size_type nextSearchPos = cmdStartPos + 15; // add length("PERFORM-ACTION-")
		specialFound = true;

		if (inText.compare(nextSearchPos, 12, "ACTIVE-LINK ") == 0)
		{
			strmTmp << processSecondParameter("PERFORM-ACTION-ACTIVE-LINK");
		}
		else if (inText.compare(nextSearchPos, 15, "ADD-ATTACHMENT ") == 0)
		{
			strmTmp << processOneField("PERFORM-ACTION-ADD-ATTACHMENT");
		}
		else if (inText.compare(nextSearchPos, 18, "DELETE-ATTACHMENT ") == 0)
		{
			strmTmp << processOneField("PERFORM-ACTION-DELETE-ATTACHMENT");
		}
		else if (inText.compare(nextSearchPos, 16, "GET-FIELD-LABEL ") == 0)
		{
			strmTmp << processOneField("PERFORM-ACTION-GET-FIELD-LABEL");
		}
		else if (inText.compare(nextSearchPos, 15, "GET-PREFERENCE ") == 0)
		{
			strmTmp << processOneField("PERFORM-ACTION-GET-PREFERENCE");
		}
		else if (inText.compare(nextSearchPos, 28, "NAV-FIELD-SET-SELECTED-ITEM ") == 0)
		{
			strmTmp << processOneField("PERFORM-ACTION-NAV-FIELD-SET-SELECTED-ITEM");
		}
		else if (inText.compare(nextSearchPos, 16, "OPEN-ATTACHMENT ") == 0)
		{
			strmTmp << processOneField("PERFORM-ACTION-OPEN-ATTACHMENT");
		}
		else if (inText.compare(nextSearchPos, 16, "SAVE-ATTACHMENT ") == 0)
		{
			strmTmp << processOneField("PERFORM-ACTION-SAVE-ATTACHMENT");
		}
		else if (inText.compare(nextSearchPos, 15, "SET-PREFERENCE ") == 0)
		{
			strmTmp << processOneField("PERFORM-ACTION-SET-PREFERENCE");
		}
		else if (inText.compare(nextSearchPos, 12, "TABLE-CLEAR ") == 0)
		{
			strmTmp << processOneField("PERFORM-ACTION-TABLE-CLEAR");
		}
		else if (inText.compare(nextSearchPos, 23, "TABLE-CLEAR-ROWCHANGED ") == 0)
		{
			strmTmp << processOneField("PERFORM-ACTION-TABLE-CLEAR-ROWCHANGED");
		}
		else if (inText.compare(nextSearchPos, 18, "TABLE-DESELECTALL ") == 0)
		{
			strmTmp << processOneField("PERFORM-ACTION-TABLE-DESELECTALL");
		}
		else if (inText.compare(nextSearchPos, 26, "TABLE-GET-SELECTED-COLUMN ") == 0)
		{
			strmTmp << processOneField("PERFORM-ACTION-TABLE-GET-SELECTED-COLUMN");
		}
		else if (inText.compare(nextSearchPos, 23, "TABLE-IS-LEAF-SELECTED ") == 0)
		{
			strmTmp << processOneField("PERFORM-ACTION-TABLE-IS-LEAF-SELECTED");
		}
		else if (inText.compare(nextSearchPos, 17, "TABLE-NEXT-CHUNK ") == 0)
		{
			strmTmp << processOneField("PERFORM-ACTION-TABLE-NEXT-CHUNK");
		}
		else if (inText.compare(nextSearchPos, 17, "TABLE-PREV-CHUNK ") == 0)
		{
			strmTmp << processOneField("PERFORM-ACTION-TABLE-PREV-CHUNK");
		}
		else if (inText.compare(nextSearchPos, 14, "TABLE-REFRESH ") == 0)
		{
			strmTmp << processOneField("PERFORM-ACTION-TABLE-REFRESH");
		}
		else if (inText.compare(nextSearchPos, 13, "TABLE-REPORT ") == 0)
		{
			strmTmp << processOneField("PERFORM-ACTION-TABLE-REPORT");
		}
		else if (inText.compare(nextSearchPos, 18, "TABLE-SELECT-NODE ") == 0)
		{
			strmTmp << processOneField("PERFORM-ACTION-TABLE-SELECT-NODE");
		}
		else if (inText.compare(nextSearchPos, 16, "TABLE-SELECTALL ") == 0)
		{
			strmTmp << processOneField("PERFORM-ACTION-TABLE-SELECTALL");
		}
		else
		{
			specialFound = false;
		}
	}

	//write the current string back to inText, then clear the stream for use with the application code
	if (specialFound)
	{
		inText = strmTmp.str();
	}
}

void CDocTextReferences::docField(std::ostream &strm, const ARParseField &parsedField)
{
	switch (parsedField.tag)
	{
	case AR_FIELD:
		{
			CDocBasicField docField(schemaInsideId, parsedField.u.fieldId);
			docField.GetResolvedAndLinkedField(strm, refItem, rootLevel);
		}
		break;
	case AR_STAT_HISTORY:
		{
			CDocStatusHistoryField docStatusHistory(schemaInsideId, parsedField.u.statHistory);
			docStatusHistory.GetResolvedAndLinkedField(strm, refItem, rootLevel);
		}
		break;
	case AR_CURRENCY_FLD:
		{
			CDocCurrencyField docCurrency(schemaInsideId, *parsedField.u.currencyField);
			docCurrency.GetResolvedAndLinkedField(strm, refItem, rootLevel);
		}
		break;
	}
}

void CDocTextReferences::replaceAllFields()
{
	stringstream strmTmp;
	string::size_type curPos = 0;
	string::size_type startPos = 0;
	string::size_type maxLen = inText.length();

	while ((startPos = inText.find(fieldSeparator.at(0),curPos)) != std::string::npos)
	{
		++startPos;
		strmTmp << inText.substr(curPos, startPos - curPos);
		curPos = startPos;

		string::size_type endPos = inText.find(fieldSeparator.at(0), startPos);

		if (endPos != string::npos)
		{
			CARParseField fieldParser(inText.substr(startPos, endPos - startPos));
			const ARParseField& parsedField = fieldParser.getField();

			if (parsedField.tag != 0)
			{
				// now create documentation/link for the parsed field
				docField(strmTmp, parsedField);

				// write the end-separator to the output and skip it for next parsing
				strmTmp << inText.substr(endPos, 1);
				endPos++;
			}
			else
			{
				strmTmp << inText.substr(curPos, endPos - curPos);
			}

			curPos = endPos;
		}
	}
	if (curPos < maxLen)
		strmTmp << inText.substr(curPos);

	inText = strmTmp.str();
}

string CDocTextReferences::processOneField(const string& command)
{
	stringstream strmTmp;
	int fieldId = 0;
	size_t length = command.length()+1;
	size_t pos = inText.find(command);

	//put the command into the stream
	strmTmp << inText.substr(0,(length+pos));
	//get everything after the command
	string tmp = inText.substr(length+pos);
	//get position of next space
	pos = tmp.find(" ");

	//set the fieldID = to the one we found

	if (pos != std::string::npos)
		fieldId = atoi(tmp.substr(0,pos).c_str());
	else
		fieldId = atoi(tmp.c_str());

	if (fieldId != std::string::npos && fieldId > 0)
		strmTmp << refFieldID(fieldId);

	if (pos != std::string::npos)
	{
		tmp = tmp.substr(pos,tmp.length());
		strmTmp << tmp;
	}

	return strmTmp.str();
}
string CDocTextReferences::processTwoFields(const string& command)
{
	stringstream strmTmp;
	int fieldId = 0;
	size_t length = command.length()+1;
	size_t pos = inText.find(command);

	//put the command into the stream
	strmTmp << inText.substr(0,(length+pos));
	//get everything after the command
	string tmp = inText.substr(length+pos);
	if (tmp.find("$") == 0 && tmp.find("$") != std::string::npos)
	{
		tmp = tmp.substr(1);
		pos = tmp.find("$")+1;
		strmTmp << "$" << tmp.substr(0,pos);
	}
	else
	{
		pos = tmp.find(" ");
		fieldId = atoi(tmp.substr(0,pos).c_str());
		strmTmp << refFieldID(fieldId);
	}

	//put a space between the field ID's
	strmTmp << " ";

	//get position of next space
	pos = tmp.find(" ");
	//get everything after the space
	tmp = tmp.substr(pos+1);

	if (tmp.find("$") == 0 && tmp.find("$") != std::string::npos)
	{
		strmTmp << tmp;
	}
	else
	{
		fieldId = atoi(tmp.c_str());
		strmTmp << refFieldID(fieldId);
	}

	return strmTmp.str();
}

string CDocTextReferences::processForm(const string& command, const CRefItem *refItem)
{
	stringstream strmTmp;
	string form = "";
	size_t length = command.length()+1;
	size_t pos = inText.find(command);

	//put the command into the stream
	strmTmp << inText.substr(0,(length+pos));
	//get everything after the command
	string tmp = inText.substr(length+pos);
	//ok, we are at the first parameter, need to first find if it starts with a "
	if (tmp.substr(0,1) == "\"")
	{
		strmTmp << "\"";
		pos = tmp.find("\"",1);
		form = tmp.substr(1,pos-1);
	}
	else
	{
		//get position of next space
		pos = tmp.find(" ");
		form = tmp.substr(0,pos);
	}
	//generate link for form
	CARSchema schema(form);
	if (schema.Exists())
	{
		strmTmp << URLLink(schema, rootLevel, false);
		if (refItem != NULL) 
		{
			if (!schema.ReferenceExists(*refItem))
				schema.AddReference(*refItem);
		}
	}
	else
	{
		// check, if $SCHEMA$ is used as form name. In this case we'll create a reference to the current schema
		if (refItem != NULL && form.compare("$-5$") == 0)
		{
			CARSchema currentSchema(schemaInsideId);
			if (currentSchema.Exists() && !currentSchema.ReferenceExists(*refItem))
			{
				currentSchema.AddReference(*refItem);
			}
		}
		strmTmp << form;
	}

	// if there is anything past the form-parameter, write it to output
	if (pos != string::npos)
		strmTmp << tmp.substr(pos);

	return strmTmp.str();
}
string CDocTextReferences::processSecondParameter(const string& command)
{
	stringstream strmTmp;
	int fieldId = 0;
	size_t length = command.length()+1;
	size_t pos = inText.find(command);

	//put the command into the stream
	strmTmp << inText.substr(0,(length+pos));
	//get everything after the command
	string tmp = inText.substr(length+pos);
	//get position of next space
	pos = tmp.find(" ");
	//set the fieldID = to the one we found
	strmTmp << tmp.substr(0,pos);
	//put a space in there
	strmTmp << " ";
	//get position of next space
	pos = tmp.find(" ");
	//get everything after the space
	if (pos != std::string::npos)
	{
		tmp = tmp.substr(pos);
		//set the fieldID = to the one we found
		fieldId = atoi(tmp.c_str());
		strmTmp << refFieldID(fieldId) << endl;
	}

	return strmTmp.str();
}

string CDocTextReferences::refFieldID(int iFieldId)
{
	stringstream strmTmp;

	if (iFieldId <= 0)
	{
		// keyword support
		int iKeyword = abs(iFieldId);
		return CAREnum::Keyword(iKeyword);
	}

	CARField field(schemaInsideId, iFieldId);
	if (field.Exists())
	{
		strmTmp << URLLink(field, rootLevel);
		// add reference
		if (refItem)
			pInside->AddFieldReference(schemaInsideId, iFieldId, *refItem);
	}
	else
		strmTmp << iFieldId;

	return strmTmp.str();
}

bool CDocTextReferences::isInvalidSchemaId()
{
	CARSchema schema(schemaInsideId);
	return schema.Exists();
}
