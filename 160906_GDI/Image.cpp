#include "Image.h"
#include "resource.h"


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

void Update(UINT Whochar, int x, int y)
{
	Graphics G(hWndMain);
	RECT crt;
	Image * pImage = NULL;
	GetClientRect(hWndMain, &crt);

	Bitmap *pBit = new Bitmap(crt.right, crt.bottom, &G);
	Graphics *memG = new Graphics(pBit);
	memG->FillRectangle(&SolidBrush(Color(255, 255, 255)), 0, 0, crt.right, crt.bottom);

	//리소스 로드.
	LoadResoucePNG(Whochar, &pImage);
	//로드 끝.

	if (pImage->GetLastStatus() != Ok)
		return;
	//끝
	memG->DrawImage(pImage, x, y, pImage->GetWidth() / 8, pImage->GetHeight() / 8);

	pCbit = new CachedBitmap(pBit, &G);
	delete pBit;
	delete memG;
	InvalidateRect(hWndMain, NULL, FALSE);
}

void OnPaint(HDC hdc, UINT Who, int x, int y)
{
	Graphics G(hdc);

	if (pCbit == NULL)
	{
		Update(Who,x,y);
	}

	G.DrawCachedBitmap(pCbit, 0, 0);
}