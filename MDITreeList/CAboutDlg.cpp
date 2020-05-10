#include "stdafx.h"
#include "afxwin.h"
#include "CAboutDlg.h"
#include "CDesignDialog.h"

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

CAboutDlg::~CAboutDlg() {
	// TODO: add delete member here
}

CAboutDlg::CAboutDlg() : CDesignDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CCustomDialog)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCustomDialog)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDesignDialog)
	//{{AFX_MSG_MAP(CCustomDialog)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

