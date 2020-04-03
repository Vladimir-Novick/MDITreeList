// ChildFrm.cpp : implementation of the CChildFrame class
//

#include "stdafx.h"
#include "MDIAppView.h"

#include "TreeListCtrlFrame.h"



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
// CTreeListCtrlFrame

IMPLEMENT_DYNCREATE(CTreeListCtrlFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CTreeListCtrlFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CTreeListCtrlFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTreeListCtrlFrame construction/destruction

CTreeListCtrlFrame::CTreeListCtrlFrame()
{
	// TODO: add member initialization code here
	
}

CTreeListCtrlFrame::~CTreeListCtrlFrame()
{
}

BOOL CTreeListCtrlFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTreeListCtrlFrame diagnostics

#ifdef _DEBUG
void CTreeListCtrlFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CTreeListCtrlFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTreeListCtrlFrame message handlers



