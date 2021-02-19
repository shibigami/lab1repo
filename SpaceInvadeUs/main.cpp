#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "game.h"
#include "ship.h"
#include "bullet.h"

using namespace sf;
using namespace std;

//controls
const Keyboard::Key controls[5] =
{
    Keyboard::W,    //player 1 up
    Keyboard::S,    //player 1 down
    Keyboard::Up,   //player 1 up
    Keyboard::Down,  //player 1 down
    Keyboard::P    //player/cpu swap
};

//game window
sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight), "SpaceInvadeUs");

//sprite sheet
sf::Texture spritesheet;
//sprites
sf::Sprite invader;

//ships
std::vector<Ship*> ships;


void Load()
{
    //load invader sprite from sprite sheet
    if (!spritesheet.loadFromFile("res/img/invaders_sheet.png"))
    {
        cerr << "Failed to load spritesheet!" << std::endl;
    }
    invader.setTexture(spritesheet);
    invader.setTextureRect(sf::IntRect(0, 0, 32, 32));

    //instantiate invader
    Invader* inv = new Invader(sf::IntRect(0, 0, 32, 32), { 100,100 });
    //multiply it
    for (int x = 0; x < invaders_columns; x++)
    {
        for (int y = 0; y < invaders_rows; y++) 
        {
            inv = new Invader(sf::IntRect(0, 0, 32, 32), { 10.0f+(25.0f*x),10.0f+(25.0f*y) });
            ships.push_back(inv);
        }
    }

    //speed and direction
    Invader::direction = true;
    Invader::speed = 20.0f;

    //player
    Player* pl = new Player();
    ships.push_back(pl);
}

void Reset() 
{
    Invader::direction = true;
    Invader::speed = 2.0f;
}

void Update(RenderWindow& window)
{
    //reset clock, recalculate delta time
    static Clock clock;
    float dt = clock.restart().asSeconds();

    //check and consume events
    Event event;
    while (window.pollEvent(event))
    {
        if (event.type == Event::Closed)
        {
            window.close();
            return;
        }
    }

    //Quit Via Esc Key
    if (Keyboard::isKeyPressed(Keyboard::Escape))
    {
        window.close();
    }

    //update ships
    for (auto& s : ships)
    {
        s->Update(dt);
    }

    //update bullets
    Bullet::Update(dt);
}

void Render()
{
    //Draw ships
    for (const auto s : ships)
    {
        window.draw(*s);
    }

    Bullet::Render(window);
}

int main(){
  //enable vertical sync
    window.setVerticalSyncEnabled(true);

    //load
    Load();

    while (window.isOpen()) {
        window.clear();

        Update(window);
        Render();

        window.display();
    }
  return 0;
}