//
// Created by hewis on 31/03/2021.
//

#ifndef ASGEMOVIEGAME_SCENE_H
#define ASGEMOVIEGAME_SCENE_H

#include <ASGEGameLib/GameObjects/GameObject.h>
#include <Engine/InputEvents.h>
#include <Engine/Renderer.h>
#include <vector>

class Scene
{
 public:
  virtual ~Scene() = default;

  virtual void keyInput(const ASGE::KeyEvent* key);
  virtual void clickInput(const ASGE::ClickEvent* click);
  virtual void mouseInput(const ASGE::MoveEvent* mouse);
  virtual void scrollInput(const ASGE::ScrollEvent* scroll);

  virtual void update(float dt);
  virtual void render(ASGE::Renderer* renderer);

  void addObject(std::unique_ptr<GameObject> object);

 private:
  std::vector<std::unique_ptr<GameObject>> game_objects;
};

#endif // ASGEMOVIEGAME_SCENE_H
