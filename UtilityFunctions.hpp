#ifndef UTILITYFUNCTIONS_H
#define UTILITYFUNCTIONS_H
#include <SDL3/SDL.h>

// for SDL_FRect
class UtilityFunctions {
public:
// Axis-Aligned Bounding Box (AABB) collision check
static bool checkCollision(const SDL_FRect& a, const SDL_FRect& b);
// Clamp a value between min and max
static float clamp(float value, float min, float max);
};
#endif // UTILITYFUNCTIONS_H