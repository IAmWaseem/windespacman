#pragma once
#include "LeafEyeState.h"

class LeafEyeAttack : public LeafEyeState
{
public:
	LeafEyeAttack(LeafEye * pLeafEye, LeafEyeStateMachine * pLeafEyeStateMachine);
	~LeafEyeAttack(void);
	virtual void Update(int timeElapsed);
	virtual void ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam);
private:
	float speed;
	void Jump();
	int timeElapsed;
	float distanceToMoveUp;
	float upwardVelocity;
	float downwardVelocity;
	float distanceToMoveDown;
};
