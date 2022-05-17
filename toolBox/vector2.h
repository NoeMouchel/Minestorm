#pragma once

#include <iostream>

#define EPSILON 0.001

class Vector2f
{
public:
    float x;
    float y;


    //CONSTRUCTORS ~
    Vector2f();
    ~Vector2f() {};
    Vector2f(float);
    Vector2f(float, float);
    Vector2f(Vector2f, Vector2f);

    //FUNCTIONS ~ 

    bool    compare(Vector2f);

    float   magnitude();
    float   squareLength() const;
    float   dot(Vector2f);
    double   angle(Vector2f);
    float   distance(Vector2f);

    Vector2f    unit();
    Vector2f    opposate();
    Vector2f    rotate(float);
    Vector2f    rotatePoint(Vector2f, float);
    Vector2f    rotate90();
    Vector2f    normalVector();

    //OPERATORS ~
    Vector2f    operator-(Vector2f vect) const { Vector2f result(this->x - vect.x, this->y - vect.y); return result; };
    Vector2f    operator-(float value) const { Vector2f result(this->x - value, this->y - value); return result; };
    Vector2f    operator+(Vector2f vect) const  { Vector2f result(this->x + vect.x, this->y + vect.y); return result; };
    Vector2f    operator+(float value) const { Vector2f result(this->x + value, this->y + value); return result; };
    Vector2f    operator*(float scale) const { Vector2f result(this->x * scale, this->y * scale); return result; };

    friend std::ostream& operator<<(std::ostream& out, Vector2f& vect) { out << " (" << vect.x << "," << vect.y << ") "; return out; };


};
