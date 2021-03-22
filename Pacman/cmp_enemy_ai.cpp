#include <SFML/System/Vector2.hpp>
#include "cmp_enemy_ai.h"
#include "LevelSystem.h"

using namespace sf;

static const Vector2i directions[] = { {1,0},{0,1},{0,-1},{-1,0} };

EnemyAIComponent::EnemyAIComponent(Entity* p):ActorMovementComponent(p)
{
	_state = ROTATING;
}

void EnemyAIComponent::Update(double dt)
{
	//amount to move
	const auto mva = (float)(dt * _speed);
	//current position
	const Vector2f pos = _parent->getPosition();
	//next position
	const Vector2f newpos = pos + _direction * mva + _direction * 20.0f;
	//inverse of our current direction
	const Vector2i baddir = -1 * Vector2i(_direction);
	//random new direction
	Vector2i newdir = directions[(rand() % 4)];

	switch (_state)
	{
	case ROAMING:
		if (LevelSystem::getTileAt(newpos) == LevelSystem::WALL)
			_state = MOVETOCENTER;
		else if (LevelSystem::getTileAt(pos) == LevelSystem::WAYPOINT)//Wall in front or at waypont
			_state = MOVETOCENTER;//start rotate
		else
			move(_direction * mva);//keep moving
		break;
	case MOVETOCENTER:
		move(_direction * mva);
		std::cout << remainder(pos.x, 25.0f) << ":" << remainder(pos.y, 25.0f) << std::endl;
		if (sqrt(pow(remainder(pos.x, 25.0f), 2)) > sqrt( pow(10.0f*_direction.x,2)) && 
			sqrt(pow(remainder(pos.y, 25.0f), 2)) > sqrt(pow(10.0f*_direction.y, 2)))
		_state = ROTATING;
		break;
	case ROTATING:
		while (
			//dont reverse
			newdir == baddir &&
			//and dont pick a direction that will lead to a wall
			LevelSystem::getTileAt(pos + Vector2f(newdir.x, newdir.y) * mva ) == LevelSystem::WALL)
		{
			//pick new direction
			Vector2i newdir = directions[(rand() % 4)];
		}
		_direction = Vector2f(newdir);
		_state = ROTATED;
		break;

	case ROTATED:
		//have we left the waypoint?
		if (LevelSystem::getTileAt(pos) != LevelSystem::WAYPOINT)
		{
			_state = ROAMING;//yes
		}
		move(_direction * mva);//no
		if (LevelSystem::getTileAt(newpos) == LevelSystem::WALL) _state = ROAMING;//go back to roaming to be rotated
		break;
	}
	ActorMovementComponent::Update(dt);
}