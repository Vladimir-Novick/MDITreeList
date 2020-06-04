#include "StdAfx.h"
#include "CDesignDialog.h"
#include "../NDC/CDefaultAppFont.h"
#include <algorithm> 
#include <list>
using namespace std;


CDesignDialog::~CDesignDialog() {
	if (pScaleFont != NULL) {
		pScaleFont->DeleteObject();
		delete  pScaleFont;
		pScaleFont = NULL;
	}

	if (pDefaultFont != NULL) {
		pDefaultFont->DeleteObject();
		delete  pDefaultFont;
		pDefaultFont = NULL;
	}
}

void CDesignDialog::Init() {
	pScaleFont = NULL;
	pDefaultFont = NULL;
}

HBRUSH CDesignDialog::SetCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{

	if (nCtlColor == CTLCOLOR_STATIC || nCtlColor == CTLCOLOR_DLG )
	{
		COLORREF defaultColor = GetSysColor(CTLCOLOR_DLG);
		HBRUSH hbr = CDefaultAppFont::GetInstance()->GetColor(DIALOG_BACKGROUNT_COLOR_NAME, defaultColor);

		COLORREF colorRef = CDefaultAppFont::GetInstance()->GetBrushColor(hbr);
		pDC->SetBkColor(colorRef);


		COLORREF defaultColorText = GetSysColor(COLOR_CAPTIONTEXT);

		HBRUSH hbrText = CDefaultAppFont::GetInstance()->GetColor(DIALOG_FONT_NAME, defaultColorText);
		COLORREF colorRefText = CDefaultAppFont::GetInstance()->GetBrushColor(hbrText);

		pDC->SetTextColor(colorRefText);
		return hbr;
	}


	return NULL;
}


BOOL CDesignDialog::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style |= DS_SETFONT;

	BOOL ret =  CDialog::PreCreateWindow(cs);

	return ret;
}



BOOL CDesignDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	CorrectDialogFonts(m_hWnd);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

SDesignSize CDesignDialog::ModifyChildrenWindow(HWND& m_hWnd, CFont* pFont, float multiplier_height)
{
	SDesignSize ret = { 0,0 };

	if (multiplier_height > 1 && pFont != NULL && m_hWnd != NULL) {
		CWnd* cWnd = CWnd::FromHandle(m_hWnd);
		list<CWnd*> wndList;
		auto pChild = cWnd->GetWindow(GW_CHILD);
		while (pChild) {

			wndList.push_back(pChild);
			pChild = pChild->GetNextWindow();
		}

		for (auto it = wndList.begin(); it != wndList.end(); ++it) {
			CWnd* window = *it;
			window->SetFont(pFont);
			ResizeChildWindow(m_hWnd, window->m_hWnd, multiplier_height);
		}


	}
	return ret;
}

void CDesignDialog::ResizeChildWindow(const HWND& mainhWnd, const HWND& source_hWnd, float multiplier_x)
{

	TCHAR clsName_v[256];
	::GetClassName(source_hWnd, clsName_v, 256);
	HWND child = source_hWnd;
	CComboBox* combobox;
	int dropW;


	RECT rect = {};
	CWnd* wnd = CWnd::FromHandle(child);
	wnd->GetWindowRect(&rect);
	wnd->GetParent()->ScreenToClient(&rect);

	float cx = (float)(rect.right - rect.left) * multiplier_x;

	float cy = (float)(rect.bottom - rect.top) * multiplier_x;

	if (_tcscmp(clsName_v, _T("ComboBox")) == 0) {
		cy *= 10;
	}

	float x = (float)(rect.left) * multiplier_x;
	float y = (float)(rect.top) * multiplier_x;

	::SetWindowPos(child, NULL, x, y, cx, cy, SWP_NOZORDER);
}



