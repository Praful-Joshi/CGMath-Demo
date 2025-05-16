#include <iostream>
#include <vec2.hpp>
#include <vec3.hpp>
#include <render.hpp>
using namespace std;

int main(int argc, char const *argv[])
{
    cout << "hello world" << endl;
    // Vec2 a(1.0f, 2.0f), b(-3.0f, 4.0f);
    // Vec2 c = Vec2::add(a, b);

    // Vec2 tmpArray[] = {a, b, c};

    // renderVec2(tmpArray, 3);

    Vec3 a(1.0f, 2.0f, 3.0f), b(-3.0f, 4.0f, -5.0f);
    Vec3 c = Vec3::add(a, b);

    Vec3 tmpArray[] = {a, b, c};

    renderVec3(tmpArray, 3);

    return 0;
}
