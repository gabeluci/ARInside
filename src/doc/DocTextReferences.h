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

class CARInside;
class CRefItem;
struct ARParseField;

class CDocTextReferences
{
private:
	CARInside *pInside;

public:
	CDocTextReferences(const std::string& inText, const std::string &fieldSeparator, int schemaInsideId, int rootLevel, bool findKeywords, const CRefItem *refItem);
	~CDocTextReferences() {}

	string TextFindFields();

protected:
	string inText;
	string fieldSeparator;
	int schemaInsideId;
	int rootLevel;
	bool findKeywords;
	const CRefItem* refItem;

private:
	string processOneField(const string& command);
	string processTwoFields(const string& command);
	string processForm(const string& command, const CRefItem *refItem = NULL);
	string processSecondParameter(const string& command);

	void replaceAllSpecials();
	void replaceAllFields();

	void docField(std::ostream &strm, const ARParseField& parsedField);

protected: /* this is protected to overwrite methods in subclasses for testing support */
	virtual string refFieldID(int iFieldID);
	virtual bool isInvalidSchemaId();
};
