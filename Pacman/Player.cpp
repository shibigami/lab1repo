#include "Player.h"
#include "system_renderer.h"
using namespace sf;
using namespace std;

void Player::Update(double dt) {
	//Move in four directions based on keys
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		move(Vector2f(-_speed * dt, 0));
	}
	else if (Keyboard::isKeyPressed(Keyboard::D)) {
		move(Vector2f(_speed * dt, 0));
	}
	if (Keyboard::isKeyPressed(Keyboard::S)) {
		move(Vector2f(0, _speed * dt));
	}
	else if (Keyboard::isKeyPressed(Keyboard::W)) {
		move(Vector2f(0, -_speed * dt));
	}
	//Entity::Update(dt);
}

/*
Player::Player()
	:_speed(200.0f), Entity(make_unique<CircleShape>(10.0f)) {
	_shape->setFillColor(Color::Yellow);
	_shape->setOrigin(Vector2f(25.0f, 25.0f));
	_shape->setPosition(Vector2f(100.0f, 100.0f));
}
*/

void Player::Render() {
	//Renderer::queue(_shape.get());
}
