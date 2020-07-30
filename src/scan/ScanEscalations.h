//Copyright (C) 2011 John Luthgers | jls17
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

#include "../util/RefItem.h"

// forward declarations
class CAREscalation;

class CScanEscalations
{
private:
	CScanEscalations(CAREscalation& escalation);
	~CScanEscalations(void);

public:
	static void Start();

private:
	CAREscalation& escal;

private:
	void Scan();
	void ScanActions(const ARFilterActionList& actions, IfElseState ifElse);
};
