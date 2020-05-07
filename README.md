# MDITreeList

MDI with tree list view . Custom draw a dynamically created CListCtrl. Auto-resize CList Control

##  Create MDI View from Dialog forms

How to create MDI View from Dialog forms.

1) Create standard Dialog form
2) Create Empty Document-View form
3) Add dialog instance to view 
4) insert OnInitialUpdate action to message handlers.

Example:

			void CListFontView::OnInitialUpdate() 
			{
				CFormView::OnInitialUpdate();
				SetScrollSizes(MM_TEXT, CSize(0, 0)); // Hide Scrollbars in CFormView 
				m_ListCtrl.SubclassDlgItem(IDC_LIST, this);
				m_ListCtrl.SetNoOfColumns(3);
				m_ListCtrl.SetNoOfRows(2);
				m_ListCtrl.ShowScrollBar(SB_BOTH, FALSE);
				m_ListCtrl.OnInitialUpdate();
			}

##  Auto-resize CList Control

			void CListCtrlExt::OnSize(UINT nType, int cx, int cy)
			{
				CListCtrl::OnSize(nType, cx, cy);

				double currentSize = 0;

				CHeaderCtrl* pHeader = NULL;
				pHeader = GetHeaderCtrl();

				if (pHeader->m_hWnd != NULL) {

					for (int i = 0; i < pHeader->GetItemCount(); i++)
					{
						int nWidth = GetColumnWidth(i);
						currentSize += nWidth;
					}

					double m = cx / currentSize;

					for (int i = 0; i < pHeader->GetItemCount(); i++)
					{
						int nWidth = GetColumnWidth(i);
						double  d = nWidth *= m;
						DWORD w = d;
						SetColumnWidth(i, w);
					}
				}
			}

#  Design Components Library ( NDC )

Components for MFC WinForm help developers execute Design with modular and customizable UI components. 
These components enable a reliable development workflow to build beautiful and functional user experiences for C++ MFC Desktop application.


## Custom MDI Frame color


CMainFrame :

            protected:
                 CClientWnd  m_Client;

OnCreateClient action :

            BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
            {
	            if (CMDIFrameWnd::OnCreateClient(lpcs, pContext))
	            {
		            m_Client.SubclassWindow(m_hWndMDIClient);
		            return TRUE;
	            }

	            return CMDIFrameWnd::OnCreateClient(lpcs, pContext);
            }

OnClose action:

            void CMainFrame::OnClose(){
                .....
                m_Client.UnsubclassWindow();
                CMDIFrameWnd::OnClose();
            }


## Custom Dialogs

Dialogs inform users about a task and can contain critical information, require decisions, or involve multiple tasks.

Using:
  change reference from
      CDialog to CDesignDialog
      CModalDialog to CModalDesignDialog

         include: CDesignDialog.h



#  Adding Icons to Menu Items

This is an easy way to add icons to the menu.

1) Create bitmap image.

If you using GIMP please export with:

			 Compatable Options:
			   - Do not write color space information
			 Advanced Options:  
			  - 24 bits R8 G8 B8

 2) Add to .rc file:

			ID_APP_ABOUT   BITMAP   DISCARDABLE    "res\\bitmap1.bmp"

 where ID_APP_ABOUT - your menu item ID

 3) Add WM_INITMENUPOPUP handler in MainFrame class:

 for example:

 ON_WM_INITMENUPOPUP():
 
			void CMainFrame::OnInitMenuPopup(CMenu* pMenu, UINT nIndex, BOOL bSysMenu)
			{
				CMDIFrameWnd::OnInitMenuPopup(pMenu, nIndex, bSysMenu);

				if (bSysMenu)
				{
					pMenu = GetSystemMenu(FALSE);
				}
				MENUINFO mnfo;
				mnfo.cbSize = sizeof(mnfo);
				mnfo.fMask = MIM_STYLE;
				mnfo.dwStyle = MNS_CHECKORBMP | MNS_AUTODISMISS;
				::SetMenuInfo(pMenu->GetSafeHmenu(), &mnfo);

				MENUITEMINFO minfo;
				minfo.cbSize = sizeof(minfo);
	
				for (UINT pos = 0; pos < pMenu->GetMenuItemCount(); pos++)
				{
					minfo.fMask = MIIM_FTYPE | MIIM_ID ;
					pMenu->GetMenuItemInfo(pos, &minfo, TRUE);

					if (ID_APP_ABOUT == minfo.wID) {
	
						if (hBitmapAbout == NULL) {
							hBitmapAbout = (HBITMAP)::LoadBitmap(::AfxGetResourceHandle(),
								MAKEINTRESOURCE(ID_APP_ABOUT));
						}
						SetMenuItemBitmaps(pMenu->m_hMenu, pos, 
							  MF_BYPOSITION , hBitmapAbout, hBitmapAbout);
					}
				}
			}

Destructor:

			CMainFrame::~CMainFrame()
			{
				if (hBitmapAbout != NULL) {
					DeleteObject(hBitmapAbout);
				}
			}

Constructor:

			CMainFrame::CMainFrame()
			{
				// TODO: add member initialization code here
				NotLoginExit = false;
				hBitmapAbout = NULL;
			}

#  Measuring size text with DrawTextEx function

		   CFont* oldFont;
           CDC * cdc = GetDC();
           oldFont = cdc->SelectObject(font);

           auto format = DT_LEFT | DT_EDITCONTROL | DT_WORDBREAK | DT_CALCRECT;
           RECT cellRect ;

           DRAWTEXTPARAMS lpDTParams;
           lpDTParams.cbSize = sizeof(lpDTParams);
           lpDTParams.iLeftMargin = 1;
           lpDTParams.iRightMargin = 1;
           lpDTParams.iTabLength = 4;
           lpDTParams.uiLengthDrawn = 0;

           cellRect.right = colWidth;
           cellRect.bottom = 0;
           cellRect.top = 0;
           cellRect.left = 0;

           cdc->DrawTextEx(text, &cellRect, format, &lpDTParams);
           
           cdc->SelectObject(oldFont);
		   ReleaseDC(cdc);