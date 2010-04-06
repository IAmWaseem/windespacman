#include "Menu.h"
#include "windowsx.h"

Menu* Menu::pInstance = NULL;

Menu* Menu::Instance(){
  if(pInstance == NULL){
    pInstance = new Menu();
  }
  return pInstance;
}

Menu::Menu()
{ 
	menuView = new MenuView();
	gameRunning = false;
	firstRun = false;
	menuRunning = false;
}

Menu::~Menu(){
  if(pInstance != 0)delete pInstance;
}

void Menu::ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam) 
 {
	 int xPos;
	 int yPos;
	 switch (message) 
	 {
	 case CM_UPDATE:
		Update();
		 break;
	 case WM_LBUTTONDBLCLK:
			xPos = GET_X_LPARAM(lParam); 
			yPos = GET_Y_LPARAM(lParam); 
			MenuClick(xPos, yPos);
		 break;
	 case CM_GAME_OVER:
			gameRunning = false;
		 break;
	 }
}

void Menu::MenuClick(int x, int y)
{
	if(x > 430)
	{
		if(y >= 0 && y < 100)
		{
			gameRunning = true;
			MessageQueue::Instance()->SendMessage(CM_UNPAUSE, NULL, NULL);
			World::Instance()->menu = false;
			if(firstRun)
				pMessageQueue->Instance()->SendMessage(CM_GAME_RESTART, NULL, NULL);
			else
				MessageQueue::Instance()->SendMessage(CM_GAME_START, NULL, NULL);
			firstRun = true;
		}
	}
}

void Menu::Update()
{
	if(pWorld->Instance()->menu && !menuRunning)
	{
		MessageQueue::Instance()->SendMessage(CM_PAUSE, NULL, NULL);
		menuView->RegisterToGraphics();
		menuRunning = true;
	}
	else if(!pWorld->Instance()->menu)
	{
		if(!gameRunning)
		{
			pWorld->Instance()->menu = true;
		}
		else
		{
			menuView->UnRegisterToGraphics();
			MessageQueue::Instance()->SendMessage(CM_UNPAUSE, NULL, NULL);
			menuRunning = false;
		}
	}
}

void Menu::LoadGameMenu()
{
	if(pWorld->Instance()->menu)
	{
		HMENU hMenu;
		HMENU hSubMenu;
		
		hMenu = CreateMenu();  

		hSubMenu = CreatePopupMenu();  
		AppendMenu(hSubMenu, MF_STRING, CM_GAME_NEW, "&New");  
		AppendMenu(hSubMenu, MF_STRING, CM_GAME_OPEN, "&Open");  
		AppendMenu(hSubMenu, MF_STRING, CM_GAME_SAVE, "&Save");  
		AppendMenu(hSubMenu, MF_SEPARATOR, 0, 0);  
		AppendMenu(hSubMenu, MF_STRING, CM_GAME_EXIT, "E&xit");  
		AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&Game");

		hSubMenu = CreatePopupMenu();  
		AppendMenu(hSubMenu, MF_STRING, CM_GAME_ABOUT, "&About");  
		AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&Help");  
		SetMenu(windowHandle, hMenu);  
	}
}

void Menu::DeleteGameMenu()
{
	HMENU emptyMenu;
	emptyMenu = CreateMenu();
	SetMenu(windowHandle, emptyMenu);
}

void Menu::OpenFileDialog()
{
	OPENFILENAME ofn;
    char szFileName[MAX_PATH] = "";

    ZeroMemory(&ofn, sizeof(ofn));

    ofn.lStructSize = sizeof(ofn); 
	ofn.hwndOwner = windowHandle;
    ofn.lpstrFilter = "Text Files (*.txt)\0*.txt\0";
    ofn.lpstrFile = szFileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
    ofn.lpstrDefExt = "txt";

    if(GetOpenFileName(&ofn))
    {
        // Do something usefull with the filename stored in szFileName 
		DeleteGameMenu();
    }
}
