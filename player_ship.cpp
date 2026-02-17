#include "player_ship.hpp"
#include "engine.hpp"
#include "game_objects.hpp"
#include "UtilityFunctions.hpp"
#include <SDL3/SDL.h>


// Constructor
Ship::Ship(char* spritePath, float LocX, float LocY, float width, float height) {
	// Access the sprite component to get our rectangle
	// (destination rectangle)
	auto* spriteComponent = addComponent<SpriteComponent>();
	spriteComponent->loadSprite(Engine::instance().getRenderer(),spritePath, LocX, LocY, width, height);
	rect = spriteComponent->getRect();

}

// Called once per frame
void Ship::update(float deltaTime) {

    GameObject::update(deltaTime);

    // Clamp to screen using UtilityFunctions
    float windowWidth  = (float)Engine::instance().getWindowWidth();
    float windowHeight = (float)Engine::instance().getWindowHeight();

    rect->x = UtilityFunctions::clamp(rect->x, 0.0f, windowWidth - rect->w);
    rect->y = UtilityFunctions::clamp(rect->y, 0.0f, windowHeight - rect->h);
}


// Movement should be based on the time that has passed
// for smoothest motion.
void Ship::left(float dt){
	rect->x -= pps * dt;
}
void Ship::right(float dt){
	rect->x += pps * dt;
}
void Ship::up(float dt){
	rect->y -= pps * dt;
}
void Ship::down(float dt){
	rect->y += pps * dt;
}

void EnemyShip::update(float deltaTime) {
    GameObject::update(deltaTime);

    // Simple AI: Move down every aiMoveInterval seconds
    aiMoveTimer += 1;
    if (aiMoveTimer >= aiMoveInterval) {
        down(aiMoveTimer);
        aiMoveTimer = 0.0f; // reset timer
    }
}

PlayerShip::PlayerShip(char* spritePath, float LocX, float LocY, float width, float height) : Ship(spritePath, LocX, LocY, width, height) {}

void PlayerShip::update(float deltaTime) {
    Ship::update(deltaTime);

    // Check for keyboard input and move accordingly
    for (auto it = Engine::keyEvents.begin(); it != Engine::keyEvents.end(); ++it) {
        if (it->key.key == SDLK_A) {
            left(deltaTime);
        }
        if (it->key.key == SDLK_D) {
            right(deltaTime);
        }
    }
}

void PlayerShip::onCollision() {
    health--;
    if (health <= 0) {
        // Handle player death (e.g., reset position, end game, etc.)
        delete this;        
    }
}
