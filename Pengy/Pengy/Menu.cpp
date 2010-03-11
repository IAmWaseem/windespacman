#include "Menu.h"

Menu* Menu::pInstance = NULL;

Menu* Menu::Inst(){
  if(pInstance == NULL){
    pInstance = new Menu();
  }
  return pInstance;
}

Menu::Menu()
{ 
}

Menu::~Menu(){
  if(pInstance != 0)delete pInstance;
}

void Menu::recieveMessage(UINT message, WPARAM wParam, LPARAM lParam) 
 {
	 switch (message) 
	 {
	 case CM_GAME_NEW:
		 messageQueue->Inst()->sendMessage(CM_GAME_START, NULL, NULL);
		 DeleteGameMenu();
		 world->Inst()->menu = false;
		 break;
	 case CM_GAME_OPEN:
		 OpenFileDialog();
		 break;
	 case CM_GAME_SAVE:
		 MessageBox(windowHandle, "Save", "Menu", 0); 
		 break;
	 case CM_GAME_EXIT:
		 PostQuitMessage(0); 
	 case CM_GAME_ABOUT:
		 MessageBox(windowHandle, "About", "Menu", 0); 
		 break;	
	 }
}

void Menu::LoadGameMenu()
{
	if(world->Inst()->menu)
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
