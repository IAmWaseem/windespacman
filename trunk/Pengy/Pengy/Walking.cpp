#include "Walking.h"
#include "Character.h"
#include "CharacterView.h"
#include "CharacterStateMachine.h"
#include "Idle.h"
#include "Jumping.h"

Walking::Walking(void)
{
	this->speed = 0.3f;
	this->moved = 0;
}

Walking::Walking(CharacterStateMachine * pStateMachine) : CharacterState(pStateMachine)
{
	this->speed = 0.3f;
	this->moved = 0;
}

void Walking::Up()
{

}

void Walking::Down()
{
	
}


void Walking::Left()
{
	if(Character::Instance()->getDirection() != Direction::Left)
	{
		Character::Instance()->GetCharacterView()->ChangeCurrentImage(CharacterView::CharacterImage::Left);
	}
	Character::Instance()->setDirection(Direction::Left);
	this->distanceToMove = 5;
}


void Walking::Right()
{
	if(Character::Instance()->getDirection() != Direction::Right) 
	{
		Character::Instance()->GetCharacterView()->ChangeCurrentImage(CharacterView::CharacterImage::Right);
	}
	Character::Instance()->setDirection(Direction::Right);
	this->distanceToMove = 5;
}

void Walking::Throw()
{

}


void Walking::Spacebar()
{
	this->pStateMachine->jumping->Spacebar();
	if(this->distanceToMove > 0.5)
	{
		if(Character::Instance()->getDirection()  == Direction::Left)
			this->pStateMachine->jumping->Left();
		else
			this->pStateMachine->jumping->Right();
	}
	this->pStateMachine->Transition(this->pStateMachine->jumping);
}

void Walking::Update(int timeElapsed)
{
	Location * oldLocation = Character::Instance()->GetLocation();
	Location * newLocation = new Location();
	newLocation->width = oldLocation->width;
	newLocation->height = oldLocation->height;

	float distanceMoved = timeElapsed * this->speed;
	if(distanceMoved > this->distanceToMove) distanceMoved = distanceToMove;
	this->distanceToMove -= distanceMoved;
	this->moved += distanceMoved;
	switch(Character::Instance()->getDirection())
	{
	case Direction::Left:
		newLocation->X = oldLocation->X - distanceMoved;
		newLocation->Y = oldLocation->Y;
		Character::Instance()->SetLocation(newLocation);
		break;
	case Direction::Right:
		newLocation->X = oldLocation->X + distanceMoved;
		newLocation->Y = oldLocation->Y;
		Character::Instance()->SetLocation(newLocation);
		break;
	}
	
	MessageQueue::Inst()->sendMessage(CM_CHARACTER_MOVE_X_FROM_TO,  (int)oldLocation, (int)newLocation);
	MessageQueue::Inst()->sendMessage(CM_CHARACTER_FALL_Y_FROM_TO,  (int)oldLocation, (int)newLocation);

	SwapPicture();
	
	if(distanceToMove == 0)
	{
		this->pStateMachine->Transition(this->pStateMachine->idle);
	}
}

void Walking::SwapPicture()
{
	if((int)this->moved % 20 < 1)
	{
		if(Character::Instance()->getDirection() == Direction::Left)
		{
			if(Character::Instance()->GetCharacterView()->GetCurrentImage() == CharacterView::CharacterImage::Left)
			{
				if(moved > 100)
				{
					Character::Instance()->GetCharacterView()->ChangeCurrentImage(CharacterView::CharacterImage::Left2);
				}
				Character::Instance()->GetCharacterView()->ChangeCurrentImage(CharacterView::CharacterImage::Left2);
			}
			else
			{
				Character::Instance()->GetCharacterView()->ChangeCurrentImage(CharacterView::CharacterImage::Left);
			}
		}
		else
		{
			if(Character::Instance()->GetCharacterView()->GetCurrentImage() == CharacterView::CharacterImage::Right)
			{
				Character::Instance()->GetCharacterView()->ChangeCurrentImage(CharacterView::CharacterImage::Right2);
			}
			else
			{
				Character::Instance()->GetCharacterView()->ChangeCurrentImage(CharacterView::CharacterImage::Right);
			}
		}
	}
}

void Walking::recieveMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case CM_CHARACTER_IS_FALLING:
		if(Character::Instance()->getDirection() == Direction::Left)
		{
			Character::Instance()->GetCharacterView()->ChangeCurrentImage(CharacterView::CharacterImage::FallingLeft);
		}
		else {	
			Character::Instance()->GetCharacterView()->ChangeCurrentImage(CharacterView::CharacterImage::FallingRight);
		}
		this->pStateMachine->Transition(this->pStateMachine->falling);

		break;
	case CM_CHARACTER_BUMPS_INTO:
		Surface * surface = (Surface*)wParam;
		if(Character::Instance()->getDirection() == Direction::Right)
		{
			Character::Instance()->GetLocation()->X = surface->xFrom - Character::Instance()->GetLocation()->width;
		}
		else
		{
			Character::Instance()->GetLocation()->X = surface->xTo;
		}
		break;
	}
}