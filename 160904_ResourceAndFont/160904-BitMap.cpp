#include <Windows.h>
#include "resource.h"

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

void TEXT_PRINT(HDC hdc)
{
	MyTextOut(hdc, 100, 100, "���鼭 ����? ��ó�� ������ ���� ����.");
	MyTextOut(hdc, 100, 120, "���α׷���, ȭ����.");
	MyTextOut(hdc, 100, 140, "By - ���ڿ� �縮");
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
	BitBlt(hdc, 0, 0, 720, 405,Memdc,0,0, SRCCOPY); //DC���� ��� ���縦 �����մϴ�. �޸� DC�� �ִ� ��Ʈ���� �ε��մϴ�.

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
	HFONT hFont, OldFont;
	switch (iMessage)
	{
	case WM_CREATE:
		MyBitMap = LoadBitmap(g_hinst, MAKEINTRESOURCE(IDB_BITMAP2));
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		BITMAP_DRAW(hdc,MyBitMap);
		hFont = MakeFont(15, 10, HANGEUL_CHARSET, TEXT("�������")); //��Ʈ ����.
		//�� 4�� �μ����� ������ ����.
		OldFont = (HFONT)SelectObject(hdc, hFont);
		TEXT_PRINT(hdc); //���ڿ� ����� �Լ��� �����.
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
