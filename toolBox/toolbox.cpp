#include <iostream>
#include "toolbox.h"


template <typename T>
T lerp(T x, T y, float a)
{
	return x * (1 - a) + y * a;
}
float randRange(Rangef r)
{
	float rnd = (rand() % RAND_MAX) / (float)RAND_MAX;
	return lerp(r.min, r.max, rnd);
}
