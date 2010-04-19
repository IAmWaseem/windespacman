#pragma once
#include "enemy.h"
#include "surface.h"
#include "location.h"

class LeafEyeStateMachine;

class View;

class LeafEye : public Enemy
{
public:
	LeafEye(Surface * pSurface);
	~LeafEye(void);
	virtual void ReceiveMessageInternal(UINT message, WPARAM wParam, LPARAM lParam);
	void SetLocation(Location * pLocation);
private:
	LeafEyeStateMachine * pLeafEyeStateMachine;
	void CheckCollision();
};