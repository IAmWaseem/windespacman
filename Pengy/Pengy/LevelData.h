#include "messages.h"
#include "Surface.h"
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

class LevelData
{
public:
    LevelData();
	virtual void LoadGadgets() = 0;
    virtual vector<Surface*> getSurfaces() = 0;
	virtual vector<int*> getTiles() = 0;
    ~LevelData();
};