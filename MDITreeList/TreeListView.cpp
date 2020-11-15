

#include "stdafx.h"
#include "TreeListView.h"

#include "CBaseTreeCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define TVS_EX_DOUBLEBUFFER         0x0004

static long StretchWidth(long nWidth, long nMeasure)
{
	return ((nWidth / nMeasure) + 1) * nMeasure;
}


CBaseTreeObj& CBaseTreeObj::operator=(CBaseTreeObj& obj)
{
	m_strColumns.SetSize(obj.m_strColumns.GetSize());

	// the CStringArray class doesn't have a operator= so copy the data by hand
	for(long i=0; i < obj.m_strColumns.GetSize(); i++)
	{
		m_strColumns[i] = obj.m_strColumns[i];
	}

	return *this;
}

//************************************ CTreeListView ******************************************************


IMPLEMENT_DYNCREATE(CTreeListView, CView)

BEGIN_MESSAGE_MAP(CTreeListView, CView)
	//{{AFX_MSG_MAP(CTreeListView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
	ON_MESSAGE(TVMYN_INSERTITEM, OnInsertItem)
	ON_WM_WINDOWPOSCHANGING()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

/************************************
 constructors and destructors
************************************/
//  initialises all variables
CTreeListView::CTreeListView()
{
	m_bDescriptionDisplay = true;									// normaly we have columnheaders
	m_nOffset = 0;													// we have not scrolled yet
	m_nHeaderWidth = 0;												// the width of the columns is zero because we have no
	m_colBackColor = RGB(255, 255, 255);							// the back color is set to white for erasing (may have other values, used for the future)
	m_vsCol = NULL;													// there are no columns so there is no data
	m_nNrColumns = 0;												// the number of columns is zero
	m_BackBrush.CreateSolidBrush(::GetSysColor(COLOR_HIGHLIGHT));	// the backgroundbrush for highlightet text is inistialised with the default value (system)
	m_colHilightText = ::GetSysColor(COLOR_HIGHLIGHTTEXT);			// the textcolor for highlightet text is inistialised with the default value (system)
	m_colText = RGB(0,0,0);											// the normal textcolor is black (may have other values, used for the future)
	m_BackBrushNormal.CreateSolidBrush( m_colBackColor );			// a proposal from codeguru (anonymus)
}

//  frees all memory
CTreeListView::~CTreeListView()
{
	// deletre dynamic array
	if(m_vsCol != NULL)
	{
		delete []m_vsCol;
	}
	
	m_nNrColumns = 0;
}

void CTreeListView::OnDraw(CDC* pDC) 
{
	UNUSED_PARAM(pDC);
}


BOOL CTreeListView::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	LPNMHDR pNmhdr = (LPNMHDR)lParam;

	//TreeCtrl notifications
	if(m_List.m_hWnd == pNmhdr->hwndFrom)
	{
		switch (pNmhdr->code)
		{
		case NM_CUSTOMDRAW:
			return OnCustomdrawTree(pNmhdr, pResult);
		case TVN_DELETEITEM:
			return OnDeleteItem(pNmhdr, pResult);
		}
	}

	else if(m_ctrlHeader.m_hWnd == pNmhdr->hwndFrom)
	{
		switch (pNmhdr->code)
		{
		case HDN_ENDTRACK:
			return OnEndTrack(pNmhdr, pResult);
		}
	}

	return CView::OnNotify(wParam, lParam, pResult);
}


int CTreeListView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// set all rects to zero because OnSize is called after creating the windows and we give them the positions in OnSize
	
	CRect rcHeader(0,0,0,0);
	CRect rcTree(0,0,0,0);
	DWORD dwStyle = 0;
	dwStyle = WS_CHILD | WS_VISIBLE | HDS_BUTTONS | HDS_HORZ;
	m_ctrlHeader.Create(dwStyle, rcHeader, this, 0);
	// first create the TreeCtrl. I use standard styles but you can also use your own styles or get TreeCtrl styles from the parameter
	dwStyle = WS_CHILD | WS_VISIBLE |  TVS_DISABLEDRAGDROP | TVS_NOHSCROLL | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS ;
	//dwStyle = LVS_REPORT |
	//	LVS_SINGLESEL | LVS_OWNERDRAWFIXED | WS_BORDER |
	//	WS_TABSTOP;
	m_List.Create(dwStyle, rcTree, this, 0);

	
	HRESULT h = TreeView_SetExtendedStyle(m_List.m_hWnd,
		TVS_EX_DOUBLEBUFFER, TVS_EX_DOUBLEBUFFER);
	// next create the HeaderCtrl. I use standard styles but you can also use your own styles or get HeaderCtrl styles from the parameter
	//TreeView_SetExtendedStyle(m_List.m_hWnd, TVS_EX_AUTOHSCROLL, TVS_EX_AUTOHSCROLL | TVS_EX_MULTISELECT);
	
	return 0;
}


