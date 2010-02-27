#include "Jumping.h"
#include "Character.h"

Jumping::Jumping(void)
{
	this->upwardVelocity = 0;
	this->speed = 0.3f;
}

Jumping::Jumping(CharacterStateMachine * pStateMachine) : CharacterState(pStateMachine)
{
	this->upwardVelocity = 0;
	this->speed = 0.3f;
}

void Jumping::Up()
{

}

void Jumping::Down()
{
	
}


void Jumping::Left()
{
	if(this->direction != Direction::Left)
	{
		Character::Instance()->GetCharacterView()->ChangeCurrentImage(CharacterView::CharacterImage::Left);
	}
	this->direction = Direction::Left;
	this->distanceToMove = 5;
}


void Jumping::Right()
{
	if(this->direction != Direction::Right) 
	{
		Character::Instance()->GetCharacterView()->ChangeCurrentImage(CharacterView::CharacterImage::Right);
	}
	this->direction = Direction::Right;
	this->distanceToMove = 5;
}

void Jumping::Throw()
{

}


void Jumping::Spacebar()
{
	if(upwardVelocity == 0)
	{
		upwardVelocity = 0.160;
	}
}

void Jumping::Update(int timeElapsed)
{
	if(upwardVelocity > 0)
	{
		float y = Character::Instance()->GetLocation()->Y;
		float newUpwardVelocity = upwardVelocity  - (0.000120 * timeElapsed);
		float averageVelocity = (upwardVelocity + newUpwardVelocity) / 2;
		float distance = averageVelocity * timeElapsed;
		Character::Instance()->GetLocation()->Y -= distance;
		upwardVelocity = newUpwardVelocity;

		float distanceMoved = timeElapsed * this->speed;
		if(distanceMoved > this->distanceToMove) distanceMoved = distanceToMove;
		this->distanceToMove -= distanceMoved;

		switch(this->direction)
		{
		case Direction::Left:
			Character::Instance()->GetLocation()->X -= distanceMoved;
			break;
		case Direction::Right:
			Character::Instance()->GetLocation()->Y += distanceMoved;
			break;
		}

	}	
	else
	{
		upwardVelocity = 0;
		this->pStateMachine->Transition(this->pStateMachine->falling);
	}
}

void Jumping::recieveMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	
}