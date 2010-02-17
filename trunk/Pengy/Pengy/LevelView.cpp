#include "LevelView.h"

LevelView::LevelView(){ 
	registerToGraphics();
}

LevelView::~LevelView(){
	unRegisterToGraphics();
}

void LevelView::Draw(HDC hDC) 
{
	vector<int*>::iterator iterator = myTiles.begin();
	while(iterator!=myTiles.end())
	{
		int * tile = *iterator;
		//doe wat met de tile
		iterator++;
	}
}

void LevelView::SetTiles(vector<int*> tiles)
{
	myTiles = tiles;
}