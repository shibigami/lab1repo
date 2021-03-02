#include "Entity.h"
#include "system_renderer.h"
using namespace std;
using namespace sf;

const Vector2f Entity::getPosition() { return _position; }
void Entity::setPosition(const Vector2f& pos) { _position = pos; }
void Entity::move(const Vector2f& pos) { _position += pos; }
void Entity::Update(const double dt) {
	_shape->setPosition(_position);
}

Entity::Entity(unique_ptr<Shape> s) :_shape(std::move(s)) {}

void Entity::EntityManager::Update(double dt)
{
	for (auto& i : list) 
	{
		i.get()->Update(dt);
	}
}

void Entity::EntityManager::Render()
{
	for (auto& i : list) {
		i.get()->Render();
	}
}
