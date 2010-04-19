#pragma once
#include "LeafEyeState.h"
#include "Windows.h"
#include "LeafEye.h"
#include "LeafEyeStateMachine.h"

class LeafEyeState
{
public:
	LeafEyeState(LeafEye * pLeafEye, LeafEyeStateMachine * pLeafEyeStateMachine);
	~LeafEyeState(void);
	virtual void Update(int timeElapsed) = 0;
	virtual void ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam) = 0;
protected:
	LeafEye * pLeafEye;
	LeafEyeStateMachine * pLeafEyeStateMachine;
};
