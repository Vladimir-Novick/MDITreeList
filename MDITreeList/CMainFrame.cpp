// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "MDIAppView.h"

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

const UINT WM_PAINTMYCAPTION = WM_USER + 5;

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_WM_SHOWWINDOW()
	ON_WM_CLOSE()
	ON_WM_ERASEBKGND()
	ON_MESSAGE(WM_PAINTMYCAPTION, OnPaintMyCaption)
	ON_WM_INITMENUPOPUP()
//	ON_WM_MEASUREITEM()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	NotLoginExit = false;
	hBitmapAbout = NULL;
	
}

CMainFrame::~CMainFrame()
{
	if (hBitmapAbout != NULL) {
		DeleteObject(hBitmapAbout);
	}
}

#pragma region updateTitle ---

void CMainFrame::OnUpdateFrameTitle(BOOL bAddToTitle)
{
	if (m_capp != NULL) {
		m_capp->UpdateFrameTitle(m_hWnd, m_strTitle);
	}
}


LRESULT CMainFrame::OnPaintMyCaption(WPARAM bActive, LPARAM lParam)
{
	if (m_capp != NULL)
	    m_capp->PaintMyCaption(bActive, lParam, m_strTitle);
	return 0;
}

#pragma endregion 

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

#pragma region custom close button

	ModifyStyle(WS_SYSMENU, 0); // Remove standard system menu

#pragma endregion
	m_capp = new CCaptionPainter();
	m_capp->Install(this, WM_PAINTMYCAPTION);

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs



	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers



void CMainFrame::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CMDIFrameWnd::OnShowWindow(bShow, nStatus);

	// TODO: Add your message handler code here
}


void CMainFrame::OnClose()
{
	if (NotLoginExit) {
		m_capp->Uninstall();
		delete m_capp;
		m_Client.UnsubclassWindow();
		CMDIFrameWnd::OnClose();  //  close message from login screen
	}
	else {
		
		if (AfxMessageBox(L"Are you Sure to quit?", MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			m_capp->Uninstall();
			delete m_capp;
			m_Client.UnsubclassWindow();
			CMDIFrameWnd::OnClose();
		}
	}

}


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	if (CMDIFrameWnd::OnCreateClient(lpcs, pContext))
	{
		m_Client.SubclassWindow(m_hWndMDIClient);
		return TRUE;
	}

	return CMDIFrameWnd::OnCreateClient(lpcs, pContext);
}





void CMainFrame::OnInitMenuPopup(CMenu* pMenu, UINT nIndex, BOOL bSysMenu)
{
	CMDIFrameWnd::OnInitMenuPopup(pMenu, nIndex, bSysMenu);

	if (bSysMenu)
	{
		pMenu = GetSystemMenu(FALSE);
	}
	MENUINFO mnfo;
	mnfo.cbSize = sizeof(mnfo);
	mnfo.fMask = MIM_STYLE;
	mnfo.dwStyle = MNS_CHECKORBMP | MNS_AUTODISMISS;
	::SetMenuInfo(pMenu->GetSafeHmenu(), &mnfo);

	MENUITEMINFO minfo;
	minfo.cbSize = sizeof(minfo);
	
	for (UINT pos = 0; pos < pMenu->GetMenuItemCount(); pos++)
	{
		minfo.fMask = MIIM_FTYPE | MIIM_ID ;
		pMenu->GetMenuItemInfo(pos, &minfo, TRUE);
		
		if (ID_APP_ABOUT == minfo.wID) {
			if (hBitmapAbout == NULL) {

				hBitmapAbout = (HBITMAP)::LoadImage(AfxGetResourceHandle(),
					MAKEINTRESOURCE(ID_APP_ABOUT),
					IMAGE_BITMAP,
					0, 0, // cx,cy
					LR_LOADTRANSPARENT | LR_LOADMAP3DCOLORS);
			//	hBitmapAbout = ReplaceColor(hBmp, RGB(0, 100, 0), GetSysColor(COLOR_MENU), NULL);
			//	DeleteObject(hBmp);
			}
			SetMenuItemBitmaps(pMenu->m_hMenu, pos, MF_BYPOSITION , hBitmapAbout, hBitmapAbout);
		}

	}
}




