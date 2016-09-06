#include <Windows.h>
#include <gdiplus.h>
#include <time.h>
#include <stdlib.h>
#include "resource.h"


using namespace Gdiplus;
#pragma comment(lib, "gdiplus")


LRESULT CALLBACK WndProc(HWND hwnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
int BITMAP_DRAW(HDC hdc, HBITMAP MyBitMap);

HINSTANCE g_hinst;
LPCTSTR lpszClass = TEXT("Win32 API");


int APIENTRY WinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hwnd;
	MSG message;
	WNDCLASS WndClass;
	g_hinst = hinstance;

	ULONG_PTR gpToken;
	GdiplusStartupInput gpsi;
	if (GdiplusStartup(&gpToken, &gpsi, NULL) != Ok)
	{
		MessageBox(NULL, TEXT("GDI°¡ Á¿µÈ°Å °°¾Æ¿ä! ÇÁ·Î±×·¡¸Ó´Ô!"), TEXT("²¥¾Æ¾Ç"), MB_OK);
		return 0;
	}

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDC_ICON);
	WndClass.hInstance = hinstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hwnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 740, 440, NULL, (HMENU)NULL, hinstance, NULL);
	ShowWindow(hwnd, nCmdShow);

	while (GetMessage(&message, NULL, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
	GdiplusShutdown(gpToken);
	return (int)message.wParam;
}

void OnPaint(HDC hdc)
{
	Graphics G(hdc);
	Pen P(Color(255, 0, 0, 255), 5);

	G.DrawEllipse(&P, 10, 10, 300, 200);
}

void PrintImege(HDC hdc,int x, int y)
{
	Graphics G(hdc);
	Image i(L"Ani (1).png");
	G.DrawImage(&i,x,y,i.GetWidth()/6,i.GetHeight()/6);
	
}

void MyTextOut(HDC hdc, int x, int y, LPCSTR str)
{
	TextOut(hdc, x, y, str, lstrlen(str));
}


HFONT MakeFont(int Height, int fnWeight, DWORD charset, LPCTSTR fontname)
{
	return CreateFont(Height, 0, 0, 0, 0, 0, 0, 0, charset, 0, 0, 0, 0, fontname);
}



LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static HBITMAP MyBitMap;
	static int TodayCharter;
	static int WhatSay;
	static int x, y;
	HFONT hFont, OldFont;
	switch (iMessage)
	{
	case WM_CREATE:
		srand((int)time(NULL));
		SetTimer(hWnd, 1, 100, NULL);
		WhatSay = rand() % 3;
		TodayCharter = rand() % 3;
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		hFont = MakeFont(15, 10, HANGEUL_CHARSET, TEXT("³ª´®°íµñ")); //ÆùÆ® ¼³Á¤.
		PrintImege(hdc, x, y);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_TIMER:
		x++;
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_DESTROY:
		DeleteObject(MyBitMap);
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);


}
