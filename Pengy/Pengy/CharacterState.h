#pragma once

class CharacterStateMachine;

class CharacterState
{
private:
	CharacterStateMachine * pStateMachine;

public:
	CharacterState(void);
	CharacterState(CharacterStateMachine * pStateMachine);
	~CharacterState(void);
	virtual void Up() = 0;
	virtual void Down() = 0;
	virtual void Left() = 0;
	virtual void Right() = 0;
	virtual void Spacebar() = 0;
	virtual void Update(int timeElapsed) = 0;
};
