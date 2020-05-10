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
#define DIALOG_BACKGROUNT_COLOR_NAME "DialogBackgroundColor"

#define DllExport   __declspec( dllexport )

using namespace std;

class DllExport  CDefaultAppFont {
private:
	static CDefaultAppFont instance;
	map<string, CFont*> fonts;
	map<string, UINT> heights;
	map<string, HBRUSH> colors;
	CDefaultAppFont();
	void DestroyObjects();
public:
	virtual ~CDefaultAppFont();
	static CDefaultAppFont* GetInstance();

	CFont* GetFont(string fontName);
	void SetFont(string fontName, CFont* font);
	void SetFont(string fontName, LOGFONT & font);

	UINT GetItemHeight(string fontName);
	void SetItemHeight(string fontName, UINT height);	
	/// <summary>
	/// Gets the HBRUSH color.
	/// </summary>
	/// <param name="colorName">Name of the color.</param>
	/// <param name="defaultColor">The default color.</param>
	/// <returns>HBRUSH instanse. do not use DeleteObject for this instance</returns>
	HBRUSH GetColor(string colorName, COLORREF defaultColor);	
	/// <summary>
	/// Sets the color.
	/// </summary>
	/// <param name="colorName">Name of the color.</param>
	/// <param name="color">The color.</param>
	/// <returns>HBRUSH instanse. do not use DeleteObject for this instance</returns>
	HBRUSH SetColor(string colorName, COLORREF color);	
	/// <summary>
	/// Set default color
	/// </summary>
	/// <param name="colorName">Name of the color.</param>
	void SetColor(string colorName);	
	/// <summary>
	/// Makes the height of the item by font.
	/// </summary>
	/// <param name="pFont">The p font.</param>
	/// <returns></returns>
	UINT MakeItemHeight(CFont* pFont);
	

	void RedrawAllWindow();	
	/// <summary>
	/// Gets the color of the brush.
	/// </summary>
	/// <param name="brush">The brush.</param>
	/// <returns></returns>
	COLORREF GetBrushColor(HBRUSH brush);
};
