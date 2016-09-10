#include "Graphic.h"
#include "resource.h"

int EndX; //이미지 파일의 끝점.
int EndY;

void LoadResoucePNG(UINT num, Image ** pimg)
{
	HRSRC hResource = FindResource(g_hinst, MAKEINTRESOURCE(IDB_PNG1 + num), TEXT("PNG"));

	if (!hResource)
		return;
	DWORD imageSize = SizeofResource(g_hinst, hResource);
	HGLOBAL hGlobal = LoadResource(g_hinst, hResource);
	LPVOID pData = LockResource(hGlobal);

	HGLOBAL hBuffer = GlobalAlloc(GMEM_MOVEABLE, imageSize);
	LPVOID pBuffer = GlobalLock(hBuffer);
	CopyMemory(pBuffer, pData, imageSize);
	GlobalUnlock(hBuffer);

	IStream * pStream;
	HRESULT hr = CreateStreamOnHGlobal(hBuffer, TRUE, &pStream);
	*pimg = new Image(pStream);
	pStream->Release();
}

void MyTextOut(HDC hdc, int x, int y, LPCSTR str)
{
	TextOut(hdc, x, y, str, lstrlen(str));
}

HFONT MakeFont(int Height, int fnWeight, DWORD charset, LPCTSTR fontname)
{
	return CreateFont(Height, 0, 0, 0, 0, 0, 0, 0, charset, 0, 0, 0, 0, fontname);
}


//This Funtion Get Mouse XY
void NowMouseXY(HDC hdc, int x, int y) //Only For Debug.
{
	char buf[100];
	wsprintf(buf, "%d, %d", x, y);

	MyTextOut(hdc, 500, 300, buf);
}

//This Funtion Work For Chariter Say.
void Say(HDC hdc, int x, int y)
{
	const int Sayx = 50, Sayy = -30;
	SYSTEMTIME now;
	TCHAR nowTime[100];
	HFONT hFont, OldFont;

	GetLocalTime(&now);

	hFont = MakeFont(15, 10, HANGEUL_CHARSET, TEXT("나눔바른고딕")); //폰트 설정.
	OldFont = (HFONT)SelectObject(hdc, hFont);

	switch (WhatSay)
	{
	case Hello_World:
		MyTextOut(hdc, x + Sayx, y + Sayy, TEXT("Hello, World!"));
		break;
	case WhatTime:
		wsprintf(nowTime,"현재 시간은 %d : %d입니다.",now.wHour,now.wMinute);
		MyTextOut(hdc, x + Sayx, y + Sayy, nowTime);
		break;
	case GoodMoring:
		if (now.wHour < 10)
		{
			MyTextOut(hdc, x + Sayx, y + Sayy, TEXT("굿 모닝!"));
		}
		else
		{
			MyTextOut(hdc, x + Sayx, y + Sayy, TEXT("아침인가요? 컴퓨터 안에만 있어서 잘.."));
		}
		break;
	default:
		break;
	}

	SelectObject(hdc, OldFont);
	DeleteObject(hFont);
}

//For Debug
void HowMuchPaint(HDC hdc)
{
	char Temp[100];
	static int PaintTry = 0;

	wsprintf(Temp, "지금까지 페인트된 횟수 : %d", PaintTry);

	MyTextOut(hdc, 600, 600, Temp);
	PaintTry++;
}



void Update(UINT Whochar, int x, int y)
{
	Graphics G(hWndMain);
	RECT crt;
	static Image * pImage = NULL;
	static int OldChar = -1;
	GetClientRect(hWndMain, &crt);
	Bitmap *pBit = new Bitmap(crt.right, crt.bottom, &G);
	Graphics *memG = new Graphics(pBit);

	memG->FillRectangle(&SolidBrush(Color(255, 255, 255)), 0, 0, crt.right, crt.bottom);

	if (pCbit != NULL) //메모리 누수의 원인. 계속 딜리트를  시켜야한다.
	{
		delete pCbit;
	}

	//리소스 로드.
	if (OldChar != Whochar)
	{
		delete pImage;
		LoadResoucePNG(Whochar, &pImage);
	}

	//로드 끝.

	if (pImage->GetLastStatus() != Ok)
		return;

	memG->DrawImage(pImage, x, y, pImage->GetWidth() / 8, pImage->GetHeight() / 8);

	//넓이와 높이의 출력 좌표를 더해주면 끝점이겠지?
	EndX = pImage->GetWidth() / 8 + x;
	EndY = pImage->GetHeight() / 8 + y; 

	pCbit = new CachedBitmap(pBit, &G);

	OldChar = Whochar;

	delete pBit;
	delete memG;

	InvalidateRect(hWndMain, NULL, FALSE);
	SendMessage(hWndMain, WM_PAINT, NULL, NULL); //WM_PAINT와 WM_MOUSEMOVE중 우선순위 더 높은건 WM_MOUSEMOVE! 
}


void OnPaint(HDC hdc, int x, int y)
{
	Graphics G(hdc);

	if (pCbit == NULL)
	{
		Update(WhatSay, x, y);
	}
	G.DrawCachedBitmap(pCbit, 0, 0);
	HowMuchPaint(hdc);
	Say(hdc,x,y);
}
