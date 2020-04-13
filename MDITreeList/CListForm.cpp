// CListForm.cpp : implementation file
//

#include "stdAfx.h"
#include "CListForm.h"
#include "resource.h"


// CListForm dialog

IMPLEMENT_DYNAMIC(CListForm, CDialog)

CListForm::CListForm(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_LIST_FORM, pParent)
{

}

CListForm::~CListForm()
{
}

void CListForm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CListForm, CDialog)
END_MESSAGE_MAP()


// CListForm message handlers
