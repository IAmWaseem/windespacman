#include "GameOverView.h"

GameOverView::GameOverView(void)
{
	timeToShow = 3000;
	timeShown = 0;
	bitmap = LoadImage(NULL, "res/gameover.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	MessageQueue::Instance()->Attach(this);
	MessageQueue::Instance()->SendMessage(CM_RENDERER_ONLY_DRAW_THIS, (int)(View*)this, NULL);
}

GameOverView::~GameOverView(void)
{
	MessageQueue::Instance()->SendMessage(CM_RENDERER_NORMAL_RENDER, NULL, NULL);
	MessageQueue::Instance()->Detach(this);
}

void GameOverView::Draw(HDC hdc, RECT rect, int xFrom, int xTo)
{
	HDC bufDC = CreateCompatibleDC(hdc);
	SelectObject(bufDC, bitmap);

	BitBlt(hdc, 0, 0, 1014, 671, bufDC, 0, 0, SRCCOPY);	
	DeleteDC(bufDC);
}

void GameOverView::ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam)
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
