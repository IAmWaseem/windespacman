#include "LeafEyePatrol.h"
#include "math.h"
#include "messages.h"

LeafEyePatrol::LeafEyePatrol(LeafEye * pLeafEye, LeafEyeStateMachine * pLeafEyeStateMachine):LeafEyeState(pLeafEye, pLeafEyeStateMachine)
{
	this->speed = 0.3f;
}


LeafEyePatrol::~LeafEyePatrol(void)
{
}

void LeafEyePatrol::ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam) 
{
	int timeElapsed;

	switch(message) {
		case CM_UPDATE:
		timeElapsed = wParam;
		this->Update(timeElapsed);
		break;
	}
}

void LeafEyePatrol::Update(int timeElapsed) 
{
	int distanceToPengy = fabs(this->pLeafEye->GetPengyLocation()->X - pLeafEye->GetLocation()->X);
	
	if(distanceToPengy < 500)
	{			
		pLeafEyeStateMachine->Transition(pLeafEyeStateMachine->pAttack);
	}
}