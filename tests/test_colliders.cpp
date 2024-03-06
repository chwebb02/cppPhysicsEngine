#include <gtest/gtest.h>
#include "collider.h"
 
TEST (circleCollider, detectCollisionWithOtherCircle) {
	using namespace physics;

	circleCollider c1 = {{0, 0}, 1};
	circleCollider c2 = {{0, 2}, 1.5};

	bool isColliding = collider::isColliding(c1, c2);
	EXPECT_TRUE(isColliding);
}

TEST (circleCollider, getNearestPoint) {
	using namespace physics;

	circleCollider c1 = {{-1, 0}, 1};
	circleCollider c2 = {{1, 0}, 1};

	bool isColliding = collider::isColliding(c1, c2);
	EXPECT_TRUE(isColliding);
	
	geometry::vector pt = c1.nearestPointToCollider(c2);
	bool isCorrect = (pt.x - 0) <= 1e-10 && (pt.y - 0) <= 1e-10;
	EXPECT_TRUE(isCorrect);
}

int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}