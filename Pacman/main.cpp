#include <SFML/Graphics.hpp>
#include <string>
#include "Entity.h"
#include "system_renderer.h"
#include "Player.h"
#include "Ghost.h"
#include "pacman.h"
#include "main.h"


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
sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight), "Pacman");

std::shared_ptr<Scene> gameScene;
std::shared_ptr<Scene> menuScene;
std::shared_ptr<Scene> activeScene;

void Load()
{
    //init system_renderer
    Renderer::initialise(window);

    //Load Scene-Local Assets
    gameScene.reset(new GameScene());
    menuScene.reset(new MenuScene());
    gameScene->Load();
    menuScene->Load();
    //Start at the main menu
    activeScene = menuScene;
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
    //em.Update(dt);
    //Renderer::update(dt);
    activeScene->Update(dt);
}

void Render(sf::RenderWindow& window)
{
    //entity manager
    //em.Render();

    activeScene->Render();
    //flush to screen
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