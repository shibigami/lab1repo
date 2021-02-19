#pragma once
#include <SFML/Graphics.hpp>

class Ship : public sf::Sprite 
{
protected:
	sf::IntRect _sprite;
	bool _exploded = false;
	//Default constructor is hidden
	Ship();
public:
	bool control;
	//get exploded
	bool is_exploded() const;
	virtual void Explode();
	//Constructor that takes a sprite
	explicit Ship(sf::IntRect ir);
	//Pure virtual deconstructor -- makes this an abstract class and avoids undefined behavior!
	virtual ~Ship() = 0;
	//Update, virtual so can be overriden, but not pure virtual
	virtual void Update(const float &dt);
};

class Invader : public Ship 
{
public:
	static bool direction;
	static float speed;

	Invader(sf::IntRect ir, sf::Vector2f pos);
	Invader();
	void Update(const float& dt) override;
	void MoveDown();
};

class Player : public Ship {
public:
	Player();
	void Update(const float& dt) override;
};