
#pragma once


#include "stdafx.h" 
#include "resource.h" 


/////////////////////////////////////////////////////////////////////////////
// CMDIAppViewApp:
// See MDIAppView.cpp for the implementation of this class
//

class CMDIAppViewApp : public CWinApp
{
protected:
	CMultiDocTemplate* m_pDocTemplateTreeView;
	CMultiDocTemplate* m_TemplateListFont;
	void ReadDefaultAppFont(LOGFONT& lf);
	void SaveDefaultAppFont(LOGFONT& lf);
public:
	CMDIAppViewApp();
	virtual ~CMDIAppViewApp();
	HINSTANCE hResourceDLL;



// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMDIAppViewApp)

	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMDIAppViewApp)
	afx_msg void OnAppAbout();
	afx_msg void OnOpenTreeView();
	afx_msg void OnOpenListView();

	afx_msg void OnSetFont();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	virtual HINSTANCE LoadAppLangResourceDLL();
	virtual int ExitInstance();
	void MakeDefaultAppFont();
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

