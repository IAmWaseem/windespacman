#include "GadgetFactory.h"
#include "Gadget.h"

GadgetFactory * GadgetFactory::pInstance = NULL;

GadgetFactory::GadgetFactory(void)
{
	gadgets = new vector<Gadget*>();
}

GadgetFactory * GadgetFactory::Instance()
{
	if(pInstance == NULL)
		pInstance = new GadgetFactory();
	return pInstance;
}

GadgetFactory::~GadgetFactory(void)
{
}

void GadgetFactory::recieveMessage(UINT message, WPARAM wParam, LPARAM lParam) 
{
	Location * location;
	Gadget * gadget;
	int id;

	switch(message)
	{
	case CM_GAME_START:
		startGame();
		break;
	case CM_GADGETFACTORY_CREATE_GOLDFISH:
		location = (Location*)wParam;
		gadget = new Gadget(gadgets->size(), location, GadgetView::GadgetImage::Goldfish);
		gadgets->push_back(gadget);
		break;
	case CM_GADGETFACTORY_CREATE_PIRANHA:
		location = (Location*)wParam;
		gadget = new Gadget(gadgets->size(), location, GadgetView::GadgetImage::Piranha);
		gadgets->push_back(gadget);
		break;
	case CM_GADGETFACTORY_DESTROY_GADGET:
		id = (int)wParam;
		gadgets->at(id)->Remove();
		break;

	default:
		vector<Gadget*>::iterator iterator = gadgets->begin();
		while(iterator != gadgets->end())
		{
			gadget = *iterator;
			if(!gadget->IsRemoved())
			{
				gadget->recieveMessage(message, wParam, lParam);
			}
			iterator++;
		}
		break;
	}
}

void GadgetFactory::startGame()
{
	Gadget * gadget;
	vector<Gadget*>::iterator iterator = gadgets->begin();
	while(iterator != gadgets->end())
	{
		gadget = *iterator;
		gadget->~Gadget();
		iterator++;
	}
	gadgets->clear();
}