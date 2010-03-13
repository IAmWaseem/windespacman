#include "MessageQueue.h"
#include "Observer.h"

#pragma once

class Menu;

class World : public Observer
{
public:
	static World* Instance();
    ~World();
    void ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam);
	int level;
	bool menu;
protected:
	World();
private:
	static World* pInstance;
	void LoadNextLevel();
	void StartGame();
	MessageQueue* pMessageQueue;
	Menu* pMenuObject;
};