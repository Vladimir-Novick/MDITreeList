#pragma once

#include "StdAfx.h"
#include "resource.h"
#include "CBaseDialog.h"

//  ----- Implement Modales dialog

class CLoginDialog : public CWinThread
{
    DECLARE_DYNCREATE(CLoginDialog)
    CLoginDialog() {};
    virtual BOOL InitInstance();
};

//   ------ Standard Modal Dialog -----


/////////////////////////////////////////////////////////////////////////////

class CLoginDlg : public CBaseLoginDialog
{
public:
	CLoginDlg();

	// Dialog Data
		//{{AFX_DATA(CLoginDlg)
	enum { IDD = IDD_DIALOG_LOGIN };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLoginDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CLoginDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
};


