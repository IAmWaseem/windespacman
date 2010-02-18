#pragma once
#include "Observer.h"
#include "CharacterView.h"

class Character : public Observer
{
protected:
	Character(void);
public:
	~Character(void);
	void recieveMessage(UINT message, WPARAM wParam, LPARAM lParam);
	static Character* Instance();
	void Update();
	int GetLocationX();
	int GetLocationY();
	void SetLocationX(int x);
	void SetLocationY(int y);
	int GetWidth();
	int GetHeight();
	void SetWidth(int width);
	void SetHeight(int height);
private:
	static Character * pInstance;
	CharacterView * characterView;
	int locationX;
	int locationY;
	int width;
	int height;
};
