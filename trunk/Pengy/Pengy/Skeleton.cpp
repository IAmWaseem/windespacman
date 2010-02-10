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

/////////////////////////////////////
// Member functions                  //
/////////////////////////////////////

LRESULT CSkeleton::MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	MessageQueue* messageQueue;
	messageQueue = messageQueue->Inst();
	Level* level;
	level = level->Inst();

	switch (uMsg) 
	{
	case WM_CREATE:
		messageQueue->attach(level);
		break;
	case WM_KEYDOWN:
		messageQueue->sendMessage("test");
		break;
	case WM_DESTROY:

		break;
	}
	return CWin::MsgProc(hWnd, uMsg, wParam, lParam);
}