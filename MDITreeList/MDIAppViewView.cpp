// MDIAppViewView.cpp : implementation of the CMDIAppViewView class
//

#include "stdafx.h"
#include "MDIAppView.h"

#include "MDIAppViewDoc.h"
#include "MDIAppViewView.h"

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
// CMDIAppViewView

IMPLEMENT_DYNCREATE(CMDIAppViewView, CView)

BEGIN_MESSAGE_MAP(CMDIAppViewView, CView)
	//{{AFX_MSG_MAP(CMDIAppViewView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMDIAppViewView construction/destruction

CMDIAppViewView::CMDIAppViewView()
{
	// TODO: add construction code here

}

CMDIAppViewView::~CMDIAppViewView()
{
}

BOOL CMDIAppViewView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMDIAppViewView drawing

void CMDIAppViewView::OnDraw(CDC* pDC)
{
	CMDIAppViewDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMDIAppViewView printing

BOOL CMDIAppViewView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMDIAppViewView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMDIAppViewView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMDIAppViewView diagnostics

#ifdef _DEBUG
void CMDIAppViewView::AssertValid() const
{
	CView::AssertValid();
}

void CMDIAppViewView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMDIAppViewDoc* CMDIAppViewView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMDIAppViewDoc)));
	return (CMDIAppViewDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMDIAppViewView message handlers

void CMDIAppViewView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	
}
