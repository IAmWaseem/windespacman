#pragma once

class Slopes
{
public:
	Slopes(void);
	~Slopes(void);
	// for calculation: positions of slope begining (x1,y2) and end (x2,y2)
	double CalculateSlopCoeffA(int x1, int y1, int x2, int y2);
	double CalculateSlopCoeffB(int x1, int y1,double a);
};
