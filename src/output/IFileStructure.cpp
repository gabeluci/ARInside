//Copyright (C) 2010 John Luthgers | jls17
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
#include "IFileStructure.h"
#include <assert.h>

// special ar-object includes
#include "../ARInside.h"
#include "../core/ARImage.h"

// include utils
#include "WebUtil.h"

using namespace OUTPUT;

///////////////////////////////////////////////////////////////////////////////
// constants
IFileNamingFactory *fileNames = NULL;

////////////////////////////////////////////////////////////////////
// strategy setup
void SetFileNamingStrategy(IFileNamingFactory* strat)
{
	assert(strat != NULL);
	fileNames = strat;
}

void InitFileNamingStrategy()
{
	assert(fileNames != NULL);
	fileNames->InitStructure();
}

void DestroyFileNamingStrategy()
{
	if (fileNames != NULL)
	{
		delete fileNames;
		fileNames = NULL;
	}
}

////////////////////////////////////////////////////////////////////
// CPageParams implementation
CPageParams::CPageParams(unsigned int page)
{
	this->page = page; 
	this->uint1 = 0; 
	this->uint2 = 0; 
	this->obj1 = NULL;
	InitFile();
}

CPageParams::CPageParams(unsigned int page, unsigned int uParam1)
{
	this->page = page; 
	this->uint1 = uParam1; 
	this->uint2 = 0; 
	this->obj1 = NULL;
	InitFile();
}

CPageParams::CPageParams(unsigned int page, unsigned int uParam1, unsigned int uParam2)
{
	this->page = page; 
	this->uint1 = uParam1; 
	this->uint2 = uParam2; 
	this->obj1 = NULL;
	InitFile();
}

CPageParams::CPageParams(unsigned int page, const CARServerObject* obj1)
{
	this->page = page; 
	this->uint1 = 0; 
	this->uint2 = 0; 
	this->obj1 = obj1;
	InitFile();
}

CPageParams::CPageParams(unsigned int page, unsigned int uParam1, const CARServerObject *obj1)
{
	this->page = page; 
	this->uint1 = uParam1; 
	this->uint2 = 0; 
	this->obj1 = obj1;
	InitFile();
}

CPageParams::CPageParams(const CPageParams& val, unsigned int page)
{
	this->page  = page;
	this->uint1 = val.uint1;
	this->uint2 = val.uint2;
	this->obj1  = val.obj1;
	InitFile();
}

CPageParams::~CPageParams()
{
	if (file != NULL) file->Release();
}

bool CPageParams::Valid() const
{
	return (file != NULL);
}

void CPageParams::InitFile()
{
	file = NULL;
	try
	{
		file = fileNames->GetFileNameOf(*this);
	}
	catch (exception e)
	{
		cout << "EXCEPTION in CPageParams::InitFile for page " << this->page << ": " << e.what() << endl;
	}
}

const IFileStructure* CPageParams::operator ->() const
{
#if DEBUG
	// maybe add some more checks in DEBUG build
#endif
	return file;
}
