#include "stdafx.h"
#include "CBaseTreeCtrl.h"

BEGIN_MESSAGE_MAP(CBaseTreeCtrl, CTreeCtrl)
	ON_MESSAGE(TVM_INSERTITEM, OnInsertItem)
	ON_MESSAGE(WM_LBUTTONDBLCLK, OnLButtonDblClk)
	ON_MESSAGE(WM_LBUTTONDOWN, OnLButtonClk)
	ON_WM_MEASUREITEM_REFLECT()
	ON_WM_MEASUREITEM()
	ON_WM_PARENTNOTIFY()
	ON_WM_WINDOWPOSCHANGING()
END_MESSAGE_MAP()


LRESULT CBaseTreeCtrl::OnInsertItem(WPARAM wParam, LPARAM lParam)
{
	HTREEITEM hItem = (HTREEITEM)DefWindowProc(TVM_INSERTITEM, wParam, lParam);

	GetParent()->SendMessage(TVMYN_INSERTITEM, (WPARAM)hItem, 0);

	return (LRESULT)hItem;
}

LRESULT CBaseTreeCtrl::OnLButtonDblClk(WPARAM wParam, LPARAM lParam)
{
	short xPos = LOWORD(lParam);
	short yPos = HIWORD(lParam);

	TVHITTESTINFO HitTestInfo;

	HitTestInfo.pt.x = xPos;
	HitTestInfo.pt.y = yPos;

	HitTest(&HitTestInfo);
	if (HitTestInfo.flags == TVHT_ONITEMRIGHT)
	{
		CRect rc;
		GetItemRect(HitTestInfo.hItem, &rc, TRUE);
		xPos = (short)(rc.left + rc.Width() / 2);
		lParam = yPos;
		lParam <<= 16;
		lParam &= 0x0ffff0000;
		lParam += xPos;
	}

	return DefWindowProc(WM_LBUTTONDBLCLK, wParam, lParam);
}


LRESULT CBaseTreeCtrl::OnLButtonClk(WPARAM wParam, LPARAM lParam)
{
	short xPos = LOWORD(lParam);
	short yPos = HIWORD(lParam);

	TVHITTESTINFO HitTestInfo;

	HitTestInfo.pt.x = xPos;
	HitTestInfo.pt.y = yPos;

	HitTest(&HitTestInfo);
	if (HitTestInfo.flags == TVHT_ONITEMRIGHT)
	{
		CRect rc;
		GetItemRect(HitTestInfo.hItem, &rc, TRUE);
		xPos = (short)(rc.left + rc.Width() / 2);
		lParam = yPos;
		lParam <<= 16;
		lParam &= 0x0ffff0000;
		lParam += xPos;
	}

	return DefWindowProc(WM_LBUTTONDOWN, wParam, lParam);
}



void CBaseTreeCtrl::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	MakeItemHeight();
	if (m_nItemHeight > 0 )
	{
		lpMeasureItemStruct->itemHeight = m_nItemHeight;
	}
	else
	{
		m_nItemHeight = lpMeasureItemStruct->itemHeight;
	}

}


void CBaseTreeCtrl::MakeItemHeight()
{
	CDC* pDC = GetDC();
	auto	pFont = CDefaultAppFont::GetFont();
		CFont* pOldFont = pDC->SelectObject(pFont);
		TEXTMETRIC tm;
		GetTextMetrics(pDC->m_hDC, &tm);
		pDC->SelectObject(pOldFont);
		ReleaseDC(pDC);

		UINT newHeight = tm.tmHeight * 1.5;
		m_nItemHeight = newHeight;
	
}


void CBaseTreeCtrl::PreSubclassWindow()
{

	CTreeCtrl::PreSubclassWindow();
}


BOOL CBaseTreeCtrl::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{

	DWORD dwListStyle = LVS_REPORT | LVS_OWNERDRAWFIXED;

	return CTreeCtrl::Create(dwStyle , rect, pParentWnd, nID);
}

void CBaseTreeCtrl::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	MakeItemHeight();
	lpMeasureItemStruct->itemHeight = m_nItemHeight;
	CTreeCtrl::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}


void CBaseTreeCtrl::OnParentNotify(UINT message, LPARAM lParam)
{
	CTreeCtrl::OnParentNotify(message, lParam);
	if (LOWORD(message) == WM_CREATE)
	{


	}
	// TODO: Add your message handler code here
}




void CBaseTreeCtrl::OnWindowPosChanging(WINDOWPOS* lpwndpos)
{
	CFont* font = CDefaultAppFont::GetFont();
	CTreeCtrl::SetFont(font);
	CTreeCtrl::OnWindowPosChanging(lpwndpos);

	// TODO: Add your message handler code here
}
