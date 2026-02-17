#include "player_ship.hpp"
#include "engine.hpp"
#include "game_objects.hpp"

int main(int argc, char** argv) {
    Engine& engine = Engine::instance();

    Scene scene;
    PlayerShip playerShip("Sprites\\Falcon.jpg",256, 920, 64, 64);
    for (int x = 128; x < 1024; x+=64) {
        for (int y = 128; y < 512; y+=64) {
            auto* enemy = new EnemyShip("Sprites\\Lvl1Enemy.jpg",x, y, 48, 48);
            enemy->setOwned(true);
            scene.addObject(enemy);
        }

    }

    scene.addObject(&playerShip);
    engine.setScene(&scene);
    engine.run();
}