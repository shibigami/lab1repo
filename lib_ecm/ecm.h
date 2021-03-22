#pragma once
#include <algorithm>
#include <memory>
#include <typeindex>
#include <vector>
#include "maths.h"

class Component; //forward declaration

class Entity {
protected:
	std::vector<std::shared_ptr<Component>> _components;
	sf::Vector2f _position;
	float _rotation;
	bool _alive;		//should be updated
	bool _visible;		//should be updated
	bool _fordeletion;	//should be updated
public:
	Entity();
	virtual ~Entity();
	virtual void Update(double dt);
	virtual void Render();

	const sf::Vector2f& getPosition() const;
	void setPosition(const sf::Vector2f& _pos);
	bool is_fordeletion() const;
	float getRotation() const;
	void setRotation(float _rot);
	bool isAlive();
	void setAlive(bool alive);
	void setForDelete();
	bool isVisible() const;
	void setVisible(bool _vis);


	template <typename T,typename... Targs>
	std::shared_ptr<T> addComponent(Targs... params) {
		static_assert(std::is_base_of<Component, T>::value, "T != component");
		std::shared_ptr<T> sp(std::make_shared<T>(this, params...));
		_components.push_back(sp);
		return sp;
	}

	template <typename T>
	const std::vector<std::shared_ptr<T>> getComponents() const {
		static_assert(std::is_base_of<Component, T>::value, "T != component");
		std::vector<std::shared_ptr<T>> ret;
		for (const auto c : _components) {
			if (typeid(*c) == typeid(T)) {
				ret.push_back(std::dynamic_pointer_cast<T>(c));
			}
		}
		return std::move(ret);
	}

	template <typename T>
	const std::vector<std::shared_ptr<T>> getCompatibleComponent() 
	{
		static_assert(std::is_base_of<Component, T>::value, "T != component");
		std::vector<std::shared_ptr<T>> ret;
		for (auto c : _components) 
		{
			auto dd = dynamic_cast<T*>(&(*c));
			if (dd) {
				ret.push_back(std::dynamic_pointer_cast<T>(c));
			}
		}
		return ret;
	}
};

struct EntityManager {
	std::vector<std::shared_ptr<Entity>> list;
	void Update(double dt);
	void Render();
};

class Component {
protected:
	Entity* const _parent;
	bool _fordeletion;	//should be removed
	explicit Component(Entity* const p);

public:
	Component() = delete;
	bool is_fordeletion() const;
	virtual void Update(double dt) = 0;
	virtual void Render() = 0;
	virtual ~Component();
};