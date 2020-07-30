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
//    along with ARInside.  If not, see <http://www.gnu.org/licenses/>.

#pragma once
#include "../ARApi.h"
#include "../core/AREnum.h"

// forward declarations
class CARInside;

// Some templates to use in combination with CARServerInfoList::LoadAndGetValue to retrieve a value
// and store it in a variable
// Use the StoreTo-function template to let the compiler determine the template argument type
// automatically
//
// example: ('dbType' should be a std::string)
// CARInside::GetInstance()->serverInfoList.LoadAndGetValue(AR_SERVER_INFO_DB_TYPE, StoreTo(dbType));
//

class CStoreToBase
{
public:
	virtual bool operator()(ARValueStruct* val) const = 0;
};

template<typename T>
class CStoreTo : public CStoreToBase
{
public:
	CStoreTo(T& v) : t(v) {}
	~CStoreTo() {}
	virtual bool operator()(ARValueStruct* val) const;

protected:
	T& t;
};

template<typename T>
CStoreTo<T> StoreTo(T &v) { return CStoreTo<T>(v); }


////////////////////// CARServerInfoList declaration //////////////////////
class CARServerInfoList
{
public:
	CARServerInfoList();
	~CARServerInfoList(void);

	// loading...
	bool Load();
	bool LoadAndGetValue(unsigned int serverInfoVal, const CStoreToBase& pred);

	// list functions
	unsigned int GetCount();
	int Find(int serverInfoId);

	// direct value functions
	ARValueStruct* GetValue(int serverInfoVal);

	// indexed data functions
	unsigned int GetOperation(int index);
	ARValueStruct* GetValueByIndex(int index);

	/**** internal ****/
private:
	ARServerInfoList serverInfo;
	ARServerInfoRequestList requestList;

	void FillRequest();
};
