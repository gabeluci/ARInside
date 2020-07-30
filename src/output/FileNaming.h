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
#pragma once

#include "IFileStructure.h"

namespace OUTPUT 
{ 
	namespace FileNaming 
	{

		///////////////////////////////////////////////////////////////////////////////
		// Declare Default Implementation
		class DefaultFileNamingStrategy : public IFileNamingFactory
		{
		public:
			DefaultFileNamingStrategy() {}

			virtual void InitStructure();
			virtual IFileStructure* GetFileNameOf(CPageParams &params);
		};

		///////////////////////////////////////////////////////////////////////////////
		// Declare new naming implementation
		class ObjectNameFileNamingStrategy : public IFileNamingFactory
		{
		public:
			ObjectNameFileNamingStrategy() {}

			virtual void InitStructure();
			virtual IFileStructure* GetFileNameOf(CPageParams &params);
		};

	} 
} // end of namespaces
