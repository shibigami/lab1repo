#pragma once
#include <ecm.h>

class ActorMovementComponent :public Component 
{
protected:
	bool validMove(const sf::Vector2f&);
	float _speed;

public:
	explicit ActorMovementComponent(Entity* p);
	ActorMovementComponent() = delete;

	float getSpeed() const;
	void setSpeed(float _speed);

	void move(const sf::Vector2f&);
	void move(float x, float y);

	void Render() override {};
	void Update(double dt) override;
};

class PlayerMovementComponent :public ActorMovementComponent
{
public:
	PlayerMovementComponent(Entity* p);
	void Update(double dt) override;
};

/*
class EnemyAIComponent :public ActorMovementComponent
{
public:
	EnemyAIComponent(Entity* p);
	void Update(double dt) override;
};
*/