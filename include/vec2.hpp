#pragma once

class Vec2 {
    public:
    //constructors
    Vec2();
    Vec2(float x, float y);

    //getters
    float getX() const { return x; }
    float getY() const { return y; }
    float getTheta() const { return theta; }
    float getLength() const { return length; }

    //math functions
    static bool isEqual(Vec2 a, Vec2 b);
    static Vec2 add(Vec2 a, Vec2 b);
    static Vec2 scale(float k, Vec2 a);
    static Vec2 subtract(Vec2 a, Vec2 b);


    private:
    //variables
    float x, y, theta, length;
};
