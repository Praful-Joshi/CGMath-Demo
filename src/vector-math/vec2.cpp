#include <vec2.hpp>
#include <iostream>
#include <cmath>

Vec2::Vec2()
{
    this->x = 0.0f;
    this->y = 0.0f;
    this->theta = 0.0f;
    this->length = 0.0f;
}

Vec2::Vec2(float x, float y)
{
    this->x = x;
    this->y = y;
    this->length = std::sqrt(x * x + y * y);
    this->theta = std::atan2(y, x); // in radians
    std::cout << "2D Vector created (" << this->x << ", " << this->y << "), " << "Length - " << this->length << " Theta - " << this->theta << std::endl;
}

bool Vec2::isEqual(Vec2 a, Vec2 b)
{
    if(a.x == b.x && a.y == b.y)
    {
        return true;
    }
    else
    {
        return false;
    }
}

Vec2 Vec2::add(Vec2 a, Vec2 b)
{
    Vec2 temp(a.x+b.x, a.y+b.y);
    return temp;
}

Vec2 Vec2::scale(float k, Vec2 a)
{
    Vec2 temp(k*a.x, k*a.y);
    return temp;
}

Vec2 Vec2::subtract(Vec2 a, Vec2 b)
{
    Vec2 scalarMultResult = scale(-1.0f, b);
    Vec2 temp = add(a, scalarMultResult);
    return temp;
}
