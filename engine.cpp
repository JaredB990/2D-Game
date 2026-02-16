#include "engine.hpp"
#include "game_objects.hpp"

#include <SDL3/SDL.h>

// Want to share these.  Easiest (and quick) way
// is with a static data structure.
std::vector<SDL_Event> Engine::keyEvents;

Engine::Engine() { init(); }

SDL_Renderer* Engine::getRenderer() { return this->renderer; };

void Engine::setScene(Scene *scene) { this->scene = scene; }
void Engine::run() {
	running = true;
	while (running) {
		// Clear the events from the last frame first.
		Engine::keyEvents.clear();
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) {
				SDL_Log("Shutting down...");
				running = false;
			}
			if (event.type == SDL_EVENT_KEY_DOWN) {
				// Since we are storing copies of events, this
				// works.  Would not work if we were storing pointers
				// as event is a local variable to this function and
				// would always have the same address.
				Engine::keyEvents.push_back(event);
			}
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		scene->updateScene(targetFrameTime);
		SDL_RenderPresent(renderer);
		// Naive delay that doesn't take into account
		// how long the loop ran.
		SDL_Delay(targetFrameTime);
	}
}

bool Engine::init() {
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_Log("SDL_Init failed: %s", SDL_GetError());
		return false;
	}

	// Gotta draw somewhere....
	window = SDL_CreateWindow("RGB Color Cycle", 800, 600, SDL_WINDOW_FULLSCREEN);

	if (!window) {
		SDL_Log("SDL_CreateWindow failed: %s", SDL_GetError());
		SDL_Quit();
		return false;
	}

	// Who is in charge of drawing?
	renderer = SDL_CreateRenderer(window, NULL);
	if (!renderer) {
		SDL_Log("SDL_CreateRenderer failed: %s", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
		return false;
	}

	SDL_SetRenderVSync(renderer, 0);

	return true;
}

void Engine::shutdown() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
