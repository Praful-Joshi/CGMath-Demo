#pragma once

class Vec3 {
    public:
    //constructors
    Vec3();
    Vec3(float x, float y, float z);

    //getters
    float getX() const { return x; }
    float getY() const { return y; }
    float getZ() const { return z; }
    float getTheta() const { return theta; }
    float getPhi() const { return phi; }
    float getLength() const { return length; }

    //math functions
    static bool isEqual(Vec3 a, Vec3 b);
    static Vec3 add(Vec3 a, Vec3 b);
    static Vec3 scale(float k, Vec3 a);
    static Vec3 subtract(Vec3 a, Vec3 b);

    private:
    //variables
    float x, y, z, theta, phi, length;
};