#include <Windows.h>
#include <gdiplus.h>
#include <time.h>
#include "resource.h"
#include "Image.h"

enum WhatToSay
{
	Hello_World, WhatTime, GoodMoring,
};

using namespace Gdiplus;

#pragma comment(lib, "gdiplus")


LRESULT CALLBACK WndProc(HWND hwnd, UINT iMessage, WPARAM wParam, LPARAM lParam);


HINSTANCE g_hinst;
CachedBitmap *pCbit;
HWND hWndMain;

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
		MessageBox(NULL, TEXT("GDI가 좆된거 같아요! 프로그래머님!"), TEXT("꺄아악"), MB_OK);
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

void MyTextOut(HDC hdc, int x, int y, LPCSTR str)
{
	TextOut(hdc, x, y, str, lstrlen(str));
}


int Say(HDC hdc, int Chx, int Chy, UINT WhatSay)
{
	const int Sayx = 50, Sayy = -30;
	SYSTEMTIME now;
	TCHAR nowTime[100];

	GetLocalTime(&now);
	switch (WhatSay)
	{
	case Hello_World:
		MyTextOut(hdc, Chx + Sayx, Chy + Sayy, TEXT("오우, 헬로우 월드."));
		return 2;
		break;
	case WhatTime:
		wsprintf(nowTime, "현재 시간은 %d : %d 입니다!", now.wHour, now.wMinute);
		MyTextOut(hdc, Chx + Sayx, Chy + Sayy, nowTime);
		return 7;
	case GoodMoring:
		if (now.wHour < 10)
		{
			MyTextOut(hdc, Chx + Sayx, Chy + Sayy, TEXT("좋은 아침입니다!"));
			return 5;
		}
		else
		{
			MyTextOut(hdc, Chx + Sayx, Chy + Sayy, TEXT("아침이라고 하긴 조금.."));
			return 1;
		}
		break;
	default:
		break;
	}
	return -1;
}

void PrintImege(HDC hdc,int x, int y) //파일로 직접 로드
{
	Graphics G(hdc);
	Image i(L"Ani (1).png");
	G.DrawImage(&i,x,y,i.GetWidth()/6,i.GetHeight()/6);
}


HFONT MakeFont(int Height, int fnWeight, DWORD charset, LPCTSTR fontname)
{
	return CreateFont(Height, 0, 0, 0, 0, 0, 0, 0, charset, 0, 0, 0, 0, fontname);
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static int x = 100, y = 100;
	static int i;
	static int WhatSay;
	HFONT hFont, OldFont;
	hWndMain = hWnd;
	switch (iMessage)
	{
	case WM_CREATE:
		srand((int)time(NULL));
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		hFont = MakeFont(15, 10, HANGEUL_CHARSET, TEXT("나눔바른고딕")); //폰트 설정.
		OldFont = (HFONT)SelectObject(hdc, hFont);
		OnPaint(hdc,i,x,y);
		i = Say(hdc, x, y, WhatSay);
		SelectObject(hdc, OldFont);
		DeleteObject(hFont);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_LBUTTONDOWN:
		if (WhatSay < WhatToSay::GoodMoring)
		{
			Update(i, x, y);
			WhatSay++;
		}
		else
		{
			Update(i, x, y);
			WhatSay = WhatToSay::Hello_World;
		}
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_DESTROY:
		if (pCbit)
		{
			delete pCbit;
		}
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);


}
