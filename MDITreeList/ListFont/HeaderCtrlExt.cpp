// HeaderCtrlEx.cpp : implementation file
//

#include "stdafx.h"
#include "HeaderCtrlExt.h"
#include "..\..\NDC\ClientWnd.h"

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
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHeaderCtrlExt message handlers



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

	pDC->SelectObject(GetStockObject(DEFAULT_GUI_FONT));

   ::DrawFrameControl(lpDrawItemStruct->hDC, 
      &lpDrawItemStruct->rcItem, DFC_BUTTON, DFCS_BUTTONPUSH);

	UINT uFormat = DT_CENTER;

   ::DrawText(lpDrawItemStruct->hDC, lpBuffer, _tcslen(lpBuffer),
      &lpDrawItemStruct->rcItem, uFormat);

   pDC->SelectStockObject(SYSTEM_FONT);
}


