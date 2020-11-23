#include "CToolBarEx.h"

BEGIN_MESSAGE_MAP(CToolBarEx, CToolBar)
    ON_WM_ERASEBKGND()
    ON_WM_PAINT()
END_MESSAGE_MAP()


IMPLEMENT_DYNAMIC(CToolBarEx, CToolBar)

CToolBarEx::CToolBarEx() : CToolBar()
{

}

CToolBarEx::~CToolBarEx()
{

}

BOOL CToolBarEx::OnEraseBkgnd(CDC* pDC)
{
    return FALSE;
}


void CToolBarEx::OnPaint()
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

    MenDC.FillSolidRect(&rect,dc.GetBkColor());


    DefWindowProc(WM_PAINT, (WPARAM)MenDC.m_hDC, (LPARAM)0);

    dc.BitBlt(0, 0, rect.Width(), rect.Height(), &MenDC, 0, 0, SRCCOPY);

    MenDC.DeleteDC();

    MemMap.DeleteObject();
}



BOOL CToolBarEx::Create(CWnd* pParentWnd, DWORD dwStyle, UINT nID)
{
    // TODO: Add your specialized code here and/or call the base class

    return CToolBar::Create(pParentWnd, dwStyle, nID);
}


BOOL CToolBarEx::CreateEx(CWnd* pParentWnd, DWORD dwCtrlStyle, DWORD dwStyle, CRect rcBorders, UINT nID)
{
    // TODO: Add your specialized code here and/or call the base class
    return CToolBar::CreateEx(pParentWnd, dwCtrlStyle, dwStyle, rcBorders, nID);
}


BOOL CToolBarEx::DestroyWindow()
{
    // TODO: Add your specialized code here and/or call the base class

    return CToolBar::DestroyWindow();
}


void CToolBarEx::DoDataExchange(CDataExchange* pDX)
{
    // TODO: Add your specialized code here and/or call the base class

    CToolBar::DoDataExchange(pDX);
}


LRESULT CToolBarEx::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
    // TODO: Add your specialized code here and/or call the base class

    return CToolBar::DefWindowProc(message, wParam, lParam);
}


BOOL CToolBarEx::PreCreateWindow(CREATESTRUCT& cs)
{
    // TODO: Add your specialized code here and/or call the base class

    return CToolBar::PreCreateWindow(cs);
}


BOOL CToolBarEx::PreTranslateMessage(MSG* pMsg)
{
    // TODO: Add your specialized code here and/or call the base class

    return CToolBar::PreTranslateMessage(pMsg);
}
