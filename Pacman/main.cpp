#include <SFML/Graphics.hpp>
#include <string>
#include "Entity.h"
#include "system_renderer.h"
#include "Player.h"
#include "Ghost.h"


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
const int gameWidth = 800;
const int gameHeight = 600;

//game window
sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight), "Pacman");

Entity::EntityManager em;
shared_ptr<Player> player;
Ghost ghost;


void Load()
{
    //init system_renderer
    Renderer::initialise(window);

    //player
    em.list.push_back(player);
    /*
    //ghosts
    ghost = new Ghost(64,sf::Color::Red, sf::Vector2f(150, 50));
    entities.push_back(ghost);
    ghost = new Ghost(64,sf::Color::Green, sf::Vector2f(50, 150));
    entities.push_back(ghost);
    ghost = new Ghost(64,sf::Color::Magenta, sf::Vector2f(150, 150));
    entities.push_back(ghost);
    ghost = new Ghost(64,sf::Color::Blue, sf::Vector2f(50, 50));
    entities.push_back(ghost);
    */
}

void Reset()
{
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

    //update code
    //entity manager
    //em.update(dt);
}

void Render(sf::RenderWindow& window)
{
    //entity manager
    //em.render(window);
    Renderer::render();
}

int main() {
    //enable vertical sync
    window.setVerticalSyncEnabled(true);

    //load
    Load();

    while (window.isOpen()) {
        window.clear();

        Update(window);
        Render(window);

        window.display();
    }
    return 0;
}