#include <memory>
#include "scene.h"

extern std::shared_ptr<Scene> gameScene;
extern std::shared_ptr<Scene> menuScene;
extern std::shared_ptr<Scene> activeScene;

class MenuScene :public Scene {
private:
	sf::Text text;

public:
	MenuScene() = default;
	void Update(double dt) override;
	void Render() override;
	void Load() override;
};

class GameScene :public Scene {
private:
	sf::Text text;
	sf::Clock scoreClock;
	void Respawn();

public :
	GameScene() = default;
	void Update(double dt) override;
	void Render() override;
	void Load() override;
};