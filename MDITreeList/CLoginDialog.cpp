#include "stdafx.h"
#include "CLoginDialog.h"
#include "CMainFrame.h"

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

IMPLEMENT_DYNCREATE(CLoginDialog, CWinThread)
BOOL CLoginDialog::InitInstance()
{
    CLoginDlg dlg;
	dlg.SetWaitTime(30); // Set Waiting time - Seconds
    int ret =  dlg.DoModal();

	if (ret != 1) {
		CWnd * wnd = AfxGetApp()->m_pMainWnd;
		((CMainFrame*)wnd)->NotLoginExit = true; // lock message 
		::PostMessage(wnd->m_hWnd, WM_CLOSE, 0, 0); // close main frame
		
	}
    return FALSE;
}

// ----- implement standard modal dialog -----

CLoginDlg::CLoginDlg() : CBaseLoginDialog(CLoginDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CBaseLoginDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CLoginDlg, CBaseLoginDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDCANCEL, &CLoginDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CLoginDlg::OnBnClickedOk)
END_MESSAGE_MAP()


void CLoginDlg::OnBnClickedCancel()
{
	CBaseLoginDialog::OnCancel();
}


void CLoginDlg::OnBnClickedOk()
{
	EndDialog(1);  // OK
}

