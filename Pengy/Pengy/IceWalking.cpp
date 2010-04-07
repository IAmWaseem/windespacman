#include "Walking.h"
#include "Character.h"
#include "CharacterView.h"
#include "CharacterStateMachine.h"
#include "Idle.h"
#include "Jumping.h"
#include "Sliding.h"
#include "IceWalking.h"

IceWalking::IceWalking(void)
{
	this->speed = 0.9f;
	this->moved = 0;
}

IceWalking::IceWalking(CharacterStateMachine * pStateMachine) : CharacterState(pStateMachine)
{
	this->speed = 0.9f;
	this->moved = 0;
}

void IceWalking::Up()
{

}

void IceWalking::Down()
{
	//this->pStateMachine->Transition(this->pStateMachine->pFalling);
	this->distanceToMove = 0;
	this->speed = 0;
}


void IceWalking::Left()
{
	if(Character::Instance()->GetDirection() != Direction::Left)
	{
		Character::Instance()->GetCharacterView()->ChangeCurrentImage(CharacterView::CharacterImage::Left);
		this->speed *= 0.90;
		SwapPicture();
	}
	else
		this->speed *= 1.10;
	if (this->speed <= 0.05f)
	{
	Character::Instance()->SetDirection(Direction::Left);
	this->speed = 0.06f;
	}
}


void IceWalking::Right()
{
	if(Character::Instance()->GetDirection() != Direction::Right) 
	{
		Character::Instance()->GetCharacterView()->ChangeCurrentImage(CharacterView::CharacterImage::Right);
		this->speed *= 0.90;
		SwapPicture();
	}
	else
		this->speed *= 1.10;
	if (this->speed <= 0.05f)
	{
	Character::Instance()->SetDirection(Direction::Right);
	this->speed = 0.06f;
	}
}

void IceWalking::Throw()
{
	this->speed = 0.9f;
	this->moved = 0;
}


void IceWalking::Spacebar()
{
	this->pStateMachine->pJumping->Spacebar();
	this->pStateMachine->Transition(this->pStateMachine->pJumping);
}

void IceWalking::Update(int timeElapsed)
{
	this->distanceToMove = 5;
	this->speed *= 0.95;
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
}

void IceWalking::SwapPicture()
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

void IceWalking::ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	Surface * pSurface;
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
		pSurface = (Surface*)wParam;
		if(((Character::Instance()->GetLocation()->X + Character::Instance()->GetLocation()->width) >= pSurface->xFrom) && pSurface->xTo > (Character::Instance()->GetLocation()->X + Character::Instance()->GetLocation()->width))
		{
			Character::Instance()->GetLocation()->X = pSurface->xFrom - Character::Instance()->GetLocation()->width;
		}
		else
		{
			Character::Instance()->GetLocation()->X = (float)pSurface->xTo;
		}
		break;
	case CM_CHARACTER_IS_STANDING:
		pSurface = (Surface*) wParam;
		if(pSurface->isSurfaceOfDeath)
		{
			MessageQueue::Instance()->SendMessage(CM_CHARACTER_KILLED, NULL, NULL);
			break;
		}
		if(pSurface->isSlope != 0)
		{
			vector<Surface*> * slopes = (vector<Surface*>*) lParam;
			Sliding * sliding = (Sliding*)pStateMachine->pSliding;
			sliding->SetSlopes(slopes);
			pStateMachine->Transition(pStateMachine->pSliding);
			break;
		}
		Character::Instance()->GetLocation()->Y = pSurface->yFrom - Character::Instance()->GetLocation()->height;
		break;
	}
}