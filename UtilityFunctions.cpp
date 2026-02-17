#include "UtilityFunctions.hpp"

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