void CTreeListView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);

	SizeObjects();
}


void CTreeListView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	UNUSED_PARAM(pScrollBar);

	CRect	rc;
	// Calculate Scrollsizes
	m_List.GetClientRect(&rc);

	long	nWidthPage	= abs(rc.right - rc.left);	// One Page
	long	nWidthLine	= 6;						// Microsofts Linestep in a CListCtrl, got from MFC - sourcecode
	long	nCurPos		= GetScrollPos(SB_HORZ);	// current scrollingposition
	long	nPrevPos	= nCurPos;;					// save current scrolling position for calculating
	int		nScrollMin;								// minimum scrolling value
	int		nScrollMax;								// maximum scrolling value

	GetScrollRange(SB_HORZ, &nScrollMin, &nScrollMax);

	// Check, which kind of scoll is wanted
	switch(nSBCode)
	{
	case SB_LEFT :								// scoll to left most position
		{
			nCurPos = 0;
			break;
		}
	case SB_RIGHT :								// scroll to right most position
		{
			nCurPos = nScrollMax;
			break;
		}
	case SB_LINELEFT :							// scroll left with the button
		{
			nCurPos = max(nCurPos - nWidthLine, 0);
			break;
		}
	case SB_LINERIGHT :							// scroll right with the button
		{
			nCurPos = min(nCurPos + nWidthLine, nScrollMax);
			break;
		}
	case SB_PAGELEFT :							// scroll left with a click to the background of the scrollbar
		{
			nCurPos = max(nCurPos - nWidthPage, 0);
			break;
		}
	case SB_PAGERIGHT :							// scroll left with a click to the background of the scrollbar
		{
			nCurPos = min(nCurPos + nWidthPage, nScrollMax);
			break;
		}
	case SB_THUMBPOSITION :						// scroll by moving the scrollbutton with the mouse
	case SB_THUMBTRACK :						// drop the scrollbarbutton
		{
			// check for illegal positions and correct them (out of the scrollbar?)
			if(nPos == 0)
			{
				nCurPos = 0;
			}
			else
			{
				nCurPos = min(StretchWidth(nPos, nWidthLine), nScrollMax);
			}
			break;
		}
	default:
		{
			break;
		}
	};

	// move the scrollbarbutton to the position (graphically)
	SetScrollPos(SB_HORZ, nCurPos, TRUE);
	m_nOffset = -nCurPos;

	// smoothly Scroll the Tree control
	CRect rcTree;
	m_List.GetClientRect(&rcTree);
	m_List.ScrollWindowEx(nPrevPos - nCurPos, 0, NULL, NULL, NULL, NULL, SW_INVALIDATE);

	// Scroll the Header
	CRect rcHeader;
	GetClientRect(&rc);
	m_ctrlHeader.GetClientRect(&rcHeader);

	if(rcTree.right - rcTree.left != 0)
	{
		m_ctrlHeader.SetWindowPos(&wndTop, m_nOffset, 0, max(StretchWidth(m_nHeaderWidth, abs(rcTree.right - rcTree.left)), nWidthPage), abs(rcHeader.bottom - rcHeader.top), SWP_SHOWWINDOW);
	}

	// redraw the treecontrol so you can see the scrolling
	m_List.Invalidate(TRUE);
}


LRESULT CTreeListView::OnInsertItem(WPARAM wParam, LPARAM lParam)
{
	UNUSED_PARAM(lParam);

	// get the treeitem
	HTREEITEM hItem = (HTREEITEM) wParam;
	CString str = m_List.GetItemText(hItem);

	// insert a new item in the ObjectMap
	CBaseTreeObj MyObj;
	MyObj.m_strColumns.SetSize(m_nNrColumns);
	MyObj.m_strColumns[0] = str;

	m_Entries.SetAt(hItem, MyObj);

	return 0;
}



int CTreeListView::InsertColumn( int nCol, LPCTSTR lpszColumnHeading, int nFormat, int nWidth, int nSubItem)
{
	// Create the LVCOLUMN struct and fill it an call the InsertColumn with two parameters
	LVCOLUMN column;
	column.mask = LVCF_TEXT|LVCF_FMT;
	column.pszText = (LPTSTR)lpszColumnHeading;
	column.fmt = nFormat;
	if (nWidth != -1)
	{
		column.mask |= LVCF_WIDTH;
		column.cx = nWidth;
	}
	if (nSubItem != -1)
	{
		column.mask |= LVCF_SUBITEM;
		column.iSubItem = nSubItem;
	}
	return InsertColumn(nCol, &column);
}


