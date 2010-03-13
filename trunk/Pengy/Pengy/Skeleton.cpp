#include "Skeleton.h"
#include "EnemyFactory.h"
//#include "Bitmap.h"
//#include "Messages.h"
#include "Location.h"
#include "Gadget.h"
#include "SPLASH.h"
#include "resource.h"
using namespace dotnetguy;


/////////////////////////////////////
// Constructors / Destructors      //
/////////////////////////////////////
CSkeleton::CSkeleton()
{
	paused = false;
}

CSkeleton::~CSkeleton()
{
}

/////////////////////////////////////
// Member functions                  //
/////////////////////////////////////

LRESULT CSkeleton::MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	SPLASH pSplash;
	Location * pLocation;

		
		

	switch (uMsg) 
	{
	case WM_CREATE:
		pSplash.Init(hWnd, this->m_hInstance, IDB_BITMAP2 );
		pSplash.Show();
		Sleep(3000);
		pSplash.Hide();
		
		pLocation = new Location();
		pLocation->X = 200;
		pLocation->Y = 300;
		
		pMessageQueue->Instance()->Attach(pLevel->Instance());
		pMessageQueue->Instance()->Attach(pCharacter->Instance());
		pMessageQueue->Instance()->Attach(pRenderer->Instance());
		pMessageQueue->Instance()->Attach(pSound->Instance());
		pMessageQueue->Instance()->Attach(GadgetFactory::Instance());
		pMessageQueue->Instance()->Attach(EnemyFactory::Instance());
		pMessageQueue->Instance()->Attach(pWorld->Inst());
		pMessageQueue->Instance()->Attach(pMenu->Instance());
		pMenu->Instance()->windowHandle = hWnd;
		break;
	case WM_KEYDOWN:

		

		//case 32:
		//	messageQueue->Inst()->sendMessage(CM_CHARACTER_SPACEBAR, NULL, NULL);
		//	break;
		//case 37:
		//	messageQueue->Inst()->sendMessage(CM_CHARACTER_LEFT, NULL, NULL);
		//	break;
		//case 38:
		//	messageQueue->Inst()->sendMessage(CM_CHARACTER_UP, NULL, NULL);
		//	break;
		//case 39:
		//	messageQueue->Inst()->sendMessage(CM_CHARACTER_RIGHT, NULL, NULL);
		//	break;
		//case 40:
		//	messageQueue->Inst()->sendMessage(CM_CHARACTER_DOWN, NULL, NULL);
		//	break;
	switch(wParam)
	{
		case 'm':
		case 'M':
			pMessageQueue->Instance()->SendMessage(CM_MENU_LOAD, NULL, NULL);
			paused = true;

		case 't':
		case 'T':
			pMessageQueue->Instance()->SendMessage(CM_CHARACTER_RESET_POSITION, NULL, 10);
			break;

		case 'r':
		case 'R':
			pMessageQueue->Instance()->SendMessage(CM_CHARACTER_RESET_POSITION, 50, 200);
			break;
		
		case 'g':
		case 'G':
			pMessageQueue->Instance()->SendMessage(CM_SOUND_EVENT,(WPARAM)(LPCTSTR)"res/pengy.wav", 0);
			break;

			// show the fps
		case 'f':
		case 'F':
			if(Renderer::ShowFps)
				Renderer::ShowFps = false;
			else
				Renderer::ShowFps = true;
			break;

			// show the surfaces
		case 's':
		case 'S':
			if(Renderer::ShowSurfaces)
				Renderer::ShowSurfaces = false;
			else
				Renderer::ShowSurfaces = true;
			break;

			// show the debug
		case 'd':
		case 'D':
			if(Renderer::ShowDebug)
				Renderer::ShowDebug = false;
			else
				Renderer::ShowDebug = true;
			break;
		}
		break;
	case WM_COMMAND:  
		switch(LOWORD(wParam)) {  
		case CM_GAME_NEW:  
			pMessageQueue->Instance()->SendMessage(CM_GAME_NEW, NULL, NULL);
			break;  
		case CM_GAME_OPEN:  
			pMessageQueue->Instance()->SendMessage(CM_GAME_OPEN, NULL, NULL);
			break;  
		case CM_GAME_SAVE:  
			pMessageQueue->Instance()->SendMessage(CM_GAME_SAVE, NULL, NULL);
			break;  
		case CM_GAME_EXIT:  
			pMessageQueue->Instance()->SendMessage(CM_GAME_EXIT, NULL, NULL); 
			break;
		case CM_GAME_ABOUT:  
			pMessageQueue->Instance()->SendMessage(CM_GAME_ABOUT, NULL, NULL);
			break;  
		}  
		break;  
	}
	return CWin::MsgProc(hWnd, uMsg, wParam, lParam);
}

void CSkeleton::GameInit()
{
	pMessageQueue->Instance()->SendMessage(CM_MENU_LOAD, NULL, NULL);
	paused = true;
	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = 800;
	rect.bottom = 600;

	bufDC = CreateCompatibleDC(graphics);
	HBITMAP bufBMP;
	bufBMP = CreateCompatibleBitmap(graphics, 800, 600);
	SelectObject(bufDC, bufBMP);
	::FillRect(bufDC, &rect, ::CreateSolidBrush(0x00FFFFFF));

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

void CSkeleton::GameLoop()
{
	Update();
	Render(this->m_hWnd);
}

void CSkeleton::GameEnd()
{

}

void CSkeleton::Render(HWND hWnd)
{
	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = 800;
	rect.bottom = 600;

	//::FillRect(bufDC, &rect, ::CreateSolidBrush(RGB(200, 255, 255)));
	pRenderer->Instance()->Render(bufDC);
	BitBlt(graphics, 0,0, 800, 600,bufDC, 0, 0, SRCCOPY);
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
	int elapsedTime = (int)(systemTimeIn_ms - previousUpdateTime);
	
	if(!paused == true)
		pMessageQueue->Instance()->SendMessage(CM_UPDATE, elapsedTime, NULL);
	previousUpdateTime = systemTimeIn_ms;
	if(pWorld->Inst()->menu == false && paused == true)
		paused = false;
}