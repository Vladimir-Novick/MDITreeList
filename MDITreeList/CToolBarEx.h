#pragma once
#include <afxext.h>
class CToolBarEx :  public CToolBar
{
	  
public:
	DECLARE_MESSAGE_MAP()
    DECLARE_DYNAMIC(CToolBarEx)

	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	CToolBarEx();
	virtual ~CToolBarEx();
	afx_msg void OnPaint();

public:
	virtual BOOL Create(CWnd* pParentWnd, DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_TOP, UINT nID = AFX_IDW_TOOLBAR);
	virtual BOOL CreateEx(CWnd* pParentWnd, DWORD dwCtrlStyle = TBSTYLE_FLAT, DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP, CRect rcBorders = CRect(0, 0, 0, 0), UINT nID = AFX_IDW_TOOLBAR);
	virtual BOOL DestroyWindow();
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

