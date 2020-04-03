// ClientWnd.cpp : implementation file
//

#include "stdafx.h"
#include "ClientWnd.h"

// CClientWnd
/// <summary>
///    Client Window for MDI Frame. Support erase backgrownd to custom color 
/// </summary>

IMPLEMENT_DYNAMIC(CClientWnd, CWnd)
CClientWnd::CClientWnd()
{
}

CClientWnd::~CClientWnd()
{
}

BEGIN_MESSAGE_MAP(CClientWnd, CWnd)
   ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


BOOL CClientWnd::OnEraseBkgnd(CDC* pDC)
{
   CRect Rect;
   GetClientRect(&Rect);
   pDC->FillSolidRect(&Rect,RGB(168, 178, 198)); // A8B2C6

   return TRUE;
}


CFont* CDefaultAppFont::GetFont() {
    return AppDefaultFont;
}

void CDefaultAppFont::SetFont(CFont* font) {
    AppDefaultFont = font;
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
				auto pFrame = pView->GetParentFrame();
				if (pFrame != NULL) {
				auto hWnd = pFrame->m_hWnd;

					RECT rect;
					::GetWindowRect(hWnd, &rect);
	
					int height, width;
					width =  rect.right - rect.left;
					height = rect.bottom - rect.top;

					WINDOWPLACEMENT placement;
					pFrame->GetWindowPlacement(&placement);

					pFrame->MoveWindow(placement.rcNormalPosition.left, placement.rcNormalPosition.top, width - 1, height - 1);

				}

			}
		}
	}
}

CFont* CDefaultAppFont::AppDefaultFont;
