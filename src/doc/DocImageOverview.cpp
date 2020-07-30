//Copyright (C) 2014 John Luthgers | jls17
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
#include "DocImageOverview.h"
#include "DocMain.h"
#include "../ARInside.h"
#include "../output/ImageTable.h"
#include "../output/LetterFilterControl.h"

CDocImageOverview::CDocImageOverview(void)
{
	pInside = CARInside::GetInstance();
	objCount = 0;
}

CDocImageOverview::~CDocImageOverview(void)
{
}

unsigned int CDocImageOverview::Build()
{
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_750
	// server version older than 7.5 ?? then there are no files to generate
	if (pInside->CompareServerVersion(7,5) < 0) return 0;

	CPageParams file(PAGE_OVERVIEW, AR_STRUCT_ITEM_XML_IMAGE);
	LetterFilterControl letterFilter;

	try
	{
		rootLevel = file->GetRootLevel();
		CImageTable imgTable(*pInside);

		unsigned int len = pInside->imageList.GetCount();
		for (unsigned int idx = 0; idx < len; ++idx)
		{
			CARImage img(idx);

#if AR_CURRENT_API_VERSION >= AR_API_VERSION_764
			if (pInside->appConfig.bOverlaySupport && !IsVisibleObject(img))
				continue;
#endif

			letterFilter.IncStartLetterOf(img);
			imgTable.AddRowJson(idx, rootLevel);
			objCount++;
		}

		if (objCount > 0)
		{
			imgTable.RemoveEmptyMessageRow();
		}

		CWebPage webPage(file->GetFileName(), "Image List", rootLevel, pInside->appConfig);
		SetupAdditionalPageResources(webPage);

		stringstream strmTmp;
		strmTmp << Header();
		strmTmp << CDocMain::CreateImageFilterControl() << endl;
		strmTmp << letterFilter;
		strmTmp << imgTable;
		
		webPage.AddContent(strmTmp.str());
		webPage.SaveInFolder(file->GetPath());
	}
	catch(exception& e)
	{
		cout << "EXCEPTION ImageList: " << e.what() << endl;
	}
#endif // AR_CURRENT_API_VERSION >= AR_API_VERSION_750
	return objCount;
}

void CDocImageOverview::SetupAdditionalPageResources(CWebPage &webPage)
{
	webPage.GetReferenceManager()
		.AddScriptReference("img/object_list.js")
		.AddScriptReference("img/imageList.js")
		.AddScriptReference("img/jquery.timers.js")
		.AddScriptReference("img/jquery.address.min.js");
}

std::string CDocImageOverview::Header()
{
#if AR_CURRENT_API_VERSION >= AR_API_VERSION_750
	return "<span id='imageListFilterResultCount'></span>" + CWebUtil::LinkToImageIndex(objCount, rootLevel);
#else
	return "";
#endif
}
