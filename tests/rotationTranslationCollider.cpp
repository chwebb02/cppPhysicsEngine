#include "../include/collider.h"
#include <vector>
#include <math.h>
#include <iostream>

int main() {
    using geometry::vector;
    using namespace physics;
    using std::cout, std::endl;

    vector t1 = vector(5, 5);
    lineCollider c1 = lineCollider(t1, vector(1, 0), 6);

    vector t2 = vector(0, 10);
    std::vector<vector> pts = {vector(-1, -1), vector(-1, 1), vector(1, 1), vector(1, -1)};
    generalCollider c2 = generalCollider(t2, pts);

    c1.translate(vector(0, 0));
    c1.rotateBy(M_PI / 2);

    vector pt = c1.nearestPointToCollider(c2);
    cout << "c1 nearest to c2 " << pt.x << ", " << pt.y << endl;

    c2.rotateBy(M_PI / 4);
}