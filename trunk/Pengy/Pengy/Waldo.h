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

		//tijdelijk voor extra waldo zodat je naar volgend level gaat
		bool superWaldo;

	public:
		Waldo(Surface * pSurface, int x, bool isSuper);
		Waldo(Surface * pSurface, int x);
		Waldo(Surface * pSurface);
		~Waldo(void);
		void ReceiveMessageInternal(UINT message, WPARAM wParam, LPARAM lParam);
};
