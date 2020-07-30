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
#include "DocAlMessageAction.h"
#include "../../core/AREnum.h"
#include "../../util/Context.h"
#include "../../util/RefItem.h"

DocAlMessageAction::DocAlMessageAction(Context &theContext, const ARMessageStruct &theAction)
: context(theContext), action(theAction)
{
}

void DocAlMessageAction::ToStream(std::ostream &strm)
{
	try
	{
		CARInside &arIn = context.getInside();

		strm << "Message Number: " << action.messageNum << "<br/>" << endl;
		strm << "Message Type: " << CAREnum::MessageType(action.messageType) << "<br/>" << endl;

		if(action.messageText != NULL)
		{
			CRefItem refItemTmp(context, REFM_MESSAGE);
			strm << "Message Text:<br/>" << arIn.TextFindFields(context, action.messageText, true, &refItemTmp) << "<br/>" << endl;
		}

#if AR_CURRENT_API_VERSION >= AR_API_VERSION_763
		if (arIn.CompareServerVersion(7,6) >= 0 || (arIn.appConfig.fileMode == true && arIn.CompareServerVersion(7,5) >= 0))
		{
			strm << "<input type=\"checkbox\" name=\"showInPromptPane\" value=\"showInPromptPane\"" << (action.usePromptingPane ? " checked" : "") << ">Show Message in Prompt Bar" << "<br/>" << endl;
		}
#endif
	}
	catch(exception& e)
	{
		cout << "EXCEPTION in DocAlActionMessage of '" << context.getCurrentObject().GetName() << "': " << e.what() << endl;
	}
}
