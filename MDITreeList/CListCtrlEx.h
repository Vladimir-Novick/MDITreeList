#pragma once
#include <afxcmn.h>

class CListCtrlEx :   public CListCtrl
{
	DECLARE_DYNAMIC(CListCtrlEx)
protected:

public:
	DECLARE_MESSAGE_MAP()

	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	CListCtrlEx();
	virtual ~CListCtrlEx();
	afx_msg void OnPaint();
};

