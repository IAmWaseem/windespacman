#include "GameWinView.h"

GameWinView::GameWinView(void)
{
	timeToShow = 6000;
	timeShown = 0;
	bitmap = LoadImage(NULL, "res/gamewin.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	mask = CreateBitmapMask(bitmap, RGB(0, 0, 0), 1024, 700);
	MessageQueue::Instance()->Attach(this);
	MessageQueue::Instance()->SendMessage(CM_RENDERER_DRAW_ONTOP, (int)(View*)this, NULL);
	MessageQueue::Instance()->SendMessage(CM_SOUND_EVENT, (WPARAM)(LPCTSTR)"res/Waves/Win Stage.wav", 0);
}

GameWinView::~GameWinView(void)
{
	MessageQueue::Instance()->SendMessage(CM_RENDERER_NORMAL_RENDER, NULL, NULL);
	MessageQueue::Instance()->Detach(this);
	MessageQueue::Instance()->SendMessage(CM_GAME_OVER, NULL, NULL);
}

void GameWinView::Draw(HDC hdc, RECT rect, int xFrom, int xTo)
{
	HDC bufDC = CreateCompatibleDC(hdc);
	SelectObject(bufDC, bitmap);

	//BitBlt(hdc, 0, 0, 1014, 671, bufDC, 0, 0, SRCCOPY);	
	BitBltTransparant(hdc, 0, 0, 1024, 700, bufDC, 0, 0, bitmap, mask);
	DeleteDC(bufDC);
}

void GameWinView::ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case CM_UPDATE:
		int timeElapsed = wParam;
		timeShown += timeElapsed;
		if(timeShown > timeToShow)
			delete this;
		break;
	}
}
