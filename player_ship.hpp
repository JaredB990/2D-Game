#ifndef		__HPP_PLAYER_SHIP__
#define		__HPP_PLAYER_SHIP__

#include "game_objects.hpp"
#include <SDL3/SDL.h>

class Ship : public GameObject {
	public:
		Ship( char* spritePath, float LocX, float LocY, float width, float height);
		void left(float);
		void right(float);
		void up(float);
		void down(float);
		void update(float deltaTime) override;
	private:
		SDL_FRect* rect;
		float pps = .5f; // pixels per second
		float locX;
		float locY;



};

class EnemyShip : public Ship {
	public:
		EnemyShip( char* spritePath, float LocX, float LocY, float width, float height) : Ship(spritePath, LocX, LocY, width, height) {}
		void update(float deltaTime) override;
	private:
		float aiMoveTimer = 0.0f;
		float aiMoveInterval = 20.0f; // move every 20 seconds
	};

class PlayerShip : public Ship {
	public:
		PlayerShip( char* spritePath, float LocX, float LocY, float width, float height);
		void update(float deltaTime) override;
	private:
		
};
#endif
