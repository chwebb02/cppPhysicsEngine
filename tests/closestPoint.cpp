#include "../include/collider.h"
#include "../include/geometry.h"
#include <iostream>
#include <vector>

using namespace geometry;
using namespace physics;

int main() {
    vector t1 = vector(-2, -1);
    vector t2 = vector(0, 0);
    vector t3 = vector(2, 1);

    std::vector<vector> pts = {vector(-1, -1), vector(-1, 1), vector(1, 1), vector(1, -1)};

    circleCollider c1 = circleCollider(t1, 1);
    generalCollider c2 = generalCollider(t2, pts);
    circleCollider c3 = circleCollider(t3, 1);

    vector closest1 = c1.nearestPointToCollider(c2);
    vector closest2 = c2.nearestPointToCollider(c1);

    std::cout << "c1 and c2" << std::endl;
    std::cout << "closest on 1: (" << closest1.x << ", " << closest1.y << ")" << std::endl;
    std::cout << "closest on 2: (" << closest2.x << ", " << closest2.y << ")" << std::endl;

    closest1 = c2.nearestPointToCollider(c3);
    closest2 = c3.nearestPointToCollider(c2);

    std::cout << "c2 and c3" << std::endl;
    std::cout << "closest on 1: (" << closest1.x << ", " << closest1.y << ")" << std::endl;
    std::cout << "closest on 2: (" << closest2.x << ", " << closest2.y << ")" << std::endl;

    closest1 = c1.nearestPointToCollider(c3);
    closest2 = c3.nearestPointToCollider(c1);
    
    std::cout << "c1 and c3" << std::endl;
    std::cout << "closest on 1: (" << closest1.x << ", " << closest1.y << ")" << std::endl;
    std::cout << "closest on 2: (" << closest2.x << ", " << closest2.y << ")" << std::endl;
}