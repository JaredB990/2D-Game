#include "player_ship.hpp"
#include "engine.hpp"
#include "game_objects.hpp"

int main(int argc, char** argv) {
    // Create the objects that make up our game, and start the run.
    Engine& engine = Engine::instance();

    Scene scene;
    PlayerShip playerShip("Sprites\\Falcon.jpg",256, 920, 64, 64);
    for (int x = 128; x < 1024; x+=64) {
        for (int y = 128; y < 512; y+=64) {
            auto* enemy = new PlayerShip("Sprites\\Lvl1Enemy.jpg",x, y, 48, 48);
            scene.addObject(enemy);
        }
        
    }

    scene.addObject(&playerShip);
    engine.setScene(&scene);
    engine.run();
}

