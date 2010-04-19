#pragma once
#include "view.h"

class MenuView : public View
{
private:
	HANDLE image;
public:
	MenuView(void);
	~MenuView(void);
	void Draw(HDC hdc, RECT rect, int xFrom, int xTo);
};
