#pragma once
#include "Observer.h"
#include "World.h"
#include "messages.h"
#include "MessageQueue.h"
#include "MenuView.h"

class Menu : public Observer
{
public:
	static Menu* Instance();
    ~Menu();
    void ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam);
	HWND windowHandle;
	void LoadGameMenu();
	void DeleteGameMenu();
protected:
	Menu();
private:
	static Menu* pInstance;
	World * pWorld;
	MessageQueue * pMessageQueue;
	void OpenFileDialog();
	void Update();
	View * menuView;
	void MenuClick(int x, int y);
	bool gameRunning;
	bool firstRun;
	bool menuRunning;
};


