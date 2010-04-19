#pragma once
#include "Slopes.h"
struct Surface
{
	int xFrom;
	int xTo;
	int yFrom;
	int yTo;

	bool isCloud;
	bool isIce;
	bool isSurfaceOfDeath;
	int isSlope;

	double SlopeCoefficientA;
	double SlopeCoefficientB;

};