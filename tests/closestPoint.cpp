#include "../include/collider.h"
#include "../include/geometry.h"
#include <iostream>

using namespace geometry;
using namespace physics;

int main() {
    vector t1 = vector(-2, 0);
    vector t2 = vector(-2, 2);
    vector dir = vector(1, 0.05);

    circleCollider c1 = circleCollider(t1, 1);
    planeCollider c2 = planeCollider(t2, dir, 10);

    vector closest1 = c1.nearestTo(c2);
    vector closest2 = c2.nearestTo(c1);

    std::cout << "closest on c1: (" << closest1.x << ", " << closest1.y << ")" << std::endl;
    std::cout << "closest on c2: (" << closest2.x << ", " << closest2.y << ")" << std::endl;
}