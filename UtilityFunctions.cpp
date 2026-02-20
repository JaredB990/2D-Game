#include "UtilityFunctions.hpp"
#include "player_ship.hpp"
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL.h>
#include <map>
#include <filesystem>

namespace fs = std::filesystem;

// AABB collision check
bool UtilityFunctions::checkCollision(const SDL_FRect& a, const SDL_FRect& b) {
return !(a.x + a.w < b.x || b.x + b.w < a.x ||
a.y + a.h < b.y || b.y + b.h < a.y);
}
// Clamp a value
float UtilityFunctions::clamp(float value, float min, float max) {
if (value < min) return min;
if (value > max) return max;
return value;
}

float UtilityFunctions::enemyClamp(float value, float min, float max, EnemyShip* enemy) {
if (value < min) enemy->destroy();
if (value > max) enemy->destroy();
return value;
}

SDL_Texture* textureManager::loadTexture(const std::string& directory, SDL_Renderer* renderer) {
    fs::path fsPath(directory);
    for (const auto& entry : fs::directory_iterator(directory)) {
        if (entry.is_regular_file()) {
            std::string path = entry.path().string();
            if (textureManager::textures.find(path) == textureManager::textures.end()) {
                SDL_Surface* surface = IMG_Load(path.c_str());
                if (!surface) {
                    SDL_Log("IMG_Load Error: %s", SDL_GetError());
                    continue;
                }
                SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
                SDL_DestroySurface(surface);
                if (texture) {
                    textureManager::textures[path] = texture;
                }
            }
        }
    }
    return nullptr;
}

SDL_Texture* textureManager::getTexture(const std::string& path) {
    auto it = textureManager::textures.find(path);
    if (it != textureManager::textures.end()) {
        return it->second;
    }
    return nullptr;
}

std::map<std::string, SDL_Texture*> textureManager::textures;
