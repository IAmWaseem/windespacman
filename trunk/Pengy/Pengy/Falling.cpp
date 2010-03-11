#include "Falling.h"
#include "Character.h"
#include "Surface.h"

Falling::Falling(void)
{
	this->distanceToMove = 0;
	this->downwardVelocity = 0;
	this->speed = 0.2f;
}

Falling::Falling(CharacterStateMachine * pStateMachine) : CharacterState(pStateMachine)
{
	this->distanceToMove = 0;
	this->downwardVelocity = 0;
	this->speed = 0.2f;
}

void Falling::Up()
{

}

void Falling::Down()
{
	
}


void Falling::Left()
{
	if(Character::Instance()->getDirection() != Direction::Left)
	{
		Character::Instance()->GetCharacterView()->ChangeCurrentImage(CharacterView::CharacterImage::FallingLeft);
	}
	Character::Instance()->setDirection(Direction::Left);
	this->distanceToMove = 5;
}


void Falling::Right()
{
	if(Character::Instance()->getDirection() != Direction::Right) 
	{
		Character::Instance()->GetCharacterView()->ChangeCurrentImage(CharacterView::CharacterImage::FallingRight);
	}
	Character::Instance()->setDirection(Direction::Right);
	this->distanceToMove = 5;
}

void Falling::Throw()
{

}


void Falling::Spacebar()
{

}

void Falling::Update(int timeElapsed)
{
	float distanceMoved = timeElapsed * this->speed;
	if(distanceMoved > this->distanceToMove) distanceMoved = distanceToMove;
	this->distanceToMove -= distanceMoved;
	Location * oldLocation = Character::Instance()->GetLocation();
	Location * newLocation = new Location();
	newLocation->X = oldLocation->X;
	newLocation->Y = oldLocation->Y;
	newLocation->width = oldLocation->width;
	newLocation->height = oldLocation->height;

	switch(Character::Instance()->getDirection())
	{
	case Direction::Left:
		newLocation->X -= distanceMoved;
		break;
	case Direction::Right:
		newLocation->X += distanceMoved;
		break;
	}

	float newDownwardVelocity = (float)(downwardVelocity + (0.000400 * timeElapsed));
	float averageVelocity = (downwardVelocity + newDownwardVelocity) / 2;
	float distance = averageVelocity * timeElapsed;
	Character::Instance()->GetLocation()->Y += distance;
	float newCharacterLocation = Character::Instance()->GetLocation()->Y + distance;
	downwardVelocity = newDownwardVelocity;
	newLocation->Y += distance;
	Character::Instance()->SetLocation(newLocation);
	MessageQueue::Inst()->sendMessage(CM_CHARACTER_MOVE_X_FROM_TO, (int)oldLocation, (int)newLocation);
	MessageQueue::Inst()->sendMessage(CM_CHARACTER_FALL_Y_FROM_TO, (int)oldLocation, (int)newLocation);
}

void Falling::recieveMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	Surface * surface;
	Location * characterLocation;
	switch(message)
	{
	case CM_CHARACTER_IS_STANDING:
		downwardVelocity = 0;
		surface = (Surface*)wParam;
		characterLocation = Character::Instance()->GetLocation();
		characterLocation->Y = surface->yFrom - characterLocation->height;
		Character::Instance()->SetLocation(characterLocation);
		this->pStateMachine->Transition(this->pStateMachine->idle);
		if(Character::Instance()->getDirection() == Direction::Right)
		{
			Character::Instance()->GetCharacterView()->ChangeCurrentImage(CharacterView::CharacterImage::Right);
		}
		else {
			Character::Instance()->GetCharacterView()->ChangeCurrentImage(CharacterView::CharacterImage::Left);
		}
		break;
	case CM_CHARACTER_BUMPS_INTO:
		Surface * surface = (Surface*)wParam;
		if(((Character::Instance()->GetLocation()->X + Character::Instance()->GetLocation()->width) >= surface->xFrom) && surface->xTo > (Character::Instance()->GetLocation()->X + Character::Instance()->GetLocation()->width))
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