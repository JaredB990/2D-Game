#include "player_ship.hpp"
#include "engine.hpp"
#include "game_objects.hpp"
#include "UtilityFunctions.hpp"
#include <SDL3/SDL.h>

static inline bool rectsIntersect(const SDL_FRect* a, const SDL_FRect* b) {
    if (!a || !b) return false;
    return !(a->x + a->w < b->x ||
             b->x + b->w < a->x ||
             a->y + a->h < b->y ||
             b->y + b->h < a->y);
}

// Constructor
Ship::Ship(SDL_Texture* texture, float LocX, float LocY, float width, float height, bool canShoot) {
    auto* spriteComponent = addComponent<SpriteComponent>();
    spriteComponent->loadSprite(Engine::instance().getRenderer(),texture, LocX, LocY, width, height);
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

EnemyShip::EnemyShip(SDL_Texture* texture, float LocX, float LocY, float width, float height, bool canShoot, int health) : Ship(texture, LocX, LocY, width, height, canShoot) {
    this->health = health;
    aiMoveTimer = 0.0f;
}

void EnemyShip::update(float deltaTime) {
    GameObject::update(deltaTime);
    aiMoveTimer += 1;
    if (aiMoveTimer >= aiMoveInterval) {
        down(aiMoveTimer);
        aiMoveTimer = 0.0f;
    }

    float windowWidth  = (float)Engine::instance().getWindowWidth();
    float windowHeight = (float)Engine::instance().getWindowHeight();

    rect->x = UtilityFunctions::enemyClamp(rect->x, 0.0f, windowWidth - rect->w, this);
    rect->y = UtilityFunctions::enemyClamp(rect->y, 0.0f, windowHeight - rect->h, this);

    if (canShoot) {
        shootTimer += 1;
        if (shootTimer >= shootInterval) {
            shoot(true, 0.5f);
            shootTimer = 0.0f;
            //SDL_Log("Enemy at (%.2f, %.2f) shoots!", rect->x, rect->y);
        }
    }
}

PlayerShip::PlayerShip(SDL_Texture* texture, float LocX, float LocY, float width, float height, bool canShoot) : Ship(texture, LocX, LocY, width, height, canShoot) {
    health = 3;
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

void Ship::shoot(bool isEnemy, float speed) {
    Scene *scene = Engine::instance().scene;
    if (!isEnemy) {
        // Create a new bullet above the player
        auto* bullet = new Bullet(textureManager::instance().getTexture("Sprites\\Laser_bullet.png"), rect->x + rect->w / 2 - 8, rect->y - 16, 16, 16, speed);
        bullet->setOwned(true);
        scene->addPendingObject(bullet);
    }
    else{
        // Create a new bullet below the enemy
        auto* bullet = new Bullet(textureManager::instance().getTexture("Sprites\\Laser_bullet.png"), rect->x + rect->w / 2 - 8, rect->y + rect->h, 16, 16, speed, true);
        bullet->setOwned(true);
        scene->addPendingObject(bullet);
    }
}

Bullet::Bullet(SDL_Texture* texture, float LocX, float LocY, float width, float height,float speed,bool isEnemyBullet) {
    this->speed = speed;
    this->isEnemyBullet = isEnemyBullet;
    auto* spriteComponent = addComponent<SpriteComponent>();
    spriteComponent->loadSprite(Engine::instance().getRenderer(),texture, LocX, LocY, width, height);
    rect = spriteComponent->getRect();
}

void Bullet::update(float deltaTime) {
    GameObject::update(deltaTime);
    rect->y += speed * deltaTime;

    Scene* scene = Engine::instance().scene;
    if (!scene) return;
    if (!isEnemyBullet) {
        for (GameObject* go : scene->getObjects()) {
            if (go == this) continue;
            EnemyShip* enemy = dynamic_cast<EnemyShip*>(go);
            if (!enemy) continue;

            auto enemySprite = enemy->getComponent<SpriteComponent>();
            if (!enemySprite) continue;

            SDL_FRect* er = enemySprite->getRect();
            if (rectsIntersect(rect, er)) {
                    this->destroy();
                enemy->health--;
                if (enemy->health <= 0) {
                    enemy->destroy();
                    scene->addScore(1);
                }
                break;
            }
        }
    }
    else{
        for (GameObject* go : scene->getObjects()) {
            if (go == this) continue;
            PlayerShip* player = dynamic_cast<PlayerShip*>(go);
            if (!player) continue;

            auto playerSprite = player->getComponent<SpriteComponent>();
            if (!playerSprite) continue;

            SDL_FRect* er = playerSprite->getRect();
            if (rectsIntersect(rect, er)) {
                    this->destroy();
                player->health--;
                if (player->health <= 0) {
                    player->destroy();
                }
                break;
            }
        }
    }

    // Destroy bullet if it goes off screen
    if (rect->y + rect->h < 0) {
        this->destroy();
    }
}