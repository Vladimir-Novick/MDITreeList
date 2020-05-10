#include "stdafx.h"
#include "CDefaultAppFont.h"
#include <map>
#include <string>
#include "CAppParamsMngr.h"


CDefaultAppFont CDefaultAppFont::instance;



CDefaultAppFont::~CDefaultAppFont() {
	DestroyObjects();
}

CDefaultAppFont* CDefaultAppFont::GetInstance() {

	return &instance;
}

UINT CDefaultAppFont::GetItemHeight(string fontName) {
	return heights[fontName];
}

void CDefaultAppFont::SetItemHeight(string fontName, UINT height) {
	heights[fontName] = height;
}

CFont* CDefaultAppFont::GetFont(string fontName) {
	CFont * font =  fonts[fontName];
	return font;
}

HBRUSH CDefaultAppFont::GetColor(string colorName,  COLORREF defaultColor) {
	
	if (colors.find(colorName) != colors.end()) {
		return colors[colorName];
	}
	return SetColor(colorName, defaultColor);
	
}

HBRUSH CDefaultAppFont::SetColor(string colorName, COLORREF color) {
	HBRUSH m_hBkgndBrush = CreateSolidBrush(color);
	if (colors.find(colorName) != colors.end()) {
		DeleteObject(colors[colorName]);
	}
	colors[colorName] = m_hBkgndBrush;
	return m_hBkgndBrush;
}




void CDefaultAppFont::SetColor(string colorName) {
	if (colors.find(colorName) != colors.end()) {
		DeleteObject(colors[colorName]);
		colors.erase(colorName);
	}
}

void CDefaultAppFont::SetFont(string fontName, LOGFONT& lf) {
	CFont* font = new CFont();
	font->CreateFontIndirect(&lf);
	SetFont(fontName, font);
}

void CDefaultAppFont::SetFont(string fontName, CFont* pFont) {
	CFont* oldFont = fonts[fontName];
	if (oldFont != NULL) {

		delete oldFont;
	}

	fonts[fontName] = pFont;
	UINT height = MakeItemHeight(pFont);
	SetItemHeight(fontName, height);
}


void CDefaultAppFont::DestroyObjects() {
	for (auto it = fonts.begin(); it != fonts.end(); ++it) {
		delete  it->second;
	}
	fonts.clear();
	for (auto it = colors.begin(); it != colors.end(); ++it) {
		DeleteObject(  it->second);
	}
	colors.clear();
	heights.clear();
}

UINT CDefaultAppFont::MakeItemHeight(CFont* pFont)
{
	auto mainWindow = AfxGetApp()->GetMainWnd();
	UINT newHeight = 0;
	if (mainWindow != NULL) {
		auto hDC = GetWindowDC(mainWindow->m_hWnd);
		CDC* pDC = CDC::FromHandle(hDC);
		CFont* pOldFont = pDC->SelectObject(pFont);
		TEXTMETRIC tm;
		GetTextMetrics(pDC->m_hDC, &tm);
		pDC->SelectObject(pOldFont);

		newHeight = tm.tmHeight * 1.4;
	}
	return newHeight;
}

CDefaultAppFont::CDefaultAppFont() {

}

void CDefaultAppFont::RedrawAllWindow()
{
	auto theApp = AfxGetApp();

	POSITION posT = theApp->GetFirstDocTemplatePosition();

	while (posT)
	{
		auto pTempl = theApp->GetNextDocTemplate(posT);

		POSITION posD = pTempl->GetFirstDocPosition();
		while (posD)
		{

			auto pDoc = pTempl->GetNextDoc(posD);


			POSITION posV = pDoc->GetFirstViewPosition();
			while (posV)
			{
				auto pView = pDoc->GetNextView(posV);
				if (pView != NULL) {
					//	auto hWnd = pView->m_hWnd;
					auto pFrame = pView->GetParentFrame();
					auto hWnd = pFrame->m_hWnd;
					if (hWnd != NULL) {
						//	 pView->Invalidate();

						// WM_SET_DEFAULT_APP_FONT

						RECT rect;

						::GetWindowRect(hWnd, &rect);

						bool retflag;

						int width;
						int height;
						width = rect.right - rect.left;
						height = rect.bottom - rect.top;
						WINDOWPLACEMENT placement;
						pFrame->GetWindowPlacement(&placement);

						pFrame->MoveWindow(placement.rcNormalPosition.left, placement.rcNormalPosition.top, width - 1, height - 1);

					}
				}

			}
		}
	}
}





COLORREF CDefaultAppFont::GetBrushColor(HBRUSH brush)
{
	LOGBRUSH lbr;
	if (GetObject(brush, sizeof(lbr), &lbr) != sizeof(lbr)) {
		return CLR_NONE;
	}
	if (lbr.lbStyle != BS_SOLID) {
		return CLR_NONE;
	}
	return lbr.lbColor;
}
