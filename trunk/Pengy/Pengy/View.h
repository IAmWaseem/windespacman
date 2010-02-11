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
	virtual void draw(HDC hdc) = 0;
    ~View();
private:
	Renderer* renderer;
};
