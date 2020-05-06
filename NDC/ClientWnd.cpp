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

