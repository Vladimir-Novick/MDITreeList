#if !defined(AFX_HEADERCTRLEX_H__30509657_B8A5_11D5_8CEB_00E098800D6B__INCLUDED_)
#define AFX_HEADERCTRLEX_H__30509657_B8A5_11D5_8CEB_00E098800D6B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HeaderCtrlEx.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHeaderCtrlExt window

class CHeaderCtrlExt : public CHeaderCtrl
{
// Construction
public:
	CHeaderCtrlExt();

// Attributes
public:
	CFont	m_NewHeaderFont;
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHeaderCtrlExt)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CHeaderCtrlExt();

	// Generated message map functions
protected:
	//{{AFX_MSG(CHeaderCtrlExt)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HEADERCTRLEX_H__30509657_B8A5_11D5_8CEB_00E098800D6B__INCLUDED_)
