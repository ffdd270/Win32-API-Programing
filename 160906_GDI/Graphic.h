#ifndef __IMAGE_H__
#define __IMAGE_H__

#include <Windows.h>
#include <gdiplus.h>

using namespace Gdiplus;

#pragma comment(lib, "gdiplus")

enum WhatToSay
{
	Hello_World, WhatTime, GoodMoring,
};

//Stading_CG Ext value
extern HINSTANCE g_hinst;
extern HWND hWndMain;
extern CachedBitmap *pCbit;
extern int WhatSay;

//Grapic Ext Value
extern int EndX;
extern int EndY;

//Funtion

//Stading_CG

//Image
void OnPaint(HDC hdc, int x, int y);
void Update(UINT Whochar, int x, int y); 
void LoadResoucePNG(UINT num, Image ** pimg);
//DeBug
void HowMuchPaint(HDC hdc);
#endif