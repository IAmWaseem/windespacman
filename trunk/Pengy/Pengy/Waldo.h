#pragma once
#include "observer.h"
#include "surface.h"
#include "location.h"
#include "direction.h"

class WaldoStateMachine;

class WaldoView;

class Waldo : public Observer
{
	private:
		Location * pLocation;
		WaldoView * pWaldoView;
		WaldoStateMachine * pWaldoStateMachine;
		Surface * pOnSurface;
		Direction direction;

	public:
		Waldo(Location * pLocation);
		Waldo(Surface * pSurface);
		~Waldo(void);
		void recieveMessage(UINT message, WPARAM wParam, LPARAM lParam);
		Location * GetLocation();
		Direction GetDirection();
		void SetDirection(Direction direction);
		Surface * GetOnSurface();
};