HBITMAP  CMainFrame::ReplaceColor(HBITMAP hBmp, COLORREF cOldColor, COLORREF cNewColor, HDC hBmpDC)
{
	HBITMAP RetBmp = NULL;
	if (hBmp)
	{
		HDC BufferDC = CreateCompatibleDC(NULL);    // DC for Source Bitmap
		if (BufferDC)
		{
			HBITMAP hTmpBitmap = (HBITMAP)NULL;
			if (hBmpDC)
				if (hBmp == (HBITMAP)GetCurrentObject(hBmpDC, OBJ_BITMAP))
				{
					hTmpBitmap = CreateBitmap(1, 1, 1, 1, NULL);
					SelectObject(hBmpDC, hTmpBitmap);
				}

			HGDIOBJ PreviousBufferObject = SelectObject(BufferDC, hBmp);
			// here BufferDC contains the bitmap

			HDC DirectDC = CreateCompatibleDC(NULL); // DC for working
			if (DirectDC)
			{
				// Get bitmap size
				BITMAP bm;
				GetObject(hBmp, sizeof(bm), &bm);

				// create a BITMAPINFO with minimal initilisation 
				// for the CreateDIBSection
				BITMAPINFO RGB32BitsBITMAPINFO;
				ZeroMemory(&RGB32BitsBITMAPINFO, sizeof(BITMAPINFO));
				RGB32BitsBITMAPINFO.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
				RGB32BitsBITMAPINFO.bmiHeader.biWidth = bm.bmWidth;
				RGB32BitsBITMAPINFO.bmiHeader.biHeight = bm.bmHeight;
				RGB32BitsBITMAPINFO.bmiHeader.biPlanes = 1;
				RGB32BitsBITMAPINFO.bmiHeader.biBitCount = 32;

				// pointer used for direct Bitmap pixels access
				UINT* ptPixels;

				HBITMAP DirectBitmap = CreateDIBSection(DirectDC,
					(BITMAPINFO*)&RGB32BitsBITMAPINFO,
					DIB_RGB_COLORS,
					(void**)&ptPixels,
					NULL, 0);
				if (DirectBitmap)
				{
					// here DirectBitmap!=NULL so ptPixels!=NULL no need to test
					HGDIOBJ PreviousObject = SelectObject(DirectDC, DirectBitmap);
					BitBlt(DirectDC, 0, 0,
						bm.bmWidth, bm.bmHeight,
						BufferDC, 0, 0, SRCCOPY);

					// here the DirectDC contains the bitmap

				 // Convert COLORREF to RGB (Invert RED and BLUE)
					cOldColor = COLORREF2RGB(cOldColor);
					cNewColor = COLORREF2RGB(cNewColor);

					// After all the inits we can do the job : Replace Color
					for (int i = ((bm.bmWidth * bm.bmHeight) - 1); i >= 0; i--)
					{
						if (ptPixels[i] == cOldColor) ptPixels[i] = cNewColor;
					}
					// little clean up
					// Don't delete the result of SelectObject because it's 
					// our modified bitmap (DirectBitmap)
					SelectObject(DirectDC, PreviousObject);

					// finish
					RetBmp = DirectBitmap;
				}
				// clean up
				DeleteDC(DirectDC);
			}
			if (hTmpBitmap)
			{
				SelectObject(hBmpDC, hBmp);
				DeleteObject(hTmpBitmap);
			}
			SelectObject(BufferDC, PreviousBufferObject);
			// BufferDC is now useless
			DeleteDC(BufferDC);
		}
	}
	return RetBmp;
}




