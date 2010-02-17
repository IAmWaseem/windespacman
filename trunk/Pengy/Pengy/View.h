#pragma once

#include <windows.h>
#include "messages.h"
#include <string>
using namespace std;

class Renderer;

class View
{
public:
    View();
    void registerToGraphics();
	void unRegisterToGraphics();
	virtual void Draw(HDC hdc, HWND m_hWnd) = 0;
    ~View();
private:
	Renderer* renderer;
};
