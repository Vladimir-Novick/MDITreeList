

#pragma once


#include "CBaseTreeCtrl.h"
#include "ListFont/HeaderCtrlExt.h"

class CBaseTreeObj : public CObject
{

public:
	CStringArray m_strColumns;
	CBaseTreeObj& operator=(CBaseTreeObj& obj);
};


class CTreeListView : public CView
{

	DECLARE_DYNCREATE(CTreeListView)

protected:
	CMap<HTREEITEM, HTREEITEM, CBaseTreeObj, CBaseTreeObj&> m_Entries;
	CBaseTreeCtrl		m_List;
	CHeaderCtrlExt		m_ctrlHeader;
	HeaderData*		m_vsCol;
	COLORREF		m_colBackColor;
	COLORREF		m_colHilightText;
	COLORREF		m_colText;
	CBrush			m_BackBrush;
	CBrush			m_BackBrushNormal;
	bool			m_bDescriptionDisplay;
	long			m_nOffset;
	long			m_nHeaderWidth;
	long			m_nNrColumns;

	CTreeListView();
	virtual ~CTreeListView();

	void CalculateClientRects(CRect& rcBase, CRect& rcTree, CRect& rcHeader);
	void SizeObjects(void);
	bool ResetScrollbar(void);
	void DrawTreeItem(bool bFocus, CRect rcItem, HDC hdc, HTREEITEM hItem);
	void UpdateColStruct(void);
	BOOL OnCustomdrawTree(LPNMHDR pNmhdr, LRESULT* pResult);
	BOOL OnEndTrack(LPNMHDR pNmhdr, LRESULT* pResult);
	BOOL OnDeleteItem(LPNMHDR pNmhdr, LRESULT* pResult);

	//{{AFX_MSG(CTreeListView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	afx_msg LRESULT OnInsertItem(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTreeListView)
	protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

public:
	int InsertColumn( int nCol, const LVCOLUMN* pColumn );
	int InsertColumn( int nCol, LPCTSTR lpszColumnHeading, int nFormat = LVCFMT_LEFT, int nWidth = -1, int nSubItem = -1 );
	BOOL DeleteColumn( int nCol );
	BOOL SetSubItemText( HTREEITEM hItem, int nSubItem, CString strBuffer);
	BOOL GetSubItemText( HTREEITEM hItem, int nSubItem, CString& strBuffer);
	CImageList* GetHeaderImageList();
	CImageList* SetHeaderImageList( CImageList * pImageList);
	CTreeCtrl& GetTreeCtrl();
	void ShowHeader(bool bShow);
	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
};
