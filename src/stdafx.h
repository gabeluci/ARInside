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
#include <string>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <map>
#include <vector>
#include <time.h>
#include <stdlib.h> // JLS17_LINUX
#include <stdio.h>
#include <memory>
#include <iterator>
#include <algorithm>
#include <functional>
#include <assert.h>

#ifdef WIN32 // JLS17 LINUX
#include <windows.h>
#include <io.h>
#include <direct.h>
#include <shlwapi.h>
#else // WIN32
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#endif // WIN32
#include <errno.h>

#include <sys/stat.h>

#include "ARApi.h"
#include "util/Util.h"

extern const char* MenuSeparator;
extern const char* EmptyRunIf;
extern const char* EmptyValue;

using namespace std;
using std::for_each;

template<typename T>
void SortAndRemoveDuplicates(vector<T>& v) { sort(v.begin(), v.end()); v.erase(unique(v.begin(), v.end()), v.end()); }

// we use the zlibwapi.dll now to support 32- and 64-bit (http://www.winimage.com/zLibDll)
#define ZLIB_WINAPI
