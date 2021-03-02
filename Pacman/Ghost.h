#pragma once
#include "Entity.h"

class Ghost :public Entity {
private:
	float _speed;

public:
	void Update(double dt) override;
	Ghost();
	Ghost(sf::Color color);
	void Render() const override;
};