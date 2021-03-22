#include "ecm.h"

Entity::Entity() {}
Entity::~Entity() {}

void Entity::Update(double dt) 
{
	for (auto c : _components)
	{
		c->Update(dt);
	}
}
void Entity::Render() 
{
	for (auto c : _components) 
	{
		c->Render();
	}
}

void EntityManager::Update(double dt)
{
	for (auto& i : list)
	{
		i.get()->Update(dt);
	}
}

void EntityManager::Render()
{
	for (auto i : list) {
		i.get()->Render();
	}
}

const sf::Vector2f& Entity::getPosition() const
{
	return _position;
}

void Entity::setPosition(const sf::Vector2f& _pos) { _position = _pos; }
bool Entity::is_fordeletion() const { return _fordeletion; }
float Entity::getRotation() const { return _rotation; }
void Entity::setRotation(float _rot) { _rotation = _rot; }
bool Entity::isAlive() { return _alive; }
void Entity::setAlive(bool alive) { _alive = alive; }
void Entity::setForDelete() { _fordeletion = true; }
bool Entity::isVisible() const { return _visible; }
void Entity::setVisible(bool _vis) { _visible = _vis; }

Component::Component(Entity* const p) :_parent(p) {}

Component::~Component() {}