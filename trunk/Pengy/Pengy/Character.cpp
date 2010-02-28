#include "Character.h"
#include "CharacterView.h"
#include <iostream>
using namespace std;

Character* Character::pInstance = NULL;

Character::Character(void)
{
	location = new Location();
	location->X = 1000;
	location->Y = 100;
	location->width = 100;
	location->height = 100;
	pCharacterStateMachine = new CharacterStateMachine();
}

Character::~Character(void)
{
}

void Character::recieveMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	this->pCharacterStateMachine->recieveMessage(message, wParam, lParam);

	ULONGLONG timeElapsed;
	switch (message) 
	{
	case CM_LEVEL_START:
		pCharacterView = new CharacterView();
		pCharacterView->LoadImage(CharacterView::CharacterImage::Left, "res/PengyWinterLeft.bmp");
		pCharacterView->LoadImage(CharacterView::CharacterImage::Left2, "res/PengyWinterLeft2.bmp");
		pCharacterView->LoadImage(CharacterView::CharacterImage::Right, "res/PengyWinterRight.bmp");
		pCharacterView->LoadImage(CharacterView::CharacterImage::Right2, "res/PengyWinterRight2.bmp");
		pCharacterView->LoadImage(CharacterView::CharacterImage::Climb, "res/PengyClimb.bmp");
		pCharacterView->LoadImage(CharacterView::CharacterImage::Climb2, "res/PengyClimb2.bmp");
		pCharacterView->LoadImage(CharacterView::CharacterImage::Jump, "res/PengyJump.bmp");
		pCharacterView->LoadImage(CharacterView::CharacterImage::Sliding, "res/PengySliding.bmp");
		pCharacterView->LoadImage(CharacterView::CharacterImage::Sliding2, "res/PengySliding2.bmp");
		pCharacterView->ChangeCurrentImage(CharacterView::CharacterImage::Right);
		pCharacterView->registerToGraphics();
		MessageQueue::Inst()->sendMessage(CM_CHARACTER_MOVE_X_FROM_TO, (int)location, (int)location);
		MessageQueue::Inst()->sendMessage(CM_CHARACTER_MOVE_Y_FROM_TO, (int)location, (int)location);
		break;

	case CM_UPDATE:
		timeElapsed = wParam;
		pCharacterStateMachine->Update(timeElapsed);
		break;

	case CM_CHARACTER_SPACEBAR:
		pCharacterStateMachine->Spacebar();
		break;

	case CM_CHARACTER_UP:
		pCharacterStateMachine->Up();
		break;

	case CM_CHARACTER_DOWN:
		pCharacterStateMachine->Down();
		break;

	case CM_CHARACTER_LEFT:
		pCharacterStateMachine->Left();
		break;

	case CM_CHARACTER_RIGHT:
		pCharacterStateMachine->Right();
		break;
	}
}

Character* Character::Instance()
{
	if(pInstance == NULL){
		pInstance = new Character();
	}
	return pInstance;
}

void Character::Update()
{

}

Location * Character::GetLocation()
{
	return location;
}


void Character::SetLocation(Location * location)
{
	this->location = location;
}

CharacterView * Character::GetCharacterView()
{
	return this->pCharacterView;
}
