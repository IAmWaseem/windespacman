#pragma once
#include "Observer.h"
#include "CharacterView.h"
#include "CharacterStateMachine.h"
#include "Location.h"
#include "Direction.h"

class Character : public Observer
{
protected:
	Character(void);
public:
	~Character(void);
	void recieveMessage(UINT message, WPARAM wParam, LPARAM lParam);
	static Character* Instance();
	void Update();
	Location * GetLocation();
	void SetLocation(Location * location);
	CharacterView * GetCharacterView();
	Direction getDirection();
	void setDirection(Direction direction);
private:
	Direction direction;
	static Character * pInstance;
	CharacterView * pCharacterView;
	CharacterStateMachine * pCharacterStateMachine;
	Location * location;
	int pickedupFish;
	int pickedupWeapons;
	World* world;
};
