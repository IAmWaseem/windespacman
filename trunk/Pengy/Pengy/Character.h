#pragma once
#include "Observer.h"
#include "CharacterView.h"
#include "CharacterStateMachine.h"
#include "Location.h"

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
private:
	static Character * pInstance;
	CharacterView * pCharacterView;
	CharacterStateMachine * pCharacterStateMachine;
	Location * location;
};
