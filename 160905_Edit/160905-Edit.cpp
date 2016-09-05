#include <Windows.h>

//16-09-05 HSH 오전 1:29분 작업시작
//락ㅇ으으음악 들으면서 하는중.
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
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

	hwnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 720, 405, NULL, (HMENU)NULL, hinstance, NULL);
	ShowWindow(hwnd, nCmdShow);

	while (GetMessage(&message, NULL, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	return (int)message.wParam;
}

#define ID_EDIT 100

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	static HWND hEdit;
	TCHAR string[40][128];
	TCHAR buf[128];
	PAINTSTRUCT ps;
	switch (iMessage)
	{
	case WM_CREATE:
		hEdit = CreateWindow(TEXT("Edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_MULTILINE, 10, 10
			, 400, 100, hWnd, (HMENU)ID_EDIT, g_hinst, NULL);
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_EDIT:
			switch (HIWORD(wParam))
			{
			case EN_CHANGE:
				GetWindowText(hEdit, buf, 128);
			}
		}
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);


}
