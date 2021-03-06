// ListCtrlEx.cpp : implementation file
//

#include "stdafx.h"
#include "ListCtrlExt.h"
#include "..\..\NDC\ClientWnd.h"
#include "..\..\NDC\CDefaultAppFont.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListCtrl

CListCtrlExt::CListCtrlExt()
{
	
}

CListCtrlExt::~CListCtrlExt()
{
}


BEGIN_MESSAGE_MAP(CListCtrlExt, CListCtrl)
	//{{AFX_MSG_MAP(CListCtrlExt)
	ON_MESSAGE(WM_SETFONT, OnSetFont)
	ON_WM_MEASUREITEM_REFLECT()
	ON_WM_MEASUREITEM()
	//}}AFX_MSG_MAP
//	ON_WM_SIZING()
ON_WM_SIZE()
ON_WM_ERASEBKGND()
ON_WM_NCCALCSIZE()
ON_WM_PAINT()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListCtrlExt message handlers

void CListCtrlExt::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{

	CDC* pDC;
	pDC = CDC::FromHandle(lpDrawItemStruct->hDC);


	TCHAR  lpBuffer[256];

	LV_ITEM lvi;

	lvi.mask = LVIF_TEXT | LVIF_PARAM ;
	lvi.iItem = lpDrawItemStruct->itemID ; 	
	lvi.iSubItem = 0;
	lvi.pszText = lpBuffer ;
	lvi.cchTextMax = sizeof(lpBuffer);
	VERIFY(GetItem(&lvi));

	LV_COLUMN lvc, lvcprev ;
	::ZeroMemory(&lvc, sizeof(lvc));
	::ZeroMemory(&lvcprev, sizeof(lvcprev));
	lvc.mask = LVCF_WIDTH | LVCF_FMT;
	lvcprev.mask = LVCF_WIDTH | LVCF_FMT;

	for ( int nCol=0; GetColumn(nCol, &lvc); nCol++)
	{
		if ( nCol > 0 ) 
		{
			// Get Previous Column Width in order to move the next display item
			GetColumn(nCol-1, &lvcprev) ;
			lpDrawItemStruct->rcItem.left += lvcprev.cx ;
			lpDrawItemStruct->rcItem.right += lpDrawItemStruct->rcItem.left ;	
		}

		// Get the text 
		::ZeroMemory(&lvi, sizeof(lvi));
		lvi.iItem = lpDrawItemStruct->itemID;
		lvi.mask = LVIF_TEXT | LVIF_PARAM;
		lvi.iSubItem = nCol;
		lvi.pszText = lpBuffer;
		lvi.cchTextMax = sizeof(lpBuffer);
		VERIFY(GetItem(&lvi));



		if ( lpDrawItemStruct->itemState & ODS_SELECTED )
		{
			pDC->FillSolidRect(&lpDrawItemStruct->rcItem, GetSysColor(COLOR_HIGHLIGHT)) ; 
			pDC->SetTextColor(GetSysColor(COLOR_HIGHLIGHTTEXT)) ;
		}
		else
		{
			pDC->FillSolidRect(&lpDrawItemStruct->rcItem, GetSysColor(COLOR_WINDOW)) ;
			pDC->SetTextColor(GetSysColor(COLOR_WINDOWTEXT)) ; 
		}
		
		pDC->SelectObject(GetStockObject(DEFAULT_GUI_FONT));

		UINT		uFormat    = DT_LEFT ;


		CFont* pFont = CDefaultAppFont::GetInstance()->GetFont(TREE_FONT_NAME);
		CDC cDC;
		cDC.Attach(lpDrawItemStruct->hDC);
		auto oldFont = cDC.SelectObject(pFont);
		::DrawText(lpDrawItemStruct->hDC, lpBuffer, _tcslen(lpBuffer),
			 &lpDrawItemStruct->rcItem, uFormat) ;
			cDC.SelectObject(oldFont) ;
			cDC.Detach();
	}
}

