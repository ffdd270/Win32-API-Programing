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
			MyTextOut(hdc, 100, 100, "���ε༭��, ����׿���! ��-����!");
			MyTextOut(hdc, 100, 120, "�����Ͱ� �ȵ�θ޴ٸ� ����Ű�� �־��!");
			MyTextOut(hdc, 100, 140, "By - �Ƹ��� �Ϸ�ī");
			break;
		case 1:
			MyTextOut(hdc, 100, 100, "���� �Ƹ��� �Ϸ�ī����! ����!");
			MyTextOut(hdc, 100, 120, "Ʈ���̵� ��ũ�� ���� ����!");
			MyTextOut(hdc, 100, 140, "���, �������̰�, ���Ÿ� ���!");
			MyTextOut(hdc, 100, 160, "�Ϸ� �ѹ� �Ѿ�����! ����!");
			MyTextOut(hdc, 100, 180, "By - �Ƹ��� �Ϸ簢ī");
			break;
		case 2:
			MyTextOut(hdc, 100, 100, "���� ������ �ƴϸ� ���� �����ΰ���?");
			MyTextOut(hdc, 100, 120, "���� ȣ���� ��Ű..? ������. ���ε༭��.");
			MyTextOut(hdc, 100, 140, "By - �Ƹ��� �Ϸ篗");
			break;
		default:
			break;
		}
		break;
	case CHIHAYA:
		switch (WhatSay)
		{
		case 0:
			MyTextOut(hdc, 100, 100, "���ε༭��, ���õ� �����Ͻʴϴ�.");
			MyTextOut(hdc, 100, 120, "���α׷����� �ٺ��� ������ ������ �����ǰ���?");
			MyTextOut(hdc, 100, 140, "By - Ű���� ġ�Ͼ�");
			break;
		case 1:
			MyTextOut(hdc, 100, 100, "���ε༭��, Ȥ�� ���� �Ӵϴٸ�.");
			MyTextOut(hdc, 100, 120, "������ ���� ���浢��� �ұ��մϴ�.");
			MyTextOut(hdc, 100, 140, "By - ����-��");
			break;
		case 2:
			MyTextOut(hdc, 100, 100, "ġ��� ������ ���� ����.");
			MyTextOut(hdc, 100, 120, "..�׷��� ü���� ���� ����ϴ�����.");
			MyTextOut(hdc, 100, 140, "By - ����-��");
			break;
		default:
			break;
		}
		break;
	case GOKOU_RURI:
		switch (WhatSay)
		{
		case 0:
			MyTextOut(hdc, 100, 100, "���鼭 ����? ��ó�� ������ ���� ����.");
			MyTextOut(hdc, 100, 120, "���α׷���, ȭ����.");
			MyTextOut(hdc, 100, 140, "By - ���ڿ� �縮");
			break;
		case 1:
			MyTextOut(hdc, 100, 100, "�Ͼ�, ���� �� ��������.");
			MyTextOut(hdc, 100, 120, "���İ�? ��.. �̾�. ���� ���ϰڳ�.");
			MyTextOut(hdc, 100, 140, "By - ���ڿ� �縮");
			break;
		case 2:
			MyTextOut(hdc, 100, 100, "��� ���� ��¥ �̸��� \"��γ���\"��� �Ѵ�.");
			MyTextOut(hdc, 100, 120, "..���� ������ ���ظ԰ڳ�.");
			MyTextOut(hdc, 100, 140, "By - ���ڿ� �縮.");
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


	Memdc = CreateCompatibleDC(hdc); //�޸� DC�� ������� �� �Լ��� �ҷ�������! ������ DC�� ������ �Ÿ𸮿� �����մϴ�.
	//MyBitMap = LoadBitmap(g_hinst, MAKEINTRESOURCE(IDB_BITMAP2)); //�ҷ��´�.. ��Ʈ��.. ������ PAINT �Ҷ����� �ε��ϸ� �������� �ҷ����� ����������̴�.
	//�ν�ź�� �ڵ�/��Ʈ���̸�
	OldBitMap = (HBITMAP)SelectObject(Memdc, MyBitMap); //�����ҷ��� Old�� �ʿ��ؿ�. ����!
	BitBlt(hdc, 0, 0, 720, 405, Memdc, 0, 0, SRCCOPY); //DC���� ��� ���縦 �����մϴ�. �޸� DC�� �ִ� ��Ʈ���� �ε��մϴ�.

	//  ����� DC/��� ��ǥ X,Y/��Ʈ���� ����/�ҷ��� �޸� DC/������� ��ǥ, ������ �ҷ��ñ��?/��� �����?

	//BLACKNESS ������ �Ѱ���
	//DSTINVERT ȭ�� ����!
	//MERGECOPY ȭ�� �̶� ��Ʈ���̶� AND����
	//MERGEPAINT OR����
	//SRCCOPY   �׳� ����
	//WHITENESS  �Ͼ�� �Ѱ���.

	//StretchBlt(HDC hdcDest, int nXOriginDest, int nYOringinDest, int nWidthDest, int nHeightDest, HDC hdcSrc, int nXOringinSrc,....);
	//Bilblt�� �ٸ��� ���������� ũ����� �����Ҽ� ����. ��� Ȯ�� ��Ұ� ������.

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
		MyBitMap = LoadBitmap(g_hinst, MAKEINTRESOURCE(IDB_BITMAP1 + TodayCharter)); //ų������ �ٲ�� ĳ���͵�!
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		BITMAP_DRAW(hdc,MyBitMap);
		hFont = MakeFont(15, 10, HANGEUL_CHARSET, TEXT("�����ٸ����")); //��Ʈ ����.
		//�� 4�� �μ����� ������ ����.
		OldFont = (HFONT)SelectObject(hdc, hFont);
		CHRITER_SAY(hdc, TodayCharter, WhatSay); //���ڿ� ����� �Լ��� �����.
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
