#include "player_ship.hpp"
#include "engine.hpp"
#include "game_objects.hpp"
#include <SDL3/SDL.h>


// Constructor
PlayerShip::PlayerShip(char* spritePath, float LocX, float LocY, float width, float height, bool player) {
	// Access the sprite component to get our rectangle
	// (destination rectangle)
	auto* spriteComponent = addComponent<SpriteComponent>();
	spriteComponent->loadSprite(Engine::instance().getRenderer(),spritePath, LocX, LocY, width, height);
	rect = spriteComponent->getRect();
	this->player = player;

}

// Called once per frame
void PlayerShip::update(float deltaTime) {

    GameObject::update(deltaTime);

    // Player-controlled movement
    for (auto it = Engine::keyEvents.begin(); it != Engine::keyEvents.end(); ++it) {
        if (it->key.key == SDLK_A && player) {
            left(deltaTime);
        }
        if (it->key.key == SDLK_D && player) {
            right(deltaTime);
        }
    }

    // AI movement
    if (!player) {
        aiMoveTimer += deltaTime;

        if (aiMoveTimer >= aiMoveInterval) {
            right(deltaTime);
            aiMoveTimer = 0.0f; // reset timer
        }
    }
}


// Movement should be based on the time that has passed
// for smoothest motion.
void PlayerShip::left(float dt){
	rect->x -= pps * dt;
}

void PlayerShip::right(float dt){
	rect->x += pps * dt;
}
