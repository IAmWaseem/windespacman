#pragma once
#include "characterstate.h"

class Sliding : public CharacterState
{
private:
	float speed;
	vector<Surface*> * pSlopes;
	Surface * CurrentSlope(Location * location);
	Surface * NextSlope(Surface * slope);
	float CalculateYOnSlope(float x, Surface * slope);

public:
	Sliding(void);
	Sliding(CharacterStateMachine * pStateMachine);
	void Up();
	void Down();
	void Left();
	void Right();
	void Throw();
	void Spacebar();
	void Update(int timeElapsed);
	void ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam);
	void SetSlopes(vector<Surface*> * pSlopes);
};
