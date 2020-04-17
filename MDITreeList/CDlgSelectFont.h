#pragma once

#include "resource.h"

// CDlgSelectFont dialog

class CDlgSelectFont : public CDialog
{
	DECLARE_DYNAMIC(CDlgSelectFont)

public:
	CDlgSelectFont(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CDlgSelectFont();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_SELECT_FONT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonListHeades();
	afx_msg void OnBnClickedButtonListItems();
};
