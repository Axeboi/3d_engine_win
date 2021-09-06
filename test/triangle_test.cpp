#include "../mesh.h"

typedef Triangle<Vector<double, 4>> Triangle4;
typedef Vector<double, 4> vec4d;

void normal()
{
    Triangle4 tri { vec4d { std::array<double, 4> {0.0, 0.0, 0.0, 1.0}}, vec4d { std::array<double, 4> {0.0, 4.0, 0.0, 1.0}}, vec4d { std::array<double, 4> {0.0, 0.0, 6.0, 1.0}} };
    vec4d normal = tri.normal();
    std::cout << "Expect 1,0,0: " << normal.x() << ", " << normal.y() << ", " << normal.z() << std::endl;
}

int main()
{
  normal();
}
