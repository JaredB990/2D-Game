#ifndef __HPP_COMPONENTS__
#define __HPP_COMPONENTS__

#include <functional>
#include <SDL3/SDL.h>
#include <glm/vec4.hpp>
#include <unordered_map>

class GameObject;

class Component {
	public:
		// We want these to be abstract (virtual in c++)
		virtual ~Component() = default;
		virtual void update(float deltaTime) {}

		GameObject* getOwner() const;

	private:
		void setOwner(GameObject* go);

		// Make it easier to share information with GameObjects
		// by letting them see our private data.
		friend class GameObject;

		// To which game object do we belong?
		GameObject* owner = nullptr;
};

class SpriteComponent : public Component {
	public:
		void setX(int x);
		void setY(int y);
		// Load an image from a file.  Normally we would
		// probably have multiple images per sprite for
		// animations.
		bool loadSprite(SDL_Renderer* renderer, SDL_Texture* texture, float x, float y, float width, float height);
		SDL_Texture* getSprite();
		void update(float deltaTime) override;
		SDL_FRect* getRect();

	private:
		// For convenience we can keep track of the renderer
		// from the engine.
		SDL_Renderer* renderer = nullptr;
		SDL_FRect destRect{};
		SDL_Texture* sprite = nullptr;
};

// Not used yet.  Will become more important
// when we get to 3D.
class TransformComponent : public Component {
	public:
		void update(float deltaTime) override;
	private:
		glm::vec4 position{};
		glm::vec4 rotation{};
		glm::vec4 scale{1.f, 1.f, 1.f, 1.f};
};

#endif
