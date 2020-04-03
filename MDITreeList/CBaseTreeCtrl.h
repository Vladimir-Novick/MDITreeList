#pragma once

#include "stdafx.h" 
#include "ClientWnd.h"


#define TVMYN_INSERTITEM WM_USER+2511

#define UNUSED_PARAM(a) (void)a

//@struct Structure for nessassary data wich is to be got from the header for drawing
struct _HeaderData
{
	long nWidth;		//@field width of the column
	RECT rcDefault;		//@field Rectangle of the ColumnHeaderItem (used for left and right value of the item's column)
	UINT nAlingment;	//@field alignment of the column
};
typedef struct _HeaderData HeaderData;


class CBaseTreeCtrl : public CTreeCtrl
{

protected:


	afx_msg LRESULT OnInsertItem(WPARAM wParam, LPARAM lParam);

	afx_msg LRESULT OnLButtonDblClk(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnLButtonClk(WPARAM wParam, LPARAM lParam);
	afx_msg void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	DECLARE_MESSAGE_MAP()
	UINT m_nItemHeight;
public:

	void MakeItemHeight();
	virtual void PreSubclassWindow();
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnParentNotify(UINT message, LPARAM lParam);

	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
};