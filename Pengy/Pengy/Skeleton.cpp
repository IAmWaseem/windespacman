#include "Skeleton.h"
#include "Bitmap.h"
using namespace dotnetguy;

/////////////////////////////////////
// Constructors / Destructors      //
/////////////////////////////////////
CSkeleton::CSkeleton()
{
	
}

CSkeleton::~CSkeleton()
{
}

/////////////////////////////////////
// Member functions                  //
/////////////////////////////////////

LRESULT CSkeleton::MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) 
	{
	case WM_CREATE:
		messageQueue->Inst()->attach(level->Inst());
		break;
	case WM_KEYDOWN:
		messageQueue->Inst()->sendMessage(CM_KEY);
		break;
	}
	return CWin::MsgProc(hWnd, uMsg, wParam, lParam);
}

void CSkeleton::GameInit()
{
	bitmap.LoadDIBFile("res/Summer2.bmp");
}

void CSkeleton::GameLoop(HWND hWnd)
{
	Update();
	Render(hWnd);
}

void CSkeleton::GameEnd()
{

}

void CSkeleton::Render(HWND hWnd)
{
	RECT placeRect;
	placeRect.left = 0;
	placeRect.top = 0;
	placeRect.right = 800;
	placeRect.bottom = 600;	

	HDC graphics = ::GetDC(m_hWnd);
	HDC bufDC = CreateCompatibleDC(graphics);
	HBITMAP bufBMP;
	bufBMP = CreateCompatibleBitmap(graphics, 800, 600);
	SelectObject(bufDC, bufBMP);
	::FillRect(bufDC, &placeRect, ::CreateSolidBrush(0x00FFFFFF));
	renderer->Inst()->render(bufDC);
	BitBlt(graphics, 0, 0, 800, 600, bufDC, 0, 0, SRCCOPY);
	ReleaseDC(hWnd, bufDC);
	DeleteDC(bufDC);
	ReleaseDC(hWnd, graphics);
	DeleteDC(graphics);
}

void CSkeleton::Update()
{
	
}