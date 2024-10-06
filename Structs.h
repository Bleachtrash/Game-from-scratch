#include <cmath>
#include <iostream>
#include <vector>

using namespace std;
#ifndef STRUCTS
#define STRUCTS

/* Vector2(float x, float y) */
struct Vector2
{
    float x;
    float y;
    float Magnitude()
    {
        return sqrt(pow(x, 2) + pow(y, 2));
    }
    Vector2 Normalized()
    {
        if(Magnitude() == 0)
            return Vector2{0, 0};
        return Vector2{x/Magnitude(), y/Magnitude()};
    }
};

Vector2 operator +(const Vector2& a, const Vector2& b)
{
	return Vector2{a.x + b.x, a.y + b.y};
}
Vector2 operator -(const Vector2& a, const Vector2& b)
{
	return Vector2{a.x - b.x, a.y - b.y};
}
Vector2 operator *(const Vector2& a, const float b)
{
    return Vector2{a.x * b, a.y * b};
}
bool operator ==(const Vector2& a, const Vector2& b)
{
    if(a.x == b.x && a.y == b.y)
    {
        return true;
    }

    return false;
}
Vector2 operator /(const Vector2& a, const float b)
{
    return Vector2{a.x / b, a.y / b};
}
ostream& operator <<(ostream &o, const Vector2 a)
{
    return o << a.x << ", " << a.y;
}

/* Object(char *Name, Vector2 Position, Vector2 Scale, SDL_Color Color) */
struct Object
{
    char *Name;
    Vector2 Position;
    Vector2 Scale;
    SDL_Color Color;
};
#endif