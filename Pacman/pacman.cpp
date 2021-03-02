#include "pacman.h"
#include "system_renderer.h"
#include "Player.h"
#include "Ghost.h"
#include "main.h"

using namespace std;
using namespace sf;

sf::Font font;

void Scene::Update(double dt) { _ents.Update(dt); }
void Scene::Render() { _ents.Render(); }
void Scene::Load() {}

void MenuScene::Update(double dt) {
    if (Keyboard::isKeyPressed(Keyboard::Space)) {
        activeScene = gameScene;
    }
	Scene::Update(dt);
}

void MenuScene::Render() {
	Renderer::queue(&text);
	Scene::Render();
}

void MenuScene::Load() {
	//Set up the text element here
    
    font.loadFromFile("res/font.ttf");
    text.setFont(font);
    text.setCharacterSize(25);
    text.setPosition(gameWidth/2,gameHeight/2);
    text.setString("Space to start!");
    text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
}

void GameScene::Respawn()
{
}

void GameScene::Update(double dt)
{
    if (Keyboard::isKeyPressed(Keyboard::Tab)) {
        activeScene = menuScene;
    }
    _ents.Update(dt);
}

void GameScene::Render()
{
    _ents.Render();
}

void GameScene::Load()
{
    //player
    shared_ptr<Player> player(new Player());
    _ents.list.push_back(player);

    //ghosts
    auto ghost = new Ghost(sf::Color::Red);
    shared_ptr<Ghost> ghost1(new Ghost(sf::Color::Red));
    ghost1.get()->setPosition(sf::Vector2f(150.0f, 150.0f));
    _ents.list.push_back(ghost1);
    shared_ptr<Ghost> ghost2(new Ghost(sf::Color::Green));
    ghost2.get()->setPosition(sf::Vector2f(50.0f, 150.0f));
    _ents.list.push_back(ghost2);
    shared_ptr<Ghost> ghost3(new Ghost(sf::Color::Blue));
    ghost3.get()->setPosition(sf::Vector2f(150.0f, 50.0f));
    _ents.list.push_back(ghost3);
    shared_ptr<Ghost> ghost4(new Ghost(sf::Color::Cyan));
    ghost4.get()->setPosition(sf::Vector2f(50.0f, 50.0f));
    _ents.list.push_back(ghost4);
}
