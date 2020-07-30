//Copyright (C) 2012 John Luthgers | jls17
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

#include "util/AppTimer.h"

// forward declarations
class AppConfig;

class CMain
{
public:
	int Run(int argc, char* argv[]);

private:
	const char* GetPlatformString() const;
	void OutputARInsideBanner();

	int StartServerMode(AppConfig &appConfig);
	int StartFileMode(AppConfig &appConfig);

	static void DoDeleteExistingFiles(std::string path);

private:
	CAppTimer mTimer;
};
