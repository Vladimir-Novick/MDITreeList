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
#include "..\NDC\CAppParamsMngr.h"
#include "TreeListCtrlFrame.h"
#include "ListFont/ListFontDoc.h"
#include "ListFont/ListFontView.h"
#include "ListFont/ListFontFrame.h"
#include "..\NDC\CDefaultAppFont.h"

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
	ON_COMMAND(ID_FILE_NEWLIST, OnOpenListView)
	ON_COMMAND(ID_TREE_ITEM_SETFONTS, OnSetFont)
	ON_COMMAND(ID_TREE_HEADER_SETFONTS, OnSetHeaderFont)
	ON_COMMAND(ID_DIALOGFONTS, OnSetDialogFont)
	ON_COMMAND(ID_SET_BACKGRAWND_COLOR, OnSetBackgrowndColor)
	ON_COMMAND(ID_SET_DEFAULT_BACKGRAWND_COLOR, OnSetDefaultBackgrowndColor)
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

void CMDIAppViewApp::OnOpenListView()
{
	auto pNewDoc = m_TemplateListFont->OpenDocumentFile(NULL);
}

void CMDIAppViewApp::SaveDefaultAppColor(const string& coolor_name, COLORREF color) {
	RGBTRIPLE rgb;

	CString strColorName = coolor_name.c_str();

	rgb.rgbtRed = GetRValue(color);
	rgb.rgbtGreen = GetGValue(color);
	rgb.rgbtBlue = GetBValue(color);

	CAppParamsMngr appParamsMngr("DefaultParams", CAppParamsMngr::WRITE);
	appParamsMngr.SetAppParameterInt("Red", strColorName, rgb.rgbtRed);
	appParamsMngr.SetAppParameterInt("Green", strColorName, rgb.rgbtGreen);
	appParamsMngr.SetAppParameterInt("Blue", strColorName, rgb.rgbtBlue);
}

COLORREF CMDIAppViewApp::ReadDefaultAppColor(const string& paramName,
	int rgbtRed, int rgbtGreen, int rgbtBlue
	)
{

	CString strColorName = paramName.c_str();
	RGBTRIPLE rgb;
	CAppParamsMngr appParamsMngr("DefaultParams", CAppParamsMngr::READ);
	rgb.rgbtRed = appParamsMngr.GetAppParameterInt("Red", strColorName, rgbtRed);
	rgb.rgbtGreen = appParamsMngr.GetAppParameterInt("Green", strColorName, rgbtGreen);
	rgb.rgbtBlue =appParamsMngr.GetAppParameterInt("Blue", strColorName, rgbtBlue);
	COLORREF colorRef = RGB(rgb.rgbtRed, rgb.rgbtGreen, rgb.rgbtBlue);
	return colorRef;
}



void CMDIAppViewApp::ReadDefaultAppFont(const string &paramName, LOGFONT & lf, int size)
{
	CString fontID(paramName.c_str());
	LOGFONT defaultLogFont;

	memset(&defaultLogFont, 0, sizeof(defaultLogFont));
	auto app = AfxGetApp();
	CDC* cdc = app->GetMainWnd()->GetDC();
	cdc->SetMapMode(MM_TEXT);

	int currentY = -MulDiv(size, GetDeviceCaps(cdc->m_hDC, LOGPIXELSY), 72);


	defaultLogFont.lfHeight = currentY;

	defaultLogFont.lfCharSet = DEFAULT_CHARSET;

	defaultLogFont.lfWeight = FW_REGULAR;
	defaultLogFont.lfPitchAndFamily = VARIABLE_PITCH | FF_SWISS;
	lstrcpy(defaultLogFont.lfFaceName, L"MS Sans Serif");

	CAppParamsMngr appParamsMngr("DefaultParams", CAppParamsMngr::READ);
	CString strTemp;
	CString strParam;

	strParam = appParamsMngr.GetAppParameter("FontName", paramName.c_str(),
		 defaultLogFont.lfFaceName);
	lstrcpy(lf.lfFaceName, strParam);

	strTemp.Format(L"%d", defaultLogFont.lfWeight);
	strParam = appParamsMngr.GetAppParameter("Weight",  paramName.c_str(),
		 strTemp);
	lf.lfWeight = _ttol(strParam);

	strTemp.Format(L"%d", defaultLogFont.lfItalic);
	strParam = appParamsMngr.GetAppParameter("Italic",  paramName.c_str(),
		 strTemp);
	lf.lfItalic = _ttoi(strParam);

	strTemp.Format(L"%d", defaultLogFont.lfUnderline);
	strParam = appParamsMngr.GetAppParameter("Underline",  paramName.c_str(),
		 strTemp);
	lf.lfUnderline = _ttoi(strParam);

	strTemp.Format(L"%d", defaultLogFont.lfStrikeOut);
	strParam = appParamsMngr.GetAppParameter("StrikeOut",  paramName.c_str(),
		 strTemp);
	lf.lfStrikeOut = _ttoi(strParam);

	strTemp.Format(L"%d", defaultLogFont.lfHeight);
	strParam = appParamsMngr.GetAppParameter("Height",  paramName.c_str(),
		 strTemp);
	lf.lfHeight = _ttoi(strParam);

	strTemp.Format(L"%d", defaultLogFont.lfCharSet);
	strParam = appParamsMngr.GetAppParameter("CharSet",  paramName.c_str(),
		 strTemp);
	lf.lfCharSet = _ttoi(strParam);

}

