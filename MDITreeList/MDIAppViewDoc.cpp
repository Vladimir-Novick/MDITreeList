// MDIAppViewDoc.cpp : implementation of the CMDIAppViewDoc class
//

#include "stdafx.h"
#include "MDIAppView.h"

#include "MDIAppViewDoc.h"

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
// CMDIAppViewDoc

IMPLEMENT_DYNCREATE(CMDIAppViewDoc, CDocument)

BEGIN_MESSAGE_MAP(CMDIAppViewDoc, CDocument)
	//{{AFX_MSG_MAP(CMDIAppViewDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMDIAppViewDoc construction/destruction

CMDIAppViewDoc::CMDIAppViewDoc()
{
	// TODO: add one-time construction code here

}

CMDIAppViewDoc::~CMDIAppViewDoc()
{
}

BOOL CMDIAppViewDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMDIAppViewDoc serialization

void CMDIAppViewDoc::Serialize(CArchive& ar)
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
// CMDIAppViewDoc diagnostics

#ifdef _DEBUG
void CMDIAppViewDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMDIAppViewDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMDIAppViewDoc commands
