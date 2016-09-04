#include <Windows.h>

//16-09-05 HSH ���� 1:29�� �۾�����
//������������ �����鼭 �ϴ���.
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
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	switch (iMessage)
	{
	case WM_CREATE:
		//��Ʈ�ѵ� �ϳ��� �������. ��� CreateWindow�Լ��� ����Ѵ�.

		//������� �ϴ� ������ Ŭ����.Button�� �̸� ���� �Ǿ�������, ��ҹ��� �������� �ʴ´�. / �����̴�. ���� �ʿ� ������ NULL.
		//��Ÿ�� : BS_���ξ�� �����Ѵ�. �ڼ��Ѱ� API 196P. / ��ġ. /�θ� ������,/ID, �̰ɷ� ��Ʈ���� �����Ѵ�./�ν��Ͻ��� �ڵ�, g_hinst�� �ѱ���.
		//�ϴ� ����, NULL.
		CreateWindow(TEXT("Button"), TEXT("�������� ����?"),WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20,20,200,25,hWnd,(HMENU)0,g_hinst,NULL);
		CreateWindow(TEXT("Button"), TEXT("�������� ����?"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20, 50, 200, 25, hWnd, (HMENU)1, g_hinst, NULL);
		return 0;
	case WM_COMMAND:
		//�θ���� ���.
		//HIWORD(wParam) = ���� �ڵ�
		//LOWORD(wParam) = ��Ʈ���� ID
		//lParma = �޼����� ���� ���ϵ� �������� ������ �ڵ�.
		switch (LOWORD(wParam))
		{
		case 0:
			MessageBox(hWnd, TEXT("���ڿ� �縮!"), TEXT("��ư"), MB_OK);
			break;
		case 1:
			MessageBox(hWnd, TEXT("�Ƹ��� �Ϸ�ī!"), TEXT("���� ��ư"), MB_OK);
		default:
			break;
		}
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);


}
