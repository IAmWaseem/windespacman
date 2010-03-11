#pragma once
#include "enemy.h"
#include "surface.h"
#include "location.h"

class WaldoStateMachine;

class View;

class Waldo : public Enemy
{
	private:
		WaldoStateMachine * pWaldoStateMachine;
		bool pengyJumping;
		bool isVulnerable;

		void CheckPengyCollision();
		bool LocationInWaldoX(Location * locationPengy, Location * locationGadget);
		bool LocationInWaldoY(Location * locationPengy, Location * locationGadget);
		void RandomDirection();

	public:
		Waldo(Surface * pSurface, int x);
		Waldo(Surface * pSurface);
		~Waldo(void);
		void recieveMessageInternal(UINT message, WPARAM wParam, LPARAM lParam);
};
