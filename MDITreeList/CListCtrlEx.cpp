#include "CListCtrlEx.h"
#include "StdAfx.h"

BEGIN_MESSAGE_MAP(CListCtrlEx, CListCtrl)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
END_MESSAGE_MAP()


IMPLEMENT_DYNAMIC(CListCtrlEx, CListCtrl)

CListCtrlEx::CListCtrlEx() : CListCtrl()
{

}

CListCtrlEx::~CListCtrlEx()
{

}

BOOL CListCtrlEx::OnEraseBkgnd(CDC* pDC)
{
    return FALSE;
}


void CListCtrlEx::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CListCtrl::OnPaint() for painting messages

    CRect headerRect;

    CRect rect;

    CDC MenDC;

    CBitmap MemMap;

    GetClientRect(&rect);

    GetDlgItem(0)->GetWindowRect(&headerRect);

    MenDC.CreateCompatibleDC(&dc);

    MemMap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());

    MenDC.SelectObject(&MemMap);

    MenDC.FillSolidRect(&rect, dc.GetBkColor());

    DefWindowProc(WM_PAINT, (WPARAM)MenDC.m_hDC, (LPARAM)0);

    dc.BitBlt(0, headerRect.Height(), rect.Width(), rect.Height(), &MenDC, 0, headerRect.Height(), SRCCOPY);

    MenDC.DeleteDC();

    MemMap.DeleteObject();
}
