#include <gtest/gtest.h>
#include "physObj.h"

using namespace physics;

TEST(staticWallCollision, circleClean1) {
	lineCollider p = {{0, 0}, {0, 1}, 10};
	circleCollider c = {{2, 0}, 1};

	physObj wall = {{0, 0}, p};
	dynamicObj ball = {{2, 0}, c, {-1, 0}, {0, 0}, 10};

	bool isColliding = collider::isColliding(p, c);
	EXPECT_FALSE(isColliding);

	ball.step(1.0);
	isColliding = collider::isColliding(p, c);
	EXPECT_TRUE(isColliding);

	dynamicObj::collide(ball, wall);
	EXPECT_TRUE(ball.getVelocity() == ((geometry::vector){1, 0}));
}

TEST(staticWallCollision, circleClean2) {
	lineCollider p = {{0, 0}, {0, 1}, 10};
	circleCollider c = {{2, 1}, 1};

	physObj wall = {{0, 0}, p};
	dynamicObj ball = dynamicObj({2, 2}, c, {-1, -1}, {0, 0}, 10);

	bool isColliding = collider::isColliding(p, c);
	EXPECT_FALSE(isColliding);

	ball.step(1.0);
	isColliding = collider::isColliding(p, c);
	EXPECT_TRUE(isColliding);

	dynamicObj::collide(ball, wall);
	EXPECT_TRUE(ball.getVelocity() == ((geometry::vector){1, -1}));
}

TEST(staticWallCollision, circleMessy) {
	lineCollider p = {{0, 0}, {0, 1}, 10};
	circleCollider c = {{1.9, 0}, 1};

	physObj wall = {{0, 0}, p};
	dynamicObj ball = {{1.9, 0}, c, {-1, 0}, {0, 0}, 10};

	bool isColliding = collider::isColliding(p, c);
	EXPECT_FALSE(isColliding);

	ball.step(1.0);
	isColliding = collider::isColliding(p, c);
	EXPECT_TRUE(isColliding);

	dynamicObj::collide(ball, wall);
	EXPECT_TRUE(ball.getVelocity() == ((geometry::vector){1, 0}));
}

int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}