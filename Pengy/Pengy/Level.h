#pragma once
#include "Observer.h"
#include "MessageQueue.h"

class Level : public Observer
{
public:
	static Level* Inst();
    ~Level();
    void recieveMessage(string message);
protected:
	Level();
private:
    static Level* pInstance;
};
