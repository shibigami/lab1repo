#include "pacman.h"
#include "system_renderer.h"
#include "Player.h"
#include "Ghost.h"
#include "main.h"
#include "cmp_sprite.h"
#include "ecm.h"
#include "cmp_actor_movement.h"
#include "LevelSystem.h"
#include "cmp_enemy_ai.h"

using namespace std;
using namespace sf;

#define GHOST_COUNT 4
vector<shared_ptr<Ghost>> ghosts;

sf::Text text;
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
    player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]));
    player->setPosition(player->getPosition() + sf::Vector2f(12.0f, 12.0f));
    player->getCompatibleComponent<ActorMovementComponent>()[0]
        ->setSpeed(150.0f);

    auto ghost_spawns = ls::findTiles(ls::ENEMY);
    for (auto& g : ghosts) {
        g->setPosition(
            ls::getTilePosition(ghost_spawns[rand() % ghost_spawns.size()]));
        g->setPosition(g->getPosition() + sf::Vector2f(12.0f, 12.0f));
        g->getCompatibleComponent<ActorMovementComponent>()[0]->setSpeed(100.0f);
    }
}

void GameScene::Update(double dt)
{
    if (Keyboard::isKeyPressed(Keyboard::Tab)) {
        activeScene = menuScene;
    }
    
    _ents.Update(dt);
    UpdateScore();

    for (auto& g : ghosts) {
        if (sqrt(pow(g->getPosition().y - player->getPosition().y, 2) + pow(g->getPosition().x - player->getPosition().x, 2)) < 10.0f) {
            Respawn();
        }
    }
}

void GameScene::Render()
{
    LevelSystem::Render(Renderer::getWindow());
    _ents.Render();
}

void GameScene::Load()
{
    ls::loadLevelFile("res/pacman.txt", 25.0f);

        auto pl = make_shared<Entity>();

        auto s = pl->addComponent<ShapeComponent>();
        s->setShape<sf::CircleShape>(12.f);
        s->getShape().setFillColor(Color::Yellow);
        s->getShape().setOrigin(Vector2f(12.f, 12.f));
        pl->addComponent<PlayerMovementComponent>();

        player = pl;
        _ents.list.push_back(pl);


    const sf::Color ghost_cols[]{
        {208,62,25},    //red Blinky
        {219,133,28},   //orange Clyde
        {70,191,238},   //cyan Inky
        {234,130,229} }; //pink Pinky

    for (int i = 0; i < GHOST_COUNT; ++i) 
    {
        auto ghost = make_shared<Entity>();
        auto s = ghost->addComponent<ShapeComponent>();
        s->setShape<sf::CircleShape>(12.f);
        s->getShape().setFillColor(ghost_cols[i % 4]);
        s->getShape().setOrigin(Vector2f(12.f, 12.f));

        ghost->addComponent<EnemyAIComponent>();
        ghosts.push_back(ghost);
        _ents.list.push_back(ghost);
    }

    Respawn();
}

void GameScene::UpdateScore()
{
    //cout << "update score" << endl;
}
