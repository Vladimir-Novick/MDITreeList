#pragma once
#include "stdafx.h" 

class CTreeCtrlEx :   public CTreeCtrl
{
	DECLARE_DYNAMIC(CTreeCtrlEx)
protected:
	DECLARE_MESSAGE_MAP()
	CTreeCtrlEx();
	virtual ~CTreeCtrlEx();
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
};

