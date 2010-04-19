#include "Slopes.h"

Slopes::Slopes(void)
{
}

Slopes::~Slopes(void)
{
}

double Slopes::CalculateSlopCoeffA(int x1, int y1, int x2, int y2)
{
	double a=0;
	a=((double)y1-(double)y2)/((double)x1-(double)x2);
	return a;
}

double Slopes::CalculateSlopCoeffB(int x, int y,double a)
{
	double b=0;
	b=(double)y-(a*(double)x);
	return b;
}
	