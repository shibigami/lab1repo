#include "cmp_actor_movement.h"
#include <LevelSystem.h>

using namespace sf;

void ActorMovementComponent::Update(double dt) {}

ActorMovementComponent::ActorMovementComponent(Entity* p)
	: _speed(100.0f), Component(p) {direction= Vector2f(0.02f* _speed, 0);
}



bool ActorMovementComponent::validMove(const sf::Vector2f& pos)
{
	return (
		LevelSystem::getTileAt(pos + Vector2f(0, -10)) != LevelSystem::WALL&&
		LevelSystem::getTileAt(pos + Vector2f(-10, 0)) != LevelSystem::WALL&&
		LevelSystem::getTileAt(pos + Vector2f(0, 10)) != LevelSystem::WALL&&
		LevelSystem::getTileAt(pos + Vector2f(10, 0)) != LevelSystem::WALL
		);
}


void ActorMovementComponent::move(const sf::Vector2f& p) 
{
	auto pp = _parent->getPosition() + p;
	if (validMove(pp)) {
		_parent->setPosition(pp);
	}
}

void ActorMovementComponent::move(float x, float y) 
{
	move(Vector2f(x, y));
}

float ActorMovementComponent::getSpeed() const { return _speed; }
void ActorMovementComponent::setSpeed(float speed) {}

PlayerMovementComponent::PlayerMovementComponent(Entity* p)
	:ActorMovementComponent(p) {}
void PlayerMovementComponent::Update(double dt)
{
	if (Keyboard::isKeyPressed(Keyboard::A)) 
	{
		direction=Vector2f(dt * -_speed, 0);
	}
	else if (Keyboard::isKeyPressed(Keyboard::D))
	{
		direction=Vector2f(dt * _speed, 0);
	}
	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		direction=Vector2f(0, dt * -_speed);
	}
	else if (Keyboard::isKeyPressed(Keyboard::S))
	{
		direction=Vector2f(0, dt * _speed);
	}
	move(direction);
}

/*
EnemyAIComponent::EnemyAIComponent(Entity* p)
	:ActorMovementComponent(p)
{
}

void EnemyAIComponent::Update(double dt)
{
}
*/