#include "WaldoPatrol.h"

WaldoPatrol::WaldoPatrol(Waldo * pWaldo, WaldoStateMachine * pWaldoStateMachine):WaldoState(pWaldo, pWaldoStateMachine)
{
}


WaldoPatrol::~WaldoPatrol(void)
{
}

void WaldoPatrol::recieveMessage(UINT message, WPARAM wParam, LPARAM lParam) 
{
	int timeElapsed;

	switch(message) {
		case CM_UPDATE:
		timeElapsed = wParam;
		this->Update(timeElapsed);
		break;
	}
}

void WaldoPatrol::Update(int timeElapsed) 
{

}