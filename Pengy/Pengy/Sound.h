#pragma once

#include "Observer.h"
#include "MessageQueue.h"
#include <SDL_mixer.h>


class Sound : public Observer
{
public:
	Mix_Music* music;
	Mix_Chunk* effect;
	static Sound* Inst();
    ~Sound();
    void ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam);
protected:
	Sound();
private:
	
	static Sound* pInstance;
	
};
