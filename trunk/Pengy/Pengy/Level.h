#pragma once
#include "Observer.h"
#include "MessageQueue.h"

class Level : public Observer
{
public:
	static Level* Inst();
    ~Level();
    void recieveMessage(UINT message);
protected:
	Level();
private:
    static Level* pInstance;
};
