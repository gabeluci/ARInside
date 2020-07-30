//Copyright (C) 2011 John Luthgers | jls17
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
#include "ScanContainers.h"
#include "../ARInside.h"

CScanContainers::CScanContainers(CARContainer& container)
: cont(container)
{
}

CScanContainers::~CScanContainers(void)
{
}

void CScanContainers::Start()
{
	cout << "Checking container references";

	CARInside* pInside = CARInside::GetInstance();
	unsigned int cntCount = pInside->containerList.GetCount();
	for (unsigned int cntIndex = 0; cntIndex < cntCount; ++cntIndex)
	{
		CARContainer cnt(cntIndex);
		if (pInside->appConfig.bOverlaySupport && !IsVisibleObject(cnt))
			continue;

		if (IsOverlayOrCustom(cnt))
		{
			pInside->containerList.AddOverlayOrCustom(cnt.GetInsideId());
		}

		CScanContainers scanCont(cnt);
		scanCont.Scan();
	}
	cout << endl;
}

void CScanContainers::Scan()
{
	switch (cont.GetType())
	{
	case ARCON_GUIDE:
	case ARCON_FILTER_GUIDE:
	case ARCON_WEBSERVICE:
		{
			const ARContainerOwnerObjList& ownerList = cont.GetOwnerObjects();
			for (unsigned int ownerIndex = 0; ownerIndex < ownerList.numItems; ++ownerIndex)
			{
				if (ownerList.ownerObjList[ownerIndex].type == ARCONOWNER_SCHEMA)
				{
					CARSchema schema(ownerList.ownerObjList[ownerIndex].ownerName);
					if (schema.Exists())
					{
						switch (cont.GetType())
						{
						case ARCON_GUIDE:
							schema.AddActLinkGuide(cont);
							break;
						case ARCON_FILTER_GUIDE:
							schema.AddFilterGuide(cont);
							break;
						case ARCON_WEBSERVICE:
							schema.AddWebservice(cont);
							break;
						}
					}
				}
			}
		}
		break;
	case ARCON_PACK:
		{
			const ARReferenceList& refs = cont.GetContent();
			for (unsigned int refIndex = 0; refIndex < refs.numItems; ++refIndex)
			{
				if (refs.referenceList[refIndex].type == ARREF_SCHEMA && refs.referenceList[refIndex].reference.dataType == ARREF_DATA_ARSREF)
				{
					CARSchema schema(refs.referenceList[refIndex].reference.u.name);
					if (schema.Exists())
					{
						schema.AddPackingList(cont);
					}
				}

				if (refs.referenceList[refIndex].type == ARREF_CONTAINER)
				{
					CARContainer container(refs.referenceList[refIndex].reference.u.name);
					if (container.Exists())
					{
						CRefItem refItem(cont, REFM_PACKINGLIST);
						container.AddReference(refItem);
					}
				}
			}
		}
		break;
	}
}
