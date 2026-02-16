#include "player_ship.hpp"
#include "engine.hpp"
#include "game_objects.hpp"
#include <SDL3/SDL.h>

// Constructor
PlayerShip::PlayerShip(){
	// Access the sprite component to get our rectangle
	// (destination rectangle)
	auto* spriteComponent = addComponent<SpriteComponent>();
	spriteComponent->loadSprite(Engine::instance().getRenderer(),"Sprites\\Falcon.jpg", 256, 920, 64, 64);
	rect = spriteComponent->getRect();

}

// Called once per frame
void PlayerShip::update(float deltaTime) {
	// Call the parent class to notify components
	GameObject::update(deltaTime);
	for(auto it = Engine::keyEvents.begin(); it != Engine::keyEvents.end(); ++it){
		if(it->key.key == SDLK_A){
			left(deltaTime);
		}
		if(it->key.key == SDLK_D){
			right(deltaTime);
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
