#include "engine.hpp"
#include "game_objects.hpp"

#include <SDL3/SDL.h>

// Want to share these.  Easiest (and quick) way
// is with a static data structure.
std::vector<SDL_Event> Engine::keyEvents;

Engine::Engine() { 
    init(); 
    ma_result result = ma_engine_init(NULL, &audioEngine);
    if (result != MA_SUCCESS) {
    printf("Audio engine failed to initialize!\n");
    }
}

ma_engine Engine::audioEngine;

SDL_Renderer* Engine::getRenderer() { return this->renderer; };

void Engine::setScenes(const std::vector<Scene*>& sceneList)
{
    scenes = sceneList;
    if (!scenes.empty())
        activeScene = scenes[0];
}
void Engine::run() {
    running = true;

    while (running) {
        Engine::keyEvents.clear();

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                SDL_Log("Shutting down...");
                running = false;
            }

            if (event.type == SDL_EVENT_KEY_DOWN) {
                Engine::keyEvents.push_back(event);
            
                if (event.type == SDL_EVENT_KEY_DOWN) {

                    Engine::keyEvents.push_back(event);
                    // Handle scene change)
                    if (event.key.key == SDLK_RETURN && activeScene != scenes[2]) {

                        if (activeScene == scenes[0]) {
                        setActiveScene(1);
                        }
                        else if (activeScene == scenes[1] && false //Check if player is dead)
                        )
                        {
                            setActiveScene(2);
                        }
                        
                        else if (activeScene == scenes[2]) {
                        setActiveScene(0);
                        }
                    }
                }
            }
        }

        // ---- UPDATE ----
        if (activeScene)
            activeScene->updateScene(targetFrameTime);

        // ---- RENDER ----
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

		SDL_FRect destRect = { 0, 0, (float)getWindowWidth(), (float)getWindowHeight()};
        SDL_RenderTexture(renderer, backgroundTexture, NULL, &destRect);

        if (activeScene)
            activeScene->updateScene(targetFrameTime);

        SDL_RenderPresent(renderer);

        SDL_Delay(targetFrameTime);

        


    
    }
}


bool Engine::init() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow("RGB Color Cycle", 800, 600, SDL_WINDOW_FULLSCREEN);
    if (!window) {
        SDL_Log("SDL_CreateWindow failed: %s", SDL_GetError());
        SDL_Quit();
        return false;
    }

    renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        SDL_Log("SDL_CreateRenderer failed: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }

    // Load background image ONCE
    SDL_Surface* surface = IMG_Load("Sprites/Space.jpg");
    if (!surface) {
        SDL_Log("IMG_Load failed: %s", SDL_GetError());
        return false;
    }

    backgroundTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);

    if (!backgroundTexture) {
        SDL_Log("CreateTexture failed: %s", SDL_GetError());
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

int Engine::getWindowWidth() const {
    int w;
    SDL_GetWindowSize(window, &w, nullptr);
    return w;
}

int Engine::getWindowHeight() const {
    int h;
    SDL_GetWindowSize(window, nullptr, &h);
    return h;
}

void Engine::setActiveScene(size_t index)
{
    if (index < scenes.size())
        activeScene = scenes[index];
}

Scene* Engine::getScene(size_t index) const
{
    if (index < scenes.size())
        return scenes[index];
    return nullptr;
}
