// CDlgSelectFont.cpp : implementation file
//

#include "StdAfx.h"
#include "CDlgSelectFont.h"
#include "resource.h"
#include <string>
#include "CAppParamsMngr.h"

// CDlgSelectFont dialog


CDlgSelectFont::CDlgSelectFont(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG2, pParent)
{

}

CDlgSelectFont::~CDlgSelectFont()
{
}

void CDlgSelectFont::SelectFont(std::string fontName) {

}

void CDlgSelectFont::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgSelectFont, CDialog)
END_MESSAGE_MAP()


// CDlgSelectFont message handlers
