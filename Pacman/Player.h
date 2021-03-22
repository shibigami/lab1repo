#pragma once
#include "ecm.h"

class Player :public Entity {
private:
	float _speed;

public:
	Player();
	void Update(double dt);
	void Render();
};