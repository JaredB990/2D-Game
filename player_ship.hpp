#ifndef		__HPP_PLAYER_SHIP__
#define		__HPP_PLAYER_SHIP__

#include "game_objects.hpp"
#include <SDL3/SDL.h>

class Ship : public GameObject {
    public:
        Ship(SDL_Texture* texture, float LocX, float LocY, float width, float height, bool canShoot);
        void left(float);
        void right(float);
        void up(float);
        void down(float);
        void update(float deltaTime) override;
    protected:
        SDL_FRect* rect;
        float pps = .5f; // pixels per second
        float locX;
        float locY;
        bool canShoot;
        void shoot(bool isEnemy = false, float speed = -0.5f);
};

class EnemyShip : public Ship {
    public:
        EnemyShip(SDL_Texture* texture, float LocX, float LocY, float width, float height, bool canShoot = false, int health = 1);
        void update(float deltaTime) override;
    private:
        float shootTimer = 0.0f;
        float shootInterval = 400.0f;
        float aiMoveTimer = 0.0f;
        float aiMoveInterval = 60.0f; // move every every 1/2 second
        int health;
        float enemyDir = 1.0f; // 1 for right, -1 for left
        friend class Bullet;
    };

class PlayerShip : public Ship {
    public:
        PlayerShip(SDL_Texture* texture, float LocX, float LocY, float width, float height, bool canShoot = true);
        void update(float deltaTime) override;
    private:
        int health = 3;
        friend class Bullet;
};

class Bullet : public GameObject {
    public:
        Bullet(SDL_Texture* texture, float LocX, float LocY, float width, float height, float speed, bool isEnemyBullet = false);
        void update(float deltaTime) override;
    private:
        SDL_FRect* rect;
        float speed; // pixels per second
        bool isEnemyBullet;
};
#endif