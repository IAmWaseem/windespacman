#pragma once
#include "LeafEyeState.h"

class LeafEyePatrol : public LeafEyeState
{
private: 
	float speed;
public:
	LeafEyePatrol(LeafEye * pLeafEye, LeafEyeStateMachine * pLeafEyeStateMachine);
	~LeafEyePatrol(void);
	virtual void Update(int timeElapsed);
	virtual void ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam);
};
