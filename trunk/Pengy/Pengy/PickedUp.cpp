#include "PickedUp.h"
#include "Gadget.h"

PickedUp::PickedUp(void)
{
}

PickedUp::~PickedUp(void)
{
}

PickedUp::PickedUp(GadgetStateMachine * pStateMachine, Gadget * gadget) : GadgetState(pStateMachine, gadget)
{
}

void PickedUp::Update(int timeElapsed) {
}

void PickedUp::recieveMessage(UINT message, WPARAM wParam, LPARAM lParam) 
{
}

void PickedUp::PickUp() 
{
	switch(this->pGadget->GetGadgetImage())
	{
	case GadgetView::GadgetImage::Goldfish:
		MessageQueue::Inst()->sendMessage(CM_GADGET_GOLDFISH_PICKEDUP, NULL, NULL);
		break;

	case GadgetView::GadgetImage::Piranha:
		MessageQueue::Inst()->sendMessage(CM_GADGET_PIRANHA_PICKEDUP, NULL, NULL);
		break;
	}
	
	MessageQueue::Inst()->sendMessage(CM_GADGETFACTORY_DESTROY_GADGET, pGadget->GetId(), NULL);
}