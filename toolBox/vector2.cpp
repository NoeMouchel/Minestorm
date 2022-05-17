#include <iostream>
#include "vector2.h"
#include "range2.h"
#include "cmath"

#define M_PI 3.14159265358979323846


Vector2f::Vector2f()
{
    this->x = 0;
    this->y = 0;
}

Vector2f::Vector2f(float flt)
{
    this->x = flt;
    this->y = flt;
}

Vector2f::Vector2f(float x_src,float y_src)
{
    this->x = x_src;
    this->y = y_src;
}

Vector2f::Vector2f(Vector2f vectA, Vector2f vectB)
{
    this->x = vectB.x - vectA.x;
    this->y = vectB.y - vectA.y;
}

float Vector2f::magnitude()
{
    return sqrt(this->x*this->x + this->y*this->y);
}

float Vector2f::squareLength() const
{
    return (this->x * this->x + this->y * this->y);
}
    
Vector2f Vector2f::unit()
{
    Vector2f unit_vector;
    float length = this->magnitude();
    if (length != 0)
    {
        unit_vector = { this->x / length, this->y / length };
        return unit_vector;
    }
    return unit_vector;
}

float Vector2f::dot(Vector2f vect)
{
    return  vect.x * this->x + vect.y * this->y;
}


Vector2f Vector2f::opposate()
{
    return (*this)*(-1.f);
}

float Vector2f::distance(Vector2f vect)
{
    Vector2f result(vect.x - this->x, vect.y - this->y);
    return result.magnitude();
}

double Vector2f::angle(Vector2f vect)
{
    return acos(this->dot(vect.unit()));
}

bool Vector2f::compare(Vector2f vect)
{
    return (this->distance(vect) < EPSILON);
}


//ANGLE APPLICATIONS

Vector2f    Vector2f::rotate(float angle)
{
    float x_result = cos(angle) * this->x - sin(angle) * this->y;
    float y_result = sin(angle) * this->x + cos(angle) * this->y;

    this->x = x_result;
    this->y = y_result;

    return *this;
}

Vector2f    Vector2f::rotatePoint(Vector2f center, float angle)
{
    Vector2f vect = *this - center; 
    return vect.rotate(angle);
}

Vector2f    Vector2f::rotate90()
{
    Vector2f vect(-(this->y), this->x);
    return vect;
}

Vector2f   Vector2f::normalVector()
{
    Vector2f vect = this->unit();
    return vect.rotate90();
}