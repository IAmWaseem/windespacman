#include "LeafEyeState.h"

LeafEyeState::LeafEyeState(LeafEye * pLeafEye, LeafEyeStateMachine * pLeafEyeStateMachine)
{
	this->pLeafEye = pLeafEye;
	this->pLeafEyeStateMachine = pLeafEyeStateMachine;
}

LeafEyeState::~LeafEyeState(void)
{
}
