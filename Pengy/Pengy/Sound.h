#pragma once

#include "Observer.h"
#include "MessageQueue.h"


class Sound : public Observer
{
public:
	static Sound* Inst();
    ~Sound();
    void recieveMessage(UINT message, WPARAM wParam, LPARAM lParam);
protected:
	Sound();
private:
	static Sound* pInstance;
	
};
