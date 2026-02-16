#ifndef		__HPP_PLAYER_SHIP__
#define		__HPP_PLAYER_SHIP__

#include "game_objects.hpp"
#include <SDL3/SDL.h>

class PlayerShip : public GameObject {
	public:
		PlayerShip( char* spritePath, float LocX, float LocY, float width, float height, bool player);
		void left(float);
		void right(float);
		void update(float deltaTime) override;
	private:
		SDL_FRect* rect;
		float pps = .5f; // pixels per second
		float locX;
		float locY;
		bool player;
		float aiMoveTimer = 0.0f;
		float aiMoveInterval = 20.0f; // move every 20 seconds

};


#endif
