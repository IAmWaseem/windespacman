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

void View::draw(HDC hDC)
{
}
