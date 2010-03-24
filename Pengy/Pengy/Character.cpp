#include "Character.h"
#include "CharacterView.h"
#include <iostream>
using namespace std;

Character* Character::pInstance = NULL;
float Character::DistanceToMove = 1.5f;

Character::Character(void)
{
	pLocation = new Location();
	pLocation->X = 50;
	pLocation->Y = 200;
	pLocation->width = 50;
	pLocation->height = 96;
	pCharacterStateMachine = new CharacterStateMachine();
	direction = Direction::Right;
	pickedupFish = 0;
	pickedupWeapons = 0;
	lives = 4;
	timeToStayKilled = 0;
	isKilled = false;
	firstGame = 0;
}

Character::~Character(void)
{
}

void Character::ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	this->pCharacterStateMachine->ReceiveMessage(message, wParam, lParam);

	int timeElapsed;
	switch (message) 
	{
	case CM_GAME_START:
		StartGame();
		firstGame = 1;
		break;
	case CM_LEVEL_LOAD:
		StartGame();
		switch(pWorld->Instance()->level)
		{
		case 1:
			pCharacterView->LoadCVImage(CharacterView::CharacterImage::Left, "res/PengySummerLeft.bmp");
			pCharacterView->LoadCVImage(CharacterView::CharacterImage::Left2, "res/PengySummerLeft2.bmp");
			pCharacterView->LoadCVImage(CharacterView::CharacterImage::Right, "res/PengySummerRight.bmp");
			pCharacterView->LoadCVImage(CharacterView::CharacterImage::Right2, "res/PengySummerRight2.bmp");
			pCharacterView->LoadCVImage(CharacterView::CharacterImage::FallingLeft, "res/PengySummerFallingLeft.bmp");
			pCharacterView->LoadCVImage(CharacterView::CharacterImage::FallingRight, "res/PengySummerFallingRight.bmp");
			pCharacterView->LoadCVImage(CharacterView::CharacterImage::JumpLeft, "res/PengySummerJump2.bmp");
			pCharacterView->LoadCVImage(CharacterView::CharacterImage::JumpRight, "res/PengySummerJump.bmp");
			break;
		case 2:
			pCharacterView->LoadCVImage(CharacterView::CharacterImage::Left, "res/PengyWinterLeft.bmp");
			pCharacterView->LoadCVImage(CharacterView::CharacterImage::Left2, "res/PengyWinterLeft2.bmp");
			pCharacterView->LoadCVImage(CharacterView::CharacterImage::Right, "res/PengyWinterRight.bmp");
			pCharacterView->LoadCVImage(CharacterView::CharacterImage::Right2, "res/PengyWinterRight2.bmp");
			pCharacterView->LoadCVImage(CharacterView::CharacterImage::FallingLeft, "res/PengyWinterFallingLeft.bmp");
			pCharacterView->LoadCVImage(CharacterView::CharacterImage::FallingRight, "res/PengyWinterFallingRight.bmp");
			pCharacterView->LoadCVImage(CharacterView::CharacterImage::JumpLeft, "res/PengyWinterJump2.bmp");
			pCharacterView->LoadCVImage(CharacterView::CharacterImage::JumpRight, "res/PengyWinterJump.bmp");
			break;
		case 3:
			pCharacterView->LoadCVImage(CharacterView::CharacterImage::Left, "res/PengyAutumnLeft.bmp");
			pCharacterView->LoadCVImage(CharacterView::CharacterImage::Left2, "res/PengyAutumnLeft2.bmp");
			pCharacterView->LoadCVImage(CharacterView::CharacterImage::Right, "res/PengyAutumnRight.bmp");
			pCharacterView->LoadCVImage(CharacterView::CharacterImage::Right2, "res/PengyAutumnRight2.bmp");
			pCharacterView->LoadCVImage(CharacterView::CharacterImage::JumpLeft, "res/PengyAutumnJump2.bmp");
			pCharacterView->LoadCVImage(CharacterView::CharacterImage::JumpRight, "res/PengyAutumnJump.bmp");
			pCharacterView->LoadCVImage(CharacterView::CharacterImage::FallingLeft, "res/PengyAutumnFallingLeft.bmp");
			pCharacterView->LoadCVImage(CharacterView::CharacterImage::FallingRight, "res/PengyAutumnFallingRight.bmp");
			break;
		}
		
		pCharacterView->LoadCVImage(CharacterView::CharacterImage::Climb, "res/PengyClimb.bmp");
		pCharacterView->LoadCVImage(CharacterView::CharacterImage::Climb2, "res/PengyClimb2.bmp");
		pCharacterView->LoadCVImage(CharacterView::CharacterImage::Sliding, "res/PengySliding.bmp");
		pCharacterView->LoadCVImage(CharacterView::CharacterImage::Sliding2, "res/PengySliding2.bmp");
		pCharacterView->ChangeCurrentImage(CharacterView::CharacterImage::Right);
		pCharacterView->RegisterToGraphics();
		MessageQueue::Instance()->SendMessage(CM_CHARACTER_MOVE_X_FROM_TO, (int)pLocation, (int)pLocation);
		MessageQueue::Instance()->SendMessage(CM_CHARACTER_FALL_Y_FROM_TO, (int)pLocation, (int)pLocation);
		pickedupWeapons = 0;
		break;

	case CM_UPDATE:
		MessageQueue::Instance()->SendMessage(CM_CHARACTER_MOVE_X_FROM_TO, (int)pLocation, (int)pLocation);
		MessageQueue::Instance()->SendMessage(CM_CHARACTER_FALL_Y_FROM_TO, (int)pLocation, (int)pLocation);
		timeElapsed = wParam;
		pCharacterStateMachine->Update(timeElapsed);
		if(isKilled) {
			this->timeToStayKilled = timeToStayKilled - timeElapsed;
			if(timeToStayKilled < 0) {
				isKilled = false;
			}
		}
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
	case CM_GADGET_GOLDFISH_PICKEDUP:
		pickedupFish++;
		break;

	case CM_CHARACTER_RESET_POSITION:
		if(wParam != NULL)
			pLocation->X = (float)wParam;

		if(lParam != NULL)
			pLocation->Y = (float)lParam;

		MessageQueue::Instance()->SendMessage(CM_CHARACTER_MOVE_X_FROM_TO, (int)pLocation, (int)pLocation);
		MessageQueue::Instance()->SendMessage(CM_CHARACTER_FALL_Y_FROM_TO, (int)pLocation, (int)pLocation);
		break;

	case CM_GADGET_PIRANHA_PICKEDUP:
		pickedupWeapons++;
		break;

	case CM_CHARACTER_GET_LOCATION:
		MessageQueue::Instance()->SendMessage(CM_CHARACTER_RETURN_LOCATION, (int)pLocation, NULL);
		break;

	case CM_CHARACTER_KILLED:
		if(!isKilled) {
			this->lives--;
			this->isKilled = true;
			this->timeToStayKilled = 2000;

			if(this->lives == 0) {
				pCharacterView->UnRegisterToGraphics();
			}
		}
		MessageQueue::Instance()->SendMessage(CM_CHARACTER_RESET_POSITION, 50, 200);
		pCharacterView->RegisterToGraphics();
		break;

	case CM_GADGET_SNOWBALL_PICKEDUP:
		pickedupWeapons++;
		break;
	case CM_GADGET_EXTRALIFE_PICKEDUP:
		lives++;
		break;
	case CM_GADGET_SWITCH_PICKEDUP:
		MessageQueue::Instance()->SendMessage(CM_WINTERLEVEL_OPEN_BRIDGE, NULL, NULL);
		break;
	case CM_GADGET_SNOWBOOTS_PICKEDUP:
		hasSnowBoots = true;
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
	return pLocation;
}

void Character::SetLocation(Location * pLocation)
{
	this->pLocation = pLocation;
}

CharacterView * Character::GetCharacterView()
{
	return this->pCharacterView;
}

Direction Character::GetDirection()
{
	return direction;
}

int Character::GetPickedWeapons() {
	return this->pickedupWeapons;
}

int Character::GetPickedGoldFish() {
	return this->pickedupFish;
}

int Character::GetAmountLives() {
	return this->lives;
}

void Character::SetDirection(Direction direction)
{
	this->direction = direction;
}


void Character::StartGame()
{
	if(firstGame==1)
	{
		delete pCharacterView;
		pCharacterView->UnRegisterToGraphics();
		delete pLocation;
		delete pCharacterStateMachine;
	}
	pCharacterView = new CharacterView();
	pLocation = new Location();
	pLocation->X = 50;
	pLocation->Y = 200;
	pLocation->width = 50;
	pLocation->height = 96;
	pCharacterStateMachine = new CharacterStateMachine();
	direction = Direction::Right;
	lives=4;
	pickedupFish = 0;
	pickedupWeapons = 0;
}