SDesignFont CDesignDialog::CorrectDialogFonts(HWND m_hWnd)
{
	SDesignFont retDate;
	retDate.pFont = NULL;
	retDate.multiplier = 1;

	float multiplier_height = 1;
	CFont* pDefaultFont = NULL;
	int max_height = 0;
	int max_width = 0;
	double multiplier_width = 0;
	TCHAR controlClassName[128];
	CFont* oldFont;

	RECT xy;
	BOOL fResult = SystemParametersInfo(SPI_GETWORKAREA, 0, &xy, 0);

	int X_max = xy.right - xy.left;
	int Y_max = xy.bottom - xy.top;

	CFont* pFont = CDefaultAppFont::GetInstance()->GetFont(DIALOG_FONT_NAME);
	int newItemHeight = CDefaultAppFont::GetInstance()->GetFontSize(pFont).y;
	CWnd* cwnd = CWnd::FromHandle(m_hWnd);


	auto screenFont = cwnd->GetFont();
	LOGFONT lf = {};
	if (screenFont != NULL) {
		LOGFONT ls_scr = {};
		screenFont->GetLogFont(&ls_scr);
		memcpy(&lf, &ls_scr, sizeof(ls_scr));
	}
	else {
		lf.lfHeight = -11;
		strcpy_s((char*)lf.lfFaceName, 32, "MS Sans Serif");
	}
	pDefaultFont = CDefaultAppFont::GetInstance()->GetScaleFont(lf);

	int itemHeight = CDefaultAppFont::GetInstance()->GetFontSize(pDefaultFont).y;
	max_height = max(max_height, itemHeight);

	CDC* cdc = cwnd->GetDC();
	CWnd* pChild;

	pChild = cwnd->GetWindow(GW_CHILD);
	CString tempTextBuf;
	int childCount = 0;
	while (pChild) {
		CFont* childFont = pChild->GetFont();
		if (childFont == NULL) {
			childFont = pDefaultFont;
		}
		else {
			childCount++;
		}
		int itemHeight = CDefaultAppFont::GetInstance()->GetFontSize(childFont).y;
		max_height = max(max_height, itemHeight);

		pChild = pChild->GetNextWindow();
	}




	multiplier_height = (float)newItemHeight / (float)max_height;
	multiplier_width = max(multiplier_height, multiplier_width);

	if (childCount > 0) {
		if (multiplier_height > 1) {

#pragma region check max window

			CWnd* wnd = CWnd::FromHandle(m_hWnd);

			RECT rect = {};
			wnd->GetWindowRect(&rect);

			float cx = (float)(rect.right - rect.left) * multiplier_height;

			float cy = (float)(rect.bottom - rect.top) * multiplier_height;



			BOOL moveToCenter = FALSE;
			float font_multiplier_x = 1;
			if (cx > X_max) {
				moveToCenter = TRUE;
				font_multiplier_x = (float)X_max / (float)cx;
			}

			float font_multiplier_y = 1;
			if (cy > Y_max) {
				moveToCenter = TRUE;
				font_multiplier_y = (float)Y_max / (float)cy;
			}

			float font_multiplier = min(font_multiplier_x, font_multiplier_y);
			if (font_multiplier < 1) {
				LOGFONT logfont = {};
				pFont->GetLogFont(&logfont);
				float f = (float)logfont.lfHeight * font_multiplier;
				logfont.lfHeight = f;
				multiplier_height = multiplier_height * font_multiplier;
				pFont = CDefaultAppFont::GetInstance()->GetScaleFont(logfont);
			}


#pragma endregion

			ModifyChildrenWindow(m_hWnd, pFont, multiplier_height);

			//wnd->SetFont(pFont);

			SDesignSize sizeXY = ResizeWindow(m_hWnd, multiplier_height);

			if (sizeXY.width > 0 && sizeXY.height > 0) {
				RECT r;
				cwnd->GetWindowRect(&r);
				if ((r.left + sizeXY.width) > X_max) { moveToCenter = TRUE; }
				if ((r.top + sizeXY.height) > Y_max) { moveToCenter = TRUE; }
				if (moveToCenter == TRUE) {

					int xPos = (GetSystemMetrics(SM_CXSCREEN) - sizeXY.width) / 2;
					int yPos = (GetSystemMetrics(SM_CYSCREEN) - sizeXY.height) / 2;

					cwnd->SetWindowPos(NULL, xPos, yPos, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
				}
			}

			retDate.pFont = pFont;
			retDate.multiplier = multiplier_height;
		}
	}
	cwnd->ReleaseDC(cdc);
	return retDate;
}

SDesignSize CDesignDialog::ResizeWindow(const HWND& source_hWnd, float multiplier)
{
	CWnd* wnd = CWnd::FromHandle(source_hWnd);

	RECT rect = {};
	wnd->GetWindowRect(&rect);

	float cx = (float)(rect.right - rect.left) * multiplier;

	float cy = (float)(rect.bottom - rect.top) * multiplier;

	SDesignSize ret;
	ret.width = cx;
	ret.height = cy;

	wnd->SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
	return ret;
}

void CDesignDialog::ResizeChildWindow(const HWND& source_hWnd, float multiplier)
{
	CWnd* wnd = CWnd::FromHandle(source_hWnd);

	RECT rect = {};
	wnd->GetWindowRect(&rect);
	this->ScreenToClient(&rect);

	float cx = (float)(rect.right - rect.left) * multiplier;

	float cy = (float)(rect.bottom - rect.top) * multiplier;

	float x = (float)(rect.left) * multiplier;
	float y = (float)(rect.top) * multiplier;
	wnd->SetWindowPos(NULL, x, y, cx, cy,  SWP_NOZORDER);

}


HRESULT CDesignDialog::accDoDefaultAction(VARIANT varChild)
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::accDoDefaultAction(varChild);
}


