#include "Skeleton.h"
#include "Bitmap.h"
#include "Messages.h"
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
		messageQueue->Inst()->attach(character->Instance());
		messageQueue->Inst()->attach(renderer->Inst());
		break;
	}
	return CWin::MsgProc(hWnd, uMsg, wParam, lParam);
}

void CSkeleton::GameInit()
{
	bitmap.LoadDIBFile("res/Summer2.bmp");
	messageQueue->Inst()->sendMessage(CM_LEVEL_START, NULL, NULL);

	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = 800;
	rect.bottom = 600;
	
	
	SYSTEMTIME systemTime;
	GetSystemTime( &systemTime );

	FILETIME fileTime;
	SystemTimeToFileTime( &systemTime, &fileTime );

	ULARGE_INTEGER uli;
	uli.LowPart = fileTime.dwLowDateTime;
	uli.HighPart = fileTime.dwHighDateTime;

	ULONGLONG systemTimeIn_ms( uli.QuadPart/10000 );
	previousUpdateTime = systemTimeIn_ms;
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

	graphics = ::GetDC(m_hWnd);
	bufDC = CreateCompatibleDC(graphics);
	HBITMAP bufBMP;
	bufBMP = CreateCompatibleBitmap(graphics, 800, 600);
	SelectObject(bufDC, bufBMP);	
	//::FillRect(bufDC, &placeRect, ::CreateSolidBrush(0x00FFFFFF));
	::FillRect(bufDC, &placeRect, ::CreateSolidBrush(RGB(171, 207, 236)));
	renderer->Inst()->render(bufDC, m_hWnd);
	BitBlt(graphics, 0, 0, 800, 600, bufDC, 0, 0, SRCCOPY);
	DeleteDC(bufDC);
	DeleteDC(graphics);
}

void CSkeleton::Update()
{
	SYSTEMTIME systemTime;
	GetSystemTime( &systemTime );

	FILETIME fileTime;
	SystemTimeToFileTime( &systemTime, &fileTime );

	ULARGE_INTEGER uli;
	uli.LowPart = fileTime.dwLowDateTime;
	uli.HighPart = fileTime.dwHighDateTime;

	ULONGLONG systemTimeIn_ms( uli.QuadPart/10000 );
	int elapsedTime = systemTimeIn_ms - previousUpdateTime;

	messageQueue->Inst()->sendMessage(CM_UPDATE, elapsedTime, NULL);
	previousUpdateTime = systemTimeIn_ms;
}