//Copyright (C) 2012 John Luthgers | jls17@gmx.net
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

// forward declarations
class CRefItem;
class CARServerObject;

/******************************************************************************
 * This class could be used to access the real workflow object of a CRefItem. *
 * It automatically handles allocation and deletion of the underlying object  *
 * instance.
 *
 * 1) specify the class of the reference object as template argument and
 *    the reference item as the constructor argument
 *    e.g: CARHandle<CARActiveLink> myAL(theRefItem);
 * 2) use the Exists method to check if the object is valid and accessible
 *    e.g: if (myAL.Exists()) ...
 * 3) use the "->" operator to access the methods of the template argument
 *    e.g: myAL->GetOrder(); 
 *         myAL->GetName();
 *
 * Example 1:   // creates ref-object as CARServerObject
 * CARHandle<> hObj(refItem);   
 * if (hObj.Exists()) 
 * {
 *   string objName = hObj->GetName();
 * }
 *
 * Example 2: // creates ref-object as CARActiveLink
 * CARHandle<CARActiveLink> hActlink(refItem);
 * if (hActlink.Exists())
 * {
 *   int execOrder = hActlink->GetOrder();
 * }
 *
 * NOTE: check ARHandle.cpp at the bottom to fix any "unresolved external"
 *       issues.
 */

template<class C = CARServerObject>
class CARHandle
{
public:
	CARHandle(const CRefItem &refItem);
	template<class T> CARHandle(const CARHandle<T> &otherHandle);
	~CARHandle(void);

	bool Exists() const;
	inline C* operator ->() const { return m_pObj; }
	inline C& operator *() const { return *m_pObj; }

private:
	C *m_pObj;
};
