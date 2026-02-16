#ifndef		__HPP_PLAYER_SHIP__
#define		__HPP_PLAYER_SHIP__

#include "game_objects.hpp"
#include <SDL3/SDL.h>

class PlayerShip : public GameObject {
	public:
		PlayerShip( char* spritePath, float LocX, float LocY, float width, float height);
		void left(float);
		void right(float);
		void update(float deltaTime) override;
	private:
		SDL_FRect* rect;
		float pps = 10.0;
		float locX;
		float locY;
};


#endif
