#include "Sliding.h"

Sliding::Sliding(void)
{

}

Sliding::Sliding(CharacterStateMachine * pStateMachine)  : CharacterState(pStateMachine)
{
	pSlopes = NULL;
	this->speed = 0.1f;
}

void Sliding::Up()
{

}

void Sliding::Down()
{

}

void Sliding::Left()
{

}

void Sliding::Right()
{

}

void Sliding::Throw()
{

}

void Sliding::Spacebar()
{
	this->speed = 0.1f;
	this->pStateMachine->pJumping->Spacebar();
	this->pStateMachine->pJumping->Right();
	this->pStateMachine->Transition(this->pStateMachine->pJumping);
}

void Sliding::Update(int timeElapsed)
{
	if(pSlopes != NULL)
	{
		speed *= 1.03;
		float distanceMoved = timeElapsed * speed;
		Location * characterLocation = Character::Instance()->GetLocation();
		Surface * currentSlope = CurrentSlope(characterLocation);
		if(currentSlope == NULL)
		{
			this->speed = 0.1f;
			pStateMachine->Transition(pStateMachine->pWalking);
			return;
		}	
		Surface * nextSlope = NextSlope(currentSlope);
		float newX = characterLocation->X + distanceMoved;
		float newY = 0;
		if(newX > currentSlope->xTo)
			newY = CalculateYOnSlope(newX + characterLocation->width, nextSlope);
		else
			newY = CalculateYOnSlope(newX + characterLocation->width, currentSlope);
		characterLocation->X = newX;
		characterLocation->Y = newY - (0.75 * characterLocation->height);
	}
}

void Sliding::ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	
}

void Sliding::SetSlopes(vector<Surface*> * pSlopes)
{
	Character::Instance()->GetCharacterView()->ChangeCurrentImage(CharacterView::CharacterImage::Sliding);
	this->pSlopes = pSlopes;
}

Surface * Sliding::CurrentSlope(Location * location)
{
	int center = location->X + location->width;
	vector<Surface*>::iterator iterator = pSlopes->begin();
	while(iterator != pSlopes->end())
	{
		Surface * tempSurface = *iterator;
		if(tempSurface->xFrom <= center && tempSurface->xTo >= center)
			return tempSurface;
		iterator++;
	}
	return NULL;
}

Surface * Sliding::NextSlope(Surface * slope)
{
	vector<Surface*>::iterator iterator = pSlopes->begin();
	while(iterator != pSlopes->end())
	{
		Surface * tempSurface = *iterator;
		if(tempSurface->xFrom == slope->xTo)
			return tempSurface;
		iterator++;
	}
	return NULL;
}

float Sliding::CalculateYOnSlope(float x, Surface * slope)
{
	float yRange = (slope->yTo - slope->yFrom);
	float xRange = (slope->xTo - slope->xFrom);
	float deltaY = yRange / xRange;
	return ((x - slope->xFrom) * deltaY) + slope->yFrom;
}