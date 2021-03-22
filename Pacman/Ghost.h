#pragma once
#include "ecm.h"

class Ghost :public Entity {
private:
	float _speed;

public:
	void Update(double dt);
	Ghost();
	void Render();
};