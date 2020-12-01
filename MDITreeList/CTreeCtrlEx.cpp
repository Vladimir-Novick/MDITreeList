#include "stdafx.h"
#include "CTreeCtrlEx.h"

BEGIN_MESSAGE_MAP(CTreeCtrlEx, CTreeCtrl)

	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_PAINT()
END_MESSAGE_MAP()

IMPLEMENT_DYNAMIC(CTreeCtrlEx, CTreeCtrl)

CTreeCtrlEx::CTreeCtrlEx() :CTreeCtrl() {

}

CTreeCtrlEx::~CTreeCtrlEx()  {

}

BOOL CTreeCtrlEx::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	return FALSE;
//	return CTreeCtrl::OnEraseBkgnd(pDC);
}


void CTreeCtrlEx::OnSize(UINT nType, int cx, int cy)
{

	CTreeCtrl::OnSize(nType, cx, cy);


	// TODO: Add your message handler code here
}


void CTreeCtrlEx::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CTreeCtrl::OnPaint() for painting messages

    CRect headerRect;

    CRect rect;

    CDC MenDC;//memory ID list. 

    CBitmap MemMap;

    GetClientRect(&rect);

    GetDlgItem(0)->GetWindowRect(&headerRect);

    MenDC.CreateCompatibleDC(&dc);

    MemMap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());

    MenDC.SelectObject(&MemMap);

    MenDC.FillSolidRect(&rect, dc.GetBkColor());

    //Call the default OnPaint () to draw the graphic on the Memory DC table  

    DefWindowProc(WM_PAINT, (WPARAM)MenDC.m_hDC, (LPARAM)0);

    //output  

    dc.BitBlt(0, headerRect.Height(), rect.Width(), rect.Height(), &MenDC, 0, headerRect.Height(), SRCCOPY);

    MenDC.DeleteDC();

    MemMap.DeleteObject();

}
