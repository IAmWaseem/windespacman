#pragma once
#include "Observer.h"
#include "CharacterView.h"
#include "CharacterStateMachine.h"
#include "Location.h"
#include "Direction.h"
#include "GadgetView.h"

class Character : public Observer
{
protected:
	Character(void);
public:
	~Character(void);
	void ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam);
	static Character* Instance();
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
	bool CanShoot();
	GadgetView::GadgetImage GetWeaponType();
private:
	Direction direction;
	static Character * pInstance;
	CharacterView * pCharacterView;
	CharacterStateMachine * pCharacterStateMachine;
	Location * pLocation;
	int pickedupFish;
	int pickedupWeapons;
	int lives;
	bool hasSnowBoots;
	World* pWorld;
	void StartGame();
	int firstGame;
	void Throw();
	static const int reloadTime;
	int timeSinceLastReload;
	GadgetView::GadgetImage weaponType;
};
