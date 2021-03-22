#pragma once
#include "cmp_actor_movement.h"

class EnemyAIComponent : public ActorMovementComponent {

protected:
	sf::Vector2f _direction;
	enum state { ROAMING,MOVETOCENTER, ROTATING, ROTATED };
	state _state;
public:
	explicit EnemyAIComponent(Entity* p);
	void Update(double dt);
};
