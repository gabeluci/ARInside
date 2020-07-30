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
#pragma once

class Context;

class DocOpenWindowAction
{
public:
	DocOpenWindowAction(Context &context, const AROpenDlgStruct &action);
	void ToStream(std::ostream& strm);

private:
	static bool ActionOpenDlgTargetLocation(int nWindowType);
	static bool ActionOpenDlgQualifier(int nWindowType);
	static bool ActionOpenDlgCloseButton(int nWindowType);
	static bool ActionOpenDlgSuppressEmptyList(int nWindowType);
	static bool ActionOpenDlgInputMapping(int nWindowType);
	static bool ActionOpenDlgOutputMapping(int nWindowType);
	static bool ActionOpenDlgPoolingInterval(int nWindowType);
	static bool ActionOpenDlgMessage(int nWindowType);
	static bool ActionOpenDlgInlineForm(int nWindowType);
	static bool IsViewFieldReference(const char* targetLocation);

private:
	Context &context;
	const AROpenDlgStruct &action;
};
