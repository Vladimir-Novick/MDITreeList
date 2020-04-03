#include "stdafx.h"
#include "CBaseDialog.h"


BOOL CBaseLoginDialog::Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd)
{
	return CDialog::Create(lpszTemplateName, pParentWnd);
}

CBaseLoginDialog::CBaseLoginDialog() : CDialog(){
	WaitTimer = 0;
}

CBaseLoginDialog::CBaseLoginDialog(LPCTSTR lpszTemplateName, CWnd* pParentWnd) :CDialog(lpszTemplateName, pParentWnd) {
	WaitTimer = 0;
}

CBaseLoginDialog::CBaseLoginDialog(UINT nIDTemplate, CWnd* pParentWnd) : CDialog(nIDTemplate, pParentWnd) {
	WaitTimer = 0;
}

BOOL CBaseLoginDialog::CreateEx(DWORD dwExStyle, LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, LPVOID lpParam)
{
	return CDialog::CreateEx(dwExStyle, lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, lpParam);
}

CBaseLoginDialog::~CBaseLoginDialog() {

}


INT_PTR CBaseLoginDialog::DoModal()
{
	ReturnDoModal = IDCANCEL;
	CDialog::DoModal();
	return ReturnDoModal;
}

void CBaseLoginDialog::EndDialog(int nResult) {
	ReturnDoModal = nResult;
	CDialog::EndDialog(nResult);
}

void CBaseLoginDialog::OnOK()
{
	ReturnDoModal = IDOK;
	CDialog::OnOK();
}


void CBaseLoginDialog::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class
	ReturnDoModal = IDCANCEL;
	CDialog::OnCancel();
}


BOOL CBaseLoginDialog::PreCreateWindow(CREATESTRUCT& cs)
{
	return CDialog::PreCreateWindow(cs);
}
BEGIN_MESSAGE_MAP(CBaseLoginDialog, CDialog)
	ON_WM_CREATE()
	ON_WM_TIMER()
END_MESSAGE_MAP()


int CBaseLoginDialog::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	if (WaitTimer > 0) {
		TimmerID = SetTimer(ID_WAIT_SECONDS, WaitTimer * 1000, NULL);
	}


	return 0;
}


void CBaseLoginDialog::SetWaitTime(UINT waitTime)
{
	WaitTimer = waitTime;
}


void CBaseLoginDialog::OnTimer(UINT_PTR nIDEvent)
{
	if (WaitTimer > 0 && nIDEvent == ID_WAIT_SECONDS) {
		OnCancel();
	}

	CDialog::OnTimer(nIDEvent);
}
