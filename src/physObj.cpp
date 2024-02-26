#include "physObj.h"
#include <vector>

namespace physics {
void dynamicObj::step(double delta) {
    using geometry::vector;

    vector acceleration = force / mass;
    velocity += acceleration.scaled(delta);

    position += velocity.scaled(delta);
}

void dynamicObj::collide(dynamicObj& o1, dynamicObj& o2) {
    using geometry::vector;
}
};