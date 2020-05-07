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

	//------------------
	CFont* font = CDefaultAppFont::GetInstance()->GetFont(TREE_FONT_NAME);
	int rowHeight = CDefaultAppFont::GetInstance()->GetItemHeight(TREE_FONT_NAME);
	CFont* oldFont;
	CDC* cdc = GetDC();
	oldFont = cdc->SelectObject(font);
	/// /// 
	auto format = DT_LEFT | DT_EDITCONTROL | DT_WORDBREAK | DT_CALCRECT;
	RECT cellRect;

	DRAWTEXTPARAMS lpDTParams;
	lpDTParams.cbSize = sizeof(lpDTParams);
	lpDTParams.iLeftMargin = 1;
	lpDTParams.iRightMargin = 1;
	lpDTParams.iTabLength = 4;
	lpDTParams.uiLengthDrawn = 0;

	int maxHeight = rowHeight;

	HDITEM hdi;
	enum
	{
		sizeOfBuffer = 256
	};
	TCHAR lpBuffer[sizeOfBuffer];
	bool fFound = false;

	hdi.mask = HDI_TEXT | HDI_WIDTH;
	hdi.pszText = lpBuffer;
	hdi.cchTextMax = sizeOfBuffer;
	int itemCount = GetItemCount();

	for (int col = 0; col < itemCount; col++) {
		GetItem(col, &hdi);
		int colWidth = hdi.cxy;
		cellRect.right = colWidth;
		cellRect.bottom = 0;
		cellRect.top = 0;
		cellRect.left = 0;
		auto text = hdi.pszText;
		if (text != NULL) {
			cdc->DrawTextEx(text, &cellRect, format, &lpDTParams);
			maxHeight = max(maxHeight, cellRect.bottom);
		}
	}

	cdc->SelectObject(oldFont);
	ReleaseDC(cdc);
	//------------------

	int nRet = CHeaderCtrl::DefWindowProc(HDM_LAYOUT, 0, lParam);

	pWPos->cy = maxHeight;

	//*** Decreases the table list height on the table header height
	pRect->top = maxHeight;

	return nRet;
}  // OnLayout

void CHeaderCtrlExt::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	ASSERT(lpDrawItemStruct->CtlType == ODT_HEADER);

	HDITEM hdi;
	TCHAR  lpBuffer[256];

	hdi.mask = HDI_TEXT;
	hdi.pszText = lpBuffer;
	hdi.cchTextMax = sizeof(lpBuffer);

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


