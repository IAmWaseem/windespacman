#pragma once
#include "observer.h"
#include "surface.h"
#include "location.h"

class WaldoStateMachine;

class WaldoView;

class Waldo : public Observer
{
	private:
		Location * pLocation;
		WaldoView * pWaldoView;
		WaldoStateMachine * pWaldoStateMachine;
		Surface * pOnSurface;
	public:
		Waldo(Location * pLocation);
		Waldo(Surface * pSurface);
		~Waldo(void);
		void recieveMessage(UINT message, WPARAM wParam, LPARAM lParam);
		Location * GetLocation();
};
