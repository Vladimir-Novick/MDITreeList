#pragma once
#include "StdAfx.h"
#include <string>
#include <map>

#define TREE_HEADER_FONT_NAME "TreeHeaderFont"
#define TREE_FONT_NAME "TreeFont"
#define GRID_FONT_NAME "GridFont"

#define GRID_HEADER_FONT_NAME "GridHeaderFont"

#define LEFT_BAR_FONT_NAME "LeftBarFont"
#define LEFT_BAR_BUTTON_FONT_NAME "LeftBarFontButton"


#define SHORTCUT_BAR_WIDTH "ShortcutBar_Width"
#define WINDOWS_CONFIGURATION "Windows Configuration"

#define DIALOG_FONT_NAME "DialogsFont"

#define DllExport   __declspec( dllexport )

using namespace std;

class DllExport  CDefaultAppFont {
private:
	static CDefaultAppFont instance;
	map<string, CFont*> fonts;
	map<string, UINT> heights;
	CDefaultAppFont();
public:
	virtual ~CDefaultAppFont();
	static CDefaultAppFont* GetInstance();

	CFont* GetFont(string fontName);
	void SetFont(string fontName, CFont* font);

	UINT GetItemHeight(string fontName);
	void SetItemHeight(string fontName, UINT height);

	UINT MakeItemHeight(CFont* pFont);

	void Destroy();

	void RedrawAllWindow();

};