HRESULT CDesignDialog::accHitTest(long xLeft, long yTop, VARIANT* pvarChild)
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::accHitTest(xLeft, yTop, pvarChild);
}


HRESULT CDesignDialog::accLocation(long* pxLeft, long* pyTop, long* pcxWidth, long* pcyHeight, VARIANT varChild)
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::accLocation(pxLeft, pyTop, pcxWidth, pcyHeight, varChild);
}


HRESULT CDesignDialog::accNavigate(long navDir, VARIANT varStart, VARIANT* pvarEndUpAt)
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::accNavigate(navDir, varStart, pvarEndUpAt);
}


HRESULT CDesignDialog::accSelect(long flagsSelect, VARIANT varChild)
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::accSelect(flagsSelect, varChild);
}

#ifdef _DEBUG

void CDesignDialog::AssertValid() const
{
	CDialog::AssertValid();

	// TODO: Add your specialized code here and/or call the base class
}


void CDesignDialog::Dump(CDumpContext& dc) const
{
	CDialog::Dump(dc);

	// TODO: Add your specialized code here and/or call the base class
}
#endif


void CDesignDialog::CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType)
{
	// TODO: Add your specialized code here and/or call the base class

	CDialog::CalcWindowRect(lpClientRect, nAdjustType);
}


BOOL CDesignDialog::ContinueModal()
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::ContinueModal();
}



BOOL CDesignDialog::CreateEx(DWORD dwExStyle, LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, LPVOID lpParam)
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::CreateEx(dwExStyle, lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, lpParam);
}


BOOL CDesignDialog::CreateIndirect(LPCDLGTEMPLATE lpDialogTemplate, CWnd* pParentWnd, void* lpDialogInit)
{
	Init();

	return CDialog::CreateIndirect(lpDialogTemplate, pParentWnd, lpDialogInit);
}


LRESULT CDesignDialog::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::DefWindowProc(message, wParam, lParam);
}


BOOL CDesignDialog::DestroyWindow()
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::DestroyWindow();
}


void CDesignDialog::DoDataExchange(CDataExchange* pDX)
{
	// TODO: Add your specialized code here and/or call the base class

	CDialog::DoDataExchange(pDX);
}


INT_PTR CDesignDialog::DoModal()
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::DoModal();
}



HRESULT CDesignDialog::get_accChild(VARIANT varChild, IDispatch** ppdispChild)
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::get_accChild(varChild, ppdispChild);
}


HRESULT CDesignDialog::get_accChildCount(long* pcountChildren)
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::get_accChildCount(pcountChildren);
}


HRESULT CDesignDialog::get_accDefaultAction(VARIANT varChild, BSTR* pszDefaultAction)
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::get_accDefaultAction(varChild, pszDefaultAction);
}


HRESULT CDesignDialog::get_accDescription(VARIANT varChild, BSTR* pszDescription)
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::get_accDescription(varChild, pszDescription);
}


HRESULT CDesignDialog::get_accFocus(VARIANT* pvarChild)
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::get_accFocus(pvarChild);
}


HRESULT CDesignDialog::get_accHelp(VARIANT varChild, BSTR* pszHelp)
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::get_accHelp(varChild, pszHelp);
}


