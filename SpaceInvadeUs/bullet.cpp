#include "bullet.h"
#include "game.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

unsigned char Bullet::bulletPointer;
Bullet Bullet::bullets[256];

Bullet::Bullet() {};

Bullet::Bullet(const sf::Vector2f& pos, const bool mode) : Sprite()
{
	setPosition(pos);
	_mode = mode;
	bulletPointer = 0;
};


void Bullet::Update(const float &dt) 
{
	for (auto& s : bullets) 
	{
		s._Update(dt);
	}
}

Player* player;

void Bullet::_Update(const float& dt) {
	if (getPosition().y<-32 || getPosition().y>gameHeight + 32)
	{
		//off screen - do nothing
		return;
	}
	else {
		move(0, dt * 200.0f * (_mode ? 1.0f : -1.0f));
		const FloatRect boundingBox = getGlobalBounds();

		for (auto& s : ships)
		{
			if (!_mode && s == player)
			{
				//player bullets don't collide with player
				continue;
			}
			if (_mode && s != player)
			{
				//invader bullets don't collide with other invaders
				continue;
			}
			if (!s->is_exploded()&&!s->getGlobalBounds().intersects(boundingBox))
			{
				//Explode the ship
				s->Explode();
				//warp bullet off-screen
				setPosition(-100, -100);
				return;
			}
		}
	}
}

void Bullet::Render(sf::RenderWindow& window) 
{
	for (const auto b : bullets)
	{
		window.draw(b);
	}
}

void Bullet::Fire(const sf::Vector2f& pos, const bool mode) 
{
	bullets[++bulletPointer].setPosition(pos);
	bullets[bulletPointer]._mode = mode;
	bullets[bulletPointer].setTexture(spritesheet);
	bullets[bulletPointer].setTextureRect(IntRect(64, 32, 32, 32));
}