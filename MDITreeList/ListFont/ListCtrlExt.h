
#pragma once

// ListCtrlEx.h : header file
//
#include "HeaderCtrlExt.h"
/////////////////////////////////////////////////////////////////////////////
// CListCtrlExt window


static _TCHAR *_gszColumnLabel[4] =
{
	_T("Column\nName 1"), _T("Column\nName 2"), _T("Column\nName 3"), _T("Column\nName 4")
};


static int _gnColumnWidth[4] =
{
	150, 100, 150, 80
};


static int _gnColumnFmt[4] =
{
	LVCFMT_LEFT, LVCFMT_RIGHT, LVCFMT_LEFT,LVCFMT_LEFT
};


static _TCHAR *_gszItem[3][4] =
{
	_T("Item 1.1\nLine 1"),  _T("Item 1.2\nLine 1"), _T("Item 1.3\nLine 1"), _T("Item 1.4\nLine 1"),
	_T("Item 2.1\nLine 2"),  _T("Item 2.2\nLine 2"), _T("Item 2.3\nLine 2"), _T("Item 2.4\nLine 2"),
	_T("Item 3.1\nLine 2"),  _T("Item 3.2\nLine 2"), _T("Item 3.3\nLine 2"), _T("Item 3.4\nLine 2")
};

class CListCtrlExt : public CListCtrl
{
// Construction
public:
	CListCtrlExt();

// Attributes
public:
	int		m_nLinesPerRow;	
	int     m_nColumns, m_nRows ;

	CFont			m_NewListFont;
	CHeaderCtrlExt	m_HeaderCtrl ;

	void OnInitialUpdate() ;
	void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) ;

	void SetNoOfLinesPerRow(int n)  { m_nLinesPerRow = 2 ; }
	void SetNoOfColumns(int n=1)	{ m_nColumns = 4 ; }
	void SetNoOfRows(int n=0)		{ m_nRows = 3 ; }

	afx_msg LRESULT	OnSetFont(WPARAM wParam, LPARAM lParam);
	afx_msg void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListCtrlExt)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CListCtrlExt();

	// Generated message map functions
protected:
	//{{AFX_MSG(CListCtrlExt)
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
	afx_msg void OnPaint();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

