#include "Player.h"
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
	Entity::Update(dt);
}

Player::Player()
	:_speed(200.0f), Entity(make_unique<CircleShape>(25.0f)) {
	_shape->setFillColor(Color::Magenta);
	_shape->setOrigin(Vector2f(25.0f, 25.0f));
}

void Player::Render(sf::RenderWindow& window) const {
	window.draw(*_shape);
}