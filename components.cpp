#include "components.hpp"
#include "game_objects.hpp"

#include <glm/vec4.hpp>
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL.h>

GameObject* Component::getOwner() const {
    return owner;
}

void Component::setOwner(GameObject* go) {
    owner = go;
}

void SpriteComponent::setX(int x) {
    destRect.x = x;
}

void SpriteComponent::setY(int y) {
    destRect.y = y;
}

bool SpriteComponent::loadSprite(SDL_Renderer* renderer, SDL_Texture* texture, float locX, float locY, float width, float height) {
    // Hard coding this for my sample game that uses 64x64 sprites.
    // You may need to adjust and/or have variable sizes.
    destRect = {locX, locY, width, height};
    this->renderer = renderer;
    sprite = texture;

    // Surfaces are software based, so slow.  But, we need them
    // when loading.
    // SDL_Surface* surface = IMG_Load(path);
    // if (!surface) {
    //     SDL_Log("IMG_Load Error: %s", SDL_GetError());
    //     return false;
    // }

    // // Now create a hardware-based renderer and delete the software one.
    // sprite = SDL_CreateTextureFromSurface(renderer, surface);
    // SDL_DestroySurface(surface);

    return sprite != nullptr;
}

// Sometimes we might need to get the image.
SDL_Texture* SpriteComponent::getSprite() {
    return sprite;
}

void SpriteComponent::update(float) {
    SDL_RenderTexture(renderer, sprite, nullptr, &destRect);
}

// The destRect is where and how much of the image will be drawn.
SDL_FRect* SpriteComponent::getRect(){
    return &destRect;
}

void TransformComponent::update(float) {
    // empty for now
}