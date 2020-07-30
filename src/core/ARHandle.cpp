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

#include "stdafx.h"
#include "ARHandle.h"
#include "../util/RefItem.h"
#include "../ARInside.h"

///////////////////////////////////////////////////////////////////////////////
// simple helper function; excluded from the template to avoid code duplication
CARServerObject* CreateObjectByRefItem(const CRefItem &refItem)
{
	if (refItem.GetObjectId() == -1) return NULL; // no object referenced

	switch (refItem.GetObjectType())
	{
	case AR_STRUCT_ITEM_XML_SCHEMA:
		return new CARSchema(refItem.GetObjectId());
	case AR_STRUCT_ITEM_XML_FIELD:
		{
			CARSchema schema(refItem.GetObjectId());
			if (!schema.Exists()) return NULL; // failed
			return new CARField(refItem.GetObjectId(), refItem.GetSubObjectId());
		}
	case AR_STRUCT_ITEM_XML_VUI:
		{
			CARSchema schema(refItem.GetObjectId());
			if (!schema.Exists()) return NULL; // failed
			return new CARVui(refItem.GetObjectId(), refItem.GetSubObjectId());
		}
	case AR_STRUCT_ITEM_XML_FILTER:
		return new CARFilter(refItem.GetObjectId());
	case AR_STRUCT_ITEM_XML_ACTIVE_LINK:
		return new CARActiveLink(refItem.GetObjectId());
	case AR_STRUCT_ITEM_XML_CHAR_MENU:
		return new CARCharMenu(refItem.GetObjectId());
		break;
	case AR_STRUCT_ITEM_XML_ESCALATION:
		return new CAREscalation(refItem.GetObjectId());
	// TODO: implement Distributed Mapping
	//case AR_STRUCT_ITEM_XML_DIST_MAP:
	//	break;
	case AR_STRUCT_ITEM_XML_CONTAINER:
		return new CARContainer(refItem.GetObjectId());
		break;
	// TODO: implement Distributed Pool
	//case AR_STRUCT_ITEM_XML_DIST_POOL:
	//	break;
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_750
	case AR_STRUCT_ITEM_IMAGE:
		return new CARImage(refItem.GetObjectId());
		break;
#endif
	default: 
		assert(true); /// Failure, this object is not supported!!!
		return NULL;
	}
}

///////////////////////////////////////////////////////////////////////////////
template<class C>
CARHandle<C>::CARHandle(const CRefItem& refItem)
{
	m_pObj = NULL;
	if (C::XmlTypeDef != refItem.GetObjectType())
		return;
	m_pObj = static_cast<C*>(CreateObjectByRefItem(refItem));
}

// in case it's just used for the base-class (CARServerObject) we don't have
// to check the type.
template<>
CARHandle<CARServerObject>::CARHandle(const CRefItem& refItem)
{
	m_pObj = CreateObjectByRefItem(refItem);
}

template<class C>
template<class T>
CARHandle<C>::CARHandle(const CARHandle<T> &otherHandle)
{
	if (otherHandle.Exists() && C::XmlTypeDef == otherHandle->GetServerObjectTypeXML())
		m_pObj = static_cast<C*>(otherHandle->Clone());
	else
		m_pObj = NULL;
}

template<>
template<class T>
CARHandle<CARServerObject>::CARHandle(const CARHandle<T> &otherHandle)
{
	if (otherHandle.Exists())
		m_pObj = otherHandle->Clone();
	else
		m_pObj = NULL;
}

template<class C>
CARHandle<C>::~CARHandle(void)
{
	if (m_pObj != NULL) delete m_pObj;
}

template<class C>
bool CARHandle<C>::Exists() const
{
	return (m_pObj != NULL && m_pObj->Exists());
}

///////////////////////////////////////////////////////////////////////////////
// now define the classes we've to generate
template class CARHandle<>;

//// NOTE: uncomment for future use ////
//template class CARHandle<CARActiveLink>;
//template CARHandle<CARActiveLink>::CARHandle(const CARHandle<CARServerObject> &);
//template CARHandle<CARServerObject>::CARHandle(const CARHandle<CARActiveLink> &);
//template class CARHandle<CARFilter>;
template class CARHandle<CARCharMenu>;
