#pragma once

#include <mutex>

/// <summary>
///   Client Window for MDI Frame. Support erase backgrownd to custom color 
/// </summary>
class CClientWnd : public CWnd
{
	DECLARE_DYNAMIC(CClientWnd)

public:
	CClientWnd();
	virtual ~CClientWnd();

protected:
   afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	DECLARE_MESSAGE_MAP()
};

const UINT  WM_SET_DEFAULT_APP_FONT = RegisterWindowMessage(L"set-default-app-font");

class CDefaultAppFont {
protected:
	static std::mutex instance_mutex;
	CDefaultAppFont();
	 CFont* m_DefaultFont;
	 static CDefaultAppFont * m_instance;
public:
	virtual ~CDefaultAppFont();
     static CDefaultAppFont *GetInstance() ;
	 CFont* GetFont();
	 void SetFont(CFont* font);
};

