#pragma once
#include "Observer.h"
#include "MessageQueue.h"
#include "LevelView.h"
#include "Tile.h"

class Level : public Observer
{
public:
	static Level* Inst();
    ~Level();
    void recieveMessage(UINT message, WPARAM wParam, LPARAM lParam);
	void LoadLevel(int level);
protected:
	Level();
private:
    static Level* pInstance;
	LevelView levelView;
	vector<int*> GetLevel1Array();
};
