#include "WaldoAttack.h"

WaldoAttack::WaldoAttack(Waldo * pWaldo, WaldoStateMachine * pWaldoStateMachine):WaldoState(pWaldo, pWaldoStateMachine)
{

}


WaldoAttack::~WaldoAttack(void)
{
}

void WaldoAttack::recieveMessage(UINT message, WPARAM wParam, LPARAM lParam) {

	switch(message)  {
	}
}

void WaldoAttack::Update(int timeElapsed) {
}