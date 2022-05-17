#pragma once

#include "collision2.h"
#include "referential2.h"

//DEGREES TO RAD 
#define PI_CONVERT 0.01745329252

struct Rangef
{
    float min;
    float max;
};

template <typename T>
T lerp(T x, T y, float a);

float randRange(Rangef r);