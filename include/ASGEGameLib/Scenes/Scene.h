//
// Created by hewis on 31/03/2021.
//

#ifndef ASGEMOVIEGAME_SCENE_H
#define ASGEMOVIEGAME_SCENE_H

#include <ASGEGameLib/GameObjects/GameObject.h>
#include <ASGEGameLib/Utilities/InputTracker.h>
#include <Engine/InputEvents.hpp>
#include <Engine/Renderer.hpp>
#include <functional>
#include <soloud.h>
#include <soloud_wav.h>
#include <vector>

class Scene
{
 public:
  enum Scenes
  {
    TITLE,
    GAME,
    LEVEL_EDITOR,
    OPTIONS,
    CREDITS,
    QUIT_GAME
  };
  explicit Scene(std::function<void(Scenes)> _scene_callback);

  Scene(const Scene& copy) = delete;
  Scene& operator=(Scene other) = delete;
  virtual ~Scene();

  virtual void update(InputTracker& input, float dt);
  virtual void render(ASGE::Renderer* renderer);

  void addObject(std::unique_ptr<GameObject> object);

 protected:
  void setScene(Scenes _scene);
  std::unique_ptr<SoLoud::Soloud> audio_engine;

 private:
  std::vector<std::unique_ptr<GameObject>> game_objects;
  std::function<void(Scenes)> scene_callback;
};

#endif // ASGEMOVIEGAME_SCENE_H
