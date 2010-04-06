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

void PickedUp::ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam) 
{
}

void PickedUp::PickUp() 
{
	switch(this->pGadget->GetGadgetImage())
	{
	case GadgetView::GadgetImage::Goldfish:
		MessageQueue::Instance()->SendMessage(CM_SOUND_EVENT,(WPARAM)(LPCTSTR)"res/Waves/coin.wav", 0);
		MessageQueue::Instance()->SendMessage(CM_GADGET_GOLDFISH_PICKEDUP, NULL, NULL);
		break;
	case GadgetView::GadgetImage::Piranha:
		MessageQueue::Instance()->SendMessage(CM_SOUND_EVENT,(WPARAM)(LPCTSTR)"res/Waves/SQUEAK2.wav", 0);
		MessageQueue::Instance()->SendMessage(CM_GADGET_PIRANHA_PICKEDUP, NULL, NULL);
		break;
	case GadgetView::GadgetImage::SnowBall:
		MessageQueue::Instance()->SendMessage(CM_SOUND_EVENT,(WPARAM)(LPCTSTR)"res/Waves/coin.wav", 0);
		MessageQueue::Instance()->SendMessage(CM_GADGET_SNOWBALL_PICKEDUP, NULL, NULL);
		break;
	case GadgetView::GadgetImage::ExtraLife:
		MessageQueue::Instance()->SendMessage(CM_SOUND_EVENT,(WPARAM)(LPCTSTR)"res/Waves/1 up.wav", 0);
		MessageQueue::Instance()->SendMessage(CM_GADGET_EXTRALIFE_PICKEDUP, NULL, NULL);
		break;
	case GadgetView::GadgetImage::Switch:
		MessageQueue::Instance()->SendMessage(CM_SOUND_EVENT,(WPARAM)(LPCTSTR)"res/Waves/Pipe Warp.wav", 0);
		MessageQueue::Instance()->SendMessage(CM_GADGET_SWITCH_PICKEDUP, NULL, NULL);
		break;
	case GadgetView::GadgetImage::SnowBoots:
		MessageQueue::Instance()->SendMessage(CM_SOUND_EVENT,(WPARAM)(LPCTSTR)"res/Waves/Power Up.wav", 0);
		MessageQueue::Instance()->SendMessage(CM_GADGET_SNOWBOOTS_PICKEDUP, NULL, NULL);
		break;
	case GadgetView::GadgetImage::RottenFish:
		MessageQueue::Instance()->SendMessage(CM_SOUND_EVENT,(WPARAM)(LPCTSTR)"res/Waves/NEGATIVESOUND.wav", 0);
		MessageQueue::Instance()->SendMessage(CM_GADGET_ROTTENFISH_PICKEDUP, NULL, NULL);
	}

	pGadget->Remove();
}