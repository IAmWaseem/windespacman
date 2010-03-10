#pragma once
#include "Observer.h"
#include <vector>
using namespace std;

class Waldo;

class EnemyFactory : public Observer
{
public:
	static EnemyFactory * Instance();
	~EnemyFactory(void);
	void recieveMessage(UINT message, WPARAM wParam, LPARAM lParam);
protected:
	EnemyFactory(void);
private:
	vector<Waldo*> * enemies;
	static EnemyFactory * pInstance;
};