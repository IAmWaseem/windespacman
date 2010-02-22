#pragma once
class CharacterState;

class CharacterStateMachine
{
private:
	CharacterState * pCurrentState;

public:
	CharacterStateMachine(void);
	~CharacterStateMachine(void);
	void Up();
	void Down();
	void Left();
	void Right();
	void Spacebar();
	void Update(int timeElapsed);
	void Transition(CharacterState * pCharacterState);
};