int CTreeListView::InsertColumn( int nCol, const LVCOLUMN* pColumn )
{
	// generate and initialise a new headeritem
	HDITEM hdi;
	::ZeroMemory(&hdi, sizeof(HDITEM));

	// fill the formatbits 
	if(pColumn->mask & LVCF_FMT)
	{
		hdi.mask |= HDI_FORMAT;

		if(pColumn->fmt & LVCFMT_BITMAP_ON_RIGHT)
			hdi.fmt |= HDF_BITMAP_ON_RIGHT;
		if(pColumn->fmt & LVCFMT_CENTER)
			hdi.fmt |= HDF_CENTER;
		if(pColumn->fmt & LVCFMT_COL_HAS_IMAGES)
			hdi.fmt |= HDF_IMAGE;
		if(pColumn->fmt & LVCFMT_IMAGE)
			hdi.fmt |= HDF_IMAGE;
		if(pColumn->fmt & LVCFMT_JUSTIFYMASK)
			hdi.fmt |= HDF_JUSTIFYMASK;
		if(pColumn->fmt & LVCFMT_LEFT)
			hdi.fmt |= HDF_LEFT;
		if(pColumn->fmt & LVCFMT_RIGHT)
			hdi.fmt |= HDF_RIGHT;
	}

	// should an image be displayed?
	if(pColumn->mask & LVCF_IMAGE)
	{
		hdi.mask |= HDI_IMAGE;
		hdi.iImage = pColumn->iImage;
	}
	
	// insert the column at the spezified position
	if(pColumn->mask & LVCF_ORDER)
	{
		hdi.mask |= HDI_ORDER;
		hdi.iOrder = pColumn->iOrder;
	}

	// dispay a text ?
	if(pColumn->mask & LVCF_TEXT)
	{
		hdi.mask |= HDI_TEXT;
		hdi.pszText = pColumn->pszText;
		hdi.cchTextMax = pColumn->cchTextMax;
	}

	// set a width?
	if(pColumn->mask & LVCF_WIDTH)
	{
		hdi.mask |= HDI_WIDTH;
		hdi.cxy = pColumn->cx;
	}

	// insert the item
	long rCol = m_ctrlHeader.InsertItem(nCol, &hdi);
	m_nNrColumns++;

	// update the internal Lists with the columntexts for the objects
	POSITION pos = m_Entries.GetStartPosition();
	HTREEITEM hItem;
	while(pos != NULL)
	{
		CBaseTreeObj item;
		m_Entries.GetNextAssoc(pos, hItem, item);
		item.m_strColumns.InsertAt(rCol, _T(""), 1);
	}

	UpdateColStruct();

	return rCol;
}


BOOL CTreeListView::DeleteColumn( int nCol )
{
	BOOL bRet = m_ctrlHeader.DeleteItem(nCol);

	// if the specified column could be deleted, delete the columns in our textarray
	if(bRet == TRUE)
	{
		m_nNrColumns--;

		POSITION pos = m_Entries.GetStartPosition();
		HTREEITEM hItem;
		while(pos != NULL)
		{
			CBaseTreeObj item;
			m_Entries.GetNextAssoc(pos, hItem, item);
			item.m_strColumns.RemoveAt(nCol, 1);
		}
	}

	UpdateColStruct();
	return bRet;
}


BOOL CTreeListView::SetSubItemText( HTREEITEM hItem, int nSubItem, CString strBuffer)
{
	BOOL bRet = TRUE;

	// set the new text
	m_Entries[hItem].m_strColumns[nSubItem] = strBuffer;;

	return bRet;
}


BOOL CTreeListView::GetSubItemText( HTREEITEM hItem, int nSubItem, CString& strBuffer)
{
	BOOL bRet = TRUE;

	strBuffer = m_Entries[hItem].m_strColumns[nSubItem];

	return bRet;
}


CImageList* CTreeListView::GetHeaderImageList()
{
	return m_ctrlHeader.GetImageList();
}


CImageList* CTreeListView::SetHeaderImageList( CImageList * pImageList)
{
	return m_ctrlHeader.SetImageList(pImageList);
}


CTreeCtrl& CTreeListView::GetTreeCtrl()
{
	return m_List;
}


void CTreeListView::ShowHeader(bool bShow)
{
	if(bShow != m_bDescriptionDisplay)
	{
		m_bDescriptionDisplay = bShow;
		SizeObjects();
	}
}


void CTreeListView::CalculateClientRects(CRect &rcBase, CRect &rcTree, CRect &rcHeader)
{
	// Perhapse, show Header
	if(m_bDescriptionDisplay == TRUE)
	{
		rcHeader = rcBase;
		rcHeader.bottom = rcHeader.top + ::GetSystemMetrics(SM_CYMENU);
	}
	else
	{
		RECT rc = {0,0,0,0};
		rcHeader = rc;
	}

	rcTree = rcBase;
	rcTree.top = rcHeader.bottom;
}


void CTreeListView::SizeObjects()
{
	ResetScrollbar();

	CRect rcBase;
	CRect rcTree;
	CRect rcHeader;
	long nOffset = m_nOffset;

	GetClientRect(&rcBase);
	CalculateClientRects(rcBase, rcTree, rcHeader);

	UpdateColStruct();



	m_ctrlHeader.SetWindowPos(&wndTop, rcHeader.left, rcHeader.top, rcHeader.Width(), rcHeader.Height(), SWP_NOZORDER);
	m_List.SetWindowPos(&wndTop, rcTree.left, rcTree.top, rcTree.Width(), rcTree.Height(), SWP_NOZORDER);

	// restore Scrollposition
	long ScrollCode = nOffset;
	ScrollCode = ((ScrollCode << 16 ) & 0x0ffff0000) + SB_THUMBPOSITION;
	SendMessage(WM_HSCROLL, ScrollCode, 0);
//	Invalidate(FALSE);
}


bool CTreeListView::ResetScrollbar()
{
	CRect rcTree;
	long nWndWidth;

	HDITEM HeaderItem;
	HeaderItem.mask = HDI_WIDTH;

	m_List.GetClientRect(&rcTree);
	m_nHeaderWidth = 0;

	// Get summary of headeritem widths
	for(int i = 0; i < m_ctrlHeader.GetItemCount(); i++)
	{
		m_ctrlHeader.GetItem(i, &HeaderItem);
		m_nHeaderWidth += HeaderItem.cxy;
	}
	nWndWidth = rcTree.right - rcTree.left;


	if(m_nHeaderWidth > nWndWidth)
	{
		SetScrollRange(SB_HORZ, 0, m_nHeaderWidth - nWndWidth);
		SetScrollPos(SB_HORZ, 0, TRUE);
		ModifyStyle(0, WS_HSCROLL, 0);
		m_nOffset = 0;
	}
	else
	{
		SetScrollRange(SB_HORZ, 0, 0);
		SetScrollPos(SB_HORZ, 0, TRUE);
		ModifyStyle(WS_HSCROLL, 0, 0);
		m_nOffset = 0;
	}

	return true;
}


void CTreeListView::DrawTreeItem(bool bFocus, CRect rcItem, HDC hdc, HTREEITEM hItem)
{
	COLORREF colText = m_colText;

	// if the item has got the focus, we have to draw sorouinding rectangle and fill a rect blue
	if(bFocus == true)
	{
		::FillRect(hdc, &rcItem, (HBRUSH)m_BackBrush.m_hObject);

		// Add new focus rect code...
		::DrawFocusRect( hdc, &rcItem );

		colText = m_colHilightText;
	}
	else
	{
		// add this to clear leftover highlight bar
		::FillRect(hdc, &rcItem, (HBRUSH)m_BackBrushNormal.m_hObject);
	}

	// always write text without background
	::SetBkMode(hdc, TRANSPARENT);
	::SetTextColor(hdc, colText);

	// draw all columns of the item
	RECT rc = rcItem;
	for(long i=0; i < m_nNrColumns; i++)
	{
		if(i != 0)
			rc.left = m_vsCol[i].rcDefault.left;
		rc.right = m_vsCol[i].rcDefault.right;
		CString str = m_Entries[hItem].m_strColumns[i];

		::DrawText(hdc, str, -1, &rc, DT_BOTTOM | DT_SINGLELINE | DT_WORD_ELLIPSIS | m_vsCol[i].nAlingment);
	}
}

