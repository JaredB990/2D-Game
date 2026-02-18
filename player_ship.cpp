#include "player_ship.hpp"
#include "engine.hpp"
#include "game_objects.hpp"
#include "UtilityFunctions.hpp"
#include <SDL3/SDL.h>

// Constructor
Ship::Ship(char* spritePath, float LocX, float LocY, float width, float height, bool canShoot) {
    auto* spriteComponent = addComponent<SpriteComponent>();
    spriteComponent->loadSprite(Engine::instance().getRenderer(),spritePath, LocX, LocY, width, height);
    rect = spriteComponent->getRect();
    this->canShoot = canShoot;
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

// Movement
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

EnemyShip::EnemyShip(char* spritePath, float LocX, float LocY, float width, float height, bool canShoot) : Ship(spritePath, LocX, LocY, width, height, canShoot) {
    aiMoveTimer = 0.0f;
}

void EnemyShip::update(float deltaTime) {
    GameObject::update(deltaTime);
    aiMoveTimer += 1;
    if (aiMoveTimer >= aiMoveInterval) {
        down(aiMoveTimer);
        aiMoveTimer = 0.0f;
    }
}

PlayerShip::PlayerShip(char* spritePath, float LocX, float LocY, float width, float height, bool canShoot) : Ship(spritePath, LocX, LocY, width, height, canShoot) {
    health = 3;
}


static inline bool rectsIntersect(const SDL_FRect* a, const SDL_FRect* b) {
    if (!a || !b) return false;
    return !(a->x + a->w < b->x ||
             b->x + b->w < a->x ||
             a->y + a->h < b->y ||
             b->y + b->h < a->y);
}

void PlayerShip::update(float deltaTime) {
    Ship::update(deltaTime);

    // Movement from input
    for (auto it = Engine::keyEvents.begin(); it != Engine::keyEvents.end(); ++it) {
        if (it->key.key == SDLK_A) {
            left(deltaTime);
        }
        if (it->key.key == SDLK_D) {
            right(deltaTime);
        }
        if (it->key.key == SDLK_SPACE) {
            shoot();
        }
    }

    // Collision detection with enemies
    Scene* scene = Engine::instance().scene;
    if (!scene) return;

    for (GameObject* go : scene->getObjects()) {
        if (go == this) continue;
        EnemyShip* enemy = dynamic_cast<EnemyShip*>(go);
        if (!enemy) continue;

        auto enemySprite = enemy->getComponent<SpriteComponent>();
        if (!enemySprite) continue;

        SDL_FRect* er = enemySprite->getRect();
        if (rectsIntersect(rect, er)) {
            // Player loses 1 HP
            health--;
            // destroy enemy
            enemy->destroy();
            // destroy player if HP <= 0
            if (health <= 0) {
                this->destroy();
            }
            break;
        }
    }
}

void PlayerShip::shoot() {
    if (!canShoot) return;

    // Create a new bullet above the player
    auto* bullet = new Bullet("Sprites\\Bullet.png", rect->x + rect->w / 2 - 8, rect->y - 16, 16, 16);
    bullet->setOwned(true);
    Engine::instance().scene->addObject(bullet);
}

Bullet::Bullet(char* spritePath, float LocX, float LocY, float width, float height) {
            auto* spriteComponent = addComponent<SpriteComponent>();
            spriteComponent->loadSprite(Engine::instance().getRenderer(),spritePath, LocX, LocY, width, height);
            rect = spriteComponent->getRect();
        }

void Bullet::update(float deltaTime) {
    GameObject::update(deltaTime);
    rect->y -= speed * deltaTime;

    // Destroy bullet if it goes off screen
    if (rect->y + rect->h < 0) {
        this->destroy();
    }
}