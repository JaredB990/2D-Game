#include "game_objects.hpp"
#include "components.hpp"

// Our component-based system needs to ensure
// all components update each frame.
void GameObject::update(float deltaTime) {
  for (auto &c : components){
    c->update(deltaTime);
  }
}
