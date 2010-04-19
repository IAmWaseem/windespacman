#pragma once
#include "MisterFrostState.h"

class MisterFrostAttack : public MisterFrostState
{
public:
	MisterFrostAttack(MisterFrost * pMisterFrost, MisterFrostStateMachine * pMisterFrostStateMachine);
	~MisterFrostAttack(void);
	virtual void Update(int timeElapsed);
	virtual void ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam);
private:
	float speed;
	void Throw();
	int throws;
	int throwsInterval;
	int RandomIntBetween(int a, int b);
};
