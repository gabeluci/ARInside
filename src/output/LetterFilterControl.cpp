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
#include "LetterFilterControl.h"
#include "../core/ARServerObject.h"
#include "../output/URLLink.h"

LetterFilterControl::LetterFilterControl()
{
	objCountPerLetter.resize(38); // see objectNameFirstCharLetters
}

LetterFilterControl::~LetterFilterControl()
{
}

void LetterFilterControl::IncStartLetterOf(CARServerObject &obj)
{
	string firstChar = obj.GetNameFirstChar();
	if (firstChar.empty()) firstChar = "*";

	int index = CARObject::GetFirstCharIndex(firstChar[0]);
	++(objCountPerLetter[index]);
}

void LetterFilterControl::Render(std::ostream &strm)
{
	try
	{
		strm << "<table id='formLetterFilter'><tr>" << endl;

		string strValue = objectNameFirstCharLetters; // "abcdefghijklmnopqrstuvwxyz0123456789#"
		for (unsigned int i = 0; i < strValue.size(); ++i) 
		{
			if (objCountPerLetter[i] > 0)
			{
				strm << "<td>";
				strm << DirectURLLink(DirectURLLink::JavascriptVoid, strValue.substr(i, 1), 0);
			}
			else
			{
				strm << "<td class=\"disabledLetter\">";
				strm << strValue.at(i);
			}

			strm << "</td>" << endl;
		}

		strm << "</tr></table>" << endl;
	}
	catch(exception& e)
	{
		cout << "EXCEPTION LetterFilterControl::Render : " << e.what() << endl;
	}
}

ostream& operator<<(ostream& strm, OUTPUT::LetterFilterControl& inst)
{ 
	inst.Render(strm);
	return strm;
}