HRESULT CDesignDialog::get_accHelpTopic(BSTR* pszHelpFile, VARIANT varChild, long* pidTopic)
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::get_accHelpTopic(pszHelpFile, varChild, pidTopic);
}


HRESULT CDesignDialog::get_accKeyboardShortcut(VARIANT varChild, BSTR* pszKeyboardShortcut)
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::get_accKeyboardShortcut(varChild, pszKeyboardShortcut);
}


HRESULT CDesignDialog::get_accName(VARIANT varChild, BSTR* pszName)
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::get_accName(varChild, pszName);
}


HRESULT CDesignDialog::get_accParent(IDispatch** ppdispParent)
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::get_accParent(ppdispParent);
}


HRESULT CDesignDialog::get_accRole(VARIANT varChild, VARIANT* pvarRole)
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::get_accRole(varChild, pvarRole);
}


HRESULT CDesignDialog::get_accSelection(VARIANT* pvarChildren)
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::get_accSelection(pvarChildren);
}


HRESULT CDesignDialog::get_accState(VARIANT varChild, VARIANT* pvarState)
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::get_accState(varChild, pvarState);
}


HRESULT CDesignDialog::get_accValue(VARIANT varChild, BSTR* pszValue)
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::get_accValue(varChild, pszValue);
}


LPUNKNOWN CDesignDialog::GetInterfaceHook(const void* /*piid*/)
{
	// TODO: Add your specialized code here and/or call the base class

	return NULL;
}


CScrollBar* CDesignDialog::GetScrollBarCtrl(int nBar) const
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::GetScrollBarCtrl(nBar);
}


void CDesignDialog::HtmlHelp(DWORD_PTR dwData, UINT nCmd)
{
	// TODO: Add your specialized code here and/or call the base class

	CDialog::HtmlHelp(dwData, nCmd);
}


BOOL CDesignDialog::IsInvokeAllowed(DISPID /*dispid*/)
{
	// TODO: Add your specialized code here and/or call the base class

	return TRUE;
}


BOOL CDesignDialog::OnAmbientProperty(COleControlSite* pSite, DISPID dispid, VARIANT* pvar)
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::OnAmbientProperty(pSite, dispid, pvar);
}


void CDesignDialog::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialog::OnCancel();
}


BOOL CDesignDialog::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult)
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::OnChildNotify(message, wParam, lParam, pLResult);
}


BOOL CDesignDialog::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}


BOOL CDesignDialog::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::OnCommand(wParam, lParam);
}


BOOL CDesignDialog::OnCreateAggregates()
{
	// TODO: Add your specialized code here and/or call the base class

	return TRUE;
}


void CDesignDialog::OnFinalRelease()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialog::OnFinalRelease();
}


BOOL CDesignDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::OnNotify(wParam, lParam, pResult);
}


void CDesignDialog::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialog::OnOK();
}


void CDesignDialog::OnSetFont(CFont* pFont)
{
	// TODO: Add your specialized code here and/or call the base class

	CDialog::OnSetFont(pFont);
}


INT_PTR CDesignDialog::OnToolHitTest(CPoint point, TOOLINFO* pTI) const
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::OnToolHitTest(point, pTI);
}


BOOL CDesignDialog::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::OnWndMsg(message, wParam, lParam, pResult);
}


void CDesignDialog::PostNcDestroy()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialog::PostNcDestroy();
}


void CDesignDialog::PreInitDialog()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialog::PreInitDialog();
}


void CDesignDialog::PreSubclassWindow()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialog::PreSubclassWindow();
}


BOOL CDesignDialog::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::PreTranslateMessage(pMsg);
}


void CDesignDialog::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
	}
	else
	{	// loading code
	}
}


LRESULT CDesignDialog::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	return CDialog::WindowProc(message, wParam, lParam);
}


void CDesignDialog::WinHelp(DWORD dwData, UINT nCmd)
{
	// TODO: Add your specialized code here and/or call the base class

	CDialog::WinHelp(dwData, nCmd);
}

BEGIN_MESSAGE_MAP(CDesignDialog, CDialog)
	//{{AFX_MSG_MAP(CCustomDialog)
		// No message handlers
	//}}AFX_MSG_MAP
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

HBRUSH CDesignDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	return SetCtlColor(pDC, pWnd, nCtlColor);
}
