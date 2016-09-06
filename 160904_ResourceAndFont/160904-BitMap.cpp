#include <Windows.h>
#include <time.h>
#include <stdlib.h>
#include "resource.h"

#define AMAMI_HARUKA 0
#define CHIHAYA 1
#define GOKOU_RURI 2



LRESULT CALLBACK WndProc(HWND hwnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
int BITMAP_DRAW(HDC hdc,HBITMAP MyBitMap);

HINSTANCE g_hinst;
LPCTSTR lpszClass = TEXT("Win32 API");


int APIENTRY WinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hwnd;
	MSG message;
	WNDCLASS WndClass;
	g_hinst = hinstance;

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

	return (int)message.wParam;
}

void MyTextOut(HDC hdc, int x, int y, LPCSTR str)
{
	TextOut(hdc, x, y, str, lstrlen(str));
}

void CHRITER_SAY(HDC hdc, int WHOIS, int WhatSay)
{
	switch (WHOIS)
	{
	case AMAMI_HARUKA:
		switch (WhatSay)
		{
		case 0:
			MyTextOut(hdc, 100, 100, "ÇÁ·Îµà¼­¾¾, µð¹ö±×¿¡¿ä! µð-¹ö±×!");
			MyTextOut(hdc, 100, 120, "Æ÷ÀÎÅÍ°¡ ¾Èµå·Î¸Þ´Ù¸¦ °¡¸£Å°°í ÀÖ¾î¿ä!");
			MyTextOut(hdc, 100, 140, "By - ¾Æ¸¶¹Ì ÇÏ·çÄ«");
			break;
		case 1:
			MyTextOut(hdc, 100, 100, "Àú´Â ¾Æ¸¶¹Ì ÇÏ·çÄ«¿¡¿ä! ¿¹ÀÌ!");
			MyTextOut(hdc, 100, 120, "Æ®·¹ÀÌµå ¸¶Å©´Â »¡°£ ¸®º»!");
			MyTextOut(hdc, 100, 140, "¹à°í, ±àÁ¤ÀûÀÌ°í, ¿ø°Å¸® Åë±Ù!");
			MyTextOut(hdc, 100, 160, "ÇÏ·ç ÇÑ¹ø ³Ñ¾îÁ®¿ä! ¿¹ÀÌ!");
			MyTextOut(hdc, 100, 180, "By - ¾Æ¸¶¹Ì ÇÏ·ç°¢Ä«");
			break;
		case 2:
			MyTextOut(hdc, 100, 100, "Á¦°¡ ¸®´õ°¡ ¾Æ´Ï¸é ´©°¡ ¸®´õÀÎ°¡¿ä?");
			MyTextOut(hdc, 100, 120, "¼³¸¶ È£½ÃÀÌ ¹ÌÅ°..? ¼³¸¶¿ä. ÇÁ·Îµà¼­¾¾.");
			MyTextOut(hdc, 100, 140, "By - ¾Æ¸¶¹Ì ÇÏ·ç¯—");
			break;
		default:
			break;
		}
		break;
	case CHIHAYA:
		switch (WhatSay)
		{
		case 0:
			MyTextOut(hdc, 100, 100, "ÇÁ·Îµà¼­¾¾, ¿À´Ãµµ ¼ö°íÇÏ½Ê´Ï´Ù.");
			MyTextOut(hdc, 100, 120, "ÇÁ·Î±×·¡¹ÖÀÌ ¹Ùºüµµ ·¹½¼Àº »©¸ÔÁö ¾ÊÀ¸½Ç°ÅÁÒ?");
			MyTextOut(hdc, 100, 140, "By - Å°»ç¶ó±â Ä¡ÇÏ¾ß");
			break;
		case 1:
			MyTextOut(hdc, 100, 100, "ÇÁ·Îµà¼­¾¾, È¤½Ã ¸»ÇØ µÓ´Ï´Ù¸¸.");
			MyTextOut(hdc, 100, 120, "°¡½¿Àº ±×Àú Áö¹æµ¢¾î¸®¿¡ ºÒ±¸ÇÕ´Ï´Ù.");
			MyTextOut(hdc, 100, 140, "By - ³³ÀÛ-Äô");
			break;
		case 2:
			MyTextOut(hdc, 100, 100, "Ä¡Çá´Â ¿ìÀ¯¸¦ ¸¹ÀÌ ¸ÔÁÒ.");
			MyTextOut(hdc, 100, 120, "..±×·¡µµ Ã¼ÇüÀº Àú¶û ºñ½ÁÇÏ´õ¶ó°í¿ä.");
			MyTextOut(hdc, 100, 140, "By - ³³ÀÛ-Äô");
			break;
		default:
			break;
		}
		break;
	case GOKOU_RURI:
		switch (WhatSay)
		{
		case 0:
			MyTextOut(hdc, 100, 100, "½¬¸é¼­ ÇÏÁö? ³ªÃ³·³ ¿µ¿øÈ÷ ½¬Áø ¸»°í.");
			MyTextOut(hdc, 100, 120, "ÇÁ·Î±×·¡¹Ö, È­ÀÌÆÃ.");
			MyTextOut(hdc, 100, 140, "By - °íÄÚ¿ì ·ç¸®");
			break;
		case 1:
			MyTextOut(hdc, 100, 100, "ÇÏ¾Æ, ¿¾³¯ ÀÏ »ý°¢³ª³×.");
			MyTextOut(hdc, 100, 120, "¹¹³Ä°í? ¾î.. ¹Ì¾È. ¸»À» ¸øÇÏ°Ú³×.");
			MyTextOut(hdc, 100, 140, "By - °íÄÚ¿ì ·ç¸®");
			break;
		case 2:
			MyTextOut(hdc, 100, 100, "»ç½Ç ³ªÀÇ ÁøÂ¥ ÀÌ¸§Àº \"Äí·Î³×ÄÚ\"¶ó°í ÇÑ´Ù.");
			MyTextOut(hdc, 100, 120, "..¿ª½Ã Áö±ÝÀº ¸øÇØ¸Ô°Ú³×.");
			MyTextOut(hdc, 100, 140, "By - °íÄÚ¿ì ·ç¸®.");
			break;
		default:
			break;
		}
		break;
	}
}

