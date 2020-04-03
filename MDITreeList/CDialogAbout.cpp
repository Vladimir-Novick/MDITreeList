#include "stdafx.h"
#include "CDialogAbout.h"
#include "CAboutDlg.h"

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

IMPLEMENT_DYNCREATE(CDialogAbout, CWinThread)

BOOL CDialogAbout::InitInstance()
{
    CAboutDlg dlg;

    dlg.DoModal();
    return FALSE;
}
