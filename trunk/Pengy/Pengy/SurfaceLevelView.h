#pragma once
#include "View.h"
#include <vector>
using namespace std;
#include "Surface.h"

class SurfaceLevelView : public View
{
public:
	SurfaceLevelView(void);
	SurfaceLevelView(vector<Surface*> * surfaces);
	~SurfaceLevelView(void);
	void Draw(HDC hdc, int xFrom, int xTo);
private:
	vector<Surface*> * surfaces;
};
