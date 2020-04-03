// MDIAppView.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "MDIAppView.h"

#include "CMainFrame.h"
#include "CChildFrame.h"
#include "MDIAppViewDoc.h"
#include "TreeListCtrlDoc.h"
#include "MDIAppViewView.h"
#include "CDialogAbout.h"
#include "TreeListCtrlView.h"
#include "CAppParamsMngr.h"
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
// CMDIAppViewApp

BEGIN_MESSAGE_MAP(CMDIAppViewApp, CWinApp)
	//{{AFX_MSG_MAP(CMDIAppViewApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_FILE_OPENTREEVIEW, OnOpenTreeView)
	ON_COMMAND(ID_VIEW_SETFONT, OnSetFont)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)


	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMDIAppViewApp construction

void CMDIAppViewApp::OnOpenTreeView()
{
	auto pNewDoc = m_pDocTemplateTreeView->OpenDocumentFile(NULL);
}

void CMDIAppViewApp::ReadDefaultAppFont(LOGFONT& lf)
{
	HGDIOBJ gui_font = ::GetStockObject(DEFAULT_GUI_FONT);

	if (gui_font == NULL) {
		gui_font = ::GetStockObject(SYSTEM_FONT);
	}

	CFont* pFontSystem =
		CFont::FromHandle((HFONT)gui_font);

	LOGFONT defaultLogFont;
	memset(&defaultLogFont, 0, sizeof defaultLogFont);

	pFontSystem->GetLogFont(&defaultLogFont);

	CAppParamsMngr appParamsMngr("DefaultParams", CAppParamsMngr::READ);
	CString strTemp;
	CString strParam;

	strParam = appParamsMngr.GetAppParameter("FontName", "AppDefaultFont",
		 defaultLogFont.lfFaceName);
	lstrcpy(lf.lfFaceName, strParam);

	strTemp.Format(L"%d", defaultLogFont.lfWeight);
	strParam = appParamsMngr.GetAppParameter("Weight", "AppDefaultFont",
		 strTemp);
	lf.lfWeight = _ttol(strParam);

	strTemp.Format(L"%d", defaultLogFont.lfItalic);
	strParam = appParamsMngr.GetAppParameter("Italic", "AppDefaultFont",
		 strTemp);
	lf.lfItalic = _ttoi(strParam);

	strTemp.Format(L"%d", defaultLogFont.lfUnderline);
	strParam = appParamsMngr.GetAppParameter("Underline", "AppDefaultFont",
		 strTemp);
	lf.lfUnderline = _ttoi(strParam);

	strTemp.Format(L"%d", defaultLogFont.lfStrikeOut);
	strParam = appParamsMngr.GetAppParameter("StrikeOut", "AppDefaultFont",
		 strTemp);
	lf.lfStrikeOut = _ttoi(strParam);

	strTemp.Format(L"%d", defaultLogFont.lfHeight);
	strParam = appParamsMngr.GetAppParameter("Height", "AppDefaultFont",
		 strTemp);
	lf.lfHeight = _ttoi(strParam);

	strTemp.Format(L"%d", defaultLogFont.lfCharSet);
	strParam = appParamsMngr.GetAppParameter("CharSet", "AppDefaultFont",
		 strTemp);
	lf.lfCharSet = _ttoi(strParam);

}

void CMDIAppViewApp::SaveDefaultAppFont(LOGFONT& lf)
{
	CAppParamsMngr appParamsMngr("DefaultParams", CAppParamsMngr::WRITE);
	CString strTemp;
	CString strParam;

	appParamsMngr.SetAppParameter("FontName", "AppDefaultFont",
		lf.lfFaceName );

	strTemp.Format(L"%d", lf.lfWeight);
	appParamsMngr.SetAppParameter("Weight", "AppDefaultFont",
		strTemp );


	strTemp.Format(L"%d", lf.lfItalic);
	appParamsMngr.SetAppParameter("Italic", "AppDefaultFont",
		strTemp );


	strTemp.Format(L"%d", lf.lfUnderline);
	appParamsMngr.SetAppParameter("Underline", "AppDefaultFont",
		strTemp );


	strTemp.Format(L"%d", lf.lfStrikeOut);
	appParamsMngr.SetAppParameter("StrikeOut", "AppDefaultFont",
		strTemp );

	strTemp.Format(L"%d", lf.lfHeight);
	appParamsMngr.SetAppParameter("Height", "AppDefaultFont",
		strTemp );

	strTemp.Format(L"%d", lf.lfCharSet);
	appParamsMngr.SetAppParameter("CharSet", "AppDefaultFont",
		strTemp );
}

