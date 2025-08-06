#include <iostream>
#include <vec2.hpp>
#include <vec3.hpp>
#include <render.hpp>
using namespace std;

int main(int argc, char const *argv[])
{
    cout << "hello world" << endl;
    // Vec2 a(1.0f, 2.0f), b(2.0f, 1/2.0f);
    // float c = Vec2::dotProduct(a, b);
    // std::cout << "Dot product is " << c << std::endl;

    // Vec2 tmpArray[] = {a, b};
    // renderVec2(tmpArray, 2);

    Vec3 a(1.0f, 2.0f, 3.0f), b(-3.0f, 4.0f, -5.0f);
    Vec3 c = Vec3::crossProduct(a, b);

    Vec3 tmpArray[] = {a, b, c};

    renderVec3(tmpArray, 3);

    return 0;
}
