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

#include "stdafx.h"
#include "AppTimer.h"

#if defined(_MSC_VER) || defined(_WINDOWS_)
int gettimeofday(struct timeval* tv, struct timezone *tz) 
{
	static int tzInitializied;
	union {
		 FILETIME ft;
		 long long lltm;
	} now;
 
	GetSystemTimeAsFileTime (&now.ft);

	if (tv != NULL)
	{
		tv->tv_sec  = (long)((now.lltm - 116444736000000000LL) / 10000000LL);
		tv->tv_usec = (long)((now.lltm / 10LL) % 1000000LL);
	}
	
	if (tz != NULL)
	{
		if (!tzInitializied) { _tzset(); ++tzInitializied; }
		tz->tz_minuteswest = _timezone / 60;
		tz->tz_dsttime     = _daylight;
	}

	return 0;
}
#endif

CAppTimer::CAppTimer(void)
{
	memset(&startTime, 0, sizeof(timeval));
	memset(&endTime, 0, sizeof(timeval));
}

CAppTimer::~CAppTimer(void)
{
}

void CAppTimer::StartTimer()
{
	gettimeofday(&startTime, NULL);
}

void CAppTimer::EndTimer()
{
	gettimeofday(&endTime, NULL);
}

float CAppTimer::GetDuration()
{
	return (float)(endTime.tv_sec - startTime.tv_sec);
}
