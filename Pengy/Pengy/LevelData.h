#include "messages.h"
#include "Surface.h"
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

class LevelData
{
private:

public:
    LevelData();
	vector<int*> SortTiles(vector<int*> data);
	virtual void LoadGadgets() = 0;
    virtual vector<Surface*> GetSurfaces() = 0;
	virtual vector<int*> GetTiles() = 0;
    ~LevelData();
};