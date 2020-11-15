#include "stdafx.h"
#include "CTreeCtrlEx.h"

BEGIN_MESSAGE_MAP(CTreeCtrlEx, CTreeCtrl)

	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

IMPLEMENT_DYNAMIC(CTreeCtrlEx, CTreeCtrl)

CTreeCtrlEx::CTreeCtrlEx() :CTreeCtrl() {

}

CTreeCtrlEx::~CTreeCtrlEx()  {

}

BOOL CTreeCtrlEx::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	return FALSE;
//	return CTreeCtrl::OnEraseBkgnd(pDC);
}
