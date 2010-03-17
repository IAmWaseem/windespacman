#include "Walking.h"
#include "Character.h"
#include "CharacterView.h"
#include "CharacterStateMachine.h"
#include "Idle.h"
#include "Jumping.h"

Walking::Walking(void)
{
	this->speed = 0.18f;
	this->moved = 0;
}

Walking::Walking(CharacterStateMachine * pStateMachine) : CharacterState(pStateMachine)
{
	this->speed = 0.18f;
	this->moved = 0;
}

void Walking::Up()
{

}

void Walking::Down()
{
	this->pStateMachine->Transition(this->pStateMachine->pFalling);
}


void Walking::Left()
{
	if(Character::Instance()->GetDirection() != Direction::Left)
	{
		Character::Instance()->GetCharacterView()->ChangeCurrentImage(CharacterView::CharacterImage::Left);
	}
	Character::Instance()->SetDirection(Direction::Left);
	this->distanceToMove = 5;
}


void Walking::Right()
{
	if(Character::Instance()->GetDirection() != Direction::Right) 
	{
		Character::Instance()->GetCharacterView()->ChangeCurrentImage(CharacterView::CharacterImage::Right);
	}
	Character::Instance()->SetDirection(Direction::Right);
	this->distanceToMove = 5;
}

void Walking::Throw()
{

}


void Walking::Spacebar()
{
	this->pStateMachine->pJumping->Spacebar();
	if(this->distanceToMove > 0.5)
	{
		if(Character::Instance()->GetDirection()  == Direction::Left)
			this->pStateMachine->pJumping->Left();
		else
			this->pStateMachine->pJumping->Right();
	}
	this->pStateMachine->Transition(this->pStateMachine->pJumping);
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
	switch(Character::Instance()->GetDirection())
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
	
	MessageQueue::Instance()->SendMessage(CM_CHARACTER_MOVE_X_FROM_TO,  (int)oldLocation, (int)newLocation);
	MessageQueue::Instance()->SendMessage(CM_CHARACTER_FALL_Y_FROM_TO,  (int)oldLocation, (int)newLocation);

	SwapPicture();
	
	if(distanceToMove == 0)
	{
		this->pStateMachine->Transition(this->pStateMachine->pIdle);
	}
}

void Walking::SwapPicture()
{
	if((int)this->moved % 15 < 1)
	{
		this->moved = 0;
		if(Character::Instance()->GetDirection() == Direction::Left)
		{
			if(Character::Instance()->GetCharacterView()->GetCurrentImage() == CharacterView::CharacterImage::Left)
			{
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

void Walking::ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case CM_CHARACTER_IS_FALLING:
		if(Character::Instance()->GetDirection() == Direction::Left)
		{
			Character::Instance()->GetCharacterView()->ChangeCurrentImage(CharacterView::CharacterImage::FallingLeft);
		}
		else 
		{	
			Character::Instance()->GetCharacterView()->ChangeCurrentImage(CharacterView::CharacterImage::FallingRight);
		}
		this->pStateMachine->Transition(this->pStateMachine->pFalling);

		break;
	case CM_CHARACTER_BUMPS_INTO:
		Surface * pSurface = (Surface*)wParam;
		if(((Character::Instance()->GetLocation()->X + Character::Instance()->GetLocation()->width) >= pSurface->xFrom) && pSurface->xTo > (Character::Instance()->GetLocation()->X + Character::Instance()->GetLocation()->width))
		{
			Character::Instance()->GetLocation()->X = pSurface->xFrom - Character::Instance()->GetLocation()->width;
		}
		else
		{
			Character::Instance()->GetLocation()->X = (float)pSurface->xTo;
		}
		break;
	}
}