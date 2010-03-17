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
		bool isVulnerable;

		void CheckPengyCollision();
		bool LocationInWaldoX(Location * pLocationPengy, Location * pLocationWaldo);
		bool LocationInWaldoY(Location * pLocationPengy, Location * pLocationWaldo);
		void RandomDirection();

	public:
		Waldo(Surface * pSurface, int x);
		Waldo(Surface * pSurface);
		~Waldo(void);
		void ReceiveMessageInternal(UINT message, WPARAM wParam, LPARAM lParam);
};
