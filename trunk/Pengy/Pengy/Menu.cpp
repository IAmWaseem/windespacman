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
	case CM_MENU_LOAD:
		LoadGameMenu();
		break;
	}
}

void Menu::LoadGameMenu()
{
	//HMENU menuHandle = CreateMenu();
	////menuHandle = GetMenu(windowHandle);
	//LPMENUITEMINFO item1;
	//item1->dwTypeData = "test";
	//bool itemIsAdded = InsertMenuItem(menuHandle, 1, false, item1);
	//bool isSet = SetMenu(windowHandle, menuHandle);
	//bool isDestroyed = DestroyMenu(menuHandle);
}
