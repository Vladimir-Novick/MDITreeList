// ListFontView.cpp : implementation of the CListFontView class
//

#include "stdafx.h"
#include "..\MDIAppView.h"

#include "ListFontDoc.h"
#include "ListFontView.h"

#ifdef _DEBUG
#undef DEBUG_NEW
#define DEBUG_NEW new(__FILE__, __LINE__)
#define _CRTDBG_MAP_ALLOC
#define new DEBUG_NEW
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#else
#undef _CRTDBG_MAP_ALLOC
#define DEBUG_NEW new
#endif

/////////////////////////////////////////////////////////////////////////////
// CListFontView

IMPLEMENT_DYNCREATE(CListFontView, CFormView)

BEGIN_MESSAGE_MAP(CListFontView, CFormView)
	//{{AFX_MSG_MAP(CListFontView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListFontView construction/destruction

CListFontView::CListFontView()
	: CFormView(CListFontView::IDD)
{
	// TODO: add construction code here

}

void CListFontView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);
	if (m_ListCtrl.m_hWnd != NULL) {
		m_ListCtrl.SetWindowPos(this, 0, 0, cx, cy, SWP_NOZORDER);
	}

}


CListFontView::~CListFontView()
{
}

BOOL CListFontView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	return CFormView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CListFontView drawing



/////////////////////////////////////////////////////////////////////////////
// CListFontView printing

BOOL CListFontView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CListFontView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CListFontView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CListFontView diagnostics

#ifdef _DEBUG
void CListFontView::AssertValid() const
{
	CFormView::AssertValid();
}

void CListFontView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CListFontDoc* CListFontView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CListFontDoc)));
	return (CListFontDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CListFontView message handlers

void CListFontView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	SetScrollSizes(MM_TEXT, CSize(0, 0)); // Hide Scrollbars in CFormView 
	m_ListCtrl.SubclassDlgItem(IDC_LIST, this);
	m_ListCtrl.SetNoOfColumns(3);
	m_ListCtrl.SetNoOfRows(2);
	m_ListCtrl.ShowScrollBar(SB_BOTH, FALSE);
	RECT rect;
	GetClientRect(&rect);
	m_ListCtrl.SetWindowPos(this, 0, 0, rect.right-rect.left, rect.bottom-rect.top, SWP_NOZORDER);
	m_ListCtrl.OnInitialUpdate();

	
	
}


int CListFontView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;



	return 0;
}


BOOL CListFontView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	//return CFormView::OnEraseBkgnd(pDC);
	return FALSE;
}
