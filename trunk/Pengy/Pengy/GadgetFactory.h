#pragma once
#include <vector>
#include "Observer.h"
#include "Gadget.h"
using namespace std;

class GadgetFactory : public Observer
{
public:
	GadgetFactory(void);
	~GadgetFactory(void);
	void recieveMessage(UINT message, WPARAM wParam, LPARAM lParam);
private:
	vector<Gadget*> * gadgets; 
};
