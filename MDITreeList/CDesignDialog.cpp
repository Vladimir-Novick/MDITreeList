#include "StdAfx.h"
#include "CDesignDialog.h"
#include "CDefaultAppFont.h"
#include <algorithm> 
#include <list>
using namespace std;

BEGIN_MESSAGE_MAP(CDesignDialog, CDialog)
	ON_WM_CTLCOLOR()

ON_WM_CREATE()

END_MESSAGE_MAP()

CDesignDialog::~CDesignDialog() {


}

void CDesignDialog::Init() {

}

HBRUSH CDesignDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{

	if (nCtlColor == CTLCOLOR_STATIC || nCtlColor == CTLCOLOR_DLG )
	{
		COLORREF defaultColor = GetSysColor(CTLCOLOR_DLG);
		HBRUSH hbr = CDefaultAppFont::GetInstance()->GetColor(DIALOG_BACKGROUNT_COLOR_NAME, defaultColor);

		COLORREF colorRef = CDefaultAppFont::GetInstance()->GetBrushColor(hbr);
		pDC->SetBkColor(colorRef);
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
	int max_height = 0;
	int max_width = 0;
	double multiplier_width = 0;
	TCHAR controlClassName[128];
	CFont* oldFont;
	CFont* pFont = CDefaultAppFont::GetInstance()->GetFont(DIALOG_FONT_NAME);
	int newItemHeight = CDefaultAppFont::GetInstance()->GetItemHeight(DIALOG_FONT_NAME);
	CWnd* cwnd = CWnd::FromHandle(m_hWnd);
	CDC* cdc = GetDC();
	CWnd* pChild;

	pChild = GetWindow(GW_CHILD);
	CString tempTextBuf;
	while (pChild) {
		CFont* childFont = pChild->GetFont();
		if (childFont != NULL) {
			int itemHeight = CDefaultAppFont::GetInstance()->MakeItemHeight(childFont);
			max_height = max(max_height, itemHeight);

			//GetClassName(pChild->m_hWnd, controlClassName, 128);
			//if (_tcscmp(_T("Static"), controlClassName) == 0) {
			//	
		}
		
		pChild = pChild->GetNextWindow();
	}

	float multiplier_height = (float)newItemHeight / (float)max_height;
	multiplier_width = max(multiplier_height, multiplier_width);

	ResizeWindow(m_hWnd, multiplier_height);

	list<CWnd*> wndList;
	pChild = GetWindow(GW_CHILD);
	while (pChild) {

		wndList.push_back(pChild);
		pChild = pChild->GetNextWindow();
	}

	for (auto it = wndList.begin(); it != wndList.end(); ++it){
		CWnd * window =  *it;
		window->SetFont(pFont);
		ResizeChildWindow(window->m_hWnd, multiplier_height);
	}

	cwnd->SetFont(pFont);
	ReleaseDC(cdc);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDesignDialog::ResizeWindow(const HWND& source_hWnd, float multiplier)
{
	CWnd* wnd = CWnd::FromHandle(source_hWnd);

	RECT rect = {};
	wnd->GetWindowRect(&rect);
	this->ScreenToClient(&rect);

	float cx = (float)(rect.right - rect.left) * multiplier;

	float cy = (float)(rect.bottom - rect.top) * multiplier;

	int X_max = GetSystemMetrics(SM_CXSCREEN); 
	int Y_max = GetSystemMetrics(SM_CYSCREEN);

	CWnd * parentCWnd = GetParent();
	

	RECT parentRect;
	parentCWnd->GetWindowRect(&parentRect);

	int deltaX = ((parentRect.right - parentRect.left)-cx) / 2;
	int deltaY = ((parentRect.bottom - parentRect.top)-cy) / 2;

	if (deltaY < 0) { deltaY = 0; }


	wnd->SetWindowPos(NULL, deltaX, deltaY, cx, cy,  SWP_NOZORDER);
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
