#pragma once


// CListForm dialog

class CListForm : public CDialog
{
	DECLARE_DYNCREATE(CListForm)
public:
	CListForm(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CListForm();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LIST_FORM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
