//Copyright (C) 2012 John Luthgers | jls17
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
#include "ScanImages.h"
#include "../ARInside.h"

#if AR_CURRENT_API_VERSION >= AR_API_VERSION_750
CScanImages::CScanImages(CARImage& image)
: img(image)
{
}

CScanImages::~CScanImages(void)
{
}

void CScanImages::Start()
{
	cout << "Checking images references";

	CARInside* pInside = CARInside::GetInstance();
	unsigned int imgCount = pInside->imageList.GetCount();
	for (unsigned int imgIndex = 0; imgIndex < imgCount; ++imgIndex)
	{
		CARImage img(imgIndex);
		if (pInside->appConfig.bOverlaySupport && !IsVisibleObject(img))
			continue;

		if (IsOverlayOrCustom(img))
		{
			pInside->imageList.AddOverlayOrCustom(img.GetInsideId());
		}

		CScanImages scanImg(img);
		scanImg.Scan();
	}

	cout << endl;
}

void CScanImages::Scan()
{
}
#endif // AR_CURRENT_API_VERSION >= AR_API_VERSION_750
