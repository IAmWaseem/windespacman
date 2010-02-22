#include "CharacterStateMachine.h"
#include "CharacterState.h"
#include "Idle.h"

CharacterStateMachine::CharacterStateMachine(void)
{
	pCurrentState = new Idle(this);
}

CharacterStateMachine::~CharacterStateMachine(void)
{

}

void CharacterStateMachine::Up()
{
	this->pCurrentState->Up();
}

void CharacterStateMachine::Down()
{
	this->pCurrentState->Down();
}

void CharacterStateMachine::Left()
{
	this->pCurrentState->Left();
}

void CharacterStateMachine::Right()
{
	this->pCurrentState->Right();
}

void CharacterStateMachine::Spacebar()
{
	this->pCurrentState->Spacebar();
}

void CharacterStateMachine::Update(int timeElapsed)
{
	this->pCurrentState->Update(timeElapsed);
}

void CharacterStateMachine::Transition(CharacterState * pCharacterState)
{
	this->pCurrentState = pCharacterState;
}