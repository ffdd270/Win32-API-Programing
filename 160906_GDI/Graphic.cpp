#include "Graphic.h"
#include "resource.h"

int EndX; //�̹��� ������ ����.
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

	hFont = MakeFont(15, 10, HANGEUL_CHARSET, TEXT("�����ٸ����")); //��Ʈ ����.
	OldFont = (HFONT)SelectObject(hdc, hFont);

	switch (WhatSay)
	{
	case Hello_World:
		MyTextOut(hdc, x + Sayx, y + Sayy, TEXT("Hello, World!"));
		break;
	case WhatTime:
		wsprintf(nowTime,"���� �ð��� %d : %d�Դϴ�.",now.wHour,now.wMinute);
		MyTextOut(hdc, x + Sayx, y + Sayy, nowTime);
		break;
	case GoodMoring:
		if (now.wHour < 10)
		{
			MyTextOut(hdc, x + Sayx, y + Sayy, TEXT("�� ���!"));
		}
		else
		{
			MyTextOut(hdc, x + Sayx, y + Sayy, TEXT("��ħ�ΰ���? ��ǻ�� �ȿ��� �־ ��.."));
		}
		break;
	default:
		break;
	}

	SelectObject(hdc, OldFont);
	DeleteObject(hFont);
}

void Update(UINT Whochar, int x, int y)
{
	Graphics G(hWndMain);
	RECT crt;
	Image * pImage = NULL;
	GetClientRect(hWndMain, &crt);

	if (pCbit != NULL)
	{
		delete pCbit;
	}

	Bitmap *pBit = new Bitmap(crt.right, crt.bottom, &G);
	Graphics *memG = new Graphics(pBit);
	memG->FillRectangle(&SolidBrush(Color(255, 255, 255)), 0, 0, crt.right, crt.bottom);

	//���ҽ� �ε�.
	LoadResoucePNG(Whochar, &pImage);
	//�ε� ��.

	if (pImage->GetLastStatus() != Ok)
		return;

	memG->DrawImage(pImage, x, y, pImage->GetWidth() / 8, pImage->GetHeight() / 8);

	//���̿� ������ ��� ��ǥ�� �����ָ� �����̰���?
	EndX = pImage->GetWidth() / 8 + x;
	EndY = pImage->GetHeight() / 8 + y; 

	pCbit = new CachedBitmap(pBit, &G);

	delete pImage;
	delete pBit;
	delete memG;

	InvalidateRect(hWndMain, NULL, FALSE);
}

void OnPaint(HDC hdc, int x, int y)
{
	Graphics G(hdc);

	if (pCbit == NULL)
	{
		Update(WhatSay,x,y);
	}

	G.DrawCachedBitmap(pCbit, 0, 0);
	Say(hdc,x,y);
}