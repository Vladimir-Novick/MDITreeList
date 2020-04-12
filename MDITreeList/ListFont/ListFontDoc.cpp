// ListFontDoc.cpp : implementation of the CListFontDoc class
//

#include "stdafx.h"
#include "..\MDIAppView.h"

#include "ListFontDoc.h"

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
// CListFontDoc

IMPLEMENT_DYNCREATE(CListFontDoc, CDocument)

BEGIN_MESSAGE_MAP(CListFontDoc, CDocument)
	//{{AFX_MSG_MAP(CListFontDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListFontDoc construction/destruction

CListFontDoc::CListFontDoc()
{
	// TODO: add one-time construction code here

}

CListFontDoc::~CListFontDoc()
{
}

BOOL CListFontDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CListFontDoc serialization

void CListFontDoc::Serialize(CArchive& ar)
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
// CListFontDoc diagnostics

#ifdef _DEBUG
void CListFontDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CListFontDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CListFontDoc commands
