#include "player_ship.hpp"
#include "engine.hpp"
#include "game_objects.hpp"

int main(int argc, char** argv) {
    Engine& engine = Engine::instance();

    Scene GameScene;
    Scene TitleScene;
    Scene EndScene;
    PlayerShip playerShip("Sprites\\Falcon.png",256, 920, 64, 64, true);
    for (int x = 128; x < 1024; x+=64) {
        for (int y = 128; y < 512; y+=64) {
            auto* enemy = new EnemyShip("Sprites\\Lvl1Enemy.png",x, y, 48, 48, true, 1);
            enemy->setOwned(true);
            GameScene.addObject(enemy);
        }

    }

    



    GameScene.addObject(&playerShip);





    engine.setScene(&GameScene);
    engine.run();
}