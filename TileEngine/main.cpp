#include <SFML/Graphics.hpp>
#include <string>
#include "Player.h"
#include "LevelSystem.h"


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
sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight), "TileEngine");

//player
Player player;


void Load()
{

    ls::loadLevelFile("res/maze_2.txt");

    // Print the level to the console
    for (size_t y = 0; y < ls::getHeight(); ++y) {
        for (size_t x = 0; x < ls::getWidth(); ++x) {
            cout << ls::getTile({ x, y });
        }
        cout << endl;
    }
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

    //player
    player.Update(dt);
}

void Render(sf::RenderWindow &window)
{
    player.Render(window);

    ls::Render(window);
}

int main(){
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