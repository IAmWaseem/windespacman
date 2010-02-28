#include "View.h"
#include "Renderer.h"

View::View()
{
}

View::~View()
{
}

void View::registerToGraphics()
{
	renderer->Inst()->attach(this);
}

void View::unRegisterToGraphics()
{
	renderer->Inst()->detach(this);
}

void View::Draw(HDC hDC, int xFrom, int xTo)
{
}