void CMDIAppViewApp::SaveDefaultAppFont(const string &paramName, LOGFONT& lf)
{
	CAppParamsMngr appParamsMngr("DefaultParams", CAppParamsMngr::WRITE);
	CString strTemp;
	CString strParam;

	appParamsMngr.SetAppParameter("FontName",  paramName.c_str(),
		lf.lfFaceName );

	strTemp.Format(L"%d", lf.lfWeight);
	appParamsMngr.SetAppParameter("Weight",  paramName.c_str(),
		strTemp );


	strTemp.Format(L"%d", lf.lfItalic);
	appParamsMngr.SetAppParameter("Italic",  paramName.c_str(),
		strTemp );


	strTemp.Format(L"%d", lf.lfUnderline);
	appParamsMngr.SetAppParameter("Underline",  paramName.c_str(),
		strTemp );


	strTemp.Format(L"%d", lf.lfStrikeOut);
	appParamsMngr.SetAppParameter("StrikeOut",  paramName.c_str(),
		strTemp );

	strTemp.Format(L"%d", lf.lfHeight);
	appParamsMngr.SetAppParameter("Height",  paramName.c_str(),
		strTemp );

	strTemp.Format(L"%d", lf.lfCharSet);
	appParamsMngr.SetAppParameter("CharSet",  paramName.c_str(),
		strTemp );
}

void CMDIAppViewApp::MakeDefaultAppFont() {
	{
		LOGFONT lf = {};
		ReadDefaultAppFont(TREE_FONT_NAME, lf, TREE_FONT_NAME_SIZE);
		CDefaultAppFont::GetInstance()->SetFont(TREE_FONT_NAME, lf);
	}

	{
		LOGFONT lf = {};
		ReadDefaultAppFont(TREE_HEADER_FONT_NAME, lf, TREE_HEADER_FONT_NAME_SIZE);
		CDefaultAppFont::GetInstance()->SetFont(TREE_HEADER_FONT_NAME, lf);
	}


	{
		LOGFONT lf = {};
		ReadDefaultAppFont(DIALOG_FONT_NAME, lf, DIALOG_FONT_NAME_SIZE);
		CDefaultAppFont::GetInstance()->SetFont(DIALOG_FONT_NAME, lf);

		COLORREF colorRef = ReadDefaultAppColor(DIALOG_FONT_NAME
		, DIALOG_FONT_NAME_R
		, DIALOG_FONT_NAME_G
		, DIALOG_FONT_NAME_B
		
		);
		CDefaultAppFont::GetInstance()->SetColor(DIALOG_FONT_NAME, colorRef);
	}


	{

		COLORREF colorRef = ReadDefaultAppColor(DIALOG_BACKGROUNT_COLOR_NAME,
			DIALOG_BACKGROUNT_COLOR_NAME_R,
			DIALOG_BACKGROUNT_COLOR_NAME_G,
			DIALOG_BACKGROUNT_COLOR_NAME_B
			);
		CDefaultAppFont::GetInstance()->SetColor(DIALOG_BACKGROUNT_COLOR_NAME, colorRef);
	}
}


