#pragma once
#include "Location.h"
#include "Direction.h"
#include "Surface.h"
#include "Windows.h"

class View;

class Enemy
{
	protected:
		Location * pLocation;
		Direction direction;
		View * pView;
		Surface * pOnSurface;
		Location * pPengyLocation;
		bool isAlive;
		int health;
		virtual void ReceiveMessageInternal(UINT message, WPARAM wParam, LPARAM lParam) = 0;
		bool isDeleted;

	public:
		Enemy(Surface * pSurface);
		virtual ~Enemy(void);
		void ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam);
		Location * GetLocation();
		Direction GetDirection();
		void SetDirection(Direction direction);
		Surface * GetOnSurface();
		Location * GetPengyLocation();
		void Delete();
		bool IsDeleted();
};
