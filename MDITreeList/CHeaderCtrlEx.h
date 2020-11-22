#pragma once
#include <afxcmn.h>
class CHeaderCtrlEx :    public CHeaderCtrl
{
	DECLARE_DYNAMIC(CHeaderCtrlEx)
public:
	DECLARE_MESSAGE_MAP()

	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	CHeaderCtrlEx();
	virtual ~CHeaderCtrlEx();
	afx_msg void OnPaint();
};

