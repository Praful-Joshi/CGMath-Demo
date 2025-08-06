#include <vec3.hpp>
#include <iostream>
#include <cmath>

Vec3::Vec3()
{
    this->x=0.0f;
    this->y=0.0f;
    this->z=0.0f;
    this->length=0.0f;
    this->theta=0.0f;
    this->phi=0.0f;
}

Vec3::Vec3(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->length = std::sqrt(x * x + y * y + z * z);
    this->theta = std::atan2(y, x);             // radians
    this->phi   = std::acos(z / this->length);  // radians
    std::cout << "3D Vector created using co-ordinates (" << this->x << ", " << this->y << ", " << this->z << ")" << std::endl;
}

bool Vec3::isEqual(Vec3 a, Vec3 b)
{
    if(a.x == b.x && a.y == b.y && a.z == b.z)
    {
        return true;
    }
    else
    {
        return false;
    }
}

Vec3 Vec3::add(Vec3 a, Vec3 b){
    Vec3 temp(a.x+b.x, a.y+b.y, a.z+b.z);
    return temp;
}

Vec3 Vec3::scale(float k, Vec3 a)
{
    Vec3 temp(k*a.x, k*a.y, k*a.z);
    return temp;
}

Vec3 Vec3::subtract(Vec3 a, Vec3 b)
{
    Vec3 scalarMultResult = scale(-1.0f, b);
    Vec3 temp = add(a, scalarMultResult);
    return temp;
}

float Vec3::dotProduct(Vec3 a, Vec3 b)
{
    float tmp = a.getX()*b.getX() + a.getY()*b.getY() + a.getZ()*b.getZ();
    return tmp;
}

Vec3 Vec3::crossProduct(Vec3 a, Vec3 b)
{
    float x = a.getY()*b.getZ() - a.getZ()*b.getY();
    float y = a.getZ()*b.getX() - a.getX()*b.getZ();
    float z = a.getX()*b.getY() - a.getY()*b.getX();
    Vec3 tmp(x,y,z);
    return tmp;
}
