#ifndef		__HPP_PLAYER_SHIP__
#define		__HPP_PLAYER_SHIP__

#include "game_objects.hpp"
#include <SDL3/SDL.h>

class PlayerShip : public GameObject {
	public:
		PlayerShip();
		void left(float);
		void right(float);
		void update(float deltaTime) override;
	private:
		SDL_FRect* rect;
		float pps = 10.0;
};


#endif
