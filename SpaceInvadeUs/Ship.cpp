#include "ship.h"
#include "game.h"
#include "bullet.h"

using namespace sf;
using namespace std;

Ship::Ship() {};


Ship::Ship(IntRect ir) : Sprite()
{
	_sprite = ir;
	setTexture(spritesheet);
	setTextureRect(_sprite);
	control = false;
};

void Ship::Update(const float& dt) {}

bool Ship::is_exploded() const
{
	return false;
		//&is_exploded;
}

void Ship::Explode()
{
	setTextureRect(IntRect(128, 32, 32, 32));
	_exploded = true;
}

//Define ship deconstructor
Ship::~Ship() = default;


//Invader
//
Invader::Invader() :Ship() {}

bool Invader::direction;
float Invader::speed;

Invader::Invader(sf::IntRect ir, sf::Vector2f pos) : Ship(ir) 
{
	setOrigin(16, 16);
	setPosition(pos);
}

void Invader::Update(const float& dt) 
{
	Ship::Update(dt);

	move(dt * (direction ? 1.0f : -1.0f) * speed, 0);
	
	MoveDown();

	static float firetime = 0.0f;
	firetime -= dt;
	if (firetime <= 0 && rand() % 100 == 0) 
	{
		Bullet::Fire(getPosition(), true);
		firetime = 4.0f + (rand() % 60);
	}

	if (is_exploded()) 
	{
		static float deathTimer = 2.0f;

		deathTimer -= dt;
		if(deathTimer<=0)
		{
			sf::Color* color = new sf::Color(0,0,0,0);
			setColor(*color);
		}
	}
}

void Invader::MoveDown() 
{
	if ((direction && getPosition().x > gameWidth - 16) ||
		(!direction && getPosition().x < 16)) {
		direction = !direction;
		for (int i = 0; i < ships.size(); ++i)
		{
			if(!ships[i]->control) ships[i]->move(0, 24);
		}
	}
}


//Player
//
Player::Player() : Ship(IntRect(160, 32, 32, 32)) 
{
	setPosition({ gameWidth * 0.5f,gameHeight - 32.0f });
	control = true;
}

void Player::Update(const float& dt)
{
	Ship::Update(dt);
	//move left
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		move(-2, 0);
	}
	//move right
	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		move(2, 0);
	}

	static float firetime = 0.5f;
	firetime -= dt;

	if (firetime <= 0 && Keyboard::isKeyPressed(Keyboard::Space)) 
	{
		Bullet::Fire(getPosition(), false);
		firetime = 0.7f;
	}
}