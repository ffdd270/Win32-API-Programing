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
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	switch (iMessage)
	{
	case WM_CREATE:
		//컨트롤도 하나의 윈도우다. 고로 CreateWindow함수를 사용한다.

		//만들고자 하는 윈도우 클래스.Button은 미리 정의 되어있으며, 대소문자 구별하지 않는다. / 제목이다. 제목 필요 없으면 NULL.
		//스타일 : BS_접두어로 시작한다. 자세한건 API 196P. / 위치. /부모 윈도우,/ID, 이걸로 컨트롤을 구별한다./인스턴스의 핸들, g_hinst를 넘기자.
		//일단 무시, NULL.
		CreateWindow(TEXT("Button"), TEXT("눌러보고 싶지?"),WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20,20,200,25,hWnd,(HMENU)0,g_hinst,NULL);
		CreateWindow(TEXT("Button"), TEXT("눌러보고 싶지?"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20, 50, 200, 25, hWnd, (HMENU)1, g_hinst, NULL);
		return 0;
	case WM_COMMAND:
		//부모와의 통신.
		//HIWORD(wParam) = 통지 코드
		//LOWORD(wParam) = 컨트롤의 ID
		//lParma = 메세지를 보낸 차일드 윈도우의 윈도우 핸들.
		switch (LOWORD(wParam))
		{
		case 0:
			MessageBox(hWnd, TEXT("고코우 루리!"), TEXT("버튼"), MB_OK);
			break;
		case 1:
			MessageBox(hWnd, TEXT("아마미 하루카!"), TEXT("역시 버튼"), MB_OK);
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
