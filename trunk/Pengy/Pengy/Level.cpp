#include "Level.h"

Level* Level::pInstance = NULL;

Level* Level::Inst(){
  if(pInstance == NULL){
    pInstance = new Level();
  }
  return pInstance;
}

Level::Level(){ 
}

Level::~Level(){
  if(pInstance != 0)delete pInstance;
}

void Level::recieveMessage(string message) 
{
	//message is recieved
}