void CMDIAppViewApp::MakeDefaultAppFont() {
	if (AppDefaultFont != NULL) {
		delete AppDefaultFont;
	}
	LOGFONT lf;
	memset(&lf, 0, sizeof lf);
	ReadDefaultAppFont(lf);
	AppDefaultFont = new CFont();
	AppDefaultFont->CreateFontIndirect(&lf);

	CDefaultAppFont::SetFont(AppDefaultFont);
}


void CMDIAppViewApp::OnSetFont()
{
	LOGFONT lf;
	memset(&lf, 0, sizeof lf);

	ReadDefaultAppFont(lf);

	CFontDialog fontDialog(&lf, CF_SCREENFONTS);
	if (fontDialog.DoModal() == IDOK)
	{
		memset(&lf, 0, sizeof lf);
		fontDialog.GetCurrentFont(&lf);

		SaveDefaultAppFont(lf);
		MakeDefaultAppFont();
		//RedrawAllWindows();
	}
}


void CMDIAppViewApp::RedrawAllWindows()
{

	CDocTemplate* pTempl;
	CDocument* pDoc;
	CView* pView;

	auto theApp = AfxGetApp();

	POSITION posT = theApp->GetFirstDocTemplatePosition();

	while (posT)
	{
		pTempl = theApp->GetNextDocTemplate(posT);

		POSITION posD = pTempl->GetFirstDocPosition();
		while (posD)
		{

			pDoc = pTempl->GetNextDoc(posD);


			POSITION posV = pDoc->GetFirstViewPosition();
			while (posV)
			{
				pView = pDoc->GetNextView(posV);
				//auto hWnd = pView->m_hWnd;
				//if (hWnd != NULL) {
				//	CRect rect;
				//	::GetWindowRect(hWnd, rect);
				//	WINDOWPOS wp;
				//	wp.hwnd = hWnd;
				//	wp.cx = rect.Width();
				//	wp.cy = rect.Height();
				//	wp.flags = SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER;
				//	::SendMessage(hWnd, WM_WINDOWPOSCHANGED, 0, (LPARAM)&wp);
				//}
				pView->Invalidate();
				//pView->RedrawWindow();
			}
		}
	}
}

CMDIAppViewApp::CMDIAppViewApp()
{
	AppDefaultFont = NULL;
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

CMDIAppViewApp::~CMDIAppViewApp() {
	if (AppDefaultFont != NULL) {
		delete AppDefaultFont;
	}
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMDIAppViewApp object

CMDIAppViewApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMDIAppViewApp initialization

BOOL CMDIAppViewApp::InitInstance()
{

	AfxEnableControlContainer();


	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("MDICustomFont_Application"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.



		CMultiDocTemplate* pDocTemplate;
		pDocTemplate = new CMultiDocTemplate(
			IDR_MYMDIATYPE,
			RUNTIME_CLASS(CMDIAppViewDoc),
			RUNTIME_CLASS(CChildFrame), // custom MDI child frame
			RUNTIME_CLASS(CMDIAppViewView));
		AddDocTemplate(pDocTemplate);


		m_pDocTemplateTreeView = new CMultiDocTemplate(
			IDR_MYMDIATYPE,
			RUNTIME_CLASS(CTreeListCtrlDoc),
			RUNTIME_CLASS(CTreeListCtrlFrame), // custom MDI child frame
			RUNTIME_CLASS(CTreeListCtrlView));
		AddDocTemplate(m_pDocTemplateTreeView);


	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}

// App command to run the dialog
void CMDIAppViewApp::OnAppAbout()
{
	AfxBeginThread(RUNTIME_CLASS(CDialogAbout));
}

/////////////////////////////////////////////////////////////////////////////
// CMDIAppViewApp message handlers



HINSTANCE CMDIAppViewApp::LoadAppLangResourceDLL()
{
	// TODO: Add your specialized code here and/or call the base class

	return CWinApp::LoadAppLangResourceDLL();
}


int CMDIAppViewApp::ExitInstance()
{

	return CWinApp::ExitInstance();
}
