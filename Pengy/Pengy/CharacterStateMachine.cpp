#include "CharacterStateMachine.h"
#include "CharacterState.h"
#include "Idle.h"
#include "Jumping.h"
#include "Walking.h"
#include "Falling.h"

CharacterStateMachine::CharacterStateMachine(void)
{
	pIdle = new Idle(this);
	pWalking = new Walking(this);
	pJumping = new Jumping(this);
	pFalling = new Falling(this);
	pCurrentState = pIdle;
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

void CharacterStateMachine::Throw()
{
	this->pCurrentState->Throw();
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

void CharacterStateMachine::ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	this->pCurrentState->ReceiveMessage(message, wParam, lParam);
}