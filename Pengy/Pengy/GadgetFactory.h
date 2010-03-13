#pragma once
#include <vector>
#include "Observer.h"
#include "Gadget.h"
using namespace std;

class GadgetFactory : public Observer
{
public:
	~GadgetFactory(void);
	void ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam);
	static GadgetFactory * Instance();
protected:
	GadgetFactory(void);
private:
	vector<Gadget*> * pGadgets; 
	static GadgetFactory * pInstance;
	void StartGame();
};
