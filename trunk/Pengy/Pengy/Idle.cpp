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
	this->pStateMachine->walking->Left();
	this->pStateMachine->Transition(this->pStateMachine->walking);
}


void Idle::Right()
{
	this->pStateMachine->walking->Right();
	this->pStateMachine->Transition(this->pStateMachine->walking);
}

void Idle::Throw()
{

}


void Idle::Spacebar()
{
	//MessageQueue::Inst()->sendMessage(CM_SOUND_EVENT,(WPARAM)(LPCTSTR)"res/pengy.wav", 0);
	this->pStateMachine->jumping->Spacebar();
	this->pStateMachine->Transition(this->pStateMachine->jumping);
}

void Idle::Update(int timeElapsed)
{

}

void Idle::recieveMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case CM_CHARACTER_IS_FALLING:
		this->pStateMachine->Transition(this->pStateMachine->falling);
		break;
	}
}