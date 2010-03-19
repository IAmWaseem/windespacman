#pragma once
// to make slopes changes were in flies besides Physics and Surfaces made to files:
//BeachLevel.cpp starting at line 57
//BeachLevel.h one object Slopes
//LevelView.ccp line 67
class Slopes
{
public:
	Slopes(void);
	~Slopes(void);
	// for calculation: positions of slope begining (x1,y2) and end (x2,y2)
	double CalculateSlopCoeffA(int x1, int y1, int x2, int y2);
	double CalculateSlopCoeffB(int x1, int y1,double a);
};
