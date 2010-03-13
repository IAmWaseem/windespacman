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
	void ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam);
	static Character* Instance();
	void Update();
	Location * GetLocation();
	void SetLocation(Location * pLocation);
	static float DistanceToMove;
	CharacterView * GetCharacterView();
	Direction GetDirection();
	void SetDirection(Direction direction);
	int GetPickedWeapons();
	int GetPickedGoldFish();
	int GetAmountLives();
	bool isKilled;
	int timeToStayKilled;
private:
	Direction direction;
	static Character * pInstance;
	CharacterView * pCharacterView;
	CharacterStateMachine * pCharacterStateMachine;
	Location * pLocation;
	int pickedupFish;
	int pickedupWeapons;
	int lives;
	World* pWorld;
	void StartGame();
};
