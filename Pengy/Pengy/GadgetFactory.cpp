#include "GadgetFactory.h"
#include "Gadget.h"

GadgetFactory * GadgetFactory::pInstance = NULL;

GadgetFactory::GadgetFactory(void)
{
	pGadgets = new vector<Gadget*>();
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

void GadgetFactory::ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam) 
{
	Location * pLocation;
	Gadget * pGadget;
	int id;

	switch(message)
	{
	case CM_GAME_START:
		StartGame();
		break;
	case CM_GADGETFACTORY_CREATE_GOLDFISH:
		pLocation = (Location*)wParam;
		pGadget = new Gadget(pGadgets->size(), pLocation, GadgetView::GadgetImage::Goldfish);
		pGadgets->push_back(pGadget);
		break;
	case CM_GADGETFACTORY_CREATE_PIRANHA:
		pLocation = (Location*)wParam;
		pGadget = new Gadget(pGadgets->size(), pLocation, GadgetView::GadgetImage::Piranha);
		pGadgets->push_back(pGadget);
		break;
	case CM_GADGETFACTORY_DESTROY_GADGET:
		id = (int)wParam;
		pGadgets->at(id)->Remove();
		break;

	default:
		vector<Gadget*>::iterator iterator = pGadgets->begin();
		while(iterator != pGadgets->end())
		{
			pGadget = *iterator;
			if(!pGadget->IsRemoved())
			{
				pGadget->ReceiveMessage(message, wParam, lParam);
			}
			iterator++;
		}
		break;
	}
}

void GadgetFactory::StartGame()
{
	Gadget * gadget;
	vector<Gadget*>::iterator iterator = pGadgets->begin();
	while(iterator != pGadgets->end())
	{
		gadget = *iterator;
		gadget->~Gadget();
		iterator++;
	}
	pGadgets->clear();
}
