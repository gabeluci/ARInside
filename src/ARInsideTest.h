#pragma once

#include "stdafx.h"
// http://code.google.com/p/googletest/
#include "gtest/gtest.h"

//To avoid a warning in the RapidJSON tests https://stackoverflow.com/a/37110288/1202807
#define RAPIDJSON_NO_SIZETYPEDEFINE
namespace rapidjson { typedef ::std::size_t SizeType; }

extern char* argv_0;
