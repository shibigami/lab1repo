#include <Box2D/Box2D.h>
b2World* world;

void init() {
	const b2Vec2 gravity(0.0f, -10.0f);

	//Construct a world, which holds and simulates the physics bodies
	world = new b2World(gravity);
}