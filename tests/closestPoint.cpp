#include "../include/collider.h"
#include "../include/geometry.h"
#include <iostream>
#include <vector>

using namespace geometry;
using namespace physics;

int main() {
    vector t1 = vector(0, 0);
    vector t2 = vector(5 , 5);

    std::vector<vector> pts = {vector(1, 1), vector(-1, 1), vector(-1, -1), vector(1, -1)};

    circleCollider c1 = circleCollider(t1, 1);
    generalCollider c2 = generalCollider(t2, pts);

    vector closest1 = c1.nearestTo(c2);
    vector closest2 = c2.nearestTo(c1);

    std::cout << "closest on c1: (" << closest1.x << ", " << closest1.y << ")" << std::endl;
    std::cout << "closest on c2: (" << closest2.x << ", " << closest2.y << ")" << std::endl;
}