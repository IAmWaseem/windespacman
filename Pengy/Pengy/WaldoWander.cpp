#include "WaldoWander.h"

WaldoWander::WaldoWander(Waldo * pWaldo, WaldoStateMachine * pWaldoStateMachine):WaldoState(pWaldo, pWaldoStateMachine)
{
}

WaldoWander::~WaldoWander(void)
{
}


void WaldoWander::recieveMessage(UINT message, WPARAM wParam, LPARAM lParam) {

}

void WaldoWander::Update(int timeElapsed) {
}