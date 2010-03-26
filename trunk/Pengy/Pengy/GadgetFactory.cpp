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
	case CM_GADGETFACTORY_CREATE_SNOWBALL:
		pLocation = (Location*)wParam;
		pGadget = new Gadget(pGadgets->size(), pLocation, GadgetView::GadgetImage::SnowBall);
		pGadgets->push_back(pGadget);
		break;
	case CM_GADGETFACTORY_CREATE_SWITCH:
		pLocation = (Location*)wParam;
		pGadget = new Gadget(pGadgets->size(), pLocation, GadgetView::GadgetImage::Switch);
		pGadgets->push_back(pGadget);
		break;
	case CM_GADGETFACTORY_CREATE_EXTRALIFE:
		pLocation = (Location*)wParam;
		pGadget = new Gadget(pGadgets->size(), pLocation, GadgetView::GadgetImage::ExtraLife);
		pGadgets->push_back(pGadget);
		break;
	case CM_GADGETFACTORY_CREATE_SNOWBOOTS:
		pLocation = (Location*)wParam;
		pGadget = new Gadget(pGadgets->size(), pLocation, GadgetView::GadgetImage::SnowBoots);
		pGadgets->push_back(pGadget);
		break;
	case CM_GADGETFACTORY_CLEAR:
		pGadgets->clear();
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
		delete gadget;
		iterator++;
	}
	pGadgets->clear();
}