HFONT MakeFont(int Height, int fnWeight, DWORD charset, LPCTSTR fontname)
{
	return CreateFont(Height, 0, 0, 0, 0, 0, 0, 0, charset, 0, 0, 0, 0, fontname);
}

int BITMAP_DRAW(HDC hdc, HBITMAP MyBitMap)
{
	HDC Memdc;
	PAINTSTRUCT ps;
	HBITMAP OldBitMap;                                          


	Memdc = CreateCompatibleDC(hdc); //¸Þ¸ð¸® DC¸¦ ¸¸µé·Á¸é ÀÌ ÇÔ¼ö¸¦ ºÒ·¯¿À¼¼¿³! µ¿ÀÏÇÑ DC¸¦ º¹»çÇØ ¸Å¸ð¸®¿¡ ÀúÀåÇÕ´Ï´Ù.
	//MyBitMap = LoadBitmap(g_hinst, MAKEINTRESOURCE(IDB_BITMAP2)); //ºÒ·¯¿Â´Ù.. ºñÆ®¸Ê.. ÇÏÁö¸¸ PAINT ÇÒ¶§¸¶´Ù ·ÎµåÇÏ¸é ÆÀÀåÇÑÅ× ºÒ·Á°¡¼­ ¸è»ìÀâÈú°ÍÀÌ´Ù.
	//ÀÎ½ºÅº½º ÇÚµé/ºñÆ®¸ÊÀÌ¸§
	OldBitMap = (HBITMAP)SelectObject(Memdc, MyBitMap); //»èÁ¦ÇÒ·Á¸é Old°¡ ÇÊ¿äÇØ¿ä. ¼¿·º!
	BitBlt(hdc, 0, 0, 720, 405, Memdc, 0, 0, SRCCOPY); //DC°£ÀÇ °í¼Ó º¹»ç¸¦ ¼öÇàÇÕ´Ï´Ù. ¸Þ¸ð¸® DC¿¡ ÀÖ´Â ºñÆ®¸ÊÀ» ·ÎµåÇÕ´Ï´Ù.

	//  Ãâ·ÂÇÒ DC/¶ç¿ï ÁÂÇ¥ X,Y/ºñÆ®¸ÊÀÇ ³ÐÀÌ/ºÒ·¯¿Ã ¸Þ¸ð¸® DC/º¹»ç¿øÀÇ ÁÂÇ¥, ¾îµðºÎÅÍ ºÒ·¯¿Ã±î¿ä?/¾î¶»°Ô ¶ç¿ï±î¿ä?

	//BLACKNESS °ËÀº»ö ÇÑ°¡µæ
	//DSTINVERT È­¸é ¹ÝÀü!
	//MERGECOPY È­¸é ÀÌ¶û ºñÆ®¸ÊÀÌ¶û AND¿¬»ê
	//MERGEPAINT OR¿¬»ê
	//SRCCOPY   ±×³É º¹»ç
	//WHITENESS  ÇÏ¾á»ö ÇÑ°¡µæ.

	//StretchBlt(HDC hdcDest, int nXOriginDest, int nYOringinDest, int nWidthDest, int nHeightDest, HDC hdcSrc, int nXOringinSrc,....);
	//Bilblt¿Í ´Ù¸£°Ô ¿øº»ÆÄÀÏÀÇ Å©±â±îÁö ÁöÁ¤ÇÒ¼ö ÀÖÀ½. °í·Î È®´ë Ãà¼Ò°¡ °¡´ÉÇÔ.

	SelectObject(Memdc,OldBitMap);
	DeleteDC(Memdc);
	return 0;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static HBITMAP MyBitMap;
	static int TodayCharter;
	static int WhatSay;
	HFONT hFont, OldFont;
	switch (iMessage)
	{
	case WM_CREATE:
		srand((int)time(NULL));
		WhatSay = rand() % 3;
		TodayCharter = rand() % 3;
		MyBitMap = LoadBitmap(g_hinst, MAKEINTRESOURCE(IDB_BITMAP1 + TodayCharter)); //Å³¶§¸¶´Ù ¹Ù²î´Â Ä³¸¯ÅÍµé!
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		BITMAP_DRAW(hdc,MyBitMap);
		hFont = MakeFont(15, 10, HANGEUL_CHARSET, TEXT("³ª´®¹Ù¸¥°íµñ")); //ÆùÆ® ¼³Á¤.
		//ÀÌ 4°³ ÀÎ¼ö»©°ï º°º¼ÀÏ ¾ø´Ù.
		OldFont = (HFONT)SelectObject(hdc, hFont);
		CHRITER_SAY(hdc, TodayCharter, WhatSay); //¹®ÀÚ¿­ Ãâ·ÂÀ» ÇÔ¼ö·Î ¹­¾î³ð.
		SelectObject(hdc, OldFont);
		DeleteObject(hFont);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		DeleteObject(MyBitMap);
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);


}
