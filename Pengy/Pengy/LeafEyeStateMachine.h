#pragma once
#include "Windows.h"

class LeafEye; 

class LeafEyeState;

class LeafEyeStateMachine
{
public:
	LeafEyeStateMachine(LeafEye * pLeafEye);
	~LeafEyeStateMachine(void);
	void Update(int timeElapsed);
	void ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam);
	void Transition(LeafEyeState * pLeafEyeState);

	LeafEyeState * pAttack;
	LeafEyeState * pPatrol;
private:
	LeafEyeState * pCurrentState;
};