LRESULT CListCtrlExt::OnSetFont(WPARAM wParam, LPARAM lParam)
{
	CRect rc;
	GetWindowRect(&rc);

	WINDOWPOS wp;
	wp.hwnd = this->m_hWnd;
	wp.cx = rc.Width() ;
	wp.cy = rc.Height() ;
	wp.flags = SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER;

	LRESULT lrReturn(Default());

	SendMessage(WM_WINDOWPOSCHANGED, 0, reinterpret_cast<LPARAM> (&wp));

	return lrReturn;
}

void CListCtrlExt::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{

	auto height  = CDefaultAppFont::GetInstance()->GetItemHeight(TREE_FONT_NAME);
		lpMeasureItemStruct->itemHeight = height * (m_nLinesPerRow);
}


void CListCtrlExt::OnInitialUpdate() 
{
	int i, j ;

	LV_COLUMN lvc;
	lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

	// Insert Header columns
	for(i = 0; i<m_nColumns; i++)
	{
		lvc.iSubItem = i;
		lvc.pszText = _gszColumnLabel[i];
		lvc.cx = _gnColumnWidth[i];
		lvc.fmt = _gnColumnFmt[i];
		InsertColumn(i,&lvc);
	}

	// Insert First Column items for every row
	LV_ITEM lvi;
	lvi.mask = LVIF_TEXT | LVIF_STATE ;

	TCHAR	buf[51] ;
	for(i=0; i<m_nRows; i++)
	{
		swprintf(buf, L"Line 1 text \n lots a a \n more text") ;
		lvi.iItem = i;
		lvi.iSubItem = 0;
		lvi.state = LVIS_SELECTED | LVIS_FOCUSED ;
		lvi.stateMask = LVIS_SELECTED | LVIS_FOCUSED ;
		lvi.pszText = buf ;
		InsertItem(&lvi);

        if (i == 0) m_nLinesPerRow = 3;
		else m_nLinesPerRow = 5;

		for(j = 1; j<m_nColumns; j++)
		{

			SetItemText(i,j,_gszItem[i][j]);
		}
	}

//	if ( m_nLinesPerRow > 1 ) 
//	{
		m_NewListFont.CreatePointFont(180,L"MS Serif");
		SetFont(&m_NewListFont);
//	}

	CHeaderCtrl* pHeader = NULL;
	pHeader=GetHeaderCtrl();

	if(pHeader==NULL)
		return;
	
	VERIFY(m_HeaderCtrl.SubclassWindow(pHeader->m_hWnd));	

	HDITEM hdItem;

	hdItem.mask = HDI_FORMAT;

	for(i=0; i<m_HeaderCtrl.GetItemCount(); i++)
	{
		m_HeaderCtrl.GetItem(i,&hdItem);

		hdItem.fmt|= HDF_OWNERDRAW;
		
		m_HeaderCtrl.SetItem(i,&hdItem);
	}

}

void CListCtrlExt::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{

	CListCtrl::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}


void CListCtrlExt::OnSize(UINT nType, int cx, int cy)
{
	CListCtrl::OnSize(nType, cx, cy);

	CRect rb;

	LockWindowUpdate();

	double currentSize = 0;

	CHeaderCtrl* pHeader = NULL;
	pHeader = GetHeaderCtrl();



	if (pHeader->m_hWnd != NULL) {

		for (int i = 0; i < pHeader->GetItemCount(); i++)
		{
			int nWidth = GetColumnWidth(i);
			currentSize += nWidth;
		}

		double m = cx / currentSize;

		for (int i = 0; i < pHeader->GetItemCount(); i++)
		{
			int nWidth = GetColumnWidth(i);
			
			double  d = nWidth *= m;
			DWORD w = d;
			SetColumnWidth(i, w);
		}
	}
	 


	
	UnlockWindowUpdate();
	

	// TODO: Add your message handler code here
}


BOOL CListCtrlExt::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return FALSE;
}


void CListCtrlExt::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp)
{
	// TODO: Add your message handler code here and/or call default

	CListCtrl::OnNcCalcSize(bCalcValidRects, lpncsp);
}


void CListCtrlExt::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CListCtrl::OnPaint() for painting messages

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
