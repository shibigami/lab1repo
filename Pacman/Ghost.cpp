#include "Ghost.h"
#include "system_renderer.h"
using namespace sf;
using namespace std;

void Ghost::Update(double dt) {

	Entity::Update(dt);
}

Ghost::Ghost()
	:_speed(200.0f), Entity(make_unique<CircleShape>(10.0f)) {
	_shape->setFillColor(Color::Magenta);
	_shape->setOrigin(Vector2f(25.0f, 25.0f));
}

Ghost::Ghost(sf::Color color)
	: _speed(200.0f), Entity(make_unique<CircleShape>(10.0f)) {
	_shape->setFillColor(color);
	_shape->setOrigin(Vector2f(25.0f, 25.0f));
}

void Ghost::Render() const {
	Renderer::queue(_shape.get());
}