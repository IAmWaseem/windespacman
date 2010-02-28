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
	virtual void Draw(HDC hdc, int xFrom, int xTo) = 0;
    ~View();
private:
	Renderer* renderer;
};
