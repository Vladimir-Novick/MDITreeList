// TreeListCtrlDoc.cpp : implementation of the CTreeListCtrlDoc class
//

#include "stdafx.h"
#include "resource.h"

#include "TreeListCtrlDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTreeListCtrlDoc

IMPLEMENT_DYNCREATE(CTreeListCtrlDoc, CDocument)

BEGIN_MESSAGE_MAP(CTreeListCtrlDoc, CDocument)
	//{{AFX_MSG_MAP(CTreeListCtrlDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTreeListCtrlDoc construction/destruction

CTreeListCtrlDoc::CTreeListCtrlDoc()
{
	// TODO: add one-time construction code here

}

CTreeListCtrlDoc::~CTreeListCtrlDoc()
{
}

BOOL CTreeListCtrlDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTreeListCtrlDoc serialization

void CTreeListCtrlDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CTreeListCtrlDoc diagnostics

#ifdef _DEBUG
void CTreeListCtrlDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTreeListCtrlDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTreeListCtrlDoc commands
