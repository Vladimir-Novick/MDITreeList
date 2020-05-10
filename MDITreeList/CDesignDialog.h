#pragma once
#include <afxwin.h>

// all CModalDialog functionality is now in CDialog
#define CModalDesignDialog    CDesignDialog



class  CDesignDialog : public CDialog
{


private:


	void Init();
	void ResizeWindow(const HWND& source_hWnd, float multiplier);
	void ResizeChildWindow(const HWND& source_hWnd, float multiplier);

public:


	CDesignDialog() :CDialog() {
		Init();
	}

	explicit CDesignDialog(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL):CDialog(lpszTemplateName, pParentWnd) {
		Init();
	};
	explicit CDesignDialog(UINT nIDTemplate, CWnd* pParentWnd = NULL) : CDialog(nIDTemplate, pParentWnd) {
		Init();
	};

	virtual ~CDesignDialog();
	DECLARE_MESSAGE_MAP()

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDesignDialog)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_VIRTUAL


	virtual BOOL OnInitDialog();

};

