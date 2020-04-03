#pragma once
#include <afxwin.h>

#define ID_WAIT_SECONDS 101

class CBaseLoginDialog :
	public CDialog
{
private:
	UINT TimmerID = 0;

public:
	void SetWaitTime(UINT waitTime);
	UINT WaitTimer;
	CBaseLoginDialog();
	explicit CBaseLoginDialog(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL);
	explicit CBaseLoginDialog(UINT nIDTemplate, CWnd* pParentWnd = NULL);
	virtual ~CBaseLoginDialog();
	HANDLE m_hSemForStopDoModal;
	INT_PTR ReturnDoModal;
	virtual BOOL Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL);
	virtual BOOL CreateEx(DWORD dwExStyle, LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, LPVOID lpParam = NULL);
	virtual int DoModal();
	virtual void OnOK();
	virtual void OnCancel();
	void EndDialog(int nResult);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

