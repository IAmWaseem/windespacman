#include "Renderer.h"
#include "View.h"

Renderer* Renderer::pInstance = NULL;

Renderer* Renderer::Inst(){
  if(pInstance == NULL){
    pInstance = new Renderer();
  }
  return pInstance;
}

Renderer::Renderer(){ 
}

Renderer::~Renderer(){
  if(pInstance != 0)delete pInstance;
}

void Renderer::attach( View *myView)
{
    myViews.push_back( myView);
}

void Renderer::detach( View *myView)
{
    for (int i= 0; i< myViews.size(); i++)
    {
        if (myViews[i]== myView)
        {
            myViews.erase(myViews.begin()+i);
            return;
        }
    }
}

void Renderer::render(HDC hdc)
{
    for (int i= 0; i< myViews.size(); i++)
    {
        myViews[i]->draw(hdc);
    }
}