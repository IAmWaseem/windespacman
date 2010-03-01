#include "Falling.h"
#include "Character.h"
#include "Surface.h"

Falling::Falling(void)
{
	this->downwardVelocity = 0;
	this->speed = 0.3f;
}

Falling::Falling(CharacterStateMachine * pStateMachine) : CharacterState(pStateMachine)
{
	this->downwardVelocity = 0;
	this->speed = 0.3f;
}

void Falling::Up()
{

}

void Falling::Down()
{
	
}


void Falling::Left()
{
	if(this->direction != Direction::Left)
	{
		Character::Instance()->GetCharacterView()->ChangeCurrentImage(CharacterView::CharacterImage::Left);
	}
	this->direction = Direction::Left;
	this->distanceToMove = 5;
}


void Falling::Right()
{
	if(this->direction != Direction::Right) 
	{
		Character::Instance()->GetCharacterView()->ChangeCurrentImage(CharacterView::CharacterImage::Right);
	}
	this->direction = Direction::Right;
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

	switch(this->direction)
	{
	case Direction::Left:
		Character::Instance()->GetLocation()->X -= distanceMoved;
		break;
	case Direction::Right:
		Character::Instance()->GetLocation()->X += distanceMoved;
		break;
	}

	float newDownwardVelocity = downwardVelocity + (0.000120 * timeElapsed);
	float averageVelocity = (downwardVelocity + newDownwardVelocity) / 2;
	float distance = averageVelocity * timeElapsed;
	Character::Instance()->GetLocation()->Y += distance;
	float newCharacterLocation = Character::Instance()->GetLocation()->Y + distance;
	downwardVelocity = newDownwardVelocity;
	Location * oldLocation = Character::Instance()->GetLocation();
	Location * newLocation = new Location();
	newLocation->X = oldLocation->X;
	newLocation->Y = oldLocation->Y;
	newLocation->width = oldLocation->width;
	newLocation->height = oldLocation->height;
	newLocation->Y += distance;
	Character::Instance()->SetLocation(newLocation);
	MessageQueue::Inst()->sendMessage(CM_CHARACTER_FALL_Y_FROM_TO, (int)oldLocation, (int)newLocation);
	MessageQueue::Inst()->sendMessage(CM_CHARACTER_MOVE_X_FROM_TO, (int)oldLocation, (int)newLocation);
}

void Falling::recieveMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case CM_CHARACTER_IS_STANDING:
		downwardVelocity = 0;
		Surface * surface = (Surface*)wParam;
		Location * characterLocation = Character::Instance()->GetLocation();
		characterLocation->Y = surface->yFrom - characterLocation->height;
		Character::Instance()->SetLocation(characterLocation);
		this->pStateMachine->Transition(this->pStateMachine->idle);
		break;
	}
}