/// <summary>
/// Called when [set font].
/// </summary>
void CMDIAppViewApp::OnSetFont()
{
	LOGFONT lf;
	memset(&lf, 0, sizeof lf);

	ReadDefaultAppFont(TREE_FONT_NAME,lf, TREE_FONT_NAME_SIZE);

	CFontDialog fontDialog(&lf, CF_SCREENFONTS);
	if (fontDialog.DoModal() == IDOK)
	{
		memset(&lf, 0, sizeof lf);
		fontDialog.GetCurrentFont(&lf);

		SaveDefaultAppFont(TREE_FONT_NAME,lf);
		MakeDefaultAppFont();
		CDefaultAppFont::GetInstance()->RedrawAllWindow();
	}
}


void CMDIAppViewApp::OnSetHeaderFont()
{
	LOGFONT lf;
	memset(&lf, 0, sizeof lf);

	ReadDefaultAppFont(TREE_HEADER_FONT_NAME,lf, TREE_HEADER_FONT_NAME_SIZE);

	CFontDialog fontDialog(&lf, CF_SCREENFONTS);




	if (fontDialog.DoModal() == IDOK)
	{
		memset(&lf, 0, sizeof lf);
		fontDialog.GetCurrentFont(&lf);

		SaveDefaultAppFont(TREE_HEADER_FONT_NAME,lf);
		MakeDefaultAppFont();
		CDefaultAppFont::GetInstance()->RedrawAllWindow();
	}
}

void CMDIAppViewApp::OnSetDialogFont()
{
	LOGFONT lf;
	memset(&lf, 0, sizeof lf);

	ReadDefaultAppFont(DIALOG_FONT_NAME, lf, DIALOG_FONT_NAME_SIZE);

	COLORREF colorRef = ReadDefaultAppColor(DIALOG_FONT_NAME
		, DIALOG_FONT_NAME_R
		, DIALOG_FONT_NAME_G
		, DIALOG_FONT_NAME_B

	);

	CFontDialog fontDialog(&lf);
	fontDialog.m_cf.Flags |= CF_EFFECTS;
	fontDialog.m_cf.rgbColors = colorRef;
	if (fontDialog.DoModal() == IDOK)
	{
		memset(&lf, 0, sizeof lf);
		fontDialog.GetCurrentFont(&lf);

		SaveDefaultAppFont(DIALOG_FONT_NAME, lf);

		colorRef = fontDialog.GetColor();

		SaveDefaultAppColor(DIALOG_FONT_NAME, colorRef);

		MakeDefaultAppFont();
		
	}
}

void CMDIAppViewApp::OnSetBackgrowndColor()
{
	COLORREF colorRef;
	
	colorRef = ReadDefaultAppColor(DIALOG_BACKGROUNT_COLOR_NAME, 
		DIALOG_BACKGROUNT_COLOR_NAME_R,
		DIALOG_BACKGROUNT_COLOR_NAME_G,
		DIALOG_BACKGROUNT_COLOR_NAME_B
	);

	CColorDialog fontDialog(colorRef, CC_FULLOPEN);
	if (fontDialog.DoModal() == IDOK)
	{

		colorRef = fontDialog.GetColor();

		SaveDefaultAppColor(DIALOG_BACKGROUNT_COLOR_NAME, colorRef);
		MakeDefaultAppFont();

	}
}

void CMDIAppViewApp::OnSetDefaultBackgrowndColor()
{
	COLORREF colorRef = GetSysColor(CTLCOLOR_DLG);
	SaveDefaultAppColor(DIALOG_BACKGROUNT_COLOR_NAME, colorRef);
	MakeDefaultAppFont();

}





CMDIAppViewApp::CMDIAppViewApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

CMDIAppViewApp::~CMDIAppViewApp() {

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

		m_TemplateListFont = new CMultiDocTemplate(
			IDR_MYMDIATYPE,
			RUNTIME_CLASS(CListFontDoc),
			RUNTIME_CLASS(CListFontFrame), // custom MDI child frame
			RUNTIME_CLASS(CListFontView));
		AddDocTemplate(m_TemplateListFont);


	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();
	MakeDefaultAppFont();
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
