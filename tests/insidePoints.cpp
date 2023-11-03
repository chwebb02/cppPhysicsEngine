#include "../include/collider.h"
#include <iostream>

using namespace physics;
using namespace geometry;
using std::cout;
using std::endl;

int main() {
    vector t1 = vector(0, 0);
    vector t2 = vector(1, 0);

    //generalCollider c1 = generalCollider(t1, {vector(-1, -1), vector(-1, 1), vector(1.5, 0)});
    circleCollider c1 = circleCollider(t1, 1.5);
    generalCollider c2 = generalCollider(t2, {vector(0, -1), vector(0, 1), vector(1, 0)});

    vector pt1 = c1.nearestPointToCollider(c2);
    vector pt2 = c2.nearestPointToCollider(c1);

    cout << "pt1: " << pt1.x << ", " << pt1.y << endl;
    cout << "pt2: " << pt2.x << ", " << pt2.y << endl;

    cout << "isColliding: " << collider::isColliding(c1, c2) << endl;
}