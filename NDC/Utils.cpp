#include "StdAfx.h"
#include "Utils.h"

namespace NDC {

	COLORREF Utils::CheckTextColor(COLORREF backgroundColor)
	{
		COLORREF clrForground;

		INT blue = GetBValue(backgroundColor);
		INT green = GetGValue(backgroundColor);
		INT red = GetRValue(backgroundColor);

		double Y = sqrt(red * red * 0.299 + green * green * 0.587 + blue * blue * 0.114);
		if (Y > 130) { // light backgrownd
			clrForground = RGB(7, 25, 25); // black
		}
		else {
			clrForground = RGB(250, 250, 250); // white
		}
		return clrForground;
	}

}
