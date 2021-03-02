#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

class Entity 
{
protected:
	sf::Vector2f _position;
	Entity(std::unique_ptr<sf::Shape> shp);

public:
	std::unique_ptr<sf::Shape> _shape;
	Entity() = delete;
	virtual ~Entity() = default;

	virtual void Update(const double dt);
	virtual void Render() const = 0;

	const sf::Vector2f getPosition();
	void setPosition(const sf::Vector2f& pos);
	void move(const sf::Vector2f& pos);

	struct EntityManager {
		std::vector<std::shared_ptr<Entity>> list;
		void Update(double dt);
		void Render();
	};
};