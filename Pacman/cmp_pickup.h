#pragma once
#include <ecm.h>

class PickUpComponent :public Component
{
protected:

public:
	explicit PickUpComponent(Entity* p);
	PickUpComponent() = delete;
};