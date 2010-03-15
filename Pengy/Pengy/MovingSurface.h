#pragma once
#include "observer.h"
#include "surface.h"
#include "MovingSurfaceView.h"

class MovingSurfaceView;

class MovingSurface : public Surface, public Observer
{
private:
	MovingSurfaceView * msView;
public:
	bool initMoveUp;
	int maxDif;
	int difY;
	int firstY;
	float speed;
	void Update(int timeElapsed);
	void ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam);
	MovingSurface(void);
	MovingSurface(int FromX, int FromY, int ToX, int ToY, int theMaxDif, bool MoveUp);
	~MovingSurface(void);
};
