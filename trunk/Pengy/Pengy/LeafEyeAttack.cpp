#pragma once
#include "LeafEyeAttack.h"
#include "math.h"
#include "messages.h"
#include "weapon.h"
#include "direction.h"
#include <ctime>
#include <cstdlib>
#include "character.h"

LeafEyeAttack::LeafEyeAttack(LeafEye * pLeafEye, LeafEyeStateMachine * pLeafEyeStateMachine):LeafEyeState(pLeafEye, pLeafEyeStateMachine)
{
	this->speed = 0.10f;
	this->distanceToMoveUp = 5;
	this->upwardVelocity = 0.330f;
	this->distanceToMoveDown = 5;
	this->downwardVelocity = 0;
}


LeafEyeAttack::~LeafEyeAttack(void)
{
}

void LeafEyeAttack::ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam) 
{
	switch(message) {
		case CM_UPDATE:
		timeElapsed = wParam;
		this->Update(timeElapsed);
		break;
	}
}

void LeafEyeAttack::Update(int timeElapsed) 
{
	Jump();
	pLeafEyeStateMachine->Transition(pLeafEyeStateMachine->pPatrol);
}

void LeafEyeAttack::Jump() 
{	
	Surface * pOnSurface = pLeafEye->GetOnSurface();
	Location * oldLocation = pLeafEye->GetLocation();
	Location * pPengyLocation = pLeafEye->GetPengyLocation();
	float distanceMoved = timeElapsed * this->speed;

	//jump to pengy
	if(pPengyLocation->X < oldLocation->X)
		oldLocation->X -= distanceMoved;
	else if(pPengyLocation->X > oldLocation->X)
		oldLocation->X += distanceMoved;
	
	Location * newLocation = new Location();
	newLocation->X = oldLocation->X;
	newLocation->Y = oldLocation->Y;
	newLocation->width = oldLocation->width;
	newLocation->height = oldLocation->height;

	if(upwardVelocity > 0)
	{
		//jumping
		float y = newLocation->Y;
		float newUpwardVelocity = (float)(upwardVelocity  - (0.000400 * timeElapsed));
		float averageVelocity = (upwardVelocity + newUpwardVelocity) / 2;
		float distance = averageVelocity * timeElapsed;
		newLocation->Y -= distance;
		upwardVelocity = newUpwardVelocity;

		if(distanceMoved > this->distanceToMoveUp) distanceMoved = distanceToMoveUp;
		this->distanceToMoveUp -= distanceMoved;

		switch(pLeafEye->GetDirection())
		{
		case Direction::Left:
			newLocation->X -= distanceMoved;
			break;
		case Direction::Right:
			newLocation->X += distanceMoved;
			break;
		}
		pLeafEye->SetLocation(newLocation);	
	}	
	else if(oldLocation->Y + oldLocation->height < pOnSurface->yFrom)
	{
		upwardVelocity = 0;
		//falling
		if(distanceMoved > this->distanceToMoveDown) distanceMoved = distanceToMoveDown;
		this->distanceToMoveDown -= distanceMoved;
		Location * pOldLocation = pLeafEye->GetLocation();
		Location * pNewLocation = new Location();
		pNewLocation->X = pOldLocation->X;
		pNewLocation->Y = pOldLocation->Y;
		pNewLocation->width = pOldLocation->width;
		pNewLocation->height = pOldLocation->height;

		switch(pLeafEye->GetDirection())
		{
		case Direction::Left:
			pNewLocation->X -= distanceMoved;
			break;
		case Direction::Right:
			pNewLocation->X += distanceMoved;
			break;
		}

		float newDownwardVelocity = (float)(downwardVelocity + (0.000400 * timeElapsed));
		float averageVelocity = (downwardVelocity + newDownwardVelocity) / 2;
		float distance = averageVelocity * timeElapsed;
		pLeafEye->GetLocation()->Y += distance;
		float newCharacterLocation = pLeafEye->GetLocation()->Y + distance;
		downwardVelocity = newDownwardVelocity;
		pNewLocation->Y += distance;
		pLeafEye->SetLocation(pNewLocation);
	}
	else if(oldLocation->Y + oldLocation->height >= pOnSurface->yFrom)
	{
		//opnieuw springen
		this->distanceToMoveUp = 5;
		this->upwardVelocity = 0.330f;
		this->distanceToMoveDown = 5;
		this->downwardVelocity = 0;
	}
}
