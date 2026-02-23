#ifndef UTILITYFUNCTIONS_H
#define UTILITYFUNCTIONS_H
#include <SDL3/SDL.h>
#include "engine.hpp"
#include "player_ship.hpp"
#include <map>
#include <string>

// for SDL_FRect
class UtilityFunctions {
public:
// Axis-Aligned Bounding Box (AABB) collision check
static bool checkCollision(const SDL_FRect& a, const SDL_FRect& b);
// Clamp a value between min and max
static float clamp(float value, float min, float max);

static float enemyClamp(float value, float min, float max, EnemyShip* enemy);

};

class textureManager {
    public:
    static std::map<std::string, SDL_Texture*> textures;
		static textureManager& instance(){
			static textureManager instance;
			return instance;
		}
    SDL_Texture* loadTexture(const std::string& path, SDL_Renderer* renderer);
    std::map<std::string, SDL_Texture*>& getTextures() { return textures; }
    SDL_Texture* getTexture(const std::string& path); 
};

class levelManager {
    public:
    static levelManager& instance(){
            static levelManager instance;
            return instance;
    }

    void createLevels();
    Scene* loadLevel(int levelNumber);
    static std::vector<std::string> levelList(const std::string& path);
};

#endif // UTILITYFUNCTIONS_H