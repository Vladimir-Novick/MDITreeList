// ChildFrm.cpp : implementation of the ListFontFrame class
//

#include "stdafx.h"
#include "..\MDIAppView.h"

#include "ListFontFrame.h"



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
// ListFontFrame

IMPLEMENT_DYNCREATE(CListFontFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CListFontFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(ListFontFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ListFontFrame construction/destruction

CListFontFrame::CListFontFrame()
{
	// TODO: add member initialization code here
	
}

CListFontFrame::~CListFontFrame()
{
}

BOOL CListFontFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// ListFontFrame diagnostics

#ifdef _DEBUG
void CListFontFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CListFontFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ListFontFrame message handlers



