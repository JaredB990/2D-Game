#ifndef __HPP_GAME_OBJECTS__
#define __HPP_GAME_OBJECTS__

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <algorithm>
#include <glm/vec4.hpp>
#include <vector>
#include <memory>

#include "components.hpp"

class GameObject {
public:
  virtual ~GameObject() = default;

  template <typename T, typename... Args> T *addComponent(Args &&...args) {
    static_assert(std::is_base_of<Component, T>::value,
                  "T must derive from Component");
    auto component = std::make_unique<T>(std::forward<Args>(args)...);
    component->setOwner(this);
    T *ptr = component.get();
    components.push_back(std::move(component));
    return ptr;
  }

  template <typename T> T *getComponent() {
    for (auto &c : components) {
      if (auto casted = dynamic_cast<T *>(c.get()))
        return casted;
    }
    return nullptr;
  }

  virtual void update(float deltaTime);

  // Lifecycle controls used by Scene to safely remove/delete objects.
  void destroy() { alive = false; }
  bool isAlive() const { return alive; }
  void setOwned(bool o) { owned = o; }
  bool isOwned() const { return owned; }

private:
  std::vector<std::unique_ptr<Component>> components;
  bool alive = true;
  bool owned = false;
};

class Scene {
public:
  void addObject(GameObject *go) { game_objects.push_back(go); }
  void updateScene(float deltaTime) {
    for (auto it = game_objects.begin(); it != game_objects.end(); ++it) {
      (*it)->update(deltaTime);
    }
    // cleanup dead objects after updates
    for (auto it = game_objects.begin(); it != game_objects.end();) {
      GameObject* go = *it;
      if (!go->isAlive()) {
        it = game_objects.erase(it);
        if (go->isOwned()) delete go;
      } else {
        ++it;
      }
    }
    if (!pendingObjects.empty()) {
      for (GameObject* go : pendingObjects) {
        addObject(go);
      }
      pendingObjects.clear();
    }
  }

  void addScore(int points) { score += points; }
  int getScore() const { return score; }

  std::vector<GameObject*>& getObjects() { return game_objects; }

  std::vector<GameObject *> pendingObjects;
  void addPendingObject(GameObject *go) { pendingObjects.push_back(go); }
private:
  std::vector<GameObject *> game_objects;

  int score = 0;
  
};

#endif
