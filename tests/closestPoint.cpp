#include "../include/collider.h"
#include "../include/geometry.h"
#include <iostream>
#include <vector>

using namespace geometry;
using namespace physics;

int main() {
    vector t1 = vector(0, 0);
    vector t2 = vector(5, 0);
    vector dir = vector(1, 0);

    std::vector<vector> pts = {vector(-1, -1), vector(-1, 1), vector(1, 1), vector(1, -1)};

    lineCollider c1 = lineCollider(t1, dir, 9);
    generalCollider c2 = generalCollider(t2, pts);

    vector closest1 = c1.nearestPointToCollider(c2);
    vector closest2 = c2.nearestPointToCollider(c1);

    std::cout << "closest on c1: (" << closest1.x << ", " << closest1.y << ")" << std::endl;
    std::cout << "closest on c2: (" << closest2.x << ", " << closest2.y << ")" << std::endl;
}