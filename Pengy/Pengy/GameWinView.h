#pragma once
#include "view.h"
#include "observer.h"

class GameWinView : public View, public Observer
{
public:
	GameWinView(void);
	~GameWinView(void);
	void Draw(HDC hdc, RECT rect, int xFrom, int xTo);
	void ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam);

private:
	HANDLE bitmap;
	HANDLE mask;
	int timeToShow;
	int timeShown;
};
