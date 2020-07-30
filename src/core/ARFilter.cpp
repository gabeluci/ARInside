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
#include "ARFilter.h"
#include "../ARInside.h"

CARFilter::CARFilter()
: CARServerObject(-1)
{
}

CARFilter::CARFilter(int insideId)
: CARServerObject(insideId)
{
}

CARFilter::CARFilter(const string& name)
: CARServerObject(-1)
{
	insideId = CARInside::GetInstance()->filterList.Find(name.c_str());
}

CARFilter::~CARFilter(void)
{
}

bool CARFilter::IsClonable() const
{
	return true;
}

CARServerObject* CARFilter::Clone() const
{
	return new CARFilter(*this);
}

bool CARFilter::Exists() const
{
	return (insideId >= 0 && (unsigned int)insideId < CARInside::GetInstance()->filterList.GetCount());
}

string CARFilter::GetExecuteOn(bool singleLine)
{		
	stringstream strm;
	strm.str("");
	bool strmHasContent = false; // use a local var to avoid use of 'strm.str().empty', because this make a copy of the string buffer evrytime

	try
	{
		typedef	struct ARInsideExecOnStruct {
			unsigned int exec;
			const char   *text;
		} ARInsideExecOnStruct;

		const ARInsideExecOnStruct executeText[] = {
			AR_OPERATION_GET, "Get Entry",
			AR_OPERATION_SET, "Modify",
			AR_OPERATION_CREATE, "Submit",
			AR_OPERATION_DELETE, "Delete",
			AR_OPERATION_MERGE, "Merge",
			//AR_OPERATION_GUIDE, "???"			// maybe used before containers exists
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_710 // Version 7.1 and higher
			AR_OPERATION_SERVICE, "Service",
#endif
			0, NULL
		};

		unsigned int opSet = this->GetOperation();
		for (unsigned int k = 0; true; ++k)
		{
			if (executeText[k].exec == 0) break;

			if ( (opSet & executeText[k].exec) != 0)
			{
				if (!singleLine && strmHasContent) strm << "<br/>";
				if (singleLine && strmHasContent) strm << ", ";
				strm << executeText[k].text;
				strmHasContent = true;
			}
		}	

		if(!strmHasContent)
		{
			strm << "None";
		}
	}
	catch(exception& e)
	{
		cout << "EXCEPTION in Filter GetExecuteOn: " << e.what() << endl; 
	}
	return strm.str();
}

string CARFilter::GetName()
{
	return CARInside::GetInstance()->filterList.FilterGetName(GetInsideId());
}

string CARFilter::GetName() const
{
	return CARInside::GetInstance()->filterList.FilterGetName(GetInsideId());
}

string CARFilter::GetNameFirstChar()
{
	return CARObject::GetNameFirstChar(CARInside::GetInstance()->filterList.FilterGetName(GetInsideId()));
}

bool CARFilter::NameStandardFirstChar()
{
	return CARObject::NameStandardFirstChar(GetNameFirstChar());
}

unsigned int CARFilter::GetOrder() const
{ 
	return CARInside::GetInstance()->filterList.FilterGetOrder(GetInsideId());
}

const ARWorkflowConnectStruct& CARFilter::GetSchemaList() const 
{ 
	return CARInside::GetInstance()->filterList.FilterGetSchemaList(GetInsideId());
}

unsigned int CARFilter::GetOperation()
{
	return CARInside::GetInstance()->filterList.FilterGetOperation(GetInsideId());
}

unsigned int CARFilter::GetEnabled()
{ 
	return CARInside::GetInstance()->filterList.FilterGetEnabled(GetInsideId());
}
	
const ARQualifierStruct& CARFilter::GetRunIf() const 
{ 
	return CARInside::GetInstance()->filterList.FilterGetRunIf(GetInsideId()); 
}

const ARFilterActionList& CARFilter::GetIfActions() const
{ 
	return CARInside::GetInstance()->filterList.FilterGetIfActions(GetInsideId());
}

const ARFilterActionList& CARFilter::GetElseActions() const
{
	return CARInside::GetInstance()->filterList.FilterGetElseActions(GetInsideId());
}

const ARPropList& CARFilter::GetPropList() const
{
	return CARInside::GetInstance()->filterList.FilterGetPropList(GetInsideId());
}

const string& CARFilter::GetAppRefName() const
{
	return CARInside::GetInstance()->filterList.FilterGetAppRefName(GetInsideId());
}

void CARFilter::SetAppRefName(const string &appName)
{
	return CARInside::GetInstance()->filterList.FilterSetAppRefName(GetInsideId(), appName);
}

const char* CARFilter::GetHelpText() const
{
	return CARInside::GetInstance()->filterList.FilterGetHelptext(GetInsideId());
}

ARTimestamp CARFilter::GetTimestamp() const
{
	return CARInside::GetInstance()->filterList.FilterGetTimestamp(GetInsideId());
}

const ARAccessNameType& CARFilter::GetOwner() const
{
	return CARInside::GetInstance()->filterList.FilterGetOwner(GetInsideId());
}

const ARAccessNameType& CARFilter::GetLastChanged() const
{
	return CARInside::GetInstance()->filterList.FilterGetModifiedBy(GetInsideId());
}

const char* CARFilter::GetChangeDiary() const
{
	return CARInside::GetInstance()->filterList.FilterGetChangeDiary(GetInsideId());
}

unsigned int CARFilter::GetErrorOption()
{
	return CARInside::GetInstance()->filterList.FilterGetErrorOption(GetInsideId());
}

const ARNameType& CARFilter::GetErrorHandler() const
{
	return CARInside::GetInstance()->filterList.FilterGetErrorHandler(GetInsideId());
}

vector<unsigned int>& CARFilter::ErrorCallers()
{
	return CARInside::GetInstance()->filterList.FilterErrorCallers(GetInsideId());
}
