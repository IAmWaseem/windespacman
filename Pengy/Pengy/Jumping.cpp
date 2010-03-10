#include "Jumping.h"
#include "Character.h"

Jumping::Jumping(void)
{
	this->upwardVelocity = 0;
	this->speed = 0.3f;
	this->distanceToMove = 0;
}

Jumping::Jumping(CharacterStateMachine * pStateMachine) : CharacterState(pStateMachine)
{
	this->upwardVelocity = 0;
	this->speed = 0.3f;
	this->distanceToMove = 0;
}

void Jumping::Up()
{

}

void Jumping::Down()
{
	
}


void Jumping::Left()
{
	if(Character::Instance()->getDirection() != Direction::Left)
	{
		Character::Instance()->GetCharacterView()->ChangeCurrentImage(CharacterView::CharacterImage::JumpLeft);
	}
	Character::Instance()->setDirection(Direction::Left);
	this->distanceToMove = 5;
}


void Jumping::Right()
{
	if(Character::Instance()->getDirection()!= Direction::Right) 
	{
		Character::Instance()->GetCharacterView()->ChangeCurrentImage(CharacterView::CharacterImage::JumpRight);
	}
	Character::Instance()->setDirection(Direction::Right);
	this->distanceToMove = 5;
}

void Jumping::Throw()
{

}


void Jumping::Spacebar()
{
	if(Character::Instance()->getDirection() == Direction::Right)
	{
		Character::Instance()->GetCharacterView()->ChangeCurrentImage(CharacterView::CharacterImage::JumpRight);
	}
	else {
		Character::Instance()->GetCharacterView()->ChangeCurrentImage(CharacterView::CharacterImage::JumpLeft);
	}
	
	if(upwardVelocity == 0)
	{
		upwardVelocity = 0.320f;
	}

	
}

void Jumping::Update(int timeElapsed)
{
	Location * oldLocation = Character::Instance()->GetLocation();
	Location * newLocation = new Location();
	newLocation->X = oldLocation->X;
	newLocation->Y = oldLocation->Y;
	newLocation->width = oldLocation->width;
	newLocation->height = oldLocation->height;

	if(upwardVelocity > 0)
	{
		float y = newLocation->Y;
		float newUpwardVelocity = (float)(upwardVelocity  - (0.000400 * timeElapsed));
		float averageVelocity = (upwardVelocity + newUpwardVelocity) / 2;
		float distance = averageVelocity * timeElapsed;
		newLocation->Y -= distance;
		upwardVelocity = newUpwardVelocity;

		float distanceMoved = timeElapsed * this->speed;
		if(distanceMoved > this->distanceToMove) distanceMoved = distanceToMove;
		this->distanceToMove -= distanceMoved;

		switch(Character::Instance()->getDirection())
		{
		case Direction::Left:
			newLocation->X -= distanceMoved;
			break;
		case Direction::Right:
			newLocation->X += distanceMoved;
			break;
		}
		Character::Instance()->SetLocation(newLocation);	
		MessageQueue::Inst()->sendMessage(CM_CHARACTER_MOVE_X_FROM_TO, (int)oldLocation, (int)newLocation);
		MessageQueue::Inst()->sendMessage(CM_CHARACTER_JUMP_Y_FROM_TO, (int)oldLocation, (int)newLocation);
	}	
	else
	{
		upwardVelocity = 0;
		this->pStateMachine->Transition(this->pStateMachine->falling);
		if(Character::Instance()->getDirection() == Direction::Right)
		{
			Character::Instance()->GetCharacterView()->ChangeCurrentImage(CharacterView::CharacterImage::FallingRight);
		}
		else {
			Character::Instance()->GetCharacterView()->ChangeCurrentImage(CharacterView::CharacterImage::FallingLeft);
		}
	}
}

void Jumping::recieveMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	Surface * surface;
	switch(message)
	{
	case CM_CHARACTER_JUMPING_BUMPS_HEAD:
		surface = (Surface*)wParam;
		Character::Instance()->GetLocation()->Y = (float)surface->yTo;
		this->pStateMachine->Transition(this->pStateMachine->falling);
		break;
	case CM_CHARACTER_BUMPS_INTO:
		Surface * surface = (Surface*)wParam;
		if((((Character::Instance()->GetLocation()->X + Character::Instance()->GetLocation()->width) >= surface->xFrom) && surface->xTo > (Character::Instance()->GetLocation()->X + Character::Instance()->GetLocation()->width)))
		{
			Character::Instance()->GetLocation()->X = surface->xFrom - Character::Instance()->GetLocation()->width;
		}
		else
		{
			Character::Instance()->GetLocation()->X = (float)surface->xTo;
		}
		break;
	}
}