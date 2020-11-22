#include "CHeaderCtrlEx.h"
#include "StdAfx.h"

BEGIN_MESSAGE_MAP(CHeaderCtrlEx, CHeaderCtrl)
    ON_WM_ERASEBKGND()
    ON_WM_PAINT()
END_MESSAGE_MAP()


IMPLEMENT_DYNAMIC(CHeaderCtrlEx, CHeaderCtrl)

CHeaderCtrlEx::CHeaderCtrlEx() : CHeaderCtrl()
{

}

CHeaderCtrlEx::~CHeaderCtrlEx()
{

}

BOOL CHeaderCtrlEx::OnEraseBkgnd(CDC* pDC)
{
    return FALSE;
}


void CHeaderCtrlEx::OnPaint()
{
    CPaintDC dc(this); // device context for painting
                       // TODO: Add your message handler code here
                       // Do not call CListCtrl::OnPaint() for painting messages


    CRect rect;

    CDC MenDC;

    CBitmap MemMap;

    GetClientRect(&rect);

    MenDC.CreateCompatibleDC(&dc);

    MemMap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());

    MenDC.SelectObject(&MemMap);

    MenDC.FillSolidRect(&rect, RGB(240, 240, 240));


    DefWindowProc(WM_PAINT, (WPARAM)MenDC.m_hDC, (LPARAM)0);

    dc.BitBlt(0, 0, rect.Width(), rect.Height(), &MenDC, 0, 0, SRCCOPY);

    MenDC.DeleteDC();

    MemMap.DeleteObject();
}