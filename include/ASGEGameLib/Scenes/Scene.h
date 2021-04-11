//
// Created by hewis on 31/03/2021.
//

#ifndef ASGEMOVIEGAME_SCENE_H
#define ASGEMOVIEGAME_SCENE_H

#include <ASGEGameLib/GameObjects/GameObject.h>
#include <Engine/InputEvents.h>
#include <Engine/Renderer.h>
#include <functional>
#include <vector>

class Scene
{
 public:
  enum Scenes
  {
    TITLE,
    LEVEL_EDITOR,
    QUIT_GAME
  };
  explicit Scene(std::function<void(Scenes)> _scene_callback);
  virtual ~Scene() = default;

  virtual void keyInput(const ASGE::KeyEvent* key);
  virtual void clickInput(const ASGE::ClickEvent* click);
  virtual void mouseInput(const ASGE::MoveEvent* mouse);
  virtual void scrollInput(const ASGE::ScrollEvent* scroll);

  virtual void update(float dt);
  virtual void render(ASGE::Renderer* renderer);

  void addObject(std::unique_ptr<GameObject> object);

 protected:
  void setScene(Scenes _scene);

 private:
  std::vector<std::unique_ptr<GameObject>> game_objects;
  std::function<void(Scenes)> scene_callback;
};

#endif // ASGEMOVIEGAME_SCENE_H
