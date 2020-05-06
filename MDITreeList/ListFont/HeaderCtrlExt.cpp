// HeaderCtrlEx.cpp : implementation file
//

#include "stdafx.h"
#include "HeaderCtrlExt.h"
#include "..\..\NDC\ClientWnd.h"
#include "..\..\NDC\CDefaultAppFont.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHeaderCtrlEx

CHeaderCtrlExt::CHeaderCtrlExt()
{
}

CHeaderCtrlExt::~CHeaderCtrlExt()
{
}


BEGIN_MESSAGE_MAP(CHeaderCtrlExt, CHeaderCtrl)
	//{{AFX_MSG_MAP(CHeaderCtrlExt)
	ON_MESSAGE(HDM_LAYOUT, OnLayout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHeaderCtrlExt message handlers


LRESULT CHeaderCtrlExt::OnLayout(WPARAM, LPARAM lParam) {
    LPHDLAYOUT pHL = reinterpret_cast<LPHDLAYOUT>(lParam);

    //*** The table list rectangle
    RECT* pRect = pHL->prc;

    //*** The table header rectangle
    WINDOWPOS* pWPos = pHL->pwpos;


    CDC* pDC = GetDC();
    auto	pFont = CDefaultAppFont::GetInstance()->GetFont(TREE_HEADER_FONT_NAME);
    CFont* pOldFont = pDC->SelectObject(pFont);
    TEXTMETRIC tm;
    GetTextMetrics(pDC->m_hDC, &tm);
    pDC->SelectObject(pOldFont);
    ReleaseDC(pDC);

    UINT newHeight = tm.tmHeight * 1.2;


    int nRet = CHeaderCtrl::DefWindowProc(HDM_LAYOUT, 0, lParam);

    pWPos->cy = newHeight * 2;

    //*** Decreases the table list height on the table header height
    pRect->top = newHeight * 2;

    return nRet;
}  // OnLayout

void CHeaderCtrlExt::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	ASSERT(lpDrawItemStruct->CtlType == ODT_HEADER);

	HDITEM hdi;
	TCHAR  lpBuffer[256];

	hdi.mask = HDI_TEXT;
	hdi.pszText = lpBuffer;
	hdi.cchTextMax = sizeof(lpBuffer) ;

	GetItem(lpDrawItemStruct->itemID, &hdi);

	CDC* pDC;
	pDC = CDC::FromHandle(lpDrawItemStruct->hDC);

    auto	pFont = CDefaultAppFont::GetInstance()->GetFont(TREE_HEADER_FONT_NAME);
    CFont* pOldFont = pDC->SelectObject(pFont);
	
   ::DrawFrameControl(lpDrawItemStruct->hDC, 
      &lpDrawItemStruct->rcItem, DFC_BUTTON, DFCS_BUTTONPUSH);

	UINT uFormat = DT_CENTER;

   ::DrawText(lpDrawItemStruct->hDC, lpBuffer, _tcslen(lpBuffer),
      &lpDrawItemStruct->rcItem, uFormat);

   pDC->SelectObject(pOldFont);
}


