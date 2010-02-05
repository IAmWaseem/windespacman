#include "Skeleton.h"

/////////////////////////////////////
// Constructors / Destructors      //
/////////////////////////////////////
CSkeleton::CSkeleton()
{
}

CSkeleton::~CSkeleton()
{
}

void CSkeleton::GameInit()
{
	width = 400;
	height = 300;

	char picfile[] = "res/Penguin.bmp";
	hImage = LoadImage(NULL, picfile, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	char picfile2[] = "res/Penguin2.bmp";
	hImage2 = LoadImage(NULL, picfile2, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	::GetClientRect(m_hWnd, &rect);
	bufDC = CreateCompatibleDC(graphics);
	bufBMP = CreateCompatibleBitmap(graphics, rect.right, rect.bottom);
	SelectObject(bufDC, bufBMP);
	::FillRect(bufDC, &rect, ::CreateSolidBrush(0x00FFFFFF));
}

void CSkeleton::GameLoop(HWND hWnd)
{		
	BITMAP bitmap;
	SIZE imgSize;
	RECT rect;
	if(pinguin == 1)
	{
		GetObject(hImage2, sizeof(BITMAP), &bitmap);
	}
	else
	{
		GetObject(hImage, sizeof(BITMAP), &bitmap);
	}

	imgSize.cx = bitmap.bmWidth;
	imgSize.cy = bitmap.bmHeight;

	HDC hImageDC = CreateCompatibleDC(bufDC);

	::GetClientRect(m_hWnd, &rect);
	FillRect(bufDC, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));
	FillRect(hImageDC, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));

	if(pinguin == 1)
	{
		SelectObject(hImageDC, hImage2);
	}
	else
	{
		SelectObject(hImageDC, hImage);
	}
	BitBlt(bufDC, 300 + positionX, 50 + positionY ,imgSize.cx, imgSize.cy, hImageDC, 0, 0, SRCCOPY);
	ReleaseDC(hWnd, hImageDC);
	DeleteDC(hImageDC);

	BitBlt(graphics, 
		rect.left,rect.top, rect.right, rect.bottom,
		bufDC, 0, 0, SRCCOPY);

	ReleaseDC(hWnd, bufDC);
}

void CSkeleton::GameEnd()
{
}

/////////////////////////////////////
// Member functions                  //
/////////////////////////////////////

LRESULT CSkeleton::MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return CWin::MsgProc(hWnd, uMsg, wParam, lParam);
}

