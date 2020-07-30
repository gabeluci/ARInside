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
#include <ctime>

#if defined(_MSC_VER) || defined(_WINDOWS_)
#include <windows.h>
struct timezone
{
	int  tz_minuteswest;
	int  tz_dsttime;
};
#else
#include <sys/time.h>
#endif

class CAppTimer
{
public:
	CAppTimer(void);
	~CAppTimer(void);

	void StartTimer();
	void EndTimer();
	float GetDuration();

private:
	//float dTimeElapsed;
	//clock_t start, end;
	timeval startTime, endTime;
};

