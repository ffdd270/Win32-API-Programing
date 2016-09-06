#ifndef __IMAGE_H__
#define __IMAGE_H__

#include <Windows.h>
#include <gdiplus.h>
using namespace Gdiplus;

#pragma comment(lib, "gdiplus")

extern HINSTANCE g_hinst;
extern HWND hWndMain;
extern CachedBitmap *pCbit;
void OnPaint(HDC hdc, UINT WhoChar, int x, int y);
void Update(UINT Whochar, int x, int y); 
void LoadResoucePNG(UINT num, Image ** pimg);

#endif