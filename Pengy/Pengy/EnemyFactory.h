#pragma once
#include "Observer.h"
#include <vector>
using namespace std;

class Enemy;

class EnemyFactory : public Observer
{
public:
	static EnemyFactory * Instance();
	~EnemyFactory(void);
	void ReceiveMessage(UINT message, WPARAM wParam, LPARAM lParam);
	void StartGame();
	static bool SendMessagesToChildren;
	vector<Enemy*> * GetEnemies();
protected:
	EnemyFactory(void);
private:
	vector<Enemy*> * pEnemies;
	static EnemyFactory * pInstance;
	void CleanUp();
};