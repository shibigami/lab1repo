#include <memory>
#include "scene.h"
#include "Entity.h"

extern std::shared_ptr<Scene> gameScene;
extern std::shared_ptr<Scene> menuScene;
extern std::shared_ptr<Scene> activeScene;

class MenuScene :public Scene {
private:

public:
	MenuScene() = default;
	void Update(double dt) override;
	void Render() override;
	void Load() override;
};

class GameScene :public Scene {
private:
	sf::Clock scoreClock;
	std::shared_ptr<Entity> player;
	std::vector<std::shared_ptr<Entity>> ghosts;
	void Respawn();

public :
	GameScene() = default;
	void Update(double dt) override;
	void Render() override;
	void Load() override;
	void UpdateScore();
};