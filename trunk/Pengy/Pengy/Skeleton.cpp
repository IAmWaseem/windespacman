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
	graphics = ::GetDC(m_hWnd);
	bufDC = CreateCompatibleDC(graphics);
	HBITMAP bufBMP;
	bufBMP = CreateCompatibleBitmap(graphics, 800, 600);
	SelectObject(bufDC, bufBMP);
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
	
	::FillRect(bufDC, &placeRect, ::CreateSolidBrush(0x00FFFFFF));
	renderer->Inst()->render(bufDC, m_hWnd);
	BitBlt(graphics, 0, 0, 800, 600, bufDC, 0, 0, SRCCOPY);
	
	ReleaseDC(hWnd, bufDC);
}

void CSkeleton::Update()
{
	Character::Instance()->SetLocationX(Character::Instance()->GetLocationX() + 1);
	Character::Instance()->SetLocationY(Character::Instance()->GetLocationY() + 1);
}