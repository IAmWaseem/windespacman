#pragma once
#include "view.h"
#include "observer.h"

class GameOverView : public View, public Observer
{
public:
	GameOverView(void);
	~GameOverView(void);
	void Draw(HDC hdc, RECT rect, int xFrom, int xTo);
	void ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam);

private:
	HANDLE bitmap;
	int timeToShow;
	int timeShown;
};
