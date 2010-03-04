#include "GadgetFactory.h"
#include "Gadget.h"

GadgetFactory::GadgetFactory(void)
{
	gadgets = new vector<Gadget*>();
}

GadgetFactory::~GadgetFactory(void)
{
}

void GadgetFactory::recieveMessage(UINT message, WPARAM wParam, LPARAM lParam) 
{
	Location * location;
	Gadget * gadget;
	vector<Gadget*>::iterator iterator;
	int id;

	switch(message)
	{
	case CM_GADGETFACTORY_CREATE_GOLDFISH:
		location = (Location*)wParam;
		gadget = new Gadget(gadgets->size(), location, GadgetView::GadgetImage::Goldfish);
		gadgets->push_back(gadget);
		break;
	case CM_GADGETFACTORY_CREATE_PIRANHA:
		gadget = new Gadget(gadgets->size(), location, GadgetView::GadgetImage::Piranha);
		gadgets->push_back(gadget);
		break;
	case CM_GADGETFACTORY_DESTROY_GADGET:
		id = (int)wParam;
		gadgets->at(id)->Remove();
		break;

	default:
		iterator = gadgets->begin();
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
