#include <Windows.h>
#include <time.h>
#include "Graphic.h"



LRESULT CALLBACK WndProc(HWND hwnd, UINT iMessage, WPARAM wParam, LPARAM lParam);


HINSTANCE g_hinst;
CachedBitmap *pCbit;
HWND hWndMain;
int WhatSay;

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




void PrintImege(HDC hdc,int x, int y) //파일로 직접 로드
{
	Graphics G(hdc);
	Image i(L"Ani (1).png");
	G.DrawImage(&i,x,y,i.GetWidth()/6,i.GetHeight()/6);
}



LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static int x = 100, y = 100;
	static int MouseX, MouseY;				
	int MidX, MidY;
	int MovementX, MovementY;
	static int i = 6;
	static bool IsItHold = false;

	hWndMain = hWnd;
	switch (iMessage)
	{
	case WM_CREATE:
		srand((int)time(NULL));
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		OnPaint(hdc, x, y);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_MOUSEMOVE:
		if (IsItHold)
		{
			if (MouseX > x && MouseY > y && MouseX < EndX && MouseY < EndY)
			{
				MidX = MouseX; MidY = MouseY;
				x = (MidX * 2) - EndX; y = (MidY * 2) - EndY;
				Update(WhatSay, x, y);
			}		

			MouseX = LOWORD(lParam); MouseY = HIWORD(lParam);
		}
		return 0;
	case WM_CHAR:
		switch ((TCHAR)wParam)
		{
		case 'n':
			if (WhatSay < WhatToSay::GoodMoring)
			{
				WhatSay++;
				Update(WhatSay, x, y);
			}
			else
			{
				WhatSay = WhatToSay::Hello_World;
				Update(WhatSay, x, y);
			}
			return 0;
		case 'b':
			if (WhatSay > 0)
			{
				WhatSay--;
				Update(WhatSay, x, y);
			}
			else
			{
				Update(WhatSay, x, y);
			}
			return 0;
		default:
			break;
		}
	case WM_LBUTTONUP:
		IsItHold = false;
		return 0;
	case WM_LBUTTONDOWN:
		MouseX = LOWORD(lParam); MouseY = HIWORD(lParam);
		IsItHold = true;
		return 0;
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
