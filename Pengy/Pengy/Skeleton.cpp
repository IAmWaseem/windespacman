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