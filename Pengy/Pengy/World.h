#include "MessageQueue.h"
#include "Observer.h"

#pragma once

class World : public Observer
{
public:
	static World* Inst();
    ~World();
    void recieveMessage(UINT message, WPARAM wParam, LPARAM lParam);
	int level;
protected:
	World();
private:
	static World* pInstance;
	void LoadNextLevel();
	MessageQueue* messageQueue;
};