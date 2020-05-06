#include "StdAfx.h"
#include "CDesignDialog.h"

IMPLEMENT_DYNAMIC(CDesignDialog, CObject)
BEGIN_MESSAGE_MAP(CDesignDialog, CDialog)
	ON_WM_CTLCOLOR()
//	ON_WM_SETFOCUS()
END_MESSAGE_MAP()

CDesignDialog::~CDesignDialog() {

	if (m_hBkgndBrush){
		DeleteObject(m_hBkgndBrush);
    }
}

void CDesignDialog::Init() {
	m_hBkgndBrush = CreateSolidBrush(RGB(226, 230, 233));
}

HBRUSH CDesignDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if (nCtlColor == CTLCOLOR_STATIC )
	{
		DWORD d = GetSysColor(COLOR_BTNFACE);

		COLORREF normal = RGB(GetRValue(d), GetGValue(d), GetBValue(d));
	
		pDC->SetBkColor(RGB(226, 230, 233));

	}

	return m_hBkgndBrush;
}



BOOL CDesignDialog::PreTranslateMessage(MSG* pMsg)
{
	HWND hWnd = pMsg->hwnd;
	CWnd* pWnd = CWnd::FromHandle(hWnd);
	if (pMsg->message == WM_SETFONT) {		
		
		OutputDebugString(L"WM_SETFONT");
		WPARAM wParam = pMsg->wParam;
	//	A handle to the font(HFONT).If this parameter is NULL, the control uses the default system font to draw text.
		if (wParam == NULL) {  // 

		}
		else {
			HFONT hfont = (HFONT)( wParam);
			CFont* pFont = pWnd->GetFont();


			LOGFONT lf;
			memset(&lf, 0, sizeof(LOGFONT)); // zero out structure
			int ret = pFont->GetLogFont(&lf);
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}


BOOL CDesignDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	
	EnumChildWindows(m_hWnd, CDesignDialog::ModifyChildFont, (LPARAM)this);
	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


BOOL CDesignDialog::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style |= DS_SETFONT;

	return CDialog::PreCreateWindow(cs);
}


BOOL __stdcall  CDesignDialog::ModifyChildFont(HWND hwnd, LPARAM)
{
	OutputDebugString(L"ModifyChildFont");
	CWnd* pWnd = CWnd::FromHandle(hwnd);
	CFont* pFont = pWnd->GetFont();

	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT)); // zero out structure
	int ret = pFont->GetLogFont(&lf);

	OutputDebugString(L"Modify font");

	//	pWnd->SetFont(pFont);
	return 0;
}

LRESULT CDesignDialog::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::DefWindowProc(message, wParam, lParam);
}
