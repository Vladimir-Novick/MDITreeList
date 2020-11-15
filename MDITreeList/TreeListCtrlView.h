
#pragma once

#include "stdafx.h" 
#include "resource.h" 
#include "TreeListView.h"


class CTreeListCtrlView : public CTreeListView
{
protected: // create from serialization only
	CTreeListCtrlView();
	DECLARE_DYNCREATE(CTreeListCtrlView)

// Attributes
public:
	CTreeListCtrlDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTreeListCtrlView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

// Implementation
public:
	CImageList m_Images;
	virtual ~CTreeListCtrlView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	bool m_bShowHeader;
	//{{AFX_MSG(CTreeListCtrlView)
	afx_msg void OnHeader();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // debug version in TreeListCtrlView.cpp
inline CTreeListCtrlDoc* CTreeListCtrlView::GetDocument()
   { return (CTreeListCtrlDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

