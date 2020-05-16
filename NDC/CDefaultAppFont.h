#pragma once
#pragma once

#define WINVER			0x0501
#define _WIN32_WINNT	0x0501 

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE classes
#include <afxodlgs.h>       // MFC OLE dialog classes
#include <afxdisp.h>        // MFC Automation classes
#endif // _AFX_NO_OLE_SUPPORT


#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>			// MFC ODBC database classes
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>			// MFC DAO database classes
#endif // _AFX_NO_DAO_SUPPORT

#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT



#include <string>
#include <map>


#define TREE_FONT_NAME "TreeFont"
#define GRID_FONT_NAME "GridFont"
#define TREE_HEADER_FONT_NAME "TreeHeaderFont"
#define GRID_HEADER_FONT_NAME "GridHeaderFont"

#define LEFT_BAR_FONT_NAME "LeftBarFont"
#define LEFT_BAR_BUTTON_FONT_NAME "LeftBarFontButton"


#define SHORTCUT_BAR_WIDTH "ShortcutBar_Width"
#define WINDOWS_CONFIGURATION "Windows Configuration"

#define DIALOG_FONT_NAME "DialogsFont"
#define DIALOG_FONT_NAME_R 0
#define DIALOG_FONT_NAME_G 0
#define DIALOG_FONT_NAME_B 0



#define DIALOG_BACKGROUNT_COLOR_NAME "DialogsBackgrownd"
#define DIALOG_BACKGROUNT_COLOR_NAME_R 226
#define DIALOG_BACKGROUNT_COLOR_NAME_G 230
#define DIALOG_BACKGROUNT_COLOR_NAME_B 233


#define DIALOG_FONT_NAME_SIZE 9
#define LEFT_BAR_BUTTON_FONT_NAME_SIZE 9
#define LEFT_BAR_FONT_NAME_SIZE 9
#define GRID_FONT_NAME_SIZE 9
#define GRID_HEADER_FONT_NAME_SIZE 9
#define TREE_FONT_NAME_SIZE 9
#define TREE_HEADER_FONT_NAME_SIZE 9

#define DllExport   __declspec( dllexport )

using namespace std;

class DllExport  CDefaultAppFont {
private:
	static CDefaultAppFont instance;
	map<string, CFont*> fonts;
	map<string, UINT> heights;
	map<string, HBRUSH> colors;
	CDefaultAppFont();

	void SetItemHeight(string fontName, UINT height);


public:

	UINT MakeItemHeight(CFont* pFont);
	~CDefaultAppFont();
	static CDefaultAppFont* GetInstance();

	CFont* GetFont(string fontName);
	void SetFont(string fontName, CFont* font);
	void SetFont(string fontName, CFont* font, COLORREF color);
	void SetFont(string fontName, LOGFONT& font);

	HBRUSH GetColor(string colorName, COLORREF defaultColor);
	HBRUSH SetColor(string colorName, COLORREF color);
	void DestroyColor(string colorName);
	COLORREF GetBrushColor(HBRUSH brush);

	UINT GetItemHeight(string fontName);
	void DestroyObjects();
	void RedrawAllWindow();

};