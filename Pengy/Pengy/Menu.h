#pragma once
#include "Observer.h"
#include "World.h"
#include "messages.h"
#include "MessageQueue.h"

class Menu : public Observer
{
public:
	static Menu* Inst();
    ~Menu();
    void recieveMessage(UINT message, WPARAM wParam, LPARAM lParam);
	HWND windowHandle;
protected:
	Menu();
private:
	static Menu* pInstance;
	void LoadGameMenu();
	World * world;
	MessageQueue * messageQueue;
	void OpenDialog();
	void DeleteGameMenu();
};


