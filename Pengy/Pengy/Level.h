#pragma once
#include "Observer.h"
#include "MessageQueue.h"
#include "LevelView.h"

class Level : public Observer
{
public:
	static Level* Inst();
    ~Level();
    void recieveMessage(UINT message);
	void LoadLevel(int level);
protected:
	Level();
private:
    static Level* pInstance;
	LevelView levelView;
};