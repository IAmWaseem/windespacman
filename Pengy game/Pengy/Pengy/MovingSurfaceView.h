#pragma once

#include "View.h"
#include "World.h"
#include <map>
#include <windows.h>
#include "MovingSurface.h"

#include "Renderer.h"
#include <sstream>

using namespace std;
using namespace dotnetguy;

class MovingSurface;
enum MovingSurfaceType;

class MovingSurfaceView : public View
{	

public:
	MovingSurfaceView(void);
	MovingSurfaceView(MovingSurface * surface, MovingSurfaceType type);
	~MovingSurfaceView(void);
	
	void Draw(HDC hdc, RECT rect, int xFrom, int xTo);

	void Update();

private:
	MovingSurface * pSurface;
	HANDLE currentBitmap;
	HANDLE currentMask;
	int* width_height;
};
