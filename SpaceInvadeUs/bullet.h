#pragma once
#include <SFML/Graphics.hpp>

class Bullet :public sf::Sprite {
public:
	//updates all bullets
	static void Update(const float &dt);
	//renders all bullets
	static void Render(sf::RenderWindow& window);
	//chose an inactive bullet and use it
	static void Fire(const sf::Vector2f& pos, const bool mode);

	Bullet(const sf::Vector2f& pos,const bool mode);
	~Bullet() = default;
protected:
	static unsigned char bulletPointer;
	static Bullet bullets[256];
	//called by the static update
	void _Update(const float& dt);
	//never called by our code
	Bullet();
	//false=player bullet, true=Enemy bullet
	bool _mode;
};