void CTreeListView::UpdateColStruct(void)
{
	// delete old coulnstructs
	m_nHeaderWidth = 0;
 	delete []m_vsCol;
	m_vsCol = NULL;

	// are there columns?
	if(m_nNrColumns != 0)
	{
		m_vsCol = new HeaderData[m_nNrColumns];

		// fill columnstructures
		for(long i=0; i < m_nNrColumns; i++)
		{
			HDITEM HeaderItem;

			// Get item information from the header control
			HeaderItem.mask = HDI_WIDTH | HDI_LPARAM | HDI_FORMAT;
			m_ctrlHeader.GetItem(i, &HeaderItem);
			m_vsCol[i].nWidth = HeaderItem.cxy;

			// calculate the rects
			if(i == 0)
			{
				m_vsCol[i].rcDefault.left = 2;
			}
			else
				m_vsCol[i].rcDefault.left = m_vsCol[i-1].rcDefault.right + 2;
			m_vsCol[i].rcDefault.right = m_vsCol[i].rcDefault.left  + m_vsCol[i].nWidth - 2;

			// get the alignment formatting
			switch(HeaderItem.fmt & 3)
			{
			case HDF_RIGHT:
				{
					m_vsCol[i].nAlingment = DT_RIGHT;
					break;
				}
			case HDF_CENTER:
				{
					m_vsCol[i].nAlingment = DT_CENTER;
					break;
				}
			case HDF_LEFT:
			default:
				{
					m_vsCol[i].nAlingment = DT_LEFT;
					break;
				}
			};
			
			m_nHeaderWidth += m_vsCol[i].nWidth;
		}
	}
}


BOOL CTreeListView::OnCustomdrawTree(LPNMHDR pNmhdr, LRESULT* pResult)
{
	static CRect	rcItem;
	static CPoint	poi;
	static bool		bFocus;

	BOOL bRet = FALSE;

	LPNMTVCUSTOMDRAW pCustomDraw = (LPNMTVCUSTOMDRAW)pNmhdr;
	switch (pCustomDraw->nmcd.dwDrawStage)
	{
		case CDDS_PREPAINT:
			// Need to process this case and set pResult to CDRF_NOTIFYITEMDRAW, 
			// otherwise parent will never receive CDDS_ITEMPREPAINT notification. (GGH) 
			*pResult = CDRF_NOTIFYITEMDRAW;

			// reposuition the viewport so the TreeCtrl DefWindowProc doesn't draw to viewport 0/0
			::SetViewportOrgEx(pCustomDraw->nmcd.hdc, m_nOffset, 0, NULL);
			bRet = TRUE;
			break;

		case CDDS_ITEMPREPAINT:
			// set the background and foregroundcolor of the item to the background, so you don't see the default drawing of the text
			pCustomDraw->clrText = m_colBackColor;
			pCustomDraw->clrTextBk = m_colBackColor;

			// reset the focus, because it will be drawn of us
			bFocus = false;
			if(	pCustomDraw->nmcd.uItemState & CDIS_FOCUS)
			{
				bFocus = true;
			}

			pCustomDraw->nmcd.uItemState &= ~CDIS_FOCUS;

			// remember the drawing rectangle of the item so we can draw it ourselves
			m_List.GetItemRect((HTREEITEM) pCustomDraw->nmcd.dwItemSpec, &rcItem, TRUE);
			rcItem.right = (pCustomDraw->nmcd.rc.right > m_nHeaderWidth) ? pCustomDraw->nmcd.rc.right : m_nHeaderWidth;

			// we want to get the CDDS_ITEMPOSTPAINT notification
			*pResult = CDRF_NOTIFYPOSTPAINT;
			bRet = TRUE;
			break;

		case CDDS_ITEMPOSTPAINT:

			// draw the item
			DrawTreeItem(bFocus, rcItem, pCustomDraw->nmcd.hdc, (HTREEITEM) pCustomDraw->nmcd.dwItemSpec);
			bRet = TRUE;
			break;
	}

	return bRet;
}

BOOL CTreeListView::OnEndTrack(LPNMHDR pNmhdr, LRESULT* pResult)
{
	UNUSED_PARAM(pResult);
	UNUSED_PARAM(pNmhdr);

	// we need to post thios message so the headercontrol can take the time to save the information of the new sizes an we can the get it from the control
	PostMessage(WM_SIZE);
	return FALSE;
}


BOOL CTreeListView::OnDeleteItem(LPNMHDR pNmhdr, LRESULT* pResult)
{
	UNUSED_PARAM(pResult);

	BOOL bRet = TRUE;

	NMTREEVIEW* pnmtv = (NMTREEVIEW*) pNmhdr;

	m_Entries.RemoveKey(pnmtv->itemOld.hItem);

	return bRet;
}


void CTreeListView::OnWindowPosChanging(WINDOWPOS* lpwndpos)
{
	CView::OnWindowPosChanging(lpwndpos);

	// TODO: Add your message handler code here
}




BOOL CTreeListView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	return FALSE;
//	return CView::OnEraseBkgnd(pDC);
}
