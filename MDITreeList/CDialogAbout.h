#pragma once

#include "stdafx.h"

class CDialogAbout : public CWinThread
{
    DECLARE_DYNCREATE(CDialogAbout)
    CDialogAbout() {};
    virtual BOOL InitInstance();
};

