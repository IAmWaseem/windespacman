#pragma once
#include "Observer.h"

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
};
