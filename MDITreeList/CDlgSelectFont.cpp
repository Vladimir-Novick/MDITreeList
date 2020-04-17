// CDlgSelectFont.cpp : implementation file
//

#include "StdAfx.h"
#include "CDlgSelectFont.h"
#include "afxdialogex.h"
#include "resource.h"


// CDlgSelectFont dialog

IMPLEMENT_DYNAMIC(CDlgSelectFont, CDialog)

CDlgSelectFont::CDlgSelectFont(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DLG_SELECT_FONT, pParent)
{

}

CDlgSelectFont::~CDlgSelectFont()
{
}

void CDlgSelectFont::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgSelectFont, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_LIST_HEADES, &CDlgSelectFont::OnBnClickedButtonListHeades)
	ON_BN_CLICKED(IDC_BUTTON_LIST_ITEMS, &CDlgSelectFont::OnBnClickedButtonListItems)
END_MESSAGE_MAP()


// CDlgSelectFont message handlers


void CDlgSelectFont::OnBnClickedButtonListHeades()
{
	// TODO: Add your control notification handler code here
}


void CDlgSelectFont::OnBnClickedButtonListItems()
{
	// TODO: Add your control notification handler code here
}
