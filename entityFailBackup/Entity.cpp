#include "Entity.h"
using namespace std;
using namespace sf;

const Vector2f Entity::getPosition() { return _position; }
void Entity::setPosition(const Vector2f& pos) { _position = pos; }
void Entity::move(const Vector2f& pos) { _position += pos; }
void Entity::Update(const double dt) {
	_shape->setPosition(_position);
}
Entity::Entity(unique_ptr<Shape> s) :_shape(std::move(s)) {}

//Ghost
Ghost::Ghost()
	: _speed(200.0f), Entity(make_unique<CircleShape>(25.0f)) {
	_shape->setFillColor(Color::Magenta);
	_shape->setOrigin(Vector2f(25.0f, 25.0f));
}

void Ghost::Update(const double dt)
{
}

void Ghost::Render(sf::RenderWindow& window) const
{
}

//Player
Player::Player()
	: _speed(200.0f), Entity(make_unique<CircleShape>(25.0f)) {
	_shape->setFillColor(Color::Yellow);
	_shape->setOrigin(Vector2f(25.0f, 25.0f));
}

void Player::Update(const double dt) 
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		_shape->move(0.0f, 100.0f*dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		_shape->move(0.0f, -100.0f * dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		_shape->move(-100.0f * dt,0.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		_shape->move(100.0f * dt,0.0f);
	}
}

void Player::Render(sf::RenderWindow& window) const
{
	
}