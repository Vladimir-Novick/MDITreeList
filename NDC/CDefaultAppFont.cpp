#include "stdafx.h"
#include "CDefaultAppFont.h"
#include <map>
#include <string>


CDefaultAppFont CDefaultAppFont::instance;



CDefaultAppFont::~CDefaultAppFont() {

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
	return fonts[fontName];
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


void CDefaultAppFont::Destroy() {
	for (auto it = fonts.begin(); it != fonts.end(); ++it) {
		delete  it->second;
	}
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



