#pragma once
#include "Surface.h"
#include "Observer.h"
#include "MessageQueue.h"
#include "SurfaceLevelView.h"

class SurfaceLevel : public Observer
{
public:
	static SurfaceLevel* Inst();
    ~SurfaceLevel();
    void recieveMessage(UINT message, WPARAM wParam, LPARAM lParam);
protected:
	SurfaceLevel();
private:
	void SetLevelLength();
	vector<Surface*> * surfaces;
    static SurfaceLevel* pInstance;
	SurfaceLevelView * surfaceLevelView;
	int levelLength;
};
