#include "MessageQueue.h"
#include "Observer.h"

#pragma once

class Menu;

class World : public Observer
{
public:
	static World* Inst();
    ~World();
    void recieveMessage(UINT message, WPARAM wParam, LPARAM lParam);
	int level;
	bool menu;
protected:
	World();
private:
	static World* pInstance;
	void LoadNextLevel();
	MessageQueue* messageQueue;
	Menu* menuObject;
};