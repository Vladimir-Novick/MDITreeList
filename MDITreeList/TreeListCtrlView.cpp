// TreeListCtrlView.cpp : implementation of the CTreeListCtrlView class
//

#include "stdafx.h"
#include "TreeListView.h"

#include "TreeListCtrlDoc.h"
#include "TreeListCtrlView.h"
#include "resource.h"
#include "CLientWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTreeListCtrlView

IMPLEMENT_DYNCREATE(CTreeListCtrlView, CTreeListView)

BEGIN_MESSAGE_MAP(CTreeListCtrlView, CTreeListView)
	//{{AFX_MSG_MAP(CTreeListCtrlView)
	ON_COMMAND(ID_HEADER, OnHeader)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTreeListCtrlView construction/destruction

CTreeListCtrlView::CTreeListCtrlView()
{
	// TODO: add construction code here
	m_bShowHeader = true;

}

CTreeListCtrlView::~CTreeListCtrlView()
{
}

BOOL CTreeListCtrlView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CTreeListView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTreeListCtrlView drawing

void CTreeListCtrlView::OnDraw(CDC* pDC)
{
	CTreeListCtrlDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	(void)pDC;
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CTreeListCtrlView diagnostics

#ifdef _DEBUG
void CTreeListCtrlView::AssertValid() const
{
	CTreeListView::AssertValid();
}

void CTreeListCtrlView::Dump(CDumpContext& dc) const
{
	CTreeListView::Dump(dc);
}

CTreeListCtrlDoc* CTreeListCtrlView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTreeListCtrlDoc)));
	return (CTreeListCtrlDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTreeListCtrlView message handlers

void CTreeListCtrlView::OnInitialUpdate()
{
	CTreeListView::OnInitialUpdate();

	m_Images.Create(16, 16, ILC_COLOR | ILC_MASK, 0, 1);
	CBitmap bm;
	bm.LoadBitmap(IDB_BITMAP1);
	m_Images.Add(&bm, RGB(255, 255, 255));
	bm.DeleteObject();
	bm.LoadBitmap(IDB_BITMAP2);
	m_Images.Add(&bm, RGB(255, 255, 255));

	CTreeCtrl& treeCtrl = GetTreeCtrl();


	InsertColumn(0, _T("1. Column"), LVCFMT_LEFT, 200);
	InsertColumn(1, _T("2. Column"), LVCFMT_LEFT, 200);
	InsertColumn(2, _T("3. Column"), LVCFMT_LEFT, 200);

	treeCtrl.SetImageList(&m_Images, TVSIL_NORMAL);
	treeCtrl.SetImageList(&m_Images, TVSIL_STATE);

	HTREEITEM hItem, hItem2;

	hItem = treeCtrl.InsertItem(_T("ItemText 1"), 0, 1);
	SetSubItemText(hItem, 1, _T("Subitem 1"));
	SetSubItemText(hItem, 2, _T("Subitem 2"));

	hItem2 = treeCtrl.InsertItem(_T("ItemText 1.1"), 0, 1, hItem);
	SetSubItemText(hItem2, 1, _T("Subitem 1"));
	SetSubItemText(hItem2, 2, _T("Subitem 2"));
	hItem2 = treeCtrl.InsertItem(_T("ItemText 1.2"), 0, 1, hItem);
	SetSubItemText(hItem2, 2, _T("Subitem 2"));

	for (long i = 2; i < 150; i = i + 2)
	{
		CString str;
		str.Format(L"ItemText %d", i);
		auto hItem = treeCtrl.InsertItem(str, 0, 1);
		SetSubItemText(hItem, 1, _T("Subitem 1"));
		SetSubItemText(hItem, 2, _T("Subitem 2"));

		str.Format(L"ItemText %d", i + 1);
		hItem = treeCtrl.InsertItem(str, 0, 1);
		SetSubItemText(hItem, 1, _T("Subitem 1"));
		SetSubItemText(hItem, 2, _T("Subitem 2"));

		str.Format(L"ItemText %d.%d", i + 1, 1);
		hItem2 = treeCtrl.InsertItem(str, 0, 1, hItem);
		SetSubItemText(hItem2, 1, _T("Subitem 1"));
		SetSubItemText(hItem2, 2, _T("Subitem 2"));
		str.Format(L"ItemText %d.%d", i + 1, 2);
		hItem2 = treeCtrl.InsertItem(str, 0, 1, hItem);
		SetSubItemText(hItem2, 1, _T("Subitem 1"));
		SetSubItemText(hItem2, 2, _T("Subitem 2"));
	}
}

void CTreeListCtrlView::OnHeader()
{
	m_bShowHeader = m_bShowHeader == true ? false : true;
	ShowHeader(m_bShowHeader);
}


LRESULT CTreeListCtrlView::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
    if (message == WM_SET_DEFAULT_APP_FONT)
	{
		Invalidate();
		return 0;
	}
	return CTreeListView::DefWindowProc(message, wParam, lParam);
}
