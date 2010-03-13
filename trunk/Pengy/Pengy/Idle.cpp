#include "Idle.h"
#include "Walking.h"
#include "Jumping.h"
#include "CharacterStateMachine.h"

Idle::Idle(void)
{
	
}

Idle::Idle(CharacterStateMachine * pStateMachine) : CharacterState(pStateMachine)
{

}

void Idle::Up()
{

}

void Idle::Down()
{
	
}


void Idle::Left()
{
	this->pStateMachine->pWalking->Left();
	this->pStateMachine->Transition(this->pStateMachine->pWalking);
}


void Idle::Right()
{
	this->pStateMachine->pWalking->Right();
	this->pStateMachine->Transition(this->pStateMachine->pWalking);
}

void Idle::Throw()
{

}


void Idle::Spacebar()
{
	this->pStateMachine->pJumping->Spacebar();
	this->pStateMachine->Transition(this->pStateMachine->pJumping);
}

void Idle::Update(int timeElapsed)
{

}

void Idle::ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case CM_CHARACTER_IS_FALLING:
		this->pStateMachine->Transition(this->pStateMachine->pFalling);
		break;
	}
}