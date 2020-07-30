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

#pragma once
#include "DocBase.h"

class CDocSummaryInfo :
	public CDocBase
{
public:
	CDocSummaryInfo(CARInside &arIn, string path);
	~CDocSummaryInfo(void);

	void Documentation();

public:
	// the following variables count the objects without taking the overlaid base objects into account
	unsigned int schemaCount;
	unsigned int activelinkCount;
	unsigned int filterCount;
	unsigned int escalationCount;
	unsigned int menuCount;
	unsigned int applicationCount;
	unsigned int webserviceCount;
	unsigned int alguideCount;
	unsigned int packlistCount;
	unsigned int fltguideCount;
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_750
	unsigned int imageCount;
#endif
};
