#pragma once
#include "enemy.h"
#include "surface.h"
#include "location.h"

class MisterFrostStateMachine;

class View;

class MisterFrost : public Enemy
{
public:
	MisterFrost(Surface * pSurface);
	~MisterFrost(void);
	virtual void ReceiveMessageInternal(UINT message, WPARAM wParam, LPARAM lParam);
private:
	MisterFrostStateMachine * pMisterFrostStateMachine;
	void CheckCollision();
};