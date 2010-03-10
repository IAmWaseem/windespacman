#pragma once
#include "observer.h"
#include "surface.h"
#include "location.h"

class WaldoStateMachine;

class WaldoView;

class Waldo : public Observer
{
	private:
		Location * location;
		WaldoView * waldoView;
		WaldoStateMachine * pWaldoStateMachine;
	public:
		Waldo(Location * location);
		Waldo(Surface * surface);
		~Waldo(void);
		void recieveMessage(UINT message, WPARAM wParam, LPARAM lParam);
		Location * GetLocation();
};
