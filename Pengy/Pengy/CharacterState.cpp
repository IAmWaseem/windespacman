#include "CharacterState.h"
#include "CharacterStateMachine.h"

CharacterState::CharacterState()
{

}

CharacterState::CharacterState(CharacterStateMachine * pStateMachine)
{
	this->pStateMachine = pStateMachine;
}

CharacterState::~CharacterState(void)
{
}
