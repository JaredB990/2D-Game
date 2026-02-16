#include "player_ship.hpp"
#include "engine.hpp"
#include "game_objects.hpp"

int main(int argc, char** argv) {
    // Create the objects that make up our game, and start the run.
    Engine& engine = Engine::instance();

    Scene scene;
    PlayerShip playerShip;

    scene.addObject(&playerShip);
    engine.setScene(&scene);
    engine.run();
}

