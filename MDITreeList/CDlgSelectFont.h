#pragma once

#include <string>
// CDlgSelectFont dialog

class CDlgSelectFont : public CDialog
{

public:
	CDlgSelectFont(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CDlgSelectFont();
	void SelectFont(std::string fontName